// 传闻 - 按类型分类的对话

#define MAX_RUMOURS_ABOUT_OWNERS 7

void ProcessCommonDialogRumors(ref NPChar, aref Link, aref NextDiag);
{
    string strum;
    string srum;
	bool bOk1, bOk2;
	switch(Dialog.CurrentNode)
	{
/////////////////////////////////////////////////---市民女性传闻---////////////////////////////////////////////
		case "rumours_towngirl":	
		NextDiag.CurrentNode = "rumours";
		
		//--> 治愈的黑暗之水
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		if (bOk1 || bOk2)
        {
			dialog.text = "你听说了吗? 据说托马斯.莫里森的女儿已经卧床六个月了。 医生对她的病完全束手无策。 唯一能帮助她的是一个吉普赛女人, 她以能治愈重病的药水闻名。 但她断然拒绝为这个可怜的女孩做任何事。 ";
			link.l1 = "谢谢你, 我得走了。 ";
			link.l1.go = "exit";
			
			SetQuestHeader("DWH");
			AddQuestRecord("DWH", "1");
			pchar.questTemp.DWH_Start = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("DWH_gypsy", "gipsy_2", "woman", "towngirl", 10, PIRATE, -1, true, "citizen"));
			ChangeCharacterAddressGroup(sld, "SentJons_town", "goto", "goto1");
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "dwh_gypsy_0";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_SetLoginTime(sld, 07.00, 21.99);
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // 激活事件
			break;
        }
		//<—— 治愈的黑暗之水
		//--> 正义的边界
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		if (bOk1 || bOk2)
        {
			dialog.text = "两天前, 有人厚颜无耻地企图刺杀港口长官! 刺客在他的办公室门口埋伏, 但长官设法呼救。 一名火枪手迅速赶到并击伤了恶棍, 不过那家伙还是逃出了城门。 \n听说港口长官为这个无赖的脑袋开出了丰厚的赏金! 到目前为止, 还没有勇敢的人站出来。 告诉你吧, 就算给一千达布隆 --我也不会拿脖子去冒险... ";
			link.l1 = "谢谢你, 我得走了。 ";
			link.l1.go = "exit";
			
			SetQuestHeader("GS");
			AddQuestRecord("GS", "1");
			pchar.questTemp.GS_Start = true;
			pchar.questTemp.GS_Portman = true;
			AddLandQuestMark(characterFromId("Beliz_portman"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // 激活事件
			break;
        }
		//<—— 正义的边界
		//--> 依法贸易
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		if (bOk1 || bOk2)
        {
			dialog.text = "听到消息了吗? ! 这简直是血腥的暴行! 酒馆里一滴朗姆酒或葡萄酒都没有了 --在这该死的炎热天气里, 人们该如何解渴? 客栈老板一周来一直用空洞的承诺敷衍我们, 说酒很快就会再来, 但一直什么都没有! 难道要我们渴到审判日吗? ";
			link.l1 = "谢谢你, 我得走了。 ";
			link.l1.go = "exit";
			
			SetQuestHeader("TPZ");
			AddQuestRecord("TPZ", "1");
			pchar.questTemp.TPZ_Start = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // 激活事件
			break;
        }
		//<—— 依法贸易
		//--> 被盗的记忆
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		if (bOk1 || bOk2)
		{
			dialog.text = "港口周围传言说, 总督的侄女朱莉.德.阿尔马尼亚克已经变得不像从前了。 她曾经容光焕发。 充满活力, 现在却在街上漫无目的地走着, 脸上刻着明显的悲伤。 镇上的人窃窃私语, 想知道她到底发生了什么, 但没有人知道真相。 也许是哪个无赖伤了她的心? " + GetSexPhrase(" 也许是你吧, 船长? ", "");
			link.l1 = "" + GetSexPhrase("我怀疑不是 ", "") + "。 谢谢你, 我得走了。 ";
			link.l1.go = "exit";
			
			SetQuestHeader("UV");
			AddQuestRecord("UV", "1");
			pchar.questTemp.UV_Start = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("UV_Juli", "women_4", "woman", "woman", sti(pchar.rank), FRANCE, -1, false, "quest"));
			sld.name = StringFromKey("Neutral_6");
			sld.lastname = StringFromKey("Neutral_7");
			sld.City = "PortPax";
			ChangeCharacterAddressGroup(sld, "PortPax_town", "goto", "goto9");
			sld.dialog.filename = "Quest\MiniEvents\StolenMemory_dialog.c";
			sld.dialog.currentnode = "Juli";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_SetImmortal(sld, true);
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // 激活事件
			break;
        }
		//<—— 被盗的记忆
		//--> 伟大捕获的俘虏 andre39966
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		if (bOk1 || bOk2)
        {
			dialog.text = "听说渔夫皮埃尔.卡诺失踪了, 无影无踪。 两天前, 他出海后就再也没有消息。 他的妻子莉娅悲痛欲绝。 无论白天还是夜晚, 她都在码头守着, 眼睛盯着无尽的海水, 祈祷能看到她心爱的人的船帆。 ";
			link.l1 = "谢谢你, 我得走了。 ";
			link.l1.go = "exit";
			
			SetQuestHeader("VPVL");
			AddQuestRecord("VPVL", "1");
			pchar.questTemp.VPVL_Start = true;
			AddDialogExitQuest("VPVL_Gegerate_Lea");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // 激活事件
			break;
        }
		//<—— 伟大捕获的俘虏
		//--> 贝齐.普莱斯的秘密
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		if (bOk1 || bOk2)
        {
			dialog.text = "船长, 你听说了吗? 我们酒馆来了个新女招待。 据说她是个大美人。 附近的男人都争先恐后地来一睹她的芳容。 但三天前, 她没来上班, 这让酒馆老板很生气, 因为自从她来了之后, 老板赚了很多钱。 听说他甚至愿意付钱给找到这个女孩的人。 ";
			link.l1 = "谢谢你, 我得走了。 ";
			link.l1.go = "exit";
			
			SetQuestHeader("TBP");
			AddQuestRecord("TBP", "1");
			pchar.questTemp.TBP_Start = true;
			pchar.questTemp.TBP_Tavern = true;
			AddLandQuestMark(CharacterFromID("Villemstad_tavernkeeper"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // 激活事件
			break;
        }
		//<—— 贝齐.普莱斯的秘密
		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 2 )
        srum = SelectRumourEx("towngirl", NPChar);
        else srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // 修复
        string posrep1, posrep2, answ1, answ2, answ3, answ4;
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" 就是这样... ", " 你可能会觉得有趣。 ");
            posrep2 = " 嘿, 船长, 你有什么关于我们殖民地的消息要告诉吗? ";
            answ1 = RandPhraseSimple(RandSwear() + "这很有趣, " + GetFullName(NPChar) + "。 ",
                                 "那告诉我关于... ");
            answ2 = RandPhraseSimple(RandSwear() + "有趣! 还有一个问题我想问... ", "还有一个问题。 ");
            answ3 = RandPhraseSimple("嗯, 什么都可能发生。 抱歉, 但我没有什么特别的要告诉你。 ", "我很匆忙, 也许下次吧。 ");
            answ4 = "";
        }
        else
        {
            posrep1 = " 这里相当乏味。 所以如果真有什么事发生, 每个人都会谈论它。 ";
            posrep2 = " 没什么有趣的。 也许" + GetAddress_Form(NPChar) + "可能知道什么? ";
            answ1 = RandPhraseSimple("那告诉我关于... ", RandSwear() + "你什么都不知道! 好吧, 另一个话题... ");
            answ2 = RandPhraseSimple("不管怎样, 告诉我别的吧... ", "是的, 你没帮上什么忙, 还有什么可以和我分享的吗? ");
            answ3 = RandPhraseSimple("我怀疑我有什么有趣的事要告诉你。 ", "我很乐意, 但下次再谈吧。 ");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,
            srum+posrep1,
            srum+posrep2,
            RandPhraseSimple("唉, 没什么可告诉你的了, 让我过去。 ", "我受够了你的问题, 对不起, 我还有很多其他事情要做。 "), "block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,
                                            answ2,
                                            answ3,
                                            answ4,
                                            npchar, Dialog.CurrentNode);
		link.l1.go = "new question";
		link.l2 = RandPhraseSimple("谢谢, 我该走了。 ", "再见。 ");
		link.l2.go = "exit";
	break;

/////////////////////////////////////////////////---市民男性传闻---////////////////////////////////////////////
	case "rumours_townman":	
		NextDiag.CurrentNode = "rumours";
		
		//--> 治愈的黑暗之水
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		if (bOk1 || bOk2)
        {
			dialog.text = "你听说了吗? 据说托马斯.莫里森的女儿已经卧床六个月了。 医生对她的病完全束手无策。 唯一能帮助她的是一个吉普赛女人, 她以能治愈重病的药水闻名。 但她断然拒绝为这个可怜的女孩做任何事。 ";
			link.l1 = "谢谢你, 我得走了。 ";
			link.l1.go = "exit";
			
			SetQuestHeader("DWH");
			AddQuestRecord("DWH", "1");
			pchar.questTemp.DWH_Start = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("DWH_gypsy", "gipsy_2", "woman", "towngirl", 10, PIRATE, -1, true, "citizen"));
			ChangeCharacterAddressGroup(sld, "SentJons_town", "goto", "goto1");
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "dwh_gypsy_0";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_SetLoginTime(sld, 07.00, 21.99);
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // 激活事件
			break;
        }
