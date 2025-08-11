void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("你竟敢来这里? ! 好大的胆子...", "那些蠢货怎么会让敌人入侵? ! 真让我想不通...", "好吧, 如果有个白痴在我的住所里乱逛, 说明我的守卫毫无用处..."), 
					LinkRandPhrase("你想干什么, 混蛋? ! 我的士兵已经追踪到你了, 你逃不掉的" + GetSexPhrase(", 肮脏的海盗", ", 肮脏的女海盗") + "! ", "肮脏的凶手, 离我的住所远点! 卫兵! ! ! ", "我不怕你, 混蛋! 你会被绞死的, 你逃不掉的..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("士兵不值钱...", "他们永远抓不到我。 "), 
					RandPhraseSimple("闭嘴, " + GetWorkTypeOfMan(npchar, "") + ", 否则我就割掉你的舌头, 塞进你的喉咙...", "我告诉你, 伙计: 安静地坐着, 你可能还能多活一天..."));
				link.l1.go = "fight";
				break;
			}
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
    			dialog.text = "敌人在我的住所里! 警报! ! ! ";
				link.l1 = "糟了! ";
				link.l1.go = "fight"; 
				break;
			}			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = TimeGreeting() + " 先生。 我是" + GetFullName(npchar) + ", 洛斯-特克斯矿场的指挥官, 该矿场归" + NationKingsName(npchar) + "所有。 现在, 请您告诉我您来访的目的, " + GetAddress_Form(NPChar) + "。 ";
				link.l1 = "这是我第一次来这里, 我想了解更多关于这个定居点及其法律的信息...";
				link.l1.go = "info";
				link.l2 = "只是想向您问好, 我这就走。 ";
				link.l2.go = "exit";
				npchar.quest.meeting = "1";
				break;
			}
			dialog.text = "又是你, 先生? 你还想要什么? ";
			link.l1 = "没什么。 我这就走。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "info":
			dialog.text = "我尊重这种纪律。 好吧, 既然你这么感兴趣, 我就给你介绍一下情况。 \n洛斯-特克斯矿场是西班牙王室的财产。 我们在这里开采银和金原矿, 以及银和金块。 所有的黄金和白银都属于西班牙, 并运往旧大陆。 \n矿场守卫森严, 一支精锐的西班牙士兵部队始终驻扎在这里。 海盗曾多次试图抢劫我们的矿场, 但后果总是很严重...对他们来说。 \n如你所见, 这是一个小镇。 我们有一家酒馆和一家商店。 你可以在那里以合理的价格购买金锭和银锭。 此外, 我们的军需官兼商店商人还可以卖给你其他有趣的金属和矿石。 \n我们的大多数工人都是罪犯, 但我们也有少量的黑人奴隶。 如你所见, 我们总是需要新的劳动力, 每天至少有一个该死的罪犯死去。 \n所以, 如果你给我们带来奴隶, 我们会用金块交换。 有关此类事宜, 请联系我们的首席工程师。 你可以在矿井里找到他。 \n在这里要规矩点。 不要决斗或打架, 不要试图偷任何东西, 尤其是金银。 我们这里没有监狱, 但我们有军事法庭。 \n差不多就是这些了。 遵守这些简单的规则, 你就不会有任何问题。 你可以在矿场内自由活动。 别忘了去酒馆, 经我许可, 他们提供某些...服务。 欢迎! ";
			link.l1 = "多谢! ";			
			link.l1.go = "exit";
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		// ============== 光天化日之下抢劫, 试图潜入宝箱 =========================
		case "Man_FackYou":
			dialog.text = "抢劫! ! ! 这是不可接受的! 准备好, " + GetSexPhrase("伙计", "姑娘") + "...";
			link.l1 = LinkRandPhrase("该死! ", "卡兰巴! ! ", "见鬼! ");
			link.l1.go = "PL_Q3_fight";
		break;
		
		case "fight":
            Pchar.quest.ArestInResidenceEnd.win_condition.l1          = "ExitFromLocation";
		    Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		    Pchar.quest.ArestInResidenceEnd.win_condition             = "ArestInResidenceEnd";
		    Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

			LAi_LockFightMode(Pchar, true); // 撒腿就跑
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		    LAi_group_Attack(NPChar, Pchar); // 对不死的梅拉不起作用 :(
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // 幽灵士兵
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;
	}
}