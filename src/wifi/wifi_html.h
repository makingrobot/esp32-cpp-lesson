/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 * Author: Billy Zhang（billy_zh@126.com）
 */
#include "config.h"
#if CONFIG_WIFI_CONFIGURE_ENABLE==1

#ifndef _WIFI_HTML_H
#define _WIFI_HTML_H

const char index_html[] = R"(<!DOCTYPE html>
<html>
<head>
    <title>Network Configuration</title>
    <meta charset='utf-8'>
    <meta http-equiv='Content-Security-Policy' content='referrer no-referrer'>
    <meta name='viewport' content='width=device-width, initial-scale=1, user-scalable=no'>
    <style type="text/css">
        body {
            font-family: Arial, sans-serif;
            margin: 0;
            padding: 0;
            background-color: #f0f0f0;
        }
        label {
            display: block;
            margin-bottom: 5px;
        }
        input {
            width: 100%;
            padding: 5px;
            box-sizing: border-box;
            border: 1px solid #ccc;
            border-radius: 3px;
        }
        input[type="submit"] {
            background-color: #007bff;
            color: #fff;
            border: none;
            border-radius: 3px;
            padding: 10px;
            cursor: pointer;
        }
        input[type="submit"]:hover {
            background-color: #0056b3;
        }
        input[type="submit"]:disabled {
            background-color: #ccc;
            cursor: not-allowed;
        }

        #ap_list {
            margin-top: 20px;
            border-top: 1px solid #ccc;
            padding-top: 10px;
        }
        #ap_list a {
            display: block;
            margin-top: 5px;
            color: #007bff;
            text-decoration: none;
        }
        #ap_list a:hover {
            text-decoration: underline;
        }

        .language-switch {
            position: absolute;
            top: 20px;
            right: 20px;
        }
        .language-switch select {
            padding: 5px;
            border-radius: 3px;
            border: 1px solid #ccc;
        }

        /* 标签页样式 */
        .tabs {
            display: flex;
            margin-top: 20px;
            margin-bottom: 0;
            padding-left: 20px;
            border-bottom: 1px solid #ccc;
        }
        .tab {
            padding: 10px 20px;
            cursor: pointer;
            border: 1px solid #ccc;
            border-bottom: none;
            border-radius: 5px 5px 0 0;
            margin-right: 5px;
            background-color: #f0f0f0;
            position: relative;
            top: 1px;
        }
        .tab.active {
            background-color: #fff;
        }
        .tab-content {
            display: none;
            border-top: none;
            padding: 20px;
            background-color: #fff;
        }
        .tab-content.active {
            display: block;
        }

        #remember_bssid {
            width: auto;
        }

        /* 提示框样式 */
        .toast {
            position: fixed;
            top: 50%;
            left: 50%;
            transform: translate(-50%, -50%);
            background-color: rgba(0, 0, 0, 0.8);
            color: white;
            padding: 15px 30px;
            border-radius: 8px;
            z-index: 1000;
            opacity: 0;
            transition: opacity 0.3s ease-in-out;
            min-width: 200px;
            text-align: center;
        }
        .toast.show {
            opacity: 1;
        }
    </style>
