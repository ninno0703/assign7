> **作者**: 學號 113703023  
> **語言**: C++17  
> **建置工具**: CMake  
> **輸出**: 文字畫面 + 顏色 ANSI escape codes

---


1. **MVC 架構**  
   - **Model**: `GameObject` 抽象類 + `RPSGameObject` 繼承 `ICollider`  
   - **View**: `View` 類別負責畫面繪製（含顏色、游標控制）  
   - **Controller**: `Controller::run()` 驅動輸入 → 更新 → 碰撞 → 渲染 → 勝利判定  

2. **多型 & Factory**  
   - 所有物件以 `GameObject*` 儲存，動態呼叫 `update()`、`getCollider()`、`onCollision()`  
   - `GameObjectFactory` 回傳 `RPSGameObject` 實例，讓 Controller 完全不需知道子類細節  

3. **碰撞同化（Assimilation）**  
   - 兩物件坐標差1時，依 Rock > Scissors > Paper 規則，一方轉換為勝方類型  

4. **玩家操控 + 切換**  
   
   - **W/A/S/D** 移動目前玩家  
   - **Tab** 隨機切換到另一隻「石頭」物件  

5. **暫停/繼續（Pause/Resume）**  
   - **P** 鍵可隨時暫停或恢復遊戲迴圈，便於觀察當前生態狀態  

6. **遊戲結束判定**  
   - 當任一類型數量降為 0，拋出自訂 `end` 例外，跳回 `main()`，印出數量為0的屠殺方勝利訊息與學號  

7. **ANSI 顏色 & 游標控制**  
   - 使用 ANSI escape codes 隱藏游標、清屏、色彩輸出  

8. **程式流程示意**  
   ```text
   初始化 → while (跑遊戲) {
     讀鍵（W/A/S/D/Tab/P/ESC）→ 處理 input →
     隨機移動 NPCs →
     碰撞檢測 & onCollision →
     物件 update() → View 更新 → 畫面 render →
     勝利檢查（拋例外跳出）
   }
   catch(end) → 印學號 → 結束