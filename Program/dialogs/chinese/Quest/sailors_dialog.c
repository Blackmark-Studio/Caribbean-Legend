// 甲板上对话时士兵的台词
// 堡垒守卫和堡垒指挥官
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
        case "exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
        case "First time":
			dialog.text = "跟我们船长谈吧, 我没什么可告诉你的。 ";
			Link.l1 = "好吧。 ";
			Link.l1.go = "exit";
			
			NextDiag.TempNode = "first time";
		break;
		// 甲板上 -->
		case "On_Deck":
			dialog.text = "跟我们船长谈吧, 我没什么可告诉你的。 ";
			Link.l1 = "好吧。 ";
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Deck";
/*			
			// 第一个教堂生成器
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapWaitOnTavern"))
			{
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithSailors"))
				{
					dialog.text = "先生, 您在找人吗? ";
					Link.l1 = "是的, 伙计。 我能见见船长吗? ";
					Link.l1.go = "ChurchQuest1_Node1";
				}
				else
				{
					dialog.text = "如果您在找我们船长, 他刚上岸了。 ";
					Link.l1 = "好的";
					Link.l1.go = "exit";
				}
				break;
			}
*/			
			//--> eddy。 市长任务, 关闭甲板出口并提供所需节点
			if (CheckAttribute(pchar, "GenQuest.DestroyPirate") && pchar.GenQuest.CaptainId == "MQPirate")
			{
				dialog.text = RandPhraseSimple("哦, 你一个人来的。 哈! 那样的话去找我们船长吧, 跟他说说你那些可悲的事迹... ", "哇, 朋友, 你好像疯了。 去找我们船长, 他会跟你谈的。 ");
				Link.l1 = "太糟了... ";
				Link.l1.go = "exit";
			}
			//< —eddy。 市长任务, 关闭甲板出口
		break;
