# Sigfox_AT_Slave_DualCore

Ce projet STM32 est une application **Dual Core** (CM4 / CM0+) pour STM32WL55, implémentant un modem **Owley  contrôlé par commandes AT**.

L'architecture s'appuie sur :
- **CM4** : gestion des commandes AT, séquenceur, UART, configuration utilisateur
- **CM0+** : stack Owley, driver radio SX1261, EEPROM émulée, et la future librairie `Owley`

---

## Fonctionnalités

- Envoi de trames uplink/downlink
- Emission en porteuse continue (CW)
- Communication inter-cœurs via MBMUX/IPCC

---
