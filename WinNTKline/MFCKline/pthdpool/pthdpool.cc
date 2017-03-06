#include "pthdpool.h"
/*
 * Copyright (c) 2013, Mathias Brossard <mathias@brossard.org>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

int err=0;

static void *my_thrd_func(void *lp)
{
	my_pool *pool = (my_pool *)lp;
    my_task task_t;

    for(;;) {
        /* Lock must be taken to wait on conditional variable */
        pthread_mutex_lock(&(pool->queue_lock));

        /* Wait on condition variable, check for spurious wakeups.
           When returning from pthread_cond_wait(), we own the lock. */
        while((pool->cur_thrd_no == 0) && (!pool->dispose)) {
            pthread_cond_wait(&(pool->queue_noti), &(pool->queue_lock));
        }
        if(pool->cur_thrd_no == 0)
            break;
        /* Grab our task */
        task_t.func = pool->queue[pool->prev].func;
        task_t.arg = pool->queue[pool->prev].arg;
        pool->prev += 1;
        pool->prev = (pool->prev == pool->queue_size) ? 0 : pool->prev;
        pool->cur_thrd_no -= 1;
        /* Unlock */
        pthread_mutex_unlock(&(pool->queue_lock));
        /* Get to work */
        (*(task_t.func))(task_t.arg);
    }
    pthread_mutex_unlock(&(pool->queue_lock));
    pthread_exit(NULL);
	return NULL;
}

int my_pool_free(my_pool *pool_t) {
    if(pool_t == NULL || pool_t->dispose) {
        return -1;
    }
    if(pool_t->thrd_id) {
        free(pool_t->thrd_id);
        free(pool_t->queue);
        pthread_mutex_destroy(&(pool_t->queue_lock));
        pthread_cond_destroy(&(pool_t->queue_noti));
    }
    free(pool_t);
    return 0;
}

my_pool* my_pool_init(int thrd_num,int sz_que)
{
	pool_t->dispose = false;
	if (thrd_num < 1) 
		thrd_num = 1;
	pool_t->thrd_num = 0;
	pool_t->queue_size = sz_que;
	pool_t->cur_thrd_no = 0;
	pool_t->thrd_id = (pthread_t *)malloc(sizeof(pthread_t) * thrd_num);
	pool_t->queue = (my_task_t *)malloc(sizeof(my_task_t) * sz_que);
		pool_t->thrd_id==null || pool_t->queue==null)
		{
			goto err;
		}
	for(int i = 0; i < thrd_num; i++) {
        if(pthread_create(&(pool_t->thrd_id[i]), NULL,
                          my_thrd_func, (void*)pool_t) != 0) {
            my_pool_destroy(pool_t);
            return NULL;
        }
        pool_t->thrd_num++;
        pool_t->cur_thrd_no++;
    }
	return pool_t;
err:
    if(pool_t) {
        my_pool_free(pool_t);
    }
	return NULL;
}

int my_pool_add_task(my_pool_t *pool, void *(*routine)(void *), void * arg)
{
	int next;
	if(pool||routine==NULL) {
		return -1;
	}    
	if(pthread_mutex_lock(&(pool->queue_lock)) != 0) {
        return -2;
    }
	next = pool->tail + 1;
    next = (next == pool->queue_size) ? 0 : next;
	
	do {
        /* Are we full ? */
        if(pool->cur_thrd_no == pool->queue_size) {
            err = -3;
            break;
        }

        /* Are we shutting down ? */
        if(pool->dispose) {
            err = -4;
            break;
        }

        /* Add task to queue */
        pool->queue[pool->tail].func = routine;
        pool->queue[pool->tail].arg = arg;
        pool->tail = next;
        pool->cur_thrd_no += 1;

        /* pthread_cond_broadcast */
        if(pthread_cond_signal(&(pool->queue_noti)) != 0) {
            err = -2;
            break;
        }
    } while(0);
	
	if(pthread_mutex_unlock(&pool->queue_lock) != 0) {
        err = -2;
    }
	
	return 0;
}

int my_pool_destroy(my_pool *pool)
{
	
    int i, err = 0;

    if(pool == NULL) {
        return -1;
    }

    if(pthread_mutex_lock(&(pool->queue_lock)) != 0) {
        return -2;
    }

    do {
        if(pool->dispose) {
            err = -4;
            break;
        }
        pool->dispose = true;

        /* Wake up all worker threads */
        if((pthread_cond_broadcast(&(pool->queue_noti)) != 0) ||
           (pthread_mutex_unlock(&(pool->queue_lock)) != 0)) {
            err = -2;
            break;
        }

        /* Join all worker thread */
        for(i = 0; i < pool->cur_thrd_no; i++) {
            if(pthread_join(pool->thrd_id[i], NULL) != 0) {
                err = -3;
            }
        }
        /* do{...} while(0) */
    } while(0);

    /* Only if everything went well do we deallocate the pool */
    if(!err) {
        my_pool_free(pool);
    }
    return err;
}

void my_pool_wait(my_pool * pool)
{
}