//<—— 治愈的黑暗之水
//--> 正义的边界
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		if (bOk1 || bOk2)
        {
			dialog.text = "两天前, 有人厚颜无耻地企图刺杀港口长官! 刺客在他的办公室门口埋伏, 但长官设法呼救。 一名火枪手迅速赶到并击伤了恶棍, 不过那家伙还是逃出了城门。 \n听说港口长官为这个无赖的脑袋开出了丰厚的赏金! 到目前为止, 还没有勇敢的人站出来。 请注意, 即使给一千达布隆 --我也不会拿脖子去冒险... ";
			link.l1 = "谢谢你, 我得走了。 ";
			link.l1.go = "exit";
			
			SetQuestHeader("GS");
			AddQuestRecord("GS", "1");
			pchar.questTemp.GS_Start = true;
			pchar.questTemp.GS_Portman = true;
			AddLandQuestMark(characterFromId("Beliz_portman"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // 激活事件
			break;
        }
		//<—— 正义的边界
		
		//--> 依法贸易
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		if (bOk1 || bOk2)
        {
			dialog.text = "听到消息了吗? ! 这简直是血腥的暴行! 酒馆里一滴朗姆酒或葡萄酒都没有了 --在这该死的炎热天气里, 人们该如何解渴? 客栈老板一周来一直用空洞的承诺敷衍我们, 说酒很快就会再来, 但一直什么都没有! 难道要我们渴到审判日吗? ";
			link.l1 = "谢谢你, 我得走了。 ";
			link.l1.go = "exit";
			
			SetQuestHeader("TPZ");
			AddQuestRecord("TPZ", "1");
			pchar.questTemp.TPZ_Start = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // 激活事件
			break;
        }
		//<—— 依法贸易
		
		//--> 被盗的记忆
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		if (bOk1 || bOk2)
        {
			dialog.text = "港口周围传言说, 总督的侄女朱莉.德.阿尔马尼亚克已经变得不像从前了。 她曾经容光焕发。 充满活力, 现在却在街上漫无目的地走着, 脸上刻着明显的悲伤。 镇上的人窃窃私语, 想知道她到底发生了什么, 但没有人知道真相。 也许是哪个无赖伤了她的心? " + GetSexPhrase(" 也许是你吧, 船长? ", "");
			link.l1 = "" + GetSexPhrase("我怀疑不是 ", "") + "。 谢谢你, 我得走了。 ";
			link.l1.go = "exit";
			
			SetQuestHeader("UV");
			AddQuestRecord("UV", "1");
			pchar.questTemp.UV_Start = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("UV_Juli", "women_4", "woman", "woman", sti(pchar.rank), FRANCE, -1, false, "quest"));
			sld.name = StringFromKey("Neutral_6");
			sld.lastname = StringFromKey("Neutral_7");
			sld.City = "PortPax";
			ChangeCharacterAddressGroup(sld, "PortPax_town", "goto", "goto9");
			sld.dialog.filename = "Quest\MiniEvents\StolenMemory_dialog.c";
			sld.dialog.currentnode = "Juli";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_SetImmortal(sld, true);
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // 激活事件
			break;
        }
		//<—— 被盗的记忆
		
		//--> 伟大捕获的俘虏 andre39966
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		if (bOk1 || bOk2)
        {
			dialog.text = "听说渔夫皮埃尔.卡诺失踪了, 无影无踪。 两天前, 他出海后就再也没有消息。 他的妻子莉娅悲痛欲绝。 无论白天还是夜晚, 她都在码头守着, 眼睛盯着无尽的海水, 祈祷能看到她心爱的人的船帆。 ";
			link.l1 = "谢谢你, 我得走了。 ";
			link.l1.go = "exit";
			
			SetQuestHeader("VPVL");
			AddQuestRecord("VPVL", "1");
			pchar.questTemp.VPVL_Start = true;
			AddDialogExitQuest("VPVL_Gegerate_Lea");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // 激活事件
			break;
        }
		//<—— 伟大捕获的俘虏 
		//--> 贝齐.普莱斯的秘密
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		if (bOk1 || bOk2)
        {
			dialog.text = "船长, 你听说了吗? 我们酒馆来了个新女招待。 据说她是个大美人。 附近的男人都争先恐后地来一睹她的芳容。 但三天前, 她没来上班, 这让酒馆老板很生气, 因为自从她来了之后, 老板赚了很多钱。 听说他甚至愿意付钱给找到这个女孩的人。 ";
			link.l1 = "谢谢你, 我得走了。 ";
			link.l1.go = "exit";
			
			SetQuestHeader("TBP");
			AddQuestRecord("TBP", "1");
			pchar.questTemp.TBP_Start = true;
			pchar.questTemp.TBP_Tavern = true;
			AddLandQuestMark(CharacterFromID("Villemstad_tavernkeeper"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // 激活事件
			break;
        }
		//<—— 贝齐.普莱斯的秘密
		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 2 )
        srum = SelectRumourEx("townman", NPChar);
        else srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // 修复
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" 就是这样... ", " 你可能会觉得有趣。 ");
            posrep2 = " 嘿, 船长, 你有什么关于我们殖民地的消息要告诉吗? ";
            answ1 = RandPhraseSimple(RandSwear() + "这很有趣, " + GetFullName(NPChar) + "。 ",
                                 "那告诉我关于... ");
            answ2 = RandPhraseSimple(RandSwear() + "有趣! 还有一个问题我想问... ", "还有一个问题。 ");
            answ3 = RandPhraseSimple("嗯, 在我们这个世界里什么都可能发生。 抱歉, 但我没有什么特别的要告诉你。 ", "我很匆忙, 也许下次吧。 ");
            answ4 = "";
        }
        else
        {
            posrep1 = " 这里相当乏味。 所以如果真有什么事发生, 每个人都会谈论它。 ";
            posrep2 = " 没什么有趣的。 也许" + GetAddress_Form(NPChar) + "可能知道什么? ";
            answ1 = RandPhraseSimple("那告诉我关于... ", RandSwear() + "你什么都不知道! 好吧, 另一个话题... ");
            answ2 = RandPhraseSimple("不管怎样, 告诉我别的吧... ", "是的, 你没帮上什么忙, 还有什么可以和我分享的吗? ");
            answ3 = RandPhraseSimple("我怀疑我有什么有趣的事要告诉你。 ", "我很乐意, 但下次再谈吧。 ");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,
            srum+posrep1,
            srum+posrep2,
            RandPhraseSimple("唉, 没什么可告诉你的了, 让我过去。 ", "我受够了你的问题, 对不起, 我还有很多其他事情要做。 "), "block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,
                                            answ2,
                                            answ3,
                                            answ4,
                                            npchar, Dialog.CurrentNode);
		link.l1.go = "new question";
		link.l2 = RandPhraseSimple("谢谢, 我该走了。 ", "再见。 ");
		link.l2.go = "exit";
	break;
	
	///////////////////////////////////---边缘人物传闻---////////////////////////////////////////////
	case "rumours_marginal":	
		NextDiag.CurrentNode = "rumours";

		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 2 )
        srum = SelectRumourEx("townman", NPChar);
        else srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // 修复
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" 就是这样... ", " 你可能会觉得有趣。 ");
            posrep2 = " 嘿, 船长, 你有什么关于我们殖民地的消息要告诉吗? ";
            answ1 = RandPhraseSimple(RandSwear() + "这很有趣, " + GetFullName(NPChar) + "。 ",
                                 "那告诉我关于... ");
            answ2 = RandPhraseSimple(RandSwear() + "不管怎样, 告诉我别的吧... ", "是的, 你没帮上什么忙, 还有什么可以和我分享的吗? ");
            answ3 = RandPhraseSimple("嗯, 在我们这个世界里什么都可能发生。 抱歉, 但我没有什么特别的要告诉你。 ", "我很匆忙, 也许下次吧。 ");
            answ4 = "";
        }
        else
        {
            posrep1 = " 这里相当乏味。 所以如果真有什么事发生, 每个人都会谈论它。 ";
            posrep2 = " 没什么有趣的。 也许" + GetAddress_Form(NPChar) + "可能知道什么? ";
            answ1 = RandPhraseSimple("那告诉我关于... ", RandSwear() + "你什么都不知道! 好吧, 另一个话题... ");
            answ2 = RandPhraseSimple("不管怎样, 告诉我别的吧... ", "是的, 你没帮上什么忙, 还有什么可以和我分享的吗? ");
            answ3 = RandPhraseSimple("我怀疑我有什么有趣的事要告诉你。 ", "我很乐意, 但下次再谈吧。 ");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,
            srum+posrep1,
            srum+posrep2,
            RandPhraseSimple("唉, 没什么可告诉你的了, 让我过去。 ", "我受够了你的问题, 对不起, 我还有很多其他事情要做。 "), "block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,
            answ2,
            answ3,
            answ4,
            npchar, Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("谢谢, 我该走了。 ", "再见。 ");
		link.l2.go = "exit";
	break;
	
/////////////////////////////////////////////////---贵族传闻---////////////////////////////////////////////
	case "rumours_nobleman":	
        srum = SelectRumourEx("nobleman", NPChar);
		//--> 被盗的记忆
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
			if (bOk1 || bOk2){
				
			dialog.text = "港口周围传言说, 总督的侄女朱莉.德.阿尔马尼亚克已经变得不像从前了。 她曾经容光焕发。 充满活力, 现在却在街上漫无目的地走着, 脸上刻着明显的悲伤。 镇上的人窃窃私语, 想知道她到底发生了什么, 但没有人知道真相。 也许是哪个无赖伤了她的心? " + GetSexPhrase(" 也许是你吧, 船长? ", "");
			link.l1 = "" + GetSexPhrase("我怀疑不是 ", "") + "。 谢谢你, 我得走了。 ";
			link.l1.go = "exit";
			
			SetQuestHeader("UV");
			AddQuestRecord("UV", "1");
			pchar.questTemp.UV_Start = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("UV_Juli", "women_4", "woman", "woman", sti(pchar.rank), FRANCE, -1, false, "quest"));
			sld.name = StringFromKey("Neutral_6");
			sld.lastname = StringFromKey("Neutral_7");
			sld.City = "PortPax";
			ChangeCharacterAddressGroup(sld, "PortPax_town", "goto", "goto9");
			sld.dialog.filename = "Quest\MiniEvents\StolenMemory_dialog.c";
			sld.dialog.currentnode = "Juli";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_SetImmortal(sld, true);
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // 激活事件
			break;
        }
