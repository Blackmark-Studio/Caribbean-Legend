// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = NPCStringReactionRepeat(RandPhraseSimple("有问题吗, " + GetAddress_Form(NPChar) + "? ", "我能为你做什么, " + GetAddress_Form(NPChar) + "? "), "" + GetSexPhrase("嗯, 你想干什么, " + GetAddress_Form(NPChar) + "? ", "又问些奇怪的问题? 伙计, 去喝点朗姆酒什么的吧... ") + "", "一整天里, 这已经是你第三次问这类问题了... " + GetSexPhrase(" 这是在引起注意吗? ", ""),
                          "我猜你又有问题要问吧, " + GetAddress_Form(NPChar) + "? ", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了", "我现在没什么好说的。 "), "不, 没什么要紧的... ",
                      "不, 亲爱的... ", "不, 什么问题? ... ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
        break;
        //--> 贝琪.普莱斯之谜
        case "TBP_BetsiPriceSex1":
            DoFunctionReloadToLocation("Villemstad_tavern_upstairs", "quest", "quest4", "TBP_Betsi_sex_2");
        break;
        //<-- 贝琪.普莱斯之谜
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果在switch中某处通过return退出, 别忘了执行卸载
}