/*		
		case "ChurchQuest1_Node1":
			dialog.text = "您最好去港口找他。 ";
			Link.l1 = "谢谢你, 朋友。 ";
			Link.l1.go = "exit";
			NextDiag.TempNode = "On_Deck";
			PChar.GenQuest.ChurchQuest_1.CapWaitOnTavern = true; 
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithSailors"); // 不询问水手
		break;
*/		
		// 甲板上 <--
				
		// ugeen --> 与水手长对话生成器"匆忙的理由"
		case "On_MyShip_Deck":
			dialog.text = "嗯, 那可真是一团糟, 船长! 我们像往常一样在酒馆喝酒, 突然听到尖叫声。 我们跑出酒馆, 看到他们正试图逮捕你。 去他们的! 所以我们决定离开这个不友好的港口。 ";
			link.l1 = "是啊, 有些人对正义的理解确实有点奇怪。 ";
			link.l1.go = "On_MyShip_Deck_1";
		break;
		
		case "On_MyShip_Deck_1":
			if(pchar.questTemp.ReasonToFast == "speakSuccess_chain_A") 
			{
				// 没有地图
				dialog.text = "船长! 别这么担心! 很明显无法和平逃离, 所以我们决定拜访当地银行家, 检查他的箱子。 这是您的份额 - " + sti(pchar.questTemp.ReasonToFast.p9) + " 比索... ";
			}
			if(pchar.questTemp.ReasonToFast == "speakSuccess_chain_B")
			{
				// 拿到了地图
				GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
				dialog.text = "船长! 别这么担心! 很明显无法和平逃离, 所以我们决定拜访当地银行家, 检查他的箱子。 当铺箱里还有一把好剑。 这是您的份额 - " + sti(pchar.questTemp.ReasonToFast.p9) + " 比索和一把剑... ";
			}		
			link.l1 = "干得好, 伙计们! 干得好! 我为你们骄傲。 ";
			link.l1.go = "On_MyShip_Deck_End";
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.ReasonToFast.p9));			
			pchar.Ship.Crew.Morale = MORALE_MAX;
			chrDisableReloadToLocation = false; // 打开出口
			AddQuestRecord("ReasonToFast", "17");		
			AddQuestUserData("ReasonToFast", "sSex", GetSexPhrase("",""));		
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar,"TownEscape");
			DeleteAttribute(pchar,"questTemp.ReasonToFast");
			QuestOpenSeaExit();
		break;
		
		case "On_MyShip_Deck_End":
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		
		// 与水手长对话生成器"盖伦船行动"
		case "CapComission_OnShipDeck":
			dialog.text = "船长, 您的朋友逃跑了。 ";
			link.l1 = "什么朋友? ";
			link.l1.go = "CapComission_OnShipDeck1";
		break;
		
		case "CapComission_OnShipDeck1":
			dialog.text = "嗯, 就是您从地牢里救出来的那个朋友。 ";
			link.l1 = "你们怎么能把他弄丢了? ! ";
			link.l1.go = "CapComission_OnShipDeck2";
		break;
		
		case "CapComission_OnShipDeck2":
			dialog.text = "这不是我们的错, 船长。 他从厕所跳进海里了... 我们试图射击, 但那里太暗了... ";
			link.l1 = "该死! 你们真是太不像话了! 你们都将被 ashore 并送去砍甘蔗! 弄丢了这么重要的大人物! 难以置信! ";
			link.l1.go = "CapComission_OnShipDeck3";
		break;
		
		case "CapComission_OnShipDeck3":
			chrDisableReloadToLocation = false; // 打开出口
			AddQuestRecord("CaptainComission2", "25");	
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));			
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");	
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterComplexReputationABS(pchar, "authority", 1);
			DeleteAttribute(pchar,"TownEscape");
			DeleteAttribute(pchar,"GenQuest.CaptainComission.canSpeakBoatswain");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			QuestOpenSeaExit();		
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		// < —ugeen
		
		// 与水手长对话关于地牢情况
		case "Hold_GenQuest_OnShipDeck":
			dialog.text = "船长, 请原谅我们, 是我们的错 - 囚犯逃跑了。 ";
			link.l1 = "什么囚犯? 谁逃跑了? ";
			link.l1.go = "Hold_GenQuest_OnShipDeck1";
		break;
				
		case "Hold_GenQuest_OnShipDeck1":
			dialog.text = "嗯, 哦, 忘了他的名字, " + pchar.GenQuest.Hold_GenQuest.CapName + ", 对吗? ";
			link.l1 = "该死! 你们当时在看什么? ";
			link.l1.go = "Hold_GenQuest_OnShipDeck2";
		break;
		
		case "Hold_GenQuest_OnShipDeck2":
			dialog.text = "他从货舱出来, 从舷墙跳下去了。 我们没开枪以免发出噪音, 当我们准备长艇时, 他被该死的渔民救了。 ";
			link.l1 = "我为什么要付钱给你们! 鞭打值班长, 剥夺他一周的朗姆酒。 各就各位! 我们要起锚了... ";
			link.l1.go = "Hold_GenQuest_OnShipDeck3";
		break;
		
		case "Hold_GenQuest_OnShipDeck3":
			chrDisableReloadToLocation = false; // 打开出口
			sld = characterFromId(pchar.GenQuest.Hold_GenQuest.CapId);
			ReleasePrisoner(sld);			
			CloseQuestHeader("HoldQuest");	
			DeleteAttribute(pchar, "TownEscape");
			DeleteAttribute(pchar, "GenQuest.Hold_GenQuest.canSpeakSailor");
			DeleteAttribute(pchar, "GenQuest.Hold_GenQuest");
			QuestOpenSeaExit();					
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		
		case "Hold_GenQuest_OnShipDeck4":
			dialog.text = "问候您, 船长。 在您... 期间没有发生意外。 ";
			link.l1 = "好的, 好的, 我知道了... 我们的货舱里有个囚犯。 他的名字是" + pchar.GenQuest.Hold_GenQuest.CapName + "。 带几个人把他送到港口。 他现在自由了。 ";
			link.l1.go = "Hold_GenQuest_OnShipDeck5";
		break;
		
		case "Hold_GenQuest_OnShipDeck5":
			dialog.text = "他真的自由了吗? 我们要用长艇送他? ";
			link.l1 = "不是用该死的海龟... 我以为我已经说得很清楚了。 快点! 我们需要在退潮开始时起锚。 ";
			link.l1.go = "Hold_GenQuest_OnShipDeck3";
		break;
		
		// Warship 09.07.09 玛丽.塞莱斯特号甲板上与我们水手的集市 -->
		case "On_MaryCeleste_Deck":
			Dialog.text = "船长, 船上根本没有人! 情况非常不对劲... 汤米说他在驾驶舱看到一只猫, 那是唯一的活物... ";
			Link.l1 = "白痴, 猫没有灵魂。 看来他很久没去教堂了, 或者根本没去过。 你去过船长的船舱吗? 我需要航海日志。 ";
			Link.l1.go = "On_MaryCeleste_Deck_1";
		break;
		
		case "On_MaryCeleste_Deck_1":
			Dialog.text = "不, 它们有灵魂。 没有航海日志, 也没有任何导航仪器。 甚至没有一艘长艇... ";
			Link.l1 = "它们没有。 是被风暴卷走了吗? ";
			Link.l1.go = "On_MaryCeleste_Deck_2";
		break;
		
		case "On_MaryCeleste_Deck_2":
			Dialog.text = "它们有, 船长。 猫有灵魂。 船长, 长艇被砍断了, 我们在驾驶舱的地板上发现了一把剑。 它生锈了, 还有血迹。 给, 看看... ";
			Link.l1 = "别跟我说这些废话, 把它扔掉, 别再谈论猫了该死的! 我们检查一下货舱然后离开... 哦, 这里非常不对劲, 我他妈的不喜欢... ";
			Link.l1.go = "On_MaryCeleste_Last";
			NextDiag.TempNode = "On_MaryCeleste_Deck_SailorLast";
		break;
		
		case "On_MaryCeleste_Last":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetCitizenType(NPChar); // 让他在甲板上行走
			
			NPChar = GetRealShip(GetCharacterShipType(CharacterFromID("MaryCelesteCapitan")));
			NPChar.TurnRate = sti(PChar.QuestTemp.MaryCeleste.TurnRate); // 恢复机动性, 用于界面
			
			chrDisableReloadToLocation = false; // 打开出口
			
			LaunchTransferMain(PChar, CharacterFromID("MaryCelesteCapitan"), "MaryCelesteTransfer");
		break;
		
		case "On_MaryCeleste_Deck_SailorLast":
			switch(rand(2))
			{
				case 0:
					Dialog.text = "船长, 我对这个地方有种不好的感觉... 也许我们该离开了? ";
					Link.l1 = "是的... 去船上的小艇。 ";
					Link.l1.go = "exit";
				break;
				
				case 1:
					Dialog.text = "船长, 如果您打算把这艘奇怪的船开到港口, 我不想待在上面。 我宁愿自己跳进海里。 ";
					Link.l1 = "我不打算那样做... 我也有点害怕... ";
					Link.l1.go = "exit";
				break;
				
				case 2:
					Dialog.text = "也许我们该把它沉了, 船长? ";
					Link.l1 = "让住在这儿的死去水手的灵魂在我们的噩梦中拜访我们? ";
					Link.l1.go = "On_MaryCeleste_Deck_SailorLast_1";
				break;
			}
			
			NextDiag.TempNode = "On_MaryCeleste_Deck_SailorLast";
		break;
		
		case "On_MaryCeleste_Deck_SailorLast_1":
			Dialog.text = "上帝啊, 不! 船长... 您为什么这么说? ";
			Link.l1 = "别脸色苍白, 我开玩笑的... 去船上的小艇。 我想你毕竟是对的, 也许猫真的有灵魂... ";
			Link.l1.go = "exit";
		break;
		// < —玛丽.塞莱斯特号甲板上与我们水手的集市
		
		// 堡垒上 <--
        case "On_Fort":
			dialog.text = RandPhraseSimple("跟长官谈, 我没什么好说的。 ", "我在站岗, 所有问题去找堡垒指挥官。 ");
			Link.l1 = "好吧。 ";
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Fort";
		break;
		
		case "On_Fort_Head":
			dialog.text = RandPhraseSimple("我现在真的很忙, 别烦我。 ", "别打扰我工作, 没什么好谈的。 ");
			Link.l1 = "可惜... ";
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Fort_Head";
		break;
		
		case "Morgan_wait_you":
			Dialog.defAni = "dialog_stay1";
			Dialog.defCam = "1";
			Dialog.defSnd = "dialogs\0\017";
			Dialog.defLinkAni = "dialog_1";
			Dialog.defLinkCam = "1";
			Dialog.defLinkSnd = "dialogs\woman\024";
			Dialog.ani = "dialog_stay2";
			Dialog.cam = "1";
			Dialog.snd = "dialogs\0\009";

			dialog.text = RandPhraseSimple("摩根想跟你'说几句'... 他就在这儿, 甲板上某个地方。 ", "嘿, 去找摩根吧, 有坏消息等着您... ");
			Link.l1 = "好的。 ";
			Link.l1.go = "exit";

			NextDiag.TempNode = "Morgan_wait_you";
		break;
	}
}