//<—— 被盗的记忆
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" 就是这样... ", " 你可能会觉得有趣。 ");
            posrep2 = " 嘿, 船长, 你有什么关于我们殖民地的消息要告诉吗? ";
            answ1 = RandPhraseSimple(RandSwear() + "这很有趣, " + GetFullName(NPChar) + "。 ",
                                 "那告诉我关于... ");
            answ2 = RandPhraseSimple(RandSwear() + "不管怎样, 告诉我别的吧... ", "是的, 你没帮上什么忙, 还有什么可以和我分享的吗? ");
            answ3 = RandPhraseSimple("嗯, 在我们这个世界里什么都可能发生。 抱歉, 但我没有什么特别的要告诉你。 ", "我很匆忙, 也许下次吧。 ");
            answ4 = "";
        }
        else
        {
            posrep1 = " 这里相当乏味。 所以如果真有什么事发生, 每个人都会谈论它。 ";
            posrep2 = " 没什么有趣的。 也许" + GetAddress_Form(NPChar) + "可能知道什么? ";
            answ1 = RandPhraseSimple("那告诉我关于... ", RandSwear() + "你什么都不知道! 好吧, 另一个话题... ");
            answ2 = RandPhraseSimple("不管怎样, 告诉我别的吧... ", "是的, 你没帮上什么忙, 还有什么可以和我分享的吗? ");
            answ3 = RandPhraseSimple("我怀疑我有什么有趣的事要告诉你。 ", "我很乐意, 但下次再谈吧。 ");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,
            srum+posrep1,
            srum+posrep2,
            RandPhraseSimple("我相信我已经表达清楚了 --我说完了。 ", "我受够了你的问题, 船长。 去找点更有意思的事做吧! "), "block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,
            answ2,
            answ3,
            answ4,
            npchar, Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("谢谢, 我该走了。 ", "再见。 ");
		link.l2.go = "exit";
	break;
	
/////////////////////////////////////////////////---贵族女性传闻---////////////////////////////////////////////
	case "rumours_noblegirl":	
        srum = SelectRumourEx("noblegirl", NPChar);
		//--> 被盗的记忆
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		if (bOk1 || bOk2)
        {
			dialog.text = "港口周围传言说, 总督的侄女朱莉.德.阿尔马尼亚克已经变得不像从前了。 她曾经容光焕发。 充满活力, 现在却在街上漫无目的地走着, 脸上刻着明显的悲伤。 镇上的人窃窃私语, 想知道她到底发生了什么, 但没有人知道真相。 也许是哪个无赖伤了她的心? " + GetSexPhrase(" 也许是你吧, 船长? ", "");
			link.l1 = "" + GetSexPhrase("我怀疑不是 ", "") + "。 谢谢你, 我得走了。 ";
			link.l1.go = "exit";
			
			SetQuestHeader("UV");
			AddQuestRecord("UV", "1");
			pchar.questTemp.UV_Start = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("UV_Juli", "women_4", "woman", "woman", sti(pchar.rank), FRANCE, -1, false, "quest"));
			sld.name = StringFromKey("Neutral_6");
			sld.lastname = StringFromKey("Neutral_7");
			sld.City = "PortPax";
			ChangeCharacterAddressGroup(sld, "PortPax_town", "goto", "goto9");
			sld.dialog.filename = "Quest\MiniEvents\StolenMemory_dialog.c";
			sld.dialog.currentnode = "Juli";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_SetImmortal(sld, true);
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // 激活事件
			break;
        }
		//<—— 被盗的记忆
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" 就是这样... ", " 你可能会觉得有趣。 ");
            posrep2 = " 嘿, 船长, 你有什么关于我们殖民地的消息要告诉吗? ";
            answ1 = RandPhraseSimple(RandSwear() + "这很有趣, " + GetFullName(NPChar) + "。 ",
                                 "那告诉我关于... ");
            answ2 = RandPhraseSimple(RandSwear() + "不管怎样, 告诉我别的吧... ", "是的, 你没帮上什么忙, 还有什么可以和我分享的吗? ");
            answ3 = RandPhraseSimple("嗯, 在我们这个世界里什么都可能发生。 抱歉, 但我没有什么特别的要告诉你。 ", "我很匆忙, 也许下次吧。 ");
            answ4 = "";
        }
        else
        {
            posrep1 = " 这里相当乏味。 所以如果真有什么事发生, 每个人都会谈论它。 ";
            posrep2 = " 没什么有趣的。 " + GetAddress_Form(NPChar) + "可能知道什么? ";
            answ1 = RandPhraseSimple("那告诉我关于... ", RandSwear() + "你什么都不知道! 好吧, 另一个话题... ");
            answ2 = RandPhraseSimple("不管怎样, 告诉我别的吧... ", "是的, 你没帮上什么忙, 还有什么可以和我分享的吗? ");
            answ3 = RandPhraseSimple("我怀疑我有什么有趣的事要告诉你。 ", "我很乐意, 但下次再谈吧。 ");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,
            srum+posrep1,
            srum+posrep2,
            RandPhraseSimple("我相信我已经表达清楚了 --我说完了。 ", "我受够了你的问题, 船长。 去找点更有意思的事做吧! "), "block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,
            answ2,
            answ3,
            answ4,
            npchar, Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("谢谢, 我该走了。 ", "再见。 ");
		link.l2.go = "exit";
	break;
	
	///////////////////////////////////////////---水手传闻---////////////////////////////////////////////
	case "rumours_sailor":	
		NextDiag.CurrentNode = "rumours";

		//--> 正义的边界
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		if (bOk1 || bOk2)
        {
			dialog.text = "两天前, 有人厚颜无耻地企图刺杀港口长官! 刺客在他的办公室门口埋伏, 但长官设法呼救。 一名火枪手迅速赶到并击伤了恶棍, 不过那家伙还是逃出了城门。 \n听说港口长官为这个无赖的脑袋开出了丰厚的赏金! 到目前为止, 还没有勇敢的人站出来。 你知道吗, 即使他出一千达布隆 --我也不会接受... ";
			link.l1 = "谢谢你, 我得走了。 ";
			link.l1.go = "exit";
			
			SetQuestHeader("GS");
			AddQuestRecord("GS", "1");
			pchar.questTemp.GS_Start = true;
			pchar.questTemp.GS_Portman = true;
			AddLandQuestMark(characterFromId("Beliz_portman"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // 激活事件
			break;
        }
		//<—— 正义的边界
		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 2) srum = SelectRumourEx("sailor", NPChar);
        else srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // 修复
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" 就是这样... ", " 你可能会觉得有趣。 ");
            posrep2 = " 嘿, 船长, 你有什么关于我们殖民地的消息要告诉吗? ";
            answ1 = RandPhraseSimple(RandSwear() + "这很有趣, " + GetFullName(NPChar) + "。 ",
                                 "那告诉我关于... ");
            answ2 = RandPhraseSimple(RandSwear() + "不管怎样, 告诉我别的吧... ", "是的, 你没帮上什么忙, 还有什么可以和我分享的吗? ");
            answ3 = RandPhraseSimple("嗯, 在我们这个世界里什么都可能发生。 抱歉, 但我没有什么特别的要告诉你。 ", "我很匆忙, 也许下次吧。 ");
            answ4 = "";
        }
        else
        {
            posrep1 = " 这里相当乏味。 所以如果真有什么事发生, 每个人都会谈论它。 ";
            posrep2 = " 没什么有趣的。 " + GetAddress_Form(NPChar) + "可能知道什么? ";
            answ1 = RandPhraseSimple("那告诉我关于... ", RandSwear() + "你什么都不知道! 好吧, 另一个话题... ");
            answ2 = RandPhraseSimple("不管怎样, 告诉我别的吧... ", "是的, 你没帮上什么忙, 还有什么可以和我分享的吗? ");
            answ3 = RandPhraseSimple("我怀疑我有什么有趣的事要告诉你。 ", "我很乐意, 但下次再谈吧。 ");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,
            srum+posrep1,
            srum+posrep2,
            RandPhraseSimple("唉, 没什么可告诉你的了, 让我过去。 ", "我受够了你的问题, 对不起, 我还有很多其他事情要做。 "), "block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,
            answ2,
            answ3,
            answ4,
            npchar, Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("谢谢, 我该走了。 ", "再见。 ");
		link.l2.go = "exit";
	break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case "rumours_habitue":
		//--> 奴隶商人
		if (pchar.questTemp.Slavetrader == "FindRatJamaica_H" && npchar.location == "FortOrange_tavern")
        {
			dialog.text = "(唱) 我们是流氓和无赖, 我们是恶棍和坏蛋; 喝光我的心肝宝贝, 哟嗬! 我们是魔鬼和害群之马, 我们真是坏蛋, 喝光我的心肝宝贝, 哟嗬!! 嘿, 伙计, 你好吗? 大海怎么样? ";
            link.l1 = "大海? 她还是老样子, 像个婊子。 又咸又湿。 告诉我, 我的伙伴去哪儿了, 就是不久前在这里租了个房间的那个? 他叫弗朗索瓦.贡捷。 ";
            link.l1.go = "Jamaica_ratH_1";
			break;
        }
		if (pchar.questTemp.Slavetrader == "EscapeSlaveVillemstad_H" && npchar.location == "Villemstad_tavern")
        {
			dialog.text = "(唱) 漂亮的姑娘, 你愿意和我一起走吗, 漂亮的姑娘, 你愿意躺在我身边吗? 我会在清晨离开你之前, 把你所有的丝带都卷起来! ";
            link.l1 = "喝一杯吧, 伙计! 大海怎么样? ";
            link.l1.go = "EscapeSlave_Villemstad_H1";
			break;
        }
		//<—— 奴隶商人
				
		//荷兰 Gambit, 对抗所有人
		if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "LetterToLucasSent" && npchar.location == "Villemstad_tavern")
        {
			dialog.text = "唉, 大海... 我真希望能像你一样! ";
            link.l1 = "没看出有什么问题, 朋友。 随时可以加入我的船员。 ";
            link.l1.go = "Lucas_Tavern";
			break;
        }
		//荷兰 Gambit
		
		//--> 寻找逃兵
		if (CheckAttribute(pchar, "GenQuest.FindFugitive") && sti(NPChar.nation) == PIRATE && !CheckAttribute(npchar, "quest.fugitive"))
        {
			dialog.text = LinkRandPhrase("你知道吗, 朗姆酒让男人成为朋友! 哈哈! ", "喝了足够的朗姆酒后, 即使是刽子手看起来也很可爱! 哈哈! ", "喝酒就睡觉, 睡觉就不犯罪! 朗姆酒和麦芽酒会带你上天堂, 所以喝吧, 该死的! 哈! ");
            link.l1 = "当然, 我们一起喝一杯... 告诉我, 好人, 你认识" + pchar.GenQuest.FindFugitive.Name + "吗? 他是我的老伙伴。 有人告诉我他搬到这里来了... ";
            link.l1.go = "FindFugitiveHb";
			break;
        }
//<—— 寻找逃兵
		
