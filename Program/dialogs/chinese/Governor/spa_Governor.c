// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
    int i, iTemp, iMoney, ShipType, Rank;
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = RandPhraseSimple("什么问题? ", "你需要什么? ");
            link.l1 = RandPhraseSimple("没什么重要的事, 先生。 ", "我没什么可说的, 抱歉。 ");
            link.l1.go = "exit";
        break;
        
        case "work_1":  // 为王室效力的工作 - 国家主线
            if (CheckAttribute(npchar, "notQuestLine"))
            {
                dialog.text = "很遗憾, 我不能考虑给你这份工作。 目前我不想和你共事。 再见。 ";
                link.l1 = "你不会是认真的吧…不过好吧。 ";
                link.l1.go = "exit";
                break;
            }                   
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 若switch内部某处通过return退出, 切记执行卸载
}