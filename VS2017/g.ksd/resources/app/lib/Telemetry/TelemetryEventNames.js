/*---------------------------------------------------------
 * Copyright (C) Microsoft Corporation. All rights reserved.
 *--------------------------------------------------------*/
"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.APPLICATION_RUN = "AppRun";
exports.APPLICATION_INITIALIZE_PRE_TELEMETRY = "AppInitializePreTelemetry";
exports.APPLICATION_INITIALIZE = "AppInitialize";
exports.APPLICATION_READY = "AppReady";
exports.APPLICATION_LAUNCH = "AppLaunched";
exports.APPLICATION_SHUTDOWN = "AppShutdown";
exports.APPLICATION_SERVICE_INITIALIZE = "initialize-app-services";
exports.APPLICATION_LEAK_DETECTED = "leak-detected";
exports.APPLICATION_CRASH = "JSCrash";
exports.APPLICATION_CONFIG_ERROR = "ConfigError";
exports.APPLICATION_CMDLINE_ERROR = "CmdlineError";
exports.APPLICATION_PARSE_CMDLINE = "parse-commandline";
exports.APPLICATION_UNINSTALL_SELF = "AppUninstall";
exports.APPLICATION_UNINSTALL_SELF_REQUESTED = "AppUninstallSelfRequested";
exports.APPLICATION_UNINSTALL_SELF_FAILED = "AppUninstallSelfFailed";
exports.APPLICATION_FINALIZE_FAILED = "AppFinalizeFailed";
exports.APPLICATION_UPDATE = "AppUpdate";
exports.APPLICATION_UPDATE_AVAILABLE = "AppUpdateAvailable";
exports.APPLICATION_UPDATE_DOWNLOAD_FINISHED = "AppUpdateDownloadFinished";
exports.RELAUNCH_WINDOW = "relaunch-window";
exports.APPLICATION_SHUTDOWN_PARAMETERS_FORWARDED = "Another instance of the app is running, shutting down and passing command line paramters to singleton instance.";
exports.APPLICATION_ENABLE_WER = "AppEnableWer";
exports.INSTALLER_INSTALLED_PRODUCT = "InstallerInstalledProduct";
exports.INSTALLER_INSTALLED_PRODUCT_SUMMARIES = "InstallerInstalledProductSummaries";
exports.INSTALLER_PRODUCT = "InstallerProduct";
exports.INSTALLER_PRODUCT_SUMMARIES = "InstallerProductSummaries";
exports.INSTALLER_ESTIMATED_INSTALL_SIZE = "InstallerEstimatedInstallSize";
exports.INSTALLER_CHANNEL_INFO = "InstallerChannelInfo";
exports.INSTALLER_REMOVE_CHANNEL = "InstallerRemoveChannel";
exports.SETUP_ENGINE_UNKNOWN = "SetupEngineUnknown";
exports.SETUP_ENGINE_DISPOSE = "disposing-setup-engine";
exports.SEND_FEEDBACK = "SendFeedback";
exports.VERSION_INFO_DOWNLOAD_FINISHED = "VersionInfoDownloadFinished";
exports.WINDOW_FOCUS_EVENT = "focus-window";
exports.SELECT_TAB = "select-tab";
exports.DETAILS_PAGE_SESSION = "DetailsPageSession";
exports.DETAILS_PAGE_SESSION_TYPE_INSTALL = "Install";
exports.DETAILS_PAGE_SESSION_TYPE_MODIFY = "Modify";
exports.WORKLOAD_SELECTION = "WorkloadSelection";
exports.COMPONENT_SELECTION = "ComponentSelection";
exports.SHOW_ERROR_DIALOG = "show-errordialog";
exports.ELEVATION_REQUIRED = "ElevationRequired";
exports.DISK_SIZE_WARNING_SHOWN_TO_USER = "DiskSizeErrorShownToUser";
exports.DISK_SIZE_WARNING_IGNORED_BY_USER = "DiskSizeErrorIgnoredByUser";
exports.CHANNEL_INFO = "ChannelInfo";
exports.SHOW_FOCUSED_UI = "show-focused-ui";
exports.CUSTOMIZE_FROM_FOCUSED_UI = "customize-from-focused-ui";
exports.END_OPERATION_GET_PRODUCT_ERROR = "EndOperationGetProductError";
exports.SETUP_INITIALIZE_INSTALLER_SERVICE = "SetupInitInstallerService";
exports.SETUP_INITIALIZE_INSTALLER_UPDATER_SERVICE = "SetupInitInstallerUpdateService";
exports.SETUP_INITIALIZE_INSTALLED_PRODUCTS_PROVIDER_SERVICE = "SetupInitInstalledProductsProviderService";
exports.SETUP_INITIALIZE_PRODUCTS_PROVIDER_SERVICE = "SetupInitProductsProviderService";
exports.SYSTEM_SUSPEND = "SystemSuspend";
exports.SYSTEM_RESUME = "SystemResume";
exports.SURVEY_PROMPT_SHOWN_TO_USER = "SurveyPromptShownToUser";
exports.CREATE_SHORTCUT_FAILED = "CreateShortcutFailed";
exports.DELETE_SHORTCUT_FAILED = "DeleteShortcutFailed";
exports.USER_DATA_WRITE_ERROR = "UserDataWriteFailed";
exports.OPEN_VS_FEEDBACK = "open-vsfeedback";
exports.OPEN_VS_FEEDBACK_ERROR = "open-vsfeedback-error";
exports.OPEN_MENU = "open-menu";
exports.CLOSE_MENU = "close-menu";
exports.ACTIVATE_MENU_ITEM = "activate-menuitem";
exports.BROWSER_WINDOW_CREATE = "BrowserWindow/create-window";
exports.BROWSER_WINDOW_RESPONSIVE = "BrowserWindow/Responsive";
exports.BROWSER_WINDOW_SHOW = "BrowserWindow/Show";
exports.BROWSER_WINDOW_READY = "BrowserWindow/Ready";
exports.BROWSER_WINDOW_UNRESPONSIVE = "BrowserWindow/Unresponsive";
exports.EMIT_EVENT_ERROR = "emit-event-error";
exports.FAILURES_DIALOG_ENABLED = "failures-dialog-enabled";
exports.VIEW_PROBLEMS = "view-problems";
exports.OPEN_LOG_ERROR = "open-log-error";
exports.TOGGLE_AUTOLAUNCH = "toggle-autolaunch";
exports.CANCEL_CONFIRMATION_DIALOG = "install-cancel-confirmation";
exports.FEEDBACK_SEARCH_STARTED = "FeedbackClient/search-started";
exports.FEEDBACK_SEARCH_FINISHED = "FeedbackClient/search-finished";
exports.FEEDBACK_SEARCH_FAILED = "FeedbackClient/search-failed";
exports.FEEDBACK_CHECKING_SOLUTIONS = "FeedbackClient/checking-solutions";
exports.ABNORMAL_SHUTDOWN_DETECTED = "detected-abnormalshutdown";
exports.START_SERVICEHUB_ERROR = "start-servicehub-error";
exports.INIT_FEATURE_STORE = "init-featurestore";
exports.UPDATE_CAMPAIGN = "update-campaign";
exports.SHOW_DELAYED_PRODUCT_MESSAGE = "show-delayedproductmessage";
exports.SURVEY_URLS = "surveys/URLs";
//# sourceMappingURL=TelemetryEventNames.js.map