//--> 加勒比习俗
		if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy" && npchar.location == "Portobello_tavern")
		{
			dialog.text = "消息? 哈! 你还没听说吗? 我们的士兵抓获了一名法国间谍。 该死的冒牌货, 想装成商人, 但*嗝* --我们的指挥官是个硬汉! ";
            link.l1 = "真的吗! 那个法国佬想打探什么? ";
            link.l1.go = "trial_spy";
			break;
		}
		if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskAlcash") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
	    {
			dialog.text = "唉, " + GetAddress_Form(pchar) + " 我们生活在一个怎样的世界啊... 到处都是混蛋! ";
			link.l1 = "你什么意思, 伙计? ";
			link.l1.go = "Alcogol_GenQuest_Church_2_1";
			break;
		}
		//<—— 加勒比习俗
		
		//--> Sinistra 旧罪的漫长阴影
		if (CheckAttribute(pchar, "questTemp.DTSG_NightIskat") && npchar.city == "SentJons")
        {
			dialog.text = "你听说了吗? ! 我简直不敢相信! 著名的弗利特伍德船长在伦敦被残忍杀害了! 他追逐荣耀, 拥有一切, 却只找到了死亡... 如果他留在这里, 会更安全。 我想说, 有时候珍惜所拥有的, 胜过追逐金钱或地位, 记住我的话, 先生! ";
            link.l1 = "朋友, 你知道殖民地每个人的住处, 对吧? ";
            link.l1.go = "DTSG_NightIskat";
			break;
        }
		//<—— 旧罪的漫长阴影
		
		//--> Rebbebion, 任务'导航星'
		if (CheckAttribute(pchar, "questTemp.Beliz.AskForLatterAndSotta") && !CheckAttribute(npchar, "questTemp.Sotta") && !CheckAttribute(npchar, "questTemp.Lutter") && npchar.city == "Beliz")
		{
			link.l1 = "那么, 今天的英雄, 埃德加多.索塔船长。 人们怎么说他? 你又怎么看? 我一直期待见到这个人。 ";
			link.l1.go = "Sotta1";
			link.l2 = "伙计, 你为什么独自喝酒? 现在大家都在聚集观看'风袋马特'的绞刑。 ";
			link.l2.go = "Lutter1";
			break;
		}
		
		if (CheckAttribute(pchar, "questTemp.PZ.TortugaCitizensAsk") && !CheckAttribute(pchar, "questTemp.PZ.TortugaHabitueBlock") && npchar.city == "Tortuga")
		{
			link.l1 = "听着, 伙计, 我一直在找一个叫乔普.范德温克的人。 我需要给他捎个口信。 你知道他长什么样或关于他的任何事吗? ";
			link.l1.go = "Sepp1";
			break;
		}
		//<—— 任务'导航星'
		
		//--> 治愈的黑暗之水
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		if (bOk1 || bOk2)
        {
			dialog.text = "你听说了吗? 据说托马斯.莫里森的女儿已经卧床六个月了。 医生对她的病完全无能为力。 唯一能帮助她的是一个吉普赛女人, 她以能治愈重病的药水闻名。 但她断然拒绝为这个可怜的女孩做任何事。 ";
			link.l1 = RandPhraseSimple(RandSwear() + "这值得再喝一杯... ",
                                 "好吧, 我们再喝一次。 ");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("谢谢, 我该走了。 ",
									 "嗯, 该死的朗姆酒。 好吧, 我该走了, 祝你在这里玩得开心。 ");
			link.l2.go = "exit_sit";
			
			SetQuestHeader("DWH");
			AddQuestRecord("DWH", "1");
			pchar.questTemp.DWH_Start = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("DWH_gypsy", "gipsy_2", "woman", "towngirl", 10, PIRATE, -1, true, "citizen"));
			ChangeCharacterAddressGroup(sld, "SentJons_town", "goto", "goto1");
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "dwh_gypsy_0";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_SetLoginTime(sld, 07.00, 21.99);
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // 激活事件
		break;
		}
		//<—— 治愈的黑暗之水
		//--> 正义的边界
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		if (bOk1 || bOk2)
        {
			dialog.text = "两天前, 有人厚颜无耻地企图刺杀港口长官! 刺客在他的办公室门口埋伏, 但长官设法呼救。 一名火枪手迅速赶到并击伤了恶棍, 不过那家伙还是逃出了城门。 \n听说港口长官为这个无赖的脑袋开出了丰厚的赏金! 到目前为止, 还没有勇敢的人站出来。 请注意, 即使给一千达布隆 --我也不会拿脖子去冒险... ";
			link.l1 = RandPhraseSimple(RandSwear() + "这值得再喝一杯... ",
                                 "好吧, 我们再喝一次。 ");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("谢谢, 我该走了。 ",
									 "嗯, 该死的朗姆酒。 好吧, 我该走了, 祝你在这里玩得开心。 ");
			link.l2.go = "exit_sit";
			
			SetQuestHeader("GS");
			AddQuestRecord("GS", "1");
			pchar.questTemp.GS_Start = true;
			pchar.questTemp.GS_Portman = true;
			AddLandQuestMark(characterFromId("Beliz_portman"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // 激活事件
			break;
        }
		//<—— 正义的边界
		//--> 依法贸易
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		if (bOk1 || bOk2)
        {
			dialog.text = "听到消息了吗? ! 这简直是血腥的暴行! 酒馆里一滴朗姆酒或葡萄酒都没有了 --在这该死的炎热天气里, 人们该如何解渴? 客栈老板一周来一直用空洞的承诺敷衍我们, 说酒很快就会再来, 但一直什么都没有! 难道要我们渴到审判日吗? ";
			link.l1 = RandPhraseSimple(RandSwear() + "这值得再喝一杯... ",
                                 "好吧, 我们再喝一次。 ");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("谢谢, 我该走了。 ",
									 "嗯, 该死的朗姆酒。 好吧, 我该走了, 祝你在这里玩得开心。 ");
			link.l2.go = "exit_sit";
			
			SetQuestHeader("TPZ");
			AddQuestRecord("TPZ", "1");
			pchar.questTemp.TPZ_Start = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // 激活事件
			break;
        }
		//<—— 依法贸易
		//--> 旧账
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.OS_Start") && npchar.city == "PuertoPrincipe";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.OS_Start") && npchar.city == "PuertoPrincipe";
		if (bOk1 || bOk2)
        {
			dialog.text = "码头周围传言说我们的酒吧老板有麻烦了! 有人偷了他的杜松子酒! 请注意, 不只是一瓶, 而是一整桶 --这种酒在这些岛上别处找不到! 据说都是从欧洲运来的。 老狐狸不肯说他是为谁保管的, 但有一点可以肯定: 如果那桶酒不尽快找到, 这个可怜的家伙就要倒霉了! ";
			link.l1 = RandPhraseSimple(RandSwear() + "这值得再喝一杯... ",
                                 "好吧, 我们再喝一次。 ");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("谢谢, 我该走了。 ",
									 "嗯, 该死的朗姆酒。 好吧, 我该走了, 祝你在这里玩得开心。 ");
			link.l2.go = "exit_sit";
			
			SetQuestHeader("OS");
			AddQuestRecord("OS", "1");
			pchar.questTemp.OS_Start = true;
			pchar.questTemp.OS_Tavern_1 = true;
			AddLandQuestMark(characterFromId("PuertoPrincipe_tavernkeeper"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // 激活事件
			break;
        }
		//<—— 旧账
		//--> 被盗的记忆
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		if (bOk1 || bOk2)
        {
			dialog.text = "港口周围传言说, 总督的侄女朱莉.德.阿尔马尼亚克已经变得不像从前了。 她曾经容光焕发。 充满活力, 现在却在街上漫无目的地走着, 脸上刻着明显的悲伤。 镇上的人窃窃私语, 想知道她到底发生了什么, 但没有人知道真相。 也许是哪个无赖伤了她的心? " + GetSexPhrase(" 也许是你吧, 船长? ", "");
			link.l1 = RandPhraseSimple(RandSwear() + "这值得再喝一杯... ",
                                 "好吧, 我们再喝一次。 ");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("谢谢, 我该走了。 ",
									 "嗯, 该死的朗姆酒。 好吧, 我该走了, 祝你在这里玩得开心。 ");
			link.l2.go = "exit_sit";
			
			SetQuestHeader("UV");
			AddQuestRecord("UV", "1");
			pchar.questTemp.UV_Start = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("UV_Juli", "women_4", "woman", "woman", sti(pchar.rank), FRANCE, -1, false, "quest"));
			sld.name = StringFromKey("Neutral_6");
			sld.lastname = StringFromKey("Neutral_7");
			sld.City = "PortPax";
			ChangeCharacterAddressGroup(sld, "PortPax_town", "goto", "goto9");
			sld.dialog.filename = "Quest\MiniEvents\StolenMemory_dialog.c";
			sld.dialog.currentnode = "Juli";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_SetImmortal(sld, true);
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // 激活事件
			break;
        }
//<—— 被盗的记忆
//--> 在伟大捕获的囚禁中 andre39966
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		if (bOk1 || bOk2)
        {
			dialog.text = "有传言说渔民皮埃尔.卡诺消失得无影无踪。 两天前黎明时分, 他扬帆驶入蓝海, 此后再无踪迹。 他的妻子莉娅悲痛欲绝, 无论白昼还是夜晚, 她都在码头守望, 目光凝视着无尽的海面, 祈祷能瞥见爱人的船帆。 ";
			link.l1 = RandPhraseSimple(RandSwear() + "这值得再喝一杯... ",
                                 "好吧, 我们再喝一次。 ");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("谢谢, 我该走了。 ",
									 "嗯, 该死的朗姆酒。 好吧, 我该走了, 祝你在这里玩得开心。 ");
			link.l2.go = "exit_sit";
			
			SetQuestHeader("VPVL");
			AddQuestRecord("VPVL", "1");
			pchar.questTemp.VPVL_Start = true;
			AddDialogExitQuest("VPVL_Gegerate_Lea");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // 激活事件
			break;
        }
		//<—— 在伟大捕获的囚禁中
		//--> 贝茜.普莱斯的秘密
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		if (bOk1 || bOk2)
        {
			dialog.text = "船长, 你听说了吗? 我们酒馆新来了个女招待, 据说长得非常漂亮, 四面八方的男人都赶来一睹她的芳容。 但三天前她没来上班, 这让酒馆老板很恼火 --自从她来后老板赚了不少钱。 听说他甚至愿意付钱给找到这个女孩的人。 ";
			link.l1 = RandPhraseSimple(RandSwear() + "这值得再喝一杯... ",
                                 "好吧, 我们再喝一次。 ");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("谢谢, 我该走了。 ",
									 "嗯, 该死的朗姆酒。 好吧, 我该走了, 祝你在这里玩得开心。 ");
			link.l2.go = "exit_sit";
			
			SetQuestHeader("TBP");
			AddQuestRecord("TBP", "1");
			pchar.questTemp.TBP_Start = true;
			pchar.questTemp.TBP_Tavern = true;
			AddLandQuestMark(CharacterFromID("Villemstad_tavernkeeper"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // 激活事件
			break;
        }
		//<—— 贝茜.普莱斯的秘密
		
		Dialog.Text = LinkRandPhrase("嗯... 嗝! ", "啊, 好朗姆酒! ", "嗯... ") + SelectRumourEx("habitue", NPChar);
		link.l1 = RandPhraseSimple(RandSwear() + "这值得再喝一杯... ",
                                 "好吧, 我们再喝一次。 ");
		link.l1.go = "sit_3";
		link.l2 = RandPhraseSimple("谢谢, 我该走了。 ",
                                 "嗯, 该死的朗姆酒。 好吧, 我该走了, 祝你在这里玩得开心。 ");
		link.l2.go = "exit_sit";
	break;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "rumours_trader":
            if (!CheckAttribute(NPChar, "quest.repeat.rumours_trader") || NPChar.quest.repeat.rumours_trader!= 3 )
            strum = SelectRumourEx("trader", NPChar);
            else strum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // 修复
			Dialog.Text =  NPCStringReactionRepeat(strum, strum + " 是的, 没别的可说了。 ",
                strum + " 现在我该回去做生意了。 ", RandPhraseSimple("我已经告诉过你, 我没时间闲聊! ", "我是个大忙人, 没时间聊八卦! "), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(pcharrepphrase(RandSwear() + "有意思! 但我们切入正题吧", "谢谢, 还有一件事。 "), pcharrepphrase("" + GetSexPhrase("该死的", "有意思") + "! 故事讲得不错。 但我还有一个问题。 ", "我们别浪费时间了, 谈正事吧。 "),
pcharrepphrase(RandSwear() + "还有一件事, 说完我就走。 ", "你说得对, 时间就是金钱。 "), pcharrepphrase("总是只想着自己的利润! 好吧, 别生气。 ", "原谅我, 我们谈正事吧。 "), npchar, Dialog.CurrentNode);
			link.l1.go = "business";
			link.l2 = HeroStringReactionRepeat(NPCharRepPhrase(npchar, pcharrepphrase("再见, 你这个老酒鬼。 ",
"再见, " + GetAddress_FormToNPC(NPChar) + " " + GetFullName(npchar) + "。 "), pcharrepphrase("天哪! 别走远, 我很快就回来。 ", "很高兴见到你, " + GetAddress_FormToNPC(NPChar) + " " + GetFullName(npchar) + "! 再见! ")), NPCharRepPhrase(npchar, pcharrepphrase("开船! ", "再见! "), pcharrepphrase("嘿! 你在那儿藏了什么? 朗姆酒? 不是? 不管了, 我去喝点。 ", "抱歉, 我在城里有重要的事。 ")), NPCharRepPhrase(npchar, pcharrepphrase("嘿! 回头见! ", "我该走了, 再见, " + GetAddress_FormToNPC(NPChar) + " " + GetFullName(npchar) + "! "), pcharrepphrase("别跟我争论! 我不想这样! ", "我想我该检查一下我的船了, 再见, " + GetAddress_FormToNPC(NPChar) + " " + GetFullName(npchar) + "! ")), NPCharRepPhrase(npchar, pcharrepphrase("你怎么了, 伙计? 是我 --" +GetFullName(pchar)+ "! 打个盹, 我稍后再和你聊。 ", "恐怕在我再来之前你的肝脏就会要了你的命。 "), pcharrepphrase("数你的银币吧, 狡猾的狗! 回头见。 ", "很高兴见到你, " + GetAddress_FormToNPC(NPChar) + " " + GetFullName(npchar) + "! ")), npchar, Dialog.CurrentNode);
			link.l2.go = "Exit";
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "rumours_capitan":
			Dialog.Text = SelectRumourEx("capitan", NPChar);
			Link.l1 = RandPhraseSimple(RandSwear() + "有意思! 我还有一件事想问... ",
                                     "还有一个问题。 ");
			Link.l1.go = "quests";
			Link.l2 = RandPhraseSimple("谢谢, 我该走了。 ",
                                     "再见。 ");
			Link.l2.go = "exit";
			NextDiag.TempNode = "quests";
            NPChar.talk_date =  lastspeakdate();
		break;
		
		 case "rumours_landcaptain":
			Dialog.Text = SelectRumourEx("landcaptain", NPChar);
			Link.l1 = RandPhraseSimple(RandSwear() + "有意思! 我还有一件事想问... ",
                                     "还有一个问题。 ");
			Link.l1.go = "question";
			Link.l2 = RandPhraseSimple("谢谢, 我该走了。 ",
                                     "再见。 ");
			Link.l2.go = "exit";
			NextDiag.TempNode = "question";
            NPChar.talk_date =  lastspeakdate();
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "rumours_tavern":  // homo 03/08/06
				if(startHeroType == 4)
				{
					Dialog.Text = NPCStringReactionRepeat(LinkRandPhrase("你知道规矩, 信息就像房间。 食物或饮料一样 --是要花钱的, 一千比索。 ",
					"你知道规矩, 信息就像房间。 食物或饮料一样 --是要花钱的, 一千比索。 ",
					"你知道规矩, 信息就像房间。 食物或饮料一样 --是要花钱的, 一千比索。 "),
					"没别的可说了, 现在失陪, 我该走了。 ",
					"", "", "block", 1, npchar, Dialog.CurrentNode);
				 
					link.l1 = HeroStringReactionRepeat(RandPhraseSimple("其实我为什么要问呢? 我可以问别人, 抱歉打扰了。 ",
											 "其实我为什么要问呢? 我可以问别人, 抱歉打扰了。 "), "", "", "", npchar, Dialog.CurrentNode);
					link.l1.go = HeroStringReactionRepeat("rumours_tavern_no", "first time", "first time", "first time", npchar, Dialog.CurrentNode);//"rumours_tavern_no";
					NextDiag.CurrentNode = NextDiag.TempNode;
					if (makeint(pchar.money) >= 1000)
					{
						link.l2 = HeroStringReactionRepeat(RandPhraseSimple("我知道, 给你钱。 ", "我知道, 给你钱。 "),
						"", "", "" , npchar, Dialog.CurrentNode);
						link.l2.go = HeroStringReactionRepeat("rumours_tavern_yes", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
					}
					else
					{
						link.l2 =  HeroStringReactionRepeat("我没那么多钱。 ", "", "", "", npchar, Dialog.CurrentNode);
						link.l2.go = HeroStringReactionRepeat("rumours_tavern_no", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
					}
				}
				else
				{
					Dialog.Text = NPCStringReactionRepeat(LinkRandPhrase("信息要花钱, 1000比索, 我就把知道的都告诉你。 ",
					"我的记忆出了点问题, 1000八里亚尔可能帮我想起什么。 ",
					"我很乐意分享信息, 但你得付1000八里亚尔, 不还价。 "),
					"没别的可说了, 现在失陪, 我该走了。 ",
					"", "", "block", 1, npchar, Dialog.CurrentNode);
				 
					link.l1 = HeroStringReactionRepeat(RandPhraseSimple(RandSwear() + "我才不会为无聊的闲聊付钱。 ",
											 "我会想更好的办法花这些钱。 "), "换个话题吧。 ", "换个话题吧。 ", "换个话题吧。 ", npchar, Dialog.CurrentNode);
					link.l1.go = HeroStringReactionRepeat("rumours_tavern_no", "first time", "first time", "first time", npchar, Dialog.CurrentNode);//"rumours_tavern_no";
					NextDiag.CurrentNode = NextDiag.TempNode;
					if (makeint(pchar.money) >= 1000 )
					{
						link.l2 = HeroStringReactionRepeat(RandPhraseSimple("如果你告诉我有价值的信息, 就给你。 ", "如果你给我有价值的东西, 我就付钱。 "),
						 "", "", "" , npchar, Dialog.CurrentNode);
						link.l2.go = HeroStringReactionRepeat("rumours_tavern_yes", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
					}
					else
					{
						link.l2 =  HeroStringReactionRepeat("我没那么多钱。 ", "", "", "", npchar, Dialog.CurrentNode);
						link.l2.go = HeroStringReactionRepeat("rumours_tavern_no", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
					}
				}

		break;
		
		case "rumours_tavern_yes":
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation"))
			{
				bool bOk = (pchar.questTemp.Saga.BarbTemptation == "silk") || (pchar.questTemp.Saga.BarbTemptation == "give_silk");
				if (bOk && npchar.location == "Marigo_tavern" && !CheckAttribute(npchar, "quest.barbtemptation"))
				{
					AddMoneyToCharacter(pchar, -1000);
					Dialog.Text =  "我们的巡逻队最近摧毁了一艘法国走私船, 船长叫莫雷尔。 现在这个人被关在地牢里, 面临死刑。 我们的指挥官认为他的船上没有满载货物, 所以仍在设法找到它... 当指挥官找到失踪的货物时, 这个法国人就会死。 ";
					link.l1 = "有意思... 好吧, 拿钱。 还有别的要说吗? ";
					link.l1.go = "rumours_tavern";
					Saga_CreateMorelle(); // 设置莫雷尔
					npchar.quest.barbtemptation = "true";
					pchar.questTemp.Saga.BarbTemptation.Prison = "true";
					break;
				}
			}	
			// Addon-2016 Jason FMK-瓜德罗普
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "headhunter_portobello" && npchar.location == "portobello_tavern")
			{
				DelLandQuestMark(npchar);
				AddMoneyToCharacter(pchar, -1000);
				Dialog.Text =  "总督府举行了一场盛大的派对。 总督阁下的朋友卡洛斯.德.米利亚尔回来了。 他在海战中被俘, 但在一位法国中尉的帮助下成功逃脱。 卡洛斯不仅聪明, 而且非常慷慨。 在他的支持下, 这位中尉让.德诺现在成为了'萨里奥'号的船长。 据我所知, 他还被赠予了一个小种植园。 现在这个法国佬被叫做胡安! 多有趣的故事! ";
				link.l1 = "有趣... 好吧, 钱给你。 拿着。 还有别的要告诉我吗? ";
				link.l1.go = "rumours_tavern";
				pchar.questTemp.FMQG = "headhunter_juan";
				AddQuestRecord("FMQ_Guadeloupe", "10");
				pchar.quest.FMQG_Juanship.win_condition.l1 = "location";
				pchar.quest.FMQG_Juanship.win_condition.l1.location = "PortoBello";
				pchar.quest.FMQG_Juanship.function = "FMQG_CreateJuanship";
				break;
			}	
			// Addon-2016 Jason FMK-圣克里斯托弗
			if (CheckAttribute(pchar, "questTemp.FMQN") && pchar.questTemp.FMQN == "town" && npchar.location == "Marigo_tavern")
			{
				AddMoneyToCharacter(pchar, -1000);
				Dialog.Text =  "我们的指挥官已派出额外部队巡逻丛林, 并增加了城镇中的警卫人数。 有传言说英国人计划潜入菲利普斯堡, 释放被俘的军官。 ";
				link.l1 = "真的吗? 他们真有胆子玩这一手? 你说的到底是哪些军官? ";
				link.l1.go = "FMQN_r";
				break;
			}	
// Addon 2016-1 Jason 海盗系列
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_3" && npchar.location == "Havana_tavern")
			{
				AddMoneyToCharacter(pchar, -1000);
				Dialog.Text =  "前几天整个镇子像马蜂窝一样被搅乱了。 一艘军用纵帆船的军官在我的酒馆里喝得酩酊大醉, 差点强奸了一位已婚妇女, 接着又殴打了试图保护妻子的丈夫, 甚至用剑威胁他。 想想看, 这一切都发生在城镇卫兵面前! 正如人们所说, 强权即公理。 当这个混蛋施暴时, 士兵们只是转过身去。 \n但这个恶棍被一群商船水手缴了械 --谁能想到呢。 他们差点把他捆起来, 尽管这个混蛋还是逃了, 躲到了自己的船上。 指挥官和市长试图掩盖此事, 但愤怒的丈夫是一位受人尊敬的市民, 他向迭戈.德.托莱多阁下求助, 并在当地贵族中引起了骚动。 \n他们签发了逮捕该军官的 warrant。 有传言说, 有人建议他的船长带他离开港口, 把这个恶棍转移到其他地方。 然而, 纵帆船船长埃斯贝多.卡巴纳斯是个重名誉的人。 他一得知自己的军官所作所为, 就立即将其逮捕并送回岸上。 这个混蛋在可预见的未来将在监狱里腐烂 --要我说, 他活该。 也许之后他会被降为普通士兵并遭受鞭刑, 以儆效尤。 ";
				link.l1 = "等等, 你是说埃斯贝多.卡巴纳斯船长? 嗯... 这故事确实够刺激! 好吧, 钱是你应得的, 给你。 还有别的能告诉我吗? ";
				link.l1.go = "rumours_tavern";
				Mtraxx_CreateOfficer(); // 放置劣迹军官
				pchar.questTemp.Mtraxx = "jewelry_4";
				pchar.GenQuest.PrisonQuestLock = "true";
				AddQuestRecord("Roger_1", "7");
				DelLandQuestMark(characterFromId("Havana_tavernkeeper"));
				AddLandQuestMarkToPhantom("havana_prison", "havanaJailOff");
				break;
			}
			// Jason 莫纳岛
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "rumours" && rand(2) == 1)
			{
				AddMoneyToCharacter(pchar, -1000);
				Dialog.Text =  "据说有些罪犯被遗弃在某个无人居住的岛屿上! 据推测, 他们是如此残忍的怪物, 以至于刽子手和神父都不敢处理他们! 但为什么他们总是把这些人送到这里来? ! ";
				link.l1 = "嗯... 真有意思! 也许我该追踪他们并招募他们 --我总是需要孤注一掷的人... 你为什么脸色发白, 伙计? 我开玩笑的, 开玩笑的... 钱是你应得的 --给你。 你还听说其他值得注意的事吗? ";
				link.l1.go = "rumours_tavern";
				IslaMona_TerksCreateHimenes();
				break;
			}
            string RumText = SelectRumourEx("tavern", NPChar); // 修复
			
		    if(!RumourHasInformation(RumText))
            {
                Dialog.Text = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // 修复
				if(startHeroType == 4)
				{
					link.l1 = "原来你根本什么都不知道。 没想到你会这样骗我, 不太聪明啊。 好吧, 再见。 ";
				}
				else
				{
					link.l1 = RandPhraseSimple("一文不值的废物。 我一毛钱都不会付给你! 再见。 ", "你的信息一文不值, 所以你什么也得不到。 ");
				}
			    link.l1.go = "Exit";
			    NextDiag.CurrentNode = NextDiag.TempNode;
            }
            else
            {
                AddMoneyToCharacter(pchar, -1000);
                Dialog.Text = RumText;
				if(startHeroType == 4)
				{
					link.l1 = "真的吗? 很有趣, 谢谢。 好吧, 我得走了, 下次见。 ";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = RandPhraseSimple("谢谢, 拿钱吧。 还有别的要说吗? ", "好吧, 拿钱吧。 还有别的要说吗? ");
					link.l1.go = "rumours_tavern";
				}
    			NextDiag.CurrentNode = NextDiag.TempNode;    
            }
		break;

		case "rumours_tavern_no":
			if(startHeroType == 4)
			{
				Dialog.Text = "你本可以用些钱帮忙的。 不像你, 海伦, 我没有兄弟会男爵支持我。 ";
				link.l1 = "你有一整个酒馆, 而我是靠自己走到今天的。 好吧, 除了船。 大炮。 船员和男爵给我的补给。 好吧, 当我没说。 ";
				link.l1.go = "exit";
				NextDiag.CurrentNode = NextDiag.TempNode;
			}
			else
			{
				Dialog.Text = "听我说, 我需要养家糊口。 ";
				link.l1 = "换个话题吧。 ";
				link.l1.go = "first time";
				NextDiag.CurrentNode = NextDiag.TempNode;
				link.l2 = LinkRandPhrase("谢谢, 我该走了。 ",
										 "再见。 ", "拜拜。 ");
				link.l2.go = "Exit";
			}
		break;	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "rumours_poor":
			if (!CheckAttribute(NPChar, "quest.repeat.rumours_poor") || NPChar.quest.repeat.rumours_poor <= 1)
			{
				Dialog.Text = SelectRumourEx("poor", NPChar);
				Link.l1 = RandPhraseSimple(RandSwear() + "有意思。 还有一个问题... ",
										"嗯, 我再问点别的... ");
				Link.l1.go = "rumours_poor_2";
				Link.l2 = RandPhraseSimple("好吧, 再见。 ",
										"再见, 伙计。 ");
				Link.l2.go = "exit";
				NPChar.quest.repeat.rumours_poor = sti(NPChar.quest.repeat.rumours_poor) + 1;
			}
			else 
			{
				Dialog.Text = RandPhraseSimple("我知道的都告诉你了。 ", 
					"没什么可分享的了, 抱歉... ");
				Link.l1 = RandPhraseSimple("明白了。 再见。 ",
										"再见, 伙计... ");
				Link.l1.go = "exit";			
			}
            NPChar.talk_date = lastspeakdate();
		break;
        case "rumours_poor_2":
			if (NPChar.quest.repeat.rumours_poor <= 1)
			{
				Dialog.Text = SelectRumourEx("poor", NPChar);
				Link.l1 = RandPhraseSimple(RandSwear() + "有意思。 还有一个问题... ",
										"嗯, 我再问点别的... ");
				Link.l1.go = "rumours_poor";
				Link.l2 = RandPhraseSimple("好吧, 再见。 ",
										"再见, 朋友。 ");
				Link.l2.go = "exit";
				NPChar.quest.repeat.rumours_poor = sti(NPChar.quest.repeat.rumours_poor) + 1;
			}
			else 
			{
				Dialog.Text = RandPhraseSimple("我知道的都告诉你了。 ", 
					"没什么可分享的了, 抱歉... ");
				Link.l1 = RandPhraseSimple("明白了。 再见。 ",
										"了解。 再见, 伙计... ");
				Link.l1.go = "exit";			
			}
			NPChar.talk_date = lastspeakdate();
		break;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "rumours_LSC":
			if (CheckNPCQuestDate(NPChar, "quest.repeat.rumours"))
			{
				Dialog.Text = SelectRumourExSpecial("LSC", NPChar);
				Link.l1 = RandPhraseSimple("了解... ",
										"明白... ");
				Link.l1.go = "exit";
				SetNPCQuestDate(NPChar, "quest.repeat.rumours");
			}
			else  
			{
				Dialog.Text = NPCharSexPhrase(npchar, RandPhraseSimple("我知道的都告诉你了。 ", "抱歉, 没听到什么新消息... "), 
					RandPhraseSimple("我知道的都告诉你了。 ", "抱歉, 没听到什么新消息... "));
				Link.l1 = RandPhraseSimple("知道了, 再见。 ", "了解。 再见, 伙计。 ");
				Link.l1.go = "exit";			
			}
		break;
		
//Jason -------------灯塔看守人的传闻, 与酒馆相同但免费, 每天1条--------------------
		case "rumours_lighthouse": 
			Dialog.Text = NPCStringReactionRepeat(RandPhraseSimple("唉, 船长! 和你聊天总是很愉快。 独自待在这里有时很无聊... ", "我一个人住, 很少有访客, 所以总是很乐意聊天。 "), "喜欢聊天吗, 船长? 嗯, 我可能还有些事要告诉你... ", "下次来的时候带瓶朗姆酒, 有酒聊得更开心... ", "唉, 我知道的都告诉你了, 没什么补充的了。 ", "block", 1, npchar, Dialog.CurrentNode);
    		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("那就分享你的信息吧, 你知道我喜欢和人聊天... ", "告诉我! 就像人们说的, 谁拥有信息, 谁就拥有世界? "), "比如什么? ", "务必! 还有别的要分享吗? ", "好吧, 反正我们聊得很开心。 " , npchar, Dialog.CurrentNode);
    		link.l1.go = HeroStringReactionRepeat("rumours_lighthouse_yes", "rumours_lighthouse_void", "rumours_lighthouse_void", "exit", npchar, Dialog.CurrentNode);
		break;
		
		case "rumours_lighthouse_yes":
            RumText = SelectRumourEx("tavern", NPChar);
		    if(!RumourHasInformation(RumText))
            {
                Dialog.Text = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)];
                link.l1 = RandPhraseSimple("谢谢! 还有别的吗? ", "很有趣! 还有别的吗? ");

			    link.l1.go = "rumours_lighthouse";
				link.l2 = RandPhraseSimple("感谢! 聊得很愉快... ", "谢谢你告诉我! ");
			    link.l2.go = "exit";
			    NextDiag.CurrentNode = NextDiag.TempNode;
            }
            else
            {
                Dialog.Text = RumText;
    			link.l1 = RandPhraseSimple("谢谢! 还有别的吗? ", "很有趣! 还有别的吗? ");
    			link.l1.go = "rumours_lighthouse";
				link.l2 = RandPhraseSimple("感谢! 聊得很愉快... ", "谢谢你告诉我! ");
			    link.l2.go = "exit";
    			NextDiag.CurrentNode = NextDiag.TempNode;    
            }
		break;
		
		case "rumours_lighthouse_void":
                Dialog.Text = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)];
                link.l1 = RandPhraseSimple("谢谢! 还有别的吗? ", "很有趣! 还有别的吗? ");

			    link.l1.go = "rumours_lighthouse";
				link.l2 = RandPhraseSimple("感谢! 聊得很愉快... ", "谢谢你告诉我! ");
			    link.l2.go = "exit";
			    NextDiag.CurrentNode = NextDiag.TempNode;
		break;
//Jason ------------------------------------全职业2级邮政生成器-------------------------------------------
		case "Postcureer_LevelUp_ForAll":
			// 开始检查
			if (!CheckCharacterItem(pchar, pchar.questTemp.WPU.Current.Item))
			{
				dialog.text = "但包裹在哪里? 你没带着吗? ";
	        	link.l1 = "嗯... 我本应把它交给你, 但它... 说实话, 被人抢走了。 我无力反抗, 只好把包裹交给了那些袭击者。 ";
	        	link.l1.go = "Postcureer_LevelUp_complete_fail";
				break;
			}
			
			if (sti(pchar.questTemp.WPU.Postcureer.AgentChance) == 4)// 揭穿骗局
			{
				dialog.text = "嗯, 抱歉, 但这个包裹之前被打开过! 我一看就知道, 封条是重新盖的... ";
	        	link.l1 = "" + GetAddress_FormToNPC(NPChar) + ", 这是我在" + XI_ConvertString("Colony" + pchar.questTemp.WPU.Postcureer.StartCity + "Gen") + "港口办公室拿到的包裹, 我毫不知情... ";
	        	link.l1.go = "Postcureer_LevelUp_complete_Agentfail";
				break;
			}
			
			if (pchar.questTemp.WPU.Postcureer == "late")// 迟到
			{
				int iTime = makeint(GetQuestPastDayParam("questTemp.Postcureer.Late")) + 1;
				pchar.questTemp.WPU.Postcureer.Money = makeint(sti(pchar.questTemp.WPU.Postcureer.Money) / (sti(iTime) + 1));// 大幅降低报酬
				dialog.text = "我一直在等你, 但你晚了" + FindRussianDaysString(iTime) + "天! 你携带的信息已经变得没那么有用了... 当然还是有一些价值, 所以我会付给你" + FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)) + "。 请拿钱离开吧。 ";
	        	link.l1 = "谢谢, 我想是吧。 ";
	        	link.l1.go = "Postcureer_LevelUp_complete";
				pchar.quest.PostcureerTime_FullOver.over = "yes";// 移除第二个计时器
				pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count) - 1;// 迟到的行程不计入
				AddQuestRecord("Postcureer", "8");
				AddQuestUserData("Postcureer", "sDay", FindRussianDaysString(iTime));
				AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)));
				AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
				break;
			}
			
			if (pchar.questTemp.WPU.Postcureer == "lost")// 完全延误
			{
				dialog.text = "原来是你! 我等了你很久, 甚至采取措施去取回包裹。 把它给我吧, 不过说实话, 多亏了你的 timing, 我现在不需要了, 但我想自己留着。 \n如你所知, 我不能付你任何钱, 但我会确保恢复你的好名声。 ";
	        	link.l1 = "谢谢... 我想是吧。 很抱歉延误了, 真的很抱歉。 再见。 ";
	        	link.l1.go = "Postcureer_LevelUp_complete_bad";
				break;
			}
			dialog.text = "我一直在等你, 你来得正是时候, 你带来的信息会很有用。 请接受这份工作报酬 --" + FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)) + "。 感谢你的 timing。 ";
        	link.l1 = "不客气, 再见! ";
        	link.l1.go = "Postcureer_LevelUp_complete";
			pchar.quest.PostcureerTime_Over.over = "yes";// 移除计时器
			AddQuestRecord("Postcureer", "10");
		break;
		
		case "Postcureer_LevelUp_complete":
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Postcureer.Money));
			CloseQuestHeader("Postcureer");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
			pchar.questTemp.WPU.Postcureer = "complete";
			AddCharacterExpToSkill(pchar, "Sailing", 120);//航海
			AddCharacterExpToSkill(pchar, "Sneak", 120);//潜行
			AddCharacterExpToSkill(pchar, "Leadership", 150);//领导力
			AddCharacterExpToSkill(pchar, "Fortune", 150);//幸运
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), 2);
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
		
		case "Postcureer_LevelUp_complete_bad":
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			AddQuestRecord("Postcureer", "9");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Postcureer");
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), 33);
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
			pchar.questTemp.WPU.Postcureer = "complete";
			DialogExit();
		break;
		
		case "Postcureer_LevelUp_complete_fail":
			dialog.text = "唉, 我就知道会是这样... 我应该雇一艘军用信使船, 而不是民用船长... 不管怎样, " + GetAddress_Form(NPChar) + ", 你不是士兵, 所以没什么好责怪你的。 再见。 ";
			link.l1 = "再见, " + GetAddress_FormToNPC(NPChar) + "。 ";
			link.l1.go = "exit";
			if (pchar.questTemp.WPU.Postcureer == "begin") pchar.quest.PostcureerTime_Over.over = "yes";//移除计时器
			if (pchar.questTemp.WPU.Postcureer == "late") pchar.quest.PostcureerTime_FullOver.over = "yes";//移除第二个计时器
			CloseQuestHeader("Postcureer");
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), -2);
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)-3;//减少计数器
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
			pchar.questTemp.WPU.Postcureer = "complete";
		break;
		
		case "Postcureer_LevelUp_complete_Agentfail":
			dialog.text = "先生, 我认识" + XI_ConvertString("Colony" + pchar.questTemp.WPU.Postcureer.StartCity + "Gen") + "的港口主管, 他是个诚实的人。 此外, 他也没有理由打开包裹。 " + GetAddress_Form(NPChar) + ", 你是个骗子! 我一毛钱都不会付给你。 滚蛋! ";
			link.l1 = "嗯... ";
			link.l1.go = "Postcureer_LevelUp_complete_Agentfail_1";
		break;
		
		case "Postcureer_LevelUp_complete_Agentfail_1":
			if (pchar.questTemp.WPU.Postcureer == "begin") pchar.quest.PostcureerTime_Over.over = "yes";//移除计时器
			if (pchar.questTemp.WPU.Postcureer == "late") pchar.quest.PostcureerTime_FullOver.over = "yes";//移除第二个计时器
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			AddQuestRecord("Postcureer", "17");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Postcureer");
			ChangeCharacterComplexReputation(pchar,"nobility", -10);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), -2);
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)-3;//减少计数器
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.AgentChance");
			pchar.questTemp.WPU.Postcureer = "complete";
			DialogExit();
		break;
		