</head>
<body>
    <div class='toast' id='toast'></div>
    <div class='language-switch'>
        <select id='language' onchange='changeLanguage()'>
            <option value='en-US'>English</option>
            <option value='zh-CN'>简体中文</option>
            <option value='zh-TW'>繁體中文</option>
            <option value='ja-JP'>日本語</option>
        </select>
    </div>
    
    <div class='tabs'>
        <div class='tab active' onclick='switchTab('wifi')' data-lang='wifi_tab'>WiFi 配置</div>
        <div class='tab' onclick='switchTab('advanced')' data-lang='advanced_tab'>高级选项</div>
    </div>

    <div id='wifi-tab' class='tab-content active'>
        <form action='/submit' method='post' onsubmit='submitForm(event)'>
            <div id='saved_list_container' style='display: none;'>
                <h3 data-lang='saved_wifi'>已保存的 WiFi</h3>
                <ul id='saved_list'>
                    <li>
                        <span>SSID</span>
                    </li>
                </ul>
            </div>
            <div>
                <h3 data-lang='new_wifi'>新的 WiFi</h3>
                <p class='error' style='color: red; text-align: center;' id='error'>
                </p>
                <p>
                    <label for='ssid'>SSID:</label>
                    <input type='text' id='ssid' name='ssid' required>
                </p>
                <p>
                    <label for='password' data-lang='password'>密码:</label>
                    <input type='password' id='password' name='password'>
                </p>
                <p style='text-align: center;'>
                    <input type='submit' value='连接' id='button' data-lang-value='connect'>
                </p>
                <p id='ap_list'>
                </p>
            </div>
        </form>
    </div>

    <div id='advanced-tab' class='tab-content'>
        <form action='/advanced/submit' method='post' onsubmit='submitAdvancedForm(event)'>
            <div>
                <h3 data-lang='advanced_tab'>高级选项</h3>
                <p class='error' style='color: red; text-align: center;' id='advanced_error'></p>
                
                <p>
                    <label for='ota_url' data-lang='ota_url'>OTA服务器地址:</label>
                    <div style='display: flex; align-items: center; gap: 10px;'>
                        <input type='text' id='ota_url' name='ota_url' style='flex: 1;'>
                        <button type='button' onclick='clearOtaUrl()' style='padding: 5px 10px; border: 1px solid #ccc; border-radius: 3px; background-color: #f0f0f0; cursor: pointer;'>❌</button>
                    </div>
                </p>

                <p style='display: flex; align-items: center; gap: 10px;'>
                    <label for='max_tx_power' data-lang='max_tx_power' style='white-space: nowrap;'>Wi-Fi发射功率:</label>
                    <select id='max_tx_power' name='max_tx_power'>
                        <option value='8'>2 dBm</option>
                        <option value='20'>5 dBm</option>
                        <option value='28'>7 dBm</option>
                        <option value='34'>8 dBm</option>
                        <option value='44'>11 dBm</option>
                        <option value='52'>13 dBm</option>
                        <option value='56'>14 dBm</option>
                        <option value='60'>15 dBm</option>
                        <option value='66'>16 dBm</option>
                        <option value='72'>18 dBm</option>
                        <option value='80'>20 dBm</option>
                    </select>
                </p>

                <p style='display: flex; align-items: center; gap: 10px;'>
                    <label for='remember_bssid' style='margin: 0;'>
                        <span data-lang='remember_bssid'>连接 Wi-Fi 时记住 BSSID</span>
                    </label>
                    <input type='checkbox' id='remember_bssid' name='remember_bssid'>
                </p>

                <p style='text-align: center;'>
                    <input type='submit' value='保存' id='advanced_button' data-lang-value='save'>
                </p>
            </div>
        </form>
    </div>

    <script type='text/javascript'>
        const button = document.getElementById('button');
        const error = document.getElementById('error');
        const ssid = document.getElementById('ssid');

        // Add language translations
        const translations = {
            'zh-CN': {
                title: '网络配置',
                saved_wifi: '已保存的 Wi-Fi',
                new_wifi: '新的 Wi-Fi',
                password: '密码:',
                connect: '连接',
                select_wifi: '从下面列表选择 2.4G Wi-Fi:',
                wifi_tab: 'Wi-Fi 配置',
                advanced_tab: '高级选项',
                ota_url: '自定义 OTA 地址:',
                max_tx_power: 'Wi-Fi 最大发射功率:',
                remember_bssid: '连接 Wi-Fi 时记住 BSSID',
                save: '保存'
            },
            'zh-TW': {
                title: '網路設定',
                saved_wifi: '已儲存的 Wi-Fi',
                new_wifi: '新的 Wi-Fi',
                password: '密碼:',
                connect: '連接',
                select_wifi: '從下方列表選擇 2.4G Wi-Fi:',
                wifi_tab: 'Wi-Fi 設定',
                advanced_tab: '進階選項',
                ota_url: '自定義 OTA 位址:',
                max_tx_power: 'Wi-Fi 最大發射功率:',
                remember_bssid: '連接 Wi-Fi 時記住 BSSID',
                save: '儲存'
            },
            'en-US': {
                title: 'Network Configuration',
                saved_wifi: 'Saved Wi-Fi',
                new_wifi: 'New Wi-Fi',
                password: 'Password:',
                connect: 'Connect',
                select_wifi: 'Select an 2.4G Wi-Fi from the list below:',
                wifi_tab: 'Wi-Fi Config',
                advanced_tab: 'Advanced',
                ota_url: 'Custom OTA URL:',
                max_tx_power: 'Wi-Fi Max TX Power:',
                remember_bssid: 'Remember BSSID when connecting to Wi-Fi',
                save: 'Save'
            },
            'ja-JP': {
                title: 'ネットワーク設定',
                saved_wifi: '保存済みのWi-Fi',
                new_wifi: '新しいWi-Fi',
                password: 'パスワード:',
                connect: '接続',
                select_wifi: '以下のリストから2.4G Wi-Fiを選択してください:',
                wifi_tab: 'Wi-Fi設定',
                advanced_tab: '詳細設定',
                ota_url: '自定義 OTA 位址:',
                max_tx_power: 'Wi-Fi最大送信電力:',
                remember_bssid: 'Wi-Fi接続時にBSSIDを記憶する',
                save: '保存'
            }
        };

        function changeLanguage() {
            const lang = document.getElementById('language').value;
            // 检查语言值是否合法
            if (!translations[lang]) {
                console.warn(`不支持的语言: ${lang}，默认使用中文`);
                document.getElementById('language').value = 'zh-CN';
                return changeLanguage();
            }
            // Set page title
            document.title = translations[lang].title;
            document.querySelectorAll('[data-lang]').forEach(element => {
                const key = element.getAttribute('data-lang');
                element.textContent = translations[lang][key];
            });
            document.querySelectorAll('[data-lang-value]').forEach(element => {
                const key = element.getAttribute('data-lang-value');
                element.value = translations[lang][key];
            });
            // Update AP list text
            const apList = document.getElementById('ap_list');
            if (apList.firstChild) {
                apList.firstChild.textContent = translations[lang].select_wifi;
            }
            // Save language preference
            localStorage.setItem('preferred_language', lang);
        }

        function renderSavedList(data) {
            const savedListContainer = document.getElementById('saved_list_container');
            const savedList = document.getElementById('saved_list');
            savedList.innerHTML = '';
            data.forEach((ssid, index) => {
                const li = document.createElement('li');
                let html = `<span>${ssid}</span>`;
                // Only add priority and delete buttons after the first item
                if (index > 0) {
                    html += ` <span>
                        <button type='button' onclick='setDefaultItem(this, ${index})'>⬆️</button>
                        <button type='button' onclick='deleteItem(this, ${index})'>❌</button>
                    </span>`;
                } else {
                    html += ` <span><button type='button' onclick='deleteItem(this, ${index})'>❌</button></span>`;
                }
                li.innerHTML = html;
                savedList.appendChild(li);
            });
            if (data.length > 0) {
                savedListContainer.style.display = 'block';
            } else {
                savedListContainer.style.display = 'none';
            }
        }

        // Delete one item from the list
        function deleteItem(item, index) {
            // disable the button
            item.disabled = true;
            // /saved/delete?index=INDEX
            fetch('/saved/delete?index=' + index)
                .then(response => response.json())
                .then(data => {
                    loadSavedList();
                });
        }

        function setDefaultItem(item, index) {
            item.disabled = true;
            fetch('/saved/set_default?index=' + index)
                .then(response => response.json())
                .then(data => {
                    loadSavedList();
                });
        }

        // Load saved ssid and password list
        function loadSavedList() {
            fetch('/saved/list')
                .then(response => response.json())
                .then(data => {
                    renderSavedList(data);
                });
        }

        // Load AP list from /scan
        function loadAPList() {
            if (button.disabled) {
                return;
            }

            fetch('/scan')
                .then(response => response.json())
                .then(data => {
                    const lang = document.getElementById('language').value;
                    const apList = document.getElementById('ap_list');
                    apList.innerHTML = '<p>' + translations[lang].select_wifi + '</p>';
                    data.forEach(ap => {
                        // Create a link for each AP
                        const link = document.createElement('a');
                        link.href = '#';
                        link.textContent = ap.ssid + ' (' + ap.rssi + ' dBm)';
                        if (ap.authmode === 0) {
                            link.textContent += ' 🌐';
                        } else {
                            link.textContent += ' 🔒';
                        }
                        link.addEventListener('click', () => {
                            ssid.value = ap.ssid;
                        });
                        apList.appendChild(link);
                    });
                    setTimeout(loadAPList, 5000);
                })
                .catch(error => {
                    console.error('Error:', error);
                });
        }

        // Set initial language
        document.addEventListener('DOMContentLoaded', () => {
            // 从 URL 参数中获取语言设置
            const urlParams = new URLSearchParams(window.location.search);
            const langParam = urlParams.get('lang');
            
            // 获取浏览器语言
            const browserLang = navigator.language || navigator.userLanguage;
            
            // 语言映射表，将浏览器语言代码映射到支持的语言代码
            const languageMap = {
                'zh': 'zh-CN',    // 简体中文
                'zh-CN': 'zh-CN', // 简体中文
                'zh-TW': 'zh-TW', // 繁体中文
                'zh-HK': 'zh-TW', // 繁体中文（香港）
                'ja': 'ja-JP',    // 日语
                'ja-JP': 'ja-JP', // 日语
                'en': 'en-US',    // 英语
                'en-US': 'en-US', // 英语
                'en-GB': 'en-US', // 英语（英国）
                'en-CA': 'en-US', // 英语（加拿大）
                'en-AU': 'en-US'  // 英语（澳大利亚）
            };
            
            // 获取支持的语言代码
            const getSupportedLanguage = (lang) => {
                // 首先尝试完全匹配
                if (languageMap[lang]) {
                    return languageMap[lang];
                }
                // 然后尝试只匹配主语言代码（例如 'zh' 而不是 'zh-CN'）
                const mainLang = lang.split('-')[0];
                if (languageMap[mainLang]) {
                    return languageMap[mainLang];
                }
                // 如果都不匹配，返回英语
                return 'en-US';
            };
            
            // 优先使用 URL 参数的语言设置，其次是本地存储的设置，最后是浏览器语言设置
            const savedLang = langParam || 
                             localStorage.getItem('preferred_language') || 
                             getSupportedLanguage(browserLang);
            
            document.getElementById('language').value = savedLang;
            changeLanguage();
            loadSavedList();
            loadAPList();
            loadAdvancedConfig();
        });

        // 监听 pageshow 事件以处理浏览器返回键
        window.addEventListener('pageshow', (event) => {
            if (event.persisted) {
                loadSavedList();
            } else {
                // 正常加载时已处理
            }
        });

        async function submitForm(event) {
            event.preventDefault();
            button.disabled = true;
            error.textContent = '';

            const ssidValue = ssid.value;
            const passwordValue = document.getElementById('password').value;

            const payload = {
                ssid: ssidValue,
                password: passwordValue
            };

            try {
                const response = await fetch('/submit', {
                    method: 'POST',
                    headers: {
                        'Content-Type': 'application/json'
                    },
                    body: JSON.stringify(payload)
                });

                const data = await response.json();
                if (!data.success) {
                    throw new Error(data.error || '连接失败');
                }

                // 连接成功，跳转到完成页面
                button.disabled = false;
                window.location.href = '/done.html';
            } catch (err) {
                error.textContent = err.message;
                button.disabled = false;
            }
        }

        function switchTab(tabName) {
            // 隐藏所有标签页内容
            document.querySelectorAll('.tab-content').forEach(content => {
                content.classList.remove('active');
            });
            // 移除所有标签页的active类
            document.querySelectorAll('.tab').forEach(tab => {
                tab.classList.remove('active');
            });
            // 显示选中的标签页内容
            document.getElementById(tabName + '-tab').classList.add('active');
            // 激活选中的标签
            document.querySelector(`.tab[onclick='switchTab('${tabName}')']`).classList.add('active');
        }

        async function submitAdvancedForm(event) {
            event.preventDefault();
            const advancedButton = document.getElementById('advanced_button');
            const advancedError = document.getElementById('advanced_error');
            advancedButton.disabled = true;
            advancedError.textContent = '';

            const config = {
                ota_url: document.getElementById('ota_url').value,
                max_tx_power: parseInt(document.getElementById('max_tx_power').value),
                remember_bssid: document.getElementById('remember_bssid').checked
            };

            try {
                const response = await fetch('/advanced/submit', {
                    method: 'POST',
                    headers: {
                        'Content-Type': 'application/json'
                    },
                    body: JSON.stringify(config)
                });

                const data = await response.json();
                if (!data.success) {
                    throw new Error(data.error || '保存失败');
                }

                advancedButton.disabled = false;
                showToast('配置已保存');
            } catch (err) {
                advancedError.textContent = err.message;
                advancedButton.disabled = false;
            }
        }

        // 显示提示框
        function showToast(message) {
            const toast = document.getElementById('toast');
            toast.textContent = message;
            toast.classList.add('show');
            setTimeout(() => {
                toast.classList.remove('show');
            }, 3000);
        }

        // 加载高级配置
        async function loadAdvancedConfig() {
            try {
                const response = await fetch('/advanced/config');
                const data = await response.json();
                
                if (data.ota_url) {
                    document.getElementById('ota_url').value = data.ota_url;
                }
                if (data.max_tx_power) {
                    document.getElementById('max_tx_power').value = data.max_tx_power;
                }
                if (data.remember_bssid !== undefined) {
                    document.getElementById('remember_bssid').checked = data.remember_bssid;
                }
            } catch (error) {
                console.error('Error loading advanced config:', error);
            }
        }

        // 清空OTA地址
        function clearOtaUrl() {
            document.getElementById('ota_url').value = '';
        }
    </script>
