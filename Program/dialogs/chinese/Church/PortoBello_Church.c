// 城市相关对话
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = NPCStringReactionRepeat(RandPhraseSimple("什么问题, "+ GetSexPhrase("我的孩子","我的孩子") +"?", "请问吧, 我在听... "), "我在听, 请说, "+ GetSexPhrase("我的孩子","我的孩子") +"... ", "第三次了, "+ GetSexPhrase("我的孩子","我的孩子") +", 问你需要什么。 ",
                          "神职人员有很多工作, 而你在分散我的注意力, "+ GetSexPhrase("我的孩子","我的孩子") +"... ", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了... ", "现在不了, 神父... "), "我没什么要说的, 抱歉。 ",
                      "我会问的, 但不是现在。 原谅我, 神父。 ", "请原谅我, 神父... ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
			//--> Письмо от покойника
			if (CheckAttribute(pchar, "questTemp.LFD_Church_1"))
            {
                link.l1 = "神父, 我正在寻找玛丽萨·卡尔德拉。听说她非常虔诚, 经常来教堂。您能告诉我该如何找到她吗? ";
                link.l1.go = "LFD_Church_1_1";
            }
			//<-- Письмо от покойника
        break;
		
		//--> Письмо от покойника
		case "LFD_Church_1_1":
			dialog.text = "玛丽萨曾是我们最虔诚的教友之一, 是教堂的灵魂人物。她的离去对教区而言是莫大的损失。我不知道是什么让她突然消失, 但我深信, 她遭遇了不该承受的磨难, 而这一切背后少不了魔鬼与其爪牙的阴谋。\n有时, 我会听说她在城里出现过, 但仅此而已。我们只能依靠主的旨意, 相信她终有一天会归来, 再次在教堂的庇佑下找到安宁。";
			link.l1 = "也许您认识谁能知道更多关于她的事? ";
			link.l1.go = "LFD_Church_1_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LFD_Church_1_2":
			dialog.text = ""+GetSexPhrase("孩子","孩子")+", 告诉我, 你为何要寻找玛丽萨? 我知道有时也会有人来打听她, 可那些人看起来并不像正直之人。世间诱惑众多, 不是每个找她的人都怀有善意。在我说出任何话之前, 我必须确定: 你不会给她, 或与她有关的人, 带来任何灾祸。";
			link.l1 = "我明白您的顾虑, 神父, 但请相信我: 我并无恶意。我只是想把这封信交给她, 它已经耽搁太久了。谁知道里面是否有她必须知道的重要内容。请您看看。";
			link.l1.go = "LFD_Church_1_3";
			TakeItemFromCharacter(pchar, "LFD_letter");
			notification("已交出: 给玛丽萨·卡尔德拉的信", "None");
		break;
		
		case "LFD_Church_1_3":
			dialog.text = "是的, 这封信看来确实经历了不少风浪才到了你手上。天晓得里面写了什么, 以及她读完后会有什么反应…… 但你能把它送还原主, 这份行为足够高尚, 船长。如果有人知道玛丽萨的下落, 那就是她的好友多洛雷斯·莫尼奥——她唯一真正信任的人。\n她家就在港务处左侧。愿这封信不要再给玛丽萨带来新的痛苦, 她已经受够了。";
			link.l1 = "谢谢您, 神父。愿上主保佑您。";
			link.l1.go = "LFD_Church_1_4";
			GiveItem2Character(PChar, "LFD_letter");
		break;
		
		case "LFD_Church_1_4":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Church_1");
		break;
		//<-- Письмо от покойника	
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果switch内部某处通过return退出, 别忘了进行卸载
}