// <--邮政生成器2级

//Jason --> ---------------------------------倒霉小偷生成器--------------------------------------------
		case "Device_Common":
			dialog.text = "看起来像行走的垃圾。 一个流浪汉或乞丐。 说不清他具体去了哪里, 我也懒得跟踪。 ";
			link.l1 = "总比没有好。 谢谢你! 我该走了。 ";
			link.l1.go = "Device_Common_1";
		break;
		
		case "Device_Common_1":
			string sNation = pchar.GenQuest.Device.Shipyarder.Nation;
			sld = GetCharacter(NPC_GenerateCharacter("Device_poorman", "panhandler_"+(rand(5)+1), "man", "man", sti(pchar.rank)+5, sNation, 20, true, "quest"));
			SetFantomParamFromRank(sld, sti(pchar.rank)+5, true);         
			GiveItem2Character(sld, "slave_02");
			EquipCharacterbyItem(sld, "slave_02");
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, sNation+"_CITIZENS");
			sld.Dialog.Filename = "Quest\Other_Quests_NPC.c"; 
			sld.dialog.currentnode = "Device_poorman"; 
			sld.greeting = "Gr_poorman";
			switch (sti(pchar.GenQuest.Device.Shipyarder.Chance2))
			{
				case 0://在城里
					sld = characterFromId("Device_poorman");
					GetCharacterPos(pchar, &locx, &locy, &locz);
					ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.City +"_town", "goto", LAi_FindFarLocator("goto", locx, locy, locz));
				break;
				case 1://在城门外
					sld = characterFromId("Device_poorman");
					ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.City + "_ExitTown", "goto", "goto1");
				break;
				case 2://在海湾
					sld = characterFromId("Device_poorman");
					pchar.GenQuest.Device.Shipyarder.Shore = SelectQuestShoreLocation();
					ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.Shore, "goto", "goto1");
				break;
				case 3://在房子里
					sld = characterFromId("Device_poorman");
					pchar.GenQuest.Device.Shipyarder.Location = GetDeviceLocation(npchar); //确定位置
					ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.Location, "goto", "goto1");
					if (pchar.GenQuest.Device.Shipyarder.Location == "none" || CheckAttribute(pchar, "GenQuest.SeekSpy.Location"))//如果碰巧或接受了寻找间谍任务
					{
						pchar.GenQuest.Device.Shipyarder.Shore = SelectQuestShoreLocation();
						ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.Shore, "goto", "goto1");
					}
				break;
			}
			pchar.GenQuest.Device.Shipyarder = "inSeek";
			DialogExit();
			AddQuestRecord("Device", "9");
		break;
		//<—— 倒霉小偷生成器
		
		// Addon-2016 Jason FMK-圣克里斯托弗
		case "FMQN_r":
			DelLandQuestMark(npchar);
			Dialog.Text =  "不久前, 一艘英国船只在圣马丁水域被俘, 船上载有几名高级军官。 原本决定将他们送往威廉斯塔德, 但目前他们被关押在我们舒适的地牢里。 据说其中一名被俘士兵告诉我们的指挥官, 英国人打算派一支突袭队来营救这些军官。 这就是为什么我们的老指挥官严阵以待。 全副武装。 如果囚犯不见了, 他会被降为普通士兵, 他怎么能不准备呢! ";
			link.l1 = "有趣... 好吧, 钱给你。 拿着。 还有别的要告诉我吗? ";
			link.l1.go = "rumours_tavern";
			pchar.questTemp.FMQN = "governor";
			pchar.quest.FMQN_governor.win_condition.l1 = "location";
			pchar.quest.FMQN_governor.win_condition.l1.location = "Marigo_town";
			pchar.quest.FMQN_governor.function = "FMQN_ToGovernor";
			if (Whr_IsDay()) AddDialogExitQuest("FMQN_GetRumoursDay");
			else AddDialogExitQuest("FMQN_GetRumoursNight");
		break;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		市长任务, 潜入敌城
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "IntelligenceForAll":
            Dialog.Text = RandPhraseSimple("那好。 我把包裹准备好了, 随时可以运送。 拿着吧\n别再到这里来跟我说话了, 太危险了。 自己小心... ", 
				"嗯, 很好。 拿上包裹, 确保把它交给我们刚才谈到的那个人\n再见, 别再跟我说话了, 太危险了。 ");
            link.l1 = RandPhraseSimple("知道了。 再见... ", "再见, 祝你好运。 ");
			link.l1.go = "exit";
			pchar.GenQuest.Intelligence = "Execute";
			GiveItem2Character(pchar, "sicretLetter");
			AddCharacterExpToSkill(pchar, "Sneak", 200);
			ref rItem = ItemsFromID("sicretLetter");
			rItem.City = XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.Intelligence.MayorId)].city+"Gen")); 
			rItem.Mayor = GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)); 
			AddQuestRecord("MayorsQuestsList", "7");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.Intelligence.MayorId)].city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Voc")); // belamour gen
			AddQuestUserData("MayorsQuestsList", "sWho", GetWorkTypeOfMan(&characters[GetCharacterIndex(pchar.GenQuest.Intelligence.SpyId)], "Gen"));
			AddQuestUserData("MayorsQuestsList", "SpyName", GetFullName(&characters[GetCharacterIndex(pchar.GenQuest.Intelligence.SpyId)]));			
		break;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		光天化日之下的抢劫, 试图打开箱子
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "Man_FackYou":
			dialog.text = LinkRandPhrase("大白天的抢劫!!! 真的吗? 待在原地, 伙计... ", "嘿, 你在那里干什么? 好像有人想抢劫我。 你完了... ", "等等, 你要去哪? 小偷! 到此为止了, 伙计... ");
			link.l1 = LinkRandPhrase("该死! ", "卡兰巴! ", "该死的! ");
			link.l1.go = "fight_owner";
		break;
		case "fight_owner":
			LAi_SetOwnerTypeNoGroup(NPChar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			NextDiag.CurrentNode = "First time";
			DialogExit();
		break;
	}
}