</body>
</html>)";

const char done_html[] = R"(<!DOCTYPE html>
<html>
<head>
    <title>WiFi Configuration</title>
    <meta charset='utf-8'>
    <meta name='viewport' content='width=device-width, initial-scale=1, user-scalable=no'>
    <style>
        body {
            margin: 0;
            padding: 0;
            overflow: hidden;
        }

        .container {
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content: center;
            height: 100vh;
            font-family: Arial, sans-serif;
            /* Prevent content from overflowing */
            max-height: 100vh;
            box-sizing: border-box;
            padding: 20px;
        }

        .checkmark {
            width: 150px;
            height: 150px;
            margin-bottom: 30px;
        }

        .message {
            text-align: center;
            font-size: 20px;
            margin-bottom: 20px;
        }
    </style>
</head>
<body>
    <div class='container'>
        <svg class='checkmark' viewBox='0 0 52 52'>
            <circle class='checkmark__circle' cx='26' cy='26' r='25' fill='none' stroke='#4CAF50' stroke-width='2'/>
            <path class='checkmark__check' fill='none' stroke='#4CAF50' stroke-width='2' d='M14.1 27.2l7.1 7.2 16.7-16.8'/>
        </svg>
        
        <div class='message'>
            <p>设备将在 <span id='countdown'>3</span> 秒后重启</p>
            <p>Device will restart in <span id='countdown-en'>3</span> seconds</p>
        </div>
    </div>
    
    <script>
        window.addEventListener('load', function() {
            let count = 3;
            const countdownElement = document.getElementById('countdown');
            const countdownEnElement = document.getElementById('countdown-en');
            
            const timer = setInterval(function() {
                count--;
                countdownElement.textContent = count;
                countdownEnElement.textContent = count;
                
                if (count <= 0) {
                    clearInterval(timer);
                    fetch('/reboot', {
                        method: 'POST'
                    })
                    .then(response => {
                        if (response.ok) {
                            console.log('重启指令已发送');
                            window.close();
                        } else {
                            console.error('发送重启指令失败');
                        }
                    })
                    .catch(error => {
                        console.error('Error:', error);
                    });
                }
            }, 1000);
        });
    </script>
</body>
</html>)";

#endif //_WIFI_HTML_H

#endif //CONFIG_WIFI_CONFIGURE_ENABLE