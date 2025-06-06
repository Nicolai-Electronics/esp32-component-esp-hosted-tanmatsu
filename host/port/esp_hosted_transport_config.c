/*
* SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
*
* SPDX-License-Identifier: Apache-2.0
*/

#include "esp_hosted_transport_config.h"
#include <string.h>
#include "esp_log.h"

static const char *TAG = "esp_hosted_transport_config";

/* Static configurations */
static struct esp_hosted_transport_config s_transport_config;

/* Flags to track if configs were set */
static bool esp_hosted_transport_config_set;

bool esp_hosted_transport_is_config_valid(void) {
  return esp_hosted_transport_config_set;
}

esp_hosted_transport_err_t esp_hosted_transport_set_default_config(void)
{
    memset(&s_transport_config, 0, sizeof(s_transport_config));

#if H_TRANSPORT_IN_USE == H_TRANSPORT_SDIO
    ESP_ERROR_CHECK(esp_hosted_sdio_set_config(NULL));
#elif H_TRANSPORT_IN_USE == H_TRANSPORT_SPI_HD
    ESP_ERROR_CHECK(esp_hosted_spi_hd_set_config(NULL));
#elif H_TRANSPORT_IN_USE == H_TRANSPORT_SPI
    ESP_ERROR_CHECK(esp_hosted_spi_set_config(NULL));
#elif H_TRANSPORT_IN_USE == H_TRANSPORT_UART
    ESP_ERROR_CHECK(esp_hosted_uart_set_config(NULL));
#else
    return ESP_TRANSPORT_ERR_INVALID_STATE;
#endif

    return ESP_TRANSPORT_OK;
}

#if H_TRANSPORT_IN_USE == H_TRANSPORT_SDIO
esp_hosted_transport_err_t esp_hosted_transport_get_config(struct esp_hosted_transport_config *config)
{
    if (!config) {
        return ESP_TRANSPORT_ERR_INVALID_ARG;
    }
    *config = s_transport_config;
    return ESP_TRANSPORT_OK;
}

/* SDIO functions */
esp_hosted_transport_err_t esp_hosted_sdio_get_config(struct esp_hosted_sdio_config *config)
{
    if (!config) {
        return ESP_TRANSPORT_ERR_INVALID_ARG;
    }
    *config = s_transport_config.u.sdio;
    return ESP_TRANSPORT_OK;
}

esp_hosted_transport_err_t esp_hosted_sdio_set_config(struct esp_hosted_sdio_config *config)
{
    if (esp_hosted_transport_config_set) {
        ESP_LOGE(TAG, "Transport already initialized (through constructor?), reconfiguring not allowed");
        return ESP_TRANSPORT_ERR_ALREADY_SET; /* Error: already set */
    }

    if (config == NULL) {
        s_transport_config.u.sdio = INIT_DEFAULT_HOST_SDIO_CONFIG();
    } else {
        s_transport_config.u.sdio = *config;
    }
    esp_hosted_transport_config_set = true;
    s_transport_config.transport_in_use = H_TRANSPORT_SDIO;
    return ESP_TRANSPORT_OK;
}

esp_hosted_transport_err_t esp_hosted_sdio_iomux_set_config(struct esp_hosted_sdio_config *config)
{
    if (esp_hosted_transport_config_set) {
        ESP_LOGE(TAG, "Transport already initialized (through constructor?), reconfiguring not allowed");
        return ESP_TRANSPORT_ERR_ALREADY_SET; /* Error: already set */
    }

    if (config == NULL) {
        s_transport_config.u.sdio = INIT_DEFAULT_HOST_SDIO_IOMUX_CONFIG();
    } else {
        s_transport_config.u.sdio = *config;
    }
    esp_hosted_transport_config_set = true;
    s_transport_config.u.sdio.iomux_enable = true;
    s_transport_config.transport_in_use = H_TRANSPORT_SDIO;
    return ESP_TRANSPORT_OK;
}
#endif

#if H_TRANSPORT_IN_USE == H_TRANSPORT_SPI_HD
/* SPI Half Duplex functions */
esp_hosted_transport_err_t esp_hosted_spi_hd_get_config(struct esp_hosted_spi_hd_config *config)
{
    if (!config) {
        return ESP_TRANSPORT_ERR_INVALID_ARG;
    }
    *config = s_transport_config.u.spi_hd;
    return ESP_TRANSPORT_OK;
}

esp_hosted_transport_err_t esp_hosted_spi_hd_set_config(struct esp_hosted_spi_hd_config *config)
{
    if (esp_hosted_transport_config_set) {
        ESP_LOGE(TAG, "Transport already initialized (through constructor?), reconfiguring not allowed");
        return ESP_TRANSPORT_ERR_ALREADY_SET; /* Error: already set */
    }

    if (config == NULL) {
        s_transport_config.u.spi_hd = INIT_DEFAULT_HOST_SPI_HD_CONFIG();
    } else {
        s_transport_config.u.spi_hd = *config;
    }
    esp_hosted_transport_config_set = true;
    s_transport_config.transport_in_use = H_TRANSPORT_SPI_HD;
    return ESP_TRANSPORT_OK;
}

esp_hosted_transport_err_t esp_hosted_spi_hd_2lines_get_config(struct esp_hosted_spi_hd_config *config)
{
    if (!config) {
        return ESP_TRANSPORT_ERR_INVALID_ARG;
    }
    *config = s_transport_config.u.spi_hd;
    config->num_data_lines = 2;
    return ESP_TRANSPORT_OK;
}

esp_hosted_transport_err_t esp_hosted_spi_hd_2lines_set_config(struct esp_hosted_spi_hd_config *config)
{
    if (esp_hosted_transport_config_set) {
        ESP_LOGE(TAG, "Transport already initialized (through constructor?), reconfiguring not allowed");
        return ESP_TRANSPORT_ERR_ALREADY_SET; /* Error: already set */
    }

    if (config == NULL) {
        s_transport_config.u.spi_hd = INIT_DEFAULT_HOST_SPI_HD_CONFIG();
        s_transport_config.u.spi_hd.num_data_lines = 2;
    } else {
        s_transport_config.u.spi_hd = *config;
    }
    s_transport_config.transport_in_use = H_TRANSPORT_SPI_HD;
    esp_hosted_transport_config_set = true;
    return ESP_TRANSPORT_OK;
}
#endif

#if H_TRANSPORT_IN_USE == H_TRANSPORT_SPI
/* SPI Full Duplex functions */
esp_hosted_transport_err_t esp_hosted_spi_get_config(struct esp_hosted_spi_config *config)
{
    if (!config) {
        return ESP_TRANSPORT_ERR_INVALID_ARG;
    }
    *config = s_transport_config.u.spi;
    return ESP_TRANSPORT_OK;
}

esp_hosted_transport_err_t esp_hosted_spi_set_config(struct esp_hosted_spi_config *config)
{
    if (esp_hosted_transport_config_set) {
        ESP_LOGE(TAG, "Transport already initialized (through constructor?), reconfiguring not allowed");
        return ESP_TRANSPORT_ERR_ALREADY_SET; /* Error: already set */
    }

    if (config == NULL) {
        s_transport_config.u.spi = INIT_DEFAULT_HOST_SPI_CONFIG();
    } else {
        s_transport_config.u.spi = *config;
    }
    esp_hosted_transport_config_set = true;
    s_transport_config.transport_in_use = H_TRANSPORT_SPI;
    return ESP_TRANSPORT_OK;
}
#endif

#if H_TRANSPORT_IN_USE == H_TRANSPORT_UART
/* UART functions */
esp_hosted_transport_err_t esp_hosted_uart_get_config(struct esp_hosted_uart_config *config)
{
    if (!config) {
        return ESP_TRANSPORT_ERR_INVALID_ARG;
    }
    *config = s_transport_config.u.uart;
    return ESP_TRANSPORT_OK;
}

esp_hosted_transport_err_t esp_hosted_uart_set_config(struct esp_hosted_uart_config *config)
{
    if (esp_hosted_transport_config_set) {
        ESP_LOGE(TAG, "Transport already initialized (through constructor?), reconfiguring not allowed");
        return ESP_TRANSPORT_ERR_ALREADY_SET; /* Error: already set */
    }

    if (config == NULL) {
        s_transport_config.u.uart = INIT_DEFAULT_HOST_UART_CONFIG();
    } else {
        s_transport_config.u.uart = *config;
    }
    esp_hosted_transport_config_set = true;
    s_transport_config.transport_in_use = H_TRANSPORT_UART;
    return ESP_TRANSPORT_OK;
}
#endif