string sRumourAboutOwners_CityRumour(string sCity, string sOwnerType) // 这里进行按城市分配
{
	string sRetRumour = "哦, 看来你发现了一个漏洞。 联系Jason并告诉他, 寻找‘Blackmark’。 ";
// 标志 - PChar.QuestTemp.RumoursAboutOwners.(sOwner) - 用于检查触发了哪个问题。 可用于任务
	switch(sCity)
	{
		case "Tortuga":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 0;
		break;
		
		case "PortRoyal":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 1;
		break;
		
		case "FortOrange":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 2);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 2;
		break;
		
		case "Beliz":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 3);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 3;
		break;
		
		case "PortoBello":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 4);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 4;
		break;
		
		case "Cartahena":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 5);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 5;
		break;
		
		case "Maracaibo":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 6);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 6;
		break;
		
		case "Caracas":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 7;
		break;
		
		case "Cumana":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 8;
		break;
		
		case "SantaCatalina":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 2);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 9;
		break;
		
		case "SanJuan":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 3);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 10;
		break;
		
		case "Marigo":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 4);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 11;
		break;
		
		case "Charles":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 5);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 12;
		break;
		
		case "SentJons":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 6);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 13;
		break;
		
		case "FortFrance":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 14;
		break;
		
		case "BasTer":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 15;
		break;
		
		case "Bridgetown":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 2);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 16;
		break;
		
		case "PortSpein":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 3);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 17;
		break;
		
		case "Havana":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 4);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 18;
		break;
		
		case "Villemstad":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 5);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 19;
		break;
		
		case "Santiago":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 6);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 20;
		break;
		
		case "PortPax":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 21;
		break;
		
		case "SantoDomingo":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 22;
		break;
	}
	
	return sRetRumour;
}

string sRumourAboutOwners_Init(string sOwnerType, int iRumourNum) // 居民传闻库。 可在不新开游戏的情况下修改
{
	
	string STR_MAYOR[MAX_RUMOURS_ABOUT_OWNERS]; // 总督
	STR_MAYOR[0] = "哦, 总督先生是个杰出的人。 他以卓越的能力管理我们的殖民地, 自建立以来从未发生过一次冲突\n他唯一的缺点是... 他... 嗯... 他相当节俭。 不过这可能只是另一种美德。 ";
	STR_MAYOR[1] = "哦, 总督先生是个杰出的人。 他以卓越的能力管理我们的殖民地, 自建立以来从未发生过一次冲突\n他唯一的缺点是... 他... 嗯... 他相当节俭。 不过这可能只是另一种美德。 ";
	STR_MAYOR[2] = "我们的总督是个好人, 但性格软弱。 如果他内心能坚定一点, 我们的商人本可以获得小额税收减免... 而且现在也该拨出补贴来修缮堡垒了。 ";
	STR_MAYOR[3] = "嗯... 他最近刚成为我们的总督。 他很年轻, 因此很有积极性。 有了他, 我们的殖民地正在蓬勃发展。 ";
	STR_MAYOR[4] = "我们的总督还比较年轻。 据说他是西班牙伯爵的无用小儿子, 被远远送到这里, 以免在家族中丢脸。 他到任时间不长, 还没来得及做出什么值得铭记的事。 ";
	STR_MAYOR[5] = "嗯... 他最近刚成为我们的总督。 他很年轻, 因此很有积极性。 有了他, 我们的殖民地正在蓬勃发展。 ";
	STR_MAYOR[6] = "嗯... 没什么... 我不能说他的坏话... ";
	
	string STR_TAVERNKEEPER[MAX_RUMOURS_ABOUT_OWNERS]; // 酒馆老板
	STR_TAVERNKEEPER[0] = "嗯, 我不会把我的财产托付给这个无赖。 别误会我, 但在我看来, 他是我们镇上最不可靠的人\n我听说他和海盗以及走私者有往来, 这些人经常出现在他的酒馆里。 ";
	STR_TAVERNKEEPER[1] = "我们能说他什么呢! 胆小, 而且也不是我认识的最聪明的人。 此外, 他贪财, 这就是为什么他总是陷入各种麻烦! 但他总是能及时了解所有新闻。 ";
	STR_TAVERNKEEPER[2] = "相当不错的家伙。 在他的酒馆里度过时光总是很愉快, 他还有着很棒的幽默感。 关于他最重要的一点是, 他把酒馆管理得井井有条, 防止喝醉的无赖骚扰善良的市民。 ";
	STR_TAVERNKEEPER[3] = "不可思议的人。 他不应该经营酒馆, 而应该成为情报办公室的线人。 有时看起来他真的知道我们镇上发生的一切。 这甚至让我感到害怕。 ";
	STR_TAVERNKEEPER[4] = "我不知道该告诉你什么。 一个男人。 经营着一家酒馆。 了解镇上及其居民的一切。 ";
	STR_TAVERNKEEPER[5] = "据说可以信赖他。 另一方面, 我听说他不喜欢不必要的风险, 做事情总是很谨慎。 是的, 而且他也不从事黑暗勾当。 ";
	STR_TAVERNKEEPER[6] = "他从父亲那里继承了这家酒馆。 他的父亲曾在离这里不远的另一个群岛的海岩岛上经营一家酒馆。 然后他的父亲搬到这里, 在这里建造了一家新酒馆, 现在由他的儿子经营。 ";
	
	string STR_SHIPYARDER[MAX_RUMOURS_ABOUT_OWNERS]; // 造船厂主
	STR_SHIPYARDER[0] = "建造船只。 我不知道。 他很安静, 很平和。 我想他是个好人。 ";
	STR_SHIPYARDER[1] = "建造船只。 我不知道。 他很安静, 很平和。 我想他是个好人。 ";
	STR_SHIPYARDER[2] = "一个好人, 但据说他太苛刻了。 经常责骂所有员工。 因此, 他们经常离职。 尽管如此, 他仍是一位出色的造船师。 ";
	STR_SHIPYARDER[3] = "他是个很有学问的人。 我听说他在英国学过造船, 然后在荷兰学过。 最后, 他来到了这里 --远离大都市, 在这个省群岛上\n人们说他与宗教裁判所有麻烦, 不得不逃到殖民地。 ";
	STR_SHIPYARDER[4] = "这位老人早就该退休了, 把机会让给一些新人。 他总是梦想着过去的时光, 当有人向他订购除了卡拉维尔帆船或大帆船之外的东西时, 他就会抱怨。 ";
	STR_SHIPYARDER[5] = "很棒的小伙子。 总是乐于助人。 我得说, 在这样一个糟糕的地方, 他建造的船只质量很好。 ";
	STR_SHIPYARDER[6] = "他曾是一名囚犯, 从欧洲流放到我们的殖民地, 直到人们发现他有造船的天赋。 在我们殖民地的造船厂, 在他的领导下建造了两艘 magnificent 双桅船之后, 他的罪行被赦免了, 现在他是我们社会的正式成员。 ";
	
	string STR_TRADER[MAX_RUMOURS_ABOUT_OWNERS]; // 店主
	STR_TRADER[0] = "我不能说他的坏话。 一个正派的市民, 经常光顾我们的小教堂。 人们似乎喜欢他。 从未听说有人对他生气。 ";
	STR_TRADER[1] = "他是我们总督的主要供应商, 这给他带来了不错的收入。 但他做事诚实。 嗯, 至少他没有被发现有任何丢脸的事情。 ";
	STR_TRADER[2] = "这个胖子在我们城市很受尊敬。 他的货物总是很好, 我不记得他有过一次欺骗别人的情况。 ";
	STR_TRADER[3] = "他真的一无是处。 做买卖, 但没有头脑。 有时一种商品缺货, 有时另一种, 有时一半的商品... 他甚至无法摆脱债务。 ";
	STR_TRADER[4] = "他不是个好人, 先生。 我听说他是前店主皮埃尔.蒂耶斯的得力助手, 但他搞垮了蒂耶斯的生意, 然后买下了这家店。 我不知道他卖的商品质量如何, 但作为一个人, 我非常不喜欢他。 ";
	STR_TRADER[5] = "哦! 他是个丑陋的人, 我不建议你和他有任何生意往来\n他让我们城市一半的居民都欠他的债! 而且他店里卖的商品质量总是很差。 ";
	STR_TRADER[6] = "没有人真正了解他。 他最近搬到这里, 立即开始了他的生意。 做生意诚实, 没有被抓到走私。 ";
	
	string sTempMayor = STR_MAYOR[iRumourNum];
	string sTempTavernkeper = STR_TAVERNKEEPER[iRumourNum];
	string sTempShipyarder = STR_SHIPYARDER[iRumourNum];
	string sTempTrader = STR_TRADER[iRumourNum];
	
	if(sOwnerType == "Mayor") return sTempMayor;
	if(sOwnerType == "TavernKeeper") return sTempTavernkeper;
	if(sOwnerType == "ShipYarder") return sTempShipyarder;
	if(sOwnerType == "Trader") return sTempTrader;
}

string GetDeviceLocation(ref npchar)
{
    aref	arCommon, arRld, arRld2;
    int	i, n, Qty, Qty2;
	string LocId; 
	string	storeArray [50];
	int howStore = 0;
    makearef(arRld, Locations[FindLocation(npchar.city + "_town")].reload);
	Qty = GetAttributesNum(arRld);
    if (CheckAttribute(pchar, "questTemp.jailCanMove.Deliver.locationId") || CheckAttribute(pchar, "GenQuest.SeekSpy.Location")) //如果接受了运送麻叶或寻找间谍的任务
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId && LocId != pchar.GenQuest.SeekSpy.Location)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId && LocId != pchar.GenQuest.SeekSpy.Location && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2" && arCommon.name != "reload1") // mitrokosta 修复
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	else
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2" && arCommon.name != "reload1") // mitrokosta 修复
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	if (howStore == 0) return "none";
	LocId = storeArray[hrand(howStore-1)];
	SetOpenDoorCommonLoc(npchar.city, LocId); //打开门
	for(n=0; n<MAX_CHARACTERS; n++)
	{
		if (CheckAttribute(&characters[n], "locations") && characters[n].locations == LocId) 
		{			
			characters[n].lifeDay = 0;
		}
	}
	return LocId;
}