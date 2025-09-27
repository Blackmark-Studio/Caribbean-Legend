void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "你需要什么? ";
			link.l1 = "没什么。 ";
			link.l1.go = "exit";
		break;
		
		// Квeст "Длинныe тeни старых грeхов"
		case "DTSG_Knippel_1":
			dialog.text = "哦, 今天真是热啊。 你不妨在腿上绑上链弹跳进海里, 也好摆脱这闷热! ";
			link.l1 = "哈哈, 查理! ... 要我说, 这可真是极端的办法。 但我不介意喝上一杯解解渴 —今天确实太热了。 一起吗? ";
			link.l1.go = "DTSG_Knippel_2";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_Knippel_2":
			dialog.text = "和你喝几杯, 船长? 随时奉陪! ";
			link.l1 = "这才对嘛。 我们走! ";
			link.l1.go = "DTSG_Knippel_3";
		break;
		
		case "DTSG_Knippel_3":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "", "", "", "DTSG_BasTerTavern", -1);
			FreeSitLocator("BasTer_tavern", "sit_base2");
			FreeSitLocator("BasTer_tavern", "sit_front2");
		break;
		
		case "DTSG_Ohotnik_1":
			dialog.text = "嘿, 水手, 你看起来见多识广! 我们喝一杯, 聊聊故事如何? 我请客! ";
			link.l1 = "... ";
			link.l1.go = "DTSG_Ohotnik_1_Animation";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Knippel"));
			
		break;
		
		case "DTSG_Ohotnik_1_Animation":
			StartInstantDialogNoType("Knippel", "DTSG_Ohotnik_2", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_2":
			dialog.text = "呃, 不了, 伙计。 我是和船长一起来的。 去找别人吧。 ";
			link.l1 = "... ";
			link.l1.go = "DTSG_Ohotnik_2_Animation";
			LAi_tmpl_SetDialog(npchar, pchar, -1.0);
			locCameraFromToPos(5.57, 2.39, -4.63, true, 8.53, 2.07, 1.84);
		break;
		
		case "DTSG_Ohotnik_2_Animation":
			StartInstantDialog("DTSG_Ohotnik", "DTSG_Ohotnik_3", "Quest\CompanionQuests\Knippel.c");
			locCameraSleep(true);
		break;
		
		case "DTSG_Ohotnik_3":
			dialog.text = "哈, 像你这样的小人物也这么高傲, 只和船长喝酒? ";
			link.l1 = "... ";
			link.l1.go = "DTSG_Ohotnik_3_Animation";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Knippel"));
		break;
		
		case "DTSG_Ohotnik_3_Animation":
			StartInstantDialogNoType("Knippel", "DTSG_Ohotnik_4", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_4":
			dialog.text = "高傲? ! 我在皇家海军服役了几十年! 我战斗不是为了贵族, 而是为了你我这样的普通人, 为了确保各地的法律和秩序! ..";
			link.l1 = "... ";
			link.l1.go = "DTSG_Ohotnik_4_Animation";
			LAi_tmpl_SetDialog(npchar, pchar, -1.0);
		break;
		
		case "DTSG_Ohotnik_4_Animation":
			StartInstantDialog("DTSG_Ohotnik", "DTSG_Ohotnik_5", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_5":
			dialog.text = "你说大话, 但只和船长贵族喝酒! 看来海军只教了你如何好好擦大炮, 哈! ";
			link.l1 = "... ";
			link.l1.go = "DTSG_Ohotnik_5_Animation";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Knippel"));
		break;
		
		case "DTSG_Ohotnik_5_Animation":
			StartInstantDialogNoType("Knippel", "DTSG_Ohotnik_6", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_6":
			dialog.text = "我要把链弹塞进你喉咙里, 小子! ";
			link.l1 = "查理, 别那么激动, 不值得。 ";
			link.l1.go = "DTSG_Ohotnik_7";
			LAi_tmpl_SetDialog(npchar, pchar, -1.0);
		break;
		
		case "DTSG_Ohotnik_7":
			dialog.text = "让我来处理, 船长。 海军的荣誉岌岌可危, 我必须自己捍卫, 不能躲在任何人背后... ";
			link.l1 = "... ";
			link.l1.go = "DTSG_Ohotnik_8";
		break;
		
		case "DTSG_Ohotnik_8":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_FadeLong("DTSG_BasTerTavern_7", "");
		break;
		
		case "DTSG_Knippel_l0":
			dialog.text = "感谢你的等待, 船长。 希望我没有耽误太久。 ";
			link.l1 = "别担心。 你没受伤吧? 那个恶棍很厉害。 ";
			link.l1.go = "DTSG_Knippel_l1";
		break;
		
		case "DTSG_Knippel_l1":
			dialog.text = "不必担心, 船长。 重要的是他得到了应有的惩罚。 我从他身上捡到了一把钥匙... ";
			link.l1 = "... ";
			link.l1.go = "DTSG_Knippel_l2";
		break;
		
		case "DTSG_Knippel_l2":
			dialog.text = "我从他身上捡到了一把钥匙... 不知道是用来做什么的? ";
			link.l1 = "很简单, 查理... 用来开门或箱子, 哈哈。 我们应该和酒馆老板谈谈这个恶棍, 可能有用。 ";
			link.l1.go = "DTSG_Knippel_l3";
			AddItems(pchar, "Key1", 1);
			Log_info("查理给了你钥匙。 ");
			PlaySound("interface\important_item.wav");
		break;
		
		case "DTSG_Knippel_l3":
			DialogExit();
			
			bDisableCharacterMenu = false;
			InterfaceStates.Buttons.Save.enable = true;
			sld = CharacterFromID("Knippel");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			sld.location = "None";
			pchar.questTemp.DTSG_BasTerTavern = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
		break;
		
		case "DTSG_Knippel_20":
			dialog.text = "难以置信... ";
			link.l1 = "你和我想的一样吗, 查理? ";
			link.l1.go = "DTSG_Knippel_21";
		break;
		
		case "DTSG_Knippel_21":
			dialog.text = "我不知道你怎么想, 先生, 但我很惊讶这里有这么多钱 —他看起来像个普通人, 不是商人也不是贵族。 ";
			link.l1 = "其实不算多, 但你说得对。 让我惊讶的是这封奇怪的烧焦的信。 ";
			link.l1.go = "DTSG_Knippel_22";
		break;
		
		case "DTSG_Knippel_22":
			dialog.text = "是啊, 他可不聪明 —就像用链弹打坚固的船体。 他应该把信彻底毁掉。 ";
			link.l1 = "没错。 但这对我们没帮助 —我们不知道他是谁, 也不知道他在和谁通信。 我们走吧, 查理, 这里没什么可做的了。 ";
			link.l1.go = "DTSG_Knippel_23";
		break;
		
		case "DTSG_Knippel_23":			//КОНeЦ ЭТАПА 1
			DialogExit();
			ReturnOfficer_Knippel();

			AddQuestRecord("DTSG", "2");
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			pchar.questTemp.DTSG_Nastoroje1 = true;
		break;
		
		case "DTSG_Ohotnik_10":
			dialog.text = "这就是你吹嘘的皇家海军, 呸! ";
			link.l1 = "查理是个善良正直的人。 而且他是炮手, 不是海军陆战队员。 ";
			link.l1.go = "DTSG_Ohotnik_11";
		break;
		
		case "DTSG_Ohotnik_11":
			dialog.text = "炮手? ! 所以正如我所说, 哈哈哈哈! 别瞪我 —你早该知道招进船员的是什么人。 ";
			link.l1 = "你早该知道自己在惹谁。 ";
			link.l1.go = "DTSG_Ohotnik_Agressia_1";
			link.l2 = "你还活着只是因为你公平获胜, 所以管好你那张臭嘴, 滚出去。 ";
			link.l2.go = "DTSG_Ohotnik_Otpustil_1";
		break;
		
		case "DTSG_Ohotnik_Otpustil_1":
			dialog.text = "嗯, 我以为接下来得和你打一架。 很高兴听到荣誉对你来说还有意义。 ";
			link.l1 = "对查理来说也不只是空话。 但至于你, 我表示怀疑。 不管怎样, 现在不重要了。 ";
			link.l1.go = "DTSG_Ohotnik_Otpustil_2";
		break;
		
		case "DTSG_Ohotnik_Otpustil_2":			//ПРОВАЛ ЭТАПА 1
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			npchar.lifeday = 0;
			LAi_LocationDisableOfficersGen("BasTer_tavern", false);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			bDisableCharacterMenu = false;
			InterfaceStates.Buttons.Save.enable = true;
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar, "authority", -3);
			ChangeCharacterComplexReputation(pchar, "fame", -3);	
		break;
		
		case "DTSG_Ohotnik_Agressia_1":
			dialog.text = "我惹了谁, 一个娇生惯养的弱者? ! 你看过自己稀疏的胡子吗? ..";
			link.l1 = "你确实知道如何激怒别人... 把怒火发泄在你身上会更痛快。 ";
			link.l1.go = "DTSG_Ohotnik_Agressia_2";
		break;
		
		case "DTSG_Ohotnik_Agressia_2":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			sld = CharacterFromID("DTSG_Ohotnik");
			DeleteAttribute(sld, "CantLoot");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_Ohotnik_Agressia_3");
			LAi_SetFightMode(pchar, true);
		break;
		
		case "DTSG_PiterAdams_1":
			dialog.text = "等等, 船长。 我看你是位值得尊敬的高尚人士, 能帮我个忙吗? 这关乎荣誉。 ";
			link.l1 = "也许可以, 但什么事? 为什么找我? 这里有很多高尚的人。 顺便问一下, 我有幸和谁说话? ";
			link.l1.go = "DTSG_PiterAdams_2";
			InterfaceStates.Buttons.Save.enable = true;
		break;
		
		case "DTSG_PiterAdams_2":
			dialog.text = "彼得。 彼得.亚当斯。 我看得出你不是典型的娇生惯养的老家族后裔, 而是个可靠。 稳当的人。 ";
			link.l1 = "哦, 先生, 你该看看我刚到加勒比海时的样子。 但请说吧, 你需要什么帮助? ";
			link.l1.go = "DTSG_PiterAdams_3";
		break;
		
		case "DTSG_PiterAdams_3":
			dialog.text = "你能... 代表我进行一场决斗吗, 先生? 一个当地的麻烦制造者, 拉尔夫.法格尔, 侮辱了我的妻子。 他还当众骚扰她。 就在我面前。 你能想象吗? ";
			link.l1 = "挑战决斗却躲在别人背后, 这没什么荣誉可言。 尤其是当这不只是你个人的荣誉, 而是一位女性, 你妻子的荣誉。 你不这么认为吗, 亚当斯? 为什么你不能自己为妻子而战? ";
			link.l1.go = "DTSG_PiterAdams_4";
		break;
		
		case "DTSG_PiterAdams_4":
			dialog.text = "你说得对, 完全正确。 但我最近患了严重的热病, 几乎站不稳... \n不得不承认, 向你提出这样的要求并不容易。 如果他侮辱的是我, 我会忍受。 但当我妻子的荣誉受到威胁时就不行! 我不是懦夫, 先生。 我曾在皇家海军服役, 和罗伯特.布莱克同船航行过! ";
			link.l1 = "我... ";
			link.l1.go = "DTSG_PiterAdams_5";
		break;
		
		case "DTSG_PiterAdams_5":
			StartInstantDialog("Knippel", "DTSG_PiterAdams_6", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_PiterAdams_6":
			dialog.text = "我们会帮你。 ";
			link.l1 = "查理? ..";
			link.l1.go = "DTSG_PiterAdams_7";
			CharacterTurnByChr(npchar, characterFromId("DTSG_PiterAdams"))
		break;
		
		case "DTSG_PiterAdams_7":
			dialog.text = "他是个值得尊敬的人, 船长。 如果我说的不是真的, 就让炮弹把我打入永恒! 和布莱克上将一起服役的都是伟大的人。 他们并肩作战, 让普通人不再受压迫\n多亏了他, 牙买加才从西班牙的暴政中解放出来! ";
			link.l1 = "即使如此, 我也不允许我的船员打断我或替我做决定。 明白了吗? ";
			link.l1.go = "DTSG_PiterAdams_8";
			link.l2 = "我明白, 真的。 不过我还没来得及回应。 以后尽量不要这么急躁, 打断我, 好吗? ";
			link.l2.go = "DTSG_PiterAdams_8";
			CharacterTurnByChr(npchar, pchar)
		break;
		
		case "DTSG_PiterAdams_8":
			dialog.text = "我告诉你, 船长 - 如果您不帮助这个人, 老查理就会放下一切, 亲自为他决斗, 让我当场受罚! ";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje1"))
			{
				link.l1 = "安静点, 我没说拒绝帮助。 对吗, 亚当斯先生? ";
				link.l1.go = "DTSG_PiterAdams_Nastoroje_1";
			}
			else
			{
				link.l1 = "老实说, 查理, 你让我看起来像个懦夫。 而我从不是懦夫。 你应该知道这一点。 ";
				link.l1.go = "DTSG_PiterAdams_NN_1";
			}
		break;
		
		case "DTSG_PiterAdams_NN_1":
			dialog.text = "呃, 抱歉, 船长, 我太激动了。 ";
			link.l1 = "没关系。 但请控制好自己, 好吗? ";
			link.l1.go = "DTSG_PiterAdams_NN_1_1";
		break;
		
		case "DTSG_PiterAdams_NN_1_1":
			StartInstantDialog("DTSG_PiterAdams", "DTSG_PiterAdams_NN_2", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_PiterAdams_NN_2":
			dialog.text = "";
			link.l1 = "我会为你决斗, 亚当斯先生。 ";
			link.l1.go = "DTSG_PiterAdams_NN_3";
		break;
		
		case "DTSG_PiterAdams_NN_3":
			dialog.text = "谢谢你, 先生! 上帝保佑你! ";
			link.l1 = "也保佑护国公, 对吧, 亚当斯先生? 别担心, 查尔斯.德莫尔从不把诚实的人置于困境。 ";
			link.l1.go = "DTSG_PiterAdams_NN_4";
		break;
		
		case "DTSG_PiterAdams_NN_4":
			dialog.text = "我们很感激, 德莫尔先生, 先生! 你愿意来和简还有我一起吃晚餐吗? ";
			link.l1 = "嗯, 我... ";
			link.l1.go = "DTSG_PiterAdams_NN_5";
		break;
		
		case "DTSG_PiterAdams_NN_5":
			dialog.text = "我坚持! ";
			link.l1 = "好吧, 既然你坚持。 谢谢你, 彼得。 请带路。 ";
			link.l1.go = "DTSG_PiterAdams_IdemKDomu";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_1":
			StartInstantDialog("DTSG_PiterAdams", "DTSG_PiterAdams_Nastoroje_2", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_PiterAdams_Nastoroje_2":
			dialog.text = "当然是真的, 先生! 你愿意和简一起过来, 旅途后休息一下吗? ";
			link.l1 = "谢谢你, 但利用你的盛情合适吗? ";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_3";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_3":
			dialog.text = "哦, 恰恰相反, 船长, 如果您不来, 我们会感到受冒犯。 ";
			link.l1 = "那我怎能拒绝? 你先请, 彼得! ";
			link.l1.go = "DTSG_PiterAdams_IdemKDomu";
		break;
		
		case "DTSG_PiterAdams_IdemKDomu":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "houseF1", "DTSG_PiterAdams_VDom", -1);
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, npchar, "", -1);
			sld = CharacterFromID("Knippel");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_1":
			dialog.text = "我们到了! 请进。 ";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje1"))
			{
				link.l1 = "谢谢。 我能和简谈谈吗? 问问她是怎么发生的 —我需要所有细节。 ";
				link.l1.go = "DTSG_PiterAdamsRyadomSDomom_2";
			}
			link.l2 = "我深表歉意, 但经过再三考虑, 我必须拒绝。 我得准备即将到来的决斗。 顺便问一下, 决斗定在何时何地? ";
			link.l2.go = "DTSG_PiterAdamsRyadomSDomom_4";
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_2":
			dialog.text = "当然可以, 先生。 我们都很乐意和你交谈, 回答所有问题。 请跟我来。 ";
			link.l1 = "谢谢你, 彼得。 ";
			link.l1.go = "DTSG_PiterAdamsRyadomSDomom_3";
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_3":
			DoQuestReloadToLocation("PortPax_houseF1", "reload", "reload1", "DTSG_PiterAdams_VDom_2");
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_4":
			dialog.text = "真遗憾! 但你说得对, 当然应该充分准备。 两小时后。 就在城门外。 ";
			link.l1 = "明白了, 谢谢。 结束后我会很高兴过来。 到时见! ";
			link.l1.go = "DTSG_PiterAdamsRyadomSDomom_5";
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_5":
			DialogExit();
			bDisableFastReload = false;
			chrDisableReloadToLocation = false; 
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "", "", "", "", -1);
			npchar.location = "None";
			
			sld = CharacterFromID("Knippel");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			sld.Dialog.CurrentNode = "Knippel_officer";
			sld.location = "None";
			
			PChar.quest.DTSG_PoP_DuelTime.win_condition.l1 = "Timer";
			PChar.quest.DTSG_PoP_DuelTime.win_condition.l1.date.hour = sti(GetTime() + 2);
			PChar.quest.DTSG_PoP_DuelTime.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
			PChar.quest.DTSG_PoP_DuelTime.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			PChar.quest.DTSG_PoP_DuelTime.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
			PChar.quest.DTSG_PoP_DuelTime.win_condition = "DTSG_PoP_DuelTime";
			
			PChar.quest.DTSG_PoP_Duel.win_condition.l1 = "location";
			PChar.quest.DTSG_PoP_Duel.win_condition.l1.location = "PortPax_ExitTown";
			PChar.quest.DTSG_PoP_Duel.win_condition = "DTSG_PoP_Duel";
			
			AddQuestRecord("DTSG", "3");
		break;
		
		case "DTSG_JeinAdams_1":
			dialog.text = "欢迎! 亲爱的, 你没告诉我要带客人来 —我该好好准备一下。 ";
			link.l1 = "谢谢你, 夫人, 我们不会久留。 查尔斯.德莫尔, 为你效劳。 我答应和你丈夫一起听听你的故事。 告诉我是怎么发生的。 ";
			link.l1.go = "DTSG_JeinAdams_2";
		break;
		
		case "DTSG_JeinAdams_2":
			dialog.text = "哦, 太可怕了! 拉尔夫喝得酩酊大醉。 他开始在邻居面前骚扰我, 甚至在彼得面前, 说些下流话... ";
			link.l1 = "他具体对你说了什么? ";
			link.l1.go = "DTSG_JeinAdams_3";
		break;
		
		case "DTSG_JeinAdams_3":
			dialog.text = "我不好意思说。 然后他清醒了, 并且... ";
			link.l1 = "道歉并请求取消决斗, 也许? ";
			link.l1.go = "DTSG_JeinAdams_4";
		break;
		
		case "DTSG_JeinAdams_4":
			dialog.text = "一次也没有。 ";
			link.l1 = "我为你难过。 如果允许, 夫人, 我想再问一件事。 ";
			link.l1.go = "DTSG_JeinAdams_5";
		break;
		
		case "DTSG_JeinAdams_5":
			dialog.text = "什么事, 先生? ";
			link.l1 = "是什么样的生活境遇和磨难迫使你和丈夫住在这里? 在任何英国城市, 鉴于你丈夫的功绩, 你早就该让拉尔夫知道自己的位置了。 ";
			link.l1.go = "DTSG_JeinAdams_6";
		break;
		
		case "DTSG_JeinAdams_6":
			StartInstantDialog("Knippel", "DTSG_JeinAdams_7", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_JeinAdams_7":
			dialog.text = "对不起, 先生, 但你怎么敢? ! 如果你不是我的船长, 我就会抓起链弹好好揍你一顿! \n你不仅不信任亚当斯先生这样值得尊敬的人, 还在一位身处困境的女士面前嘲笑她... ";
			link.l1 = "你听到我嘲笑女士了吗? 没有? 那就别诽谤我。 我们的人可以帮助他们, 所以我才问。 ";
			link.l1.go = "DTSG_JeinAdams_8a";
			link.l1 = "冷静点, 查理! 你怎么能... 我只是想多了解简和彼得的艰辛, 同情他们。 在英国殖民地, 他们现在肯定已经得到帮助了。 ";
			link.l1.go = "DTSG_JeinAdams_8b";
		break;
		
		case "DTSG_JeinAdams_8a":
			dialog.text = "生活总有很多可能... 海难。 或者某人的诽谤, 有时甚至会迫使如此诚实的人屈辱地躲藏起来\n如果你如此多疑 —可以和邻居谈谈。 我相信他们会证实每一句话。 但老查理不会背后议论别人的苦难! ";
			link.l1 = "你没听到吗? 我说我会帮助这些人。 ";
			link.l1.go = "DTSG_JeinAdams_9";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
		break;
		
		case "DTSG_JeinAdams_8b":
			dialog.text = "生活总有很多可能... 海难。 或者某人的诽谤, 有时甚至会迫使如此诚实的人屈辱地躲藏起来\n如果你如此多疑 —可以和邻居谈谈。 我相信他们会证实每一句话。 但老查理不会背后议论别人的苦难! ";
			link.l1 = "你没听到吗? 我说我会帮助这些人。 ";
			link.l1.go = "DTSG_JeinAdams_9";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterComplexReputation(pchar, "authority", -2);
		break;
		
		case "DTSG_JeinAdams_9":
			StartInstantDialog("DTSG_PiterAdams", "DTSG_JeinAdams_10", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_JeinAdams_10":
			dialog.text = "我们从心底感谢你。 我们会在祈祷中记住你。 ";
			link.l1 = "那很好。 顺便说一下, 关于我们的事。 你把决斗安排在何时何地, 亚当斯先生? ";
			link.l1.go = "DTSG_JeinAdams_11";
		break;
		
		case "DTSG_JeinAdams_11":
			dialog.text = "城门外, 先生。 两小时后。 ";
			link.l1 = "我会到的。 等我的好消息。 别提前为我点安息蜡烛! ";
			link.l1.go = "DTSG_JeinAdams_13";
		break;
		
		case "DTSG_JeinAdams_13":
			DoQuestReloadToLocation("PortPax_town", "reload", "houseF1", "DTSG_PiterAdams_IsDoma");
		break;
		
		case "DTSG_Knippel_30":
			dialog.text = "你在烦恼什么吗, 船长? 你看起来若有所思。 ";
			link.l1 = "你知道, 是的。 亚当斯的故事有些地方说不通, 而且... ";
			link.l1.go = "DTSG_Knippel_31";
		break;
		
		case "DTSG_Knippel_31":
			dialog.text = "这要持续多久, 先生? ! 每次有人需要帮助, 你都这样反应吗? ";
			link.l1 = "看在上帝的份上, 小点声。 你会整条街都听到。 我说过我会去决斗。 这对你还不够吗? 现在仔细听我说。 ";
			link.l1.go = "DTSG_Knippel_32";
		break;
		
		case "DTSG_Knippel_32":
			dialog.text = "嗯, 好吧, 船长。 抱歉我失态了 —我关心那些在皇家海军服役的人的命运。 我们很多人都是正派的人, 应该得到比大多数人更好的命运。 ";
			link.l1 = "我理解你, 查理。 现在记住需要做什么。 我要你派一些船员到城门口。 随着决斗时间临近, 让他们悄悄集合, 准备好我的信号。 ";
			link.l1.go = "DTSG_Knippel_33";
		break;
		
		case "DTSG_Knippel_33":
			dialog.text = "你打算把一场诚实的决斗变成谋杀吗? ";
			link.l1 = "我怀疑这不完全是诚实的。 我只在必要时发信号。 如果一切真的光明正大, 我会很高兴自己错了。 现在明白了吗? 还记得一个月前发生的事吗? ";
			link.l1.go = "DTSG_Knippel_34";
		break;
		
		case "DTSG_Knippel_34":
			dialog.text = "明白了, 先生。 坦率地说, 我不太高兴, 但我会做必要的事。 别担心。 ";
			link.l1 = "这正是我想听到的。 ";
			link.l1.go = "DTSG_Knippel_35";
		break;
		
		case "DTSG_Knippel_35":
			DialogExit();
			
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "", "", "", "", -1);
			npchar.location = "None";
			AddDialogExitQuestFunction("DTSG_Knippel_36");
		break;
		
		case "DTSG_RalfFaggl":
			LAi_LocationDisableOfficersGen("PortPax_ExitTown", false);
			PChar.quest.DTSG_PoP_DuelTime.over = "yes";
			PChar.quest.DTSG_PoP_Duel.over = "yes";
			dialog.text = "那么, 德莫尔。 你早到了。 我们还在城里。 不过没关系。 可惜你没把那个老傻瓜带来。 但别担心, 我们最终会找到他的。 ";
			link.l1 = "随时为你服务。 雇佣兵, 是吗? 我惹了谁? ";
			link.l1.go = "DTSG_RalfFaggl_2";
		break;
		
		case "DTSG_RalfFaggl_2":
			dialog.text = "问题就在这里, 谁也没惹。 我们在找那个老混蛋查理, 我们得知他现在在你的船上, 通过你找他更容易。 这不是丛林, 所以我们得快点行动, 避免引来人群。 但在这里, 至少你跑不掉。 ";
			link.l1 = "我想这场决斗就是个陷阱? ";
			link.l1.go = "DTSG_RalfFaggl_3";
		break;
		
		case "DTSG_RalfFaggl_3":
			dialog.text = "现在才意识到有点晚了, 朋友。 我们无论如何都会打一架 —我是拉尔夫.法格尔, 为你效劳。 ";
			link.l1 = "实际上, 我早就怀疑了, 所以决定和邻居谈谈。 顺便问一下, 亚当斯也参与了吗? 简呢? 她会不会... ";
			link.l1.go = "DTSG_RalfFaggl_4";
		break;
		
		case "DTSG_RalfFaggl_4":
			dialog.text = "好奇心害死猫, 没听说过吗? 有人告诉你来决斗, 不是来打探的。 你本来有机会活下来\n当然。 激怒那个老军人, 迫使他的指挥官决斗 —我想这是我和彼得想出的完美计划。 简也做得很好。 ";
			link.l1 = "告诉我, 谁想除掉查理? ";
			link.l1.go = "DTSG_RalfFaggl_5";
		break;
		
		case "DTSG_RalfFaggl_5":
			dialog.text = "哈, 我怎么会告诉你? 自卫吧。 ";
			link.l1 = "可惜。 那我稍后问彼得。 ";
			link.l1.go = "DTSG_RalfFaggl_6";
		break;
		
		case "DTSG_RalfFaggl_6":
			DialogExit();
			
			sld = CharacterFromID("DTSG_FrederikStouks");
			LAi_SetCheckMinHP(sld, 1, true, "DTSG_FrederikStouks_ranen");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			sld = CharacterFromID("DTSG_RalfFaggl");
			LAi_SetCheckMinHP(sld, 1, false, "DTSG_RalfFaggl_ubit");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_SetFightMode(pchar, true);
		break;
		
		case "DTSG_PiterAdams_11":
			dialog.text = "哦, 我看你把我的故事放在心上, 已经惩罚了拉尔夫, 船长。 ";
			link.l1 = "当然, 正如你所说, 我是个值得尊敬的高尚人士。 现在我得惩罚你设下这个奸诈的陷阱。 ";
			link.l1.go = "DTSG_PiterAdams_12";
			npchar.SaveItemsForDead = true;
			npchar.DontClearDead = true;
			GiveItem2Character(npchar, "letter_1");
			ChangeItemName("letter_1", "itmname_specialletter");
			ChangeItemDescribe("letter_1", "itmdescr_DTSG_letter2");
		break;
		
		case "DTSG_PiterAdams_12":
			dialog.text = "欢迎尝试, 船长 - 你肯定已经筋疲力尽, 还受了伤。 ";
			link.l1 = "那我们休息一下。 同时告诉我, 你为谁工作? ";
			link.l1.go = "DTSG_PiterAdams_13";
		break;
		
		case "DTSG_PiterAdams_13":
			dialog.text = "抱歉, 但我的雇主不会喜欢, 即使之后我成功解决了你。 顺便说一下, 现在就会发生。 ";
			link.l1 = "该死! ..";
			link.l1.go = "DTSG_PiterAdams_14";
		break;
		
		case "DTSG_PiterAdams_14":
			DialogExit();
			
			if (MOD_SKILL_ENEMY_RATE > 4)
			{
				sld = CharacterFromID("DTSG_FrederikStouks");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_SetHP(sld, GetCharacterBaseHPValue(sld)/2, GetCharacterBaseHPValue(sld));
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			else
			{
				sld = CharacterFromID("DTSG_FrederikStouks");
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
				LAi_KillCharacter(sld);
			}
			
			sld = CharacterFromID("Knippel");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = CharacterFromID("DTSG_PiterAdams");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_Sosedi_Pobeda");
			LAi_SetFightMode(pchar, true);
		break;
		
		case "DTSG_Knippel_40":
			dialog.text = "我不敢相信这些... 这些恶棍不仅欺骗了我们, 还污蔑皇家海军! 他们怎么敢! 如果他们没死, 我会让他们吞下几颗链弹来惩罚这种背叛! ..";
			link.l1 = "人们什么都可能撒谎, 查理。 我以为你很清楚。 但你肯定知道是谁派他们来的。 这不是第一次为你设陷阱了。 他们身上每次都有一大笔钱。 ";
			link.l1.go = "DTSG_Knippel_41";
		break;
		
		case "DTSG_Knippel_41":
			dialog.text = "嗯, 我... 也许我们可以在亚当斯家找到别的东西, 先生? ";
			link.l1 = "回避问题? 但你说得对, 我本来就打算彻底搜查。 我们走。 ";
			link.l1.go = "DTSG_Knippel_42";
		break;
		
		case "DTSG_Knippel_42":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			LAi_LocationDisableOfficersGen("PortPax_town", false);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			PChar.quest.DTSG_PoP_ProverimSunduk.win_condition.l1 = "ExitFromLocation";
			PChar.quest.DTSG_PoP_ProverimSunduk.win_condition.l1.location = PChar.location;
			PChar.quest.DTSG_PoP_ProverimSunduk.win_condition = "DTSG_PoP_ProverimSunduk";
		break;
		
		case "DTSG_Knippel_50":
			dialog.text = "我的天, 这么多金子! ";
			link.l1 = "可惜这里没有别的东西了。 ‘简’也不见了。 你觉得她还活着吗? ";
			link.l1.go = "DTSG_Knippel_51";
		break;
		
		case "DTSG_Knippel_51":
			dialog.text = "我不知道, 先生, 这种恶棍什么都做得出来... ";
			link.l1 = "没错, 但我觉得你知道的比说的多。 这不是第一次有人追捕你了。 每次我们都在他们身上找到一堆钱。 ";
			link.l1.go = "DTSG_Knippel_52";
		break;
		
		case "DTSG_Knippel_52":
			dialog.text = "我不确定, 船长, 但也许是圣约翰的一个放贷人。 ";
			link.l1 = "你怎么惹到他的? ";
			link.l1.go = "DTSG_Knippel_53";
		break;
		
		case "DTSG_Knippel_53":
			dialog.text = "嗯... 前段时间, 我向他借钱偿还其他债务。 理查德答应支付, 但... ";
			link.l1 = "你觉得他没付? ";
			link.l1.go = "DTSG_Knippel_54";
		break;
		
		case "DTSG_Knippel_54":
			dialog.text = "以前我不会相信, 但在他对你做了那些事, 又带着阿比匆匆离开加勒比海之后... 也许他忘了债务。 或者没忘但还是走了... 理查德的行为像个混蛋, 先生。 如果再次证明是真的, 我不会惊讶, 但还是很失望。 ";
			link.l1 = "别太早下结论, 查理。 那就去圣约翰吧。 ";
			link.l1.go = "DTSG_Knippel_55";
		break;
		
		case "DTSG_Knippel_55":			//КОНeЦ ЭТАПА 2
			DialogExit();
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.location = "None";
			
			n = Findlocation("PortPax_town");
			locations[n].reload.l31.name = "houseF1";
			locations[n].reload.l31.go = "CommonRoom_MH9";
			locations[n].reload.l31.emerge = "reload1";
			locations[n].reload.l31.autoreload = "0";
			locations[n].reload.l31.label = "House";
			
			BackItemName("letter_1");
			BackItemDescribe("letter_1");
			TakeItemFromCharacter(pchar, "letter_1");
			AddQuestRecord("DTSG", "5");
			QuestOpenSeaExit()
			
			AddMapQuestMarkCity("SentJons", true);
			PChar.quest.DTSG_Etap3_Start.win_condition.l1 = "location";
			PChar.quest.DTSG_Etap3_Start.win_condition.l1.location = "Antigua";
			PChar.quest.DTSG_Etap3_Start.win_condition = "DTSG_Etap3_Start";
		break;
		
		case "DTSG_PiterAdams_20":
			if (CheckAttribute(pchar, "questTemp.DTSG_ZovemMatrosov"))
			{
				dialog.text = "啊, 你来了, 先生 - 看来大家都决定早到。 从你的样子看, 你似乎很轻松, 对自己的能力这么有信心? ";
				link.l1 = "当然, 这远不是我第一次决斗。 ";
				link.l1.go = "DTSG_PiterAdams_Nastoroje_21";
				ChangeCharacterComplexReputation(pchar, "authority", 1);
			}
			else
			{
				dialog.text = "我担心你不会来, 先生。 其他人已经到了。 ";
				link.l1 = "真正的贵族只会为死亡迟到。 ";
				link.l1.go = "DTSG_PiterAdams_NN_21";
				ChangeCharacterComplexReputation(pchar, "nobility", 1);
			}
		break;
		
		case "DTSG_PiterAdams_NN_21":
			dialog.text = "说得好, 先生! 这是我们的对手, 拉尔夫.法格尔。 这是我们的副手, 弗雷德里克.斯托克斯。 ";
			link.l1 = "... ";
			link.l1.go = "DTSG_PiterAdams_NN_22";
		break;
		
		case "DTSG_PiterAdams_NN_22":
			dialog.text = "认识一下... ";
			link.l1 = "... ";
			link.l1.go = "DTSG_PiterAdams_NN_23";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_NN_23":
			dialog.text = "我们的对手, 拉尔夫.法格尔。 ";
			link.l1 = "... ";
			link.l1.go = "DTSG_PiterAdams_NN_24";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_NN_24":
			dialog.text = "这是我们的副手, 弗雷德里克.斯托克斯。 ";
			link.l1 = "... ";
			link.l1.go = "DTSG_PiterAdams_NN_25";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_FrederikStouks"));
		break;
		
		case "DTSG_PiterAdams_NN_25":
			dialog.text = "... ";
			link.l1 = "这就是拉尔夫? 他看起来不像典型的醉酒邻居。 ";
			link.l1.go = "DTSG_PiterAdams_NN_26";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetCameraDialogMode(CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_NN_26":
			dialog.text = "你永远不知道邻居是谁, 德莫尔先生, 想过吗? 嘿嘿嘿。 ";
			link.l1 = "所以, 这是个陷阱... 我看你已经不发抖了。 装热病装腻了? ";
			link.l1.go = "DTSG_PiterAdams_NN_27";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetCameraDialogMode(npchar);
		break;
		
		case "DTSG_PiterAdams_NN_27":
			dialog.text = "从现在起, 我唯一能抖的就是嘲笑你的天真。 ";
			link.l1 = "好吧, 好吧。 我只后悔查理跟着来 - 单独对付你们会更轻松安静... ";
			link.l1.go = "DTSG_PiterAdams_BitvaDuel";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_21":
			dialog.text = "那太好了! ";
			link.l1 = "... ";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_22";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_22":
			dialog.text = "请允许我介绍... ";
			link.l1 = "... ";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_23";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_Nastoroje_23":
			dialog.text = "斯托克斯先生, 我们的副手。 ";
			link.l1 = "... ";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_24";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_FrederikStouks"));
		break;
		
		case "DTSG_PiterAdams_Nastoroje_24":
			dialog.text = "这是拉尔夫.法格尔。 ";
			link.l1 = "原来这就是拉尔夫? 我得承认, 和我想象的不一样。 但没关系, 我对付过更糟的。 ";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_25";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_Nastoroje_25":
			dialog.text = "嗯, 我想知道, 你是天真, 什么都不懂? 还是过于自信? ";
			link.l1 = "我不懂什么, 亚当斯先生? 来吧, 让我惊讶一下。 ";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_26";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetCameraDialogMode(npchar);
		break;
		
		case "DTSG_PiterAdams_Nastoroje_26":
			dialog.text = "通常情况下, 人们在这种情况下会表现出惊讶或害怕, 但你似乎是另一种类型。 把你脸上那得意的笑容抹去会更愉快, 德莫尔先生。 ";
			link.l1 = "什么威胁! 我们不是站在同一边吗, 彼得? ";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_27";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_27":
			dialog.text = "别告诉我你希望用那个老人打败我们所有人。 你寡不敌众, 我亲爱的先生。 ";
			link.l1 = "正如我所说, 是你不懂。 查理抱怨了几句, 但我还是让他以防万一带伙计们来。 事实证明, 不是徒劳的。 伙计们, 过来!!! ";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_28";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_28":
			DialogExit();
			
			StartQuestMovie(true, false, true);
			locCameraFromToPos(0.34, 0.51, 34.93, true, -5.63, -1.20, 57.46);
			DoQuestCheckDelay("DTSG_PoP_Duel_Podkreplenie", 3.0);
			
			int DTSG_PoP_MK;
			if (MOD_SKILL_ENEMY_RATE == 2) DTSG_PoP_MK = 5;
			if (MOD_SKILL_ENEMY_RATE == 4) DTSG_PoP_MK = 5;
			if (MOD_SKILL_ENEMY_RATE == 6) DTSG_PoP_MK = 4;
			if (MOD_SKILL_ENEMY_RATE == 8) DTSG_PoP_MK = 4;
			if (MOD_SKILL_ENEMY_RATE == 10) DTSG_PoP_MK = 3;
			
			for (i=1; i<=DTSG_PoP_MK; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("DTSG_PoP_Matrosy_"+i, "citiz_3"+i, "man", "man", sti(pchar.rank)-5, sti(pchar.nation), -1, false, "quest"));
				GiveItem2Character(sld, "blade_11");
				sld.equip.blade = "blade_11";
				ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
				sld.lifeday = 0;
				LAi_SetHP(sld, 120.0, 120.0);
			}
		break;
		
		case "DTSG_PiterAdams_Nastoroje_29":
			dialog.text = "什么? ..";
			link.l1 = "惊讶和害怕吗, 亚当斯先生? 很高兴知道。 ";
			link.l1.go = "DTSG_PiterAdams_BitvaDuel";
			SetCameraDialogMode(npchar);
		break;
		
		case "DTSG_PiterAdams_BitvaDuel":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("PortPax_ExitTown")], false);
			LAi_SetFightMode(pchar, true);
			
			for (i=1; i<=5; i++)
			{
				if (GetCharacterIndex("DTSG_PoP_Matrosy_"+i) != -1)
				{
					sld = CharacterFromID("DTSG_PoP_Matrosy_"+i);
					LAi_SetWarriorType(sld);
					LAi_CharacterDisableDialog(sld);
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				}
			}
			
			sld = CharacterFromID("Knippel");
			LAi_SetWarriorType(sld);
			LAi_SetCheckMinHP(sld, 10, true, "KnippelRanen");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = CharacterFromID("DTSG_PiterAdams");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			sld = CharacterFromID("DTSG_FrederikStouks");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			sld = CharacterFromID("DTSG_RalfFaggl2");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_PiterAdams_Duel_Pobeda");
		break;
		
		case "DTSG_Knippel_60":
			dialog.text = "就该这样对付这种撒谎的无赖。 我还是不敢相信他们竟敢污蔑皇家海军! 我真该用链弹勒死他们! ..";
			link.l1 = "到现在你该知道了, 查理, 有些人根本没有底线。 我说过我会处理, 你本可以待在船上的。 你是想确认我会帮这些‘值得尊敬的人’吗? 现在谁又说对了, 事情并不像你想的那么简单? ";
			link.l1.go = "DTSG_Knippel_61";
		break;
		
		case "DTSG_Knippel_61":
			dialog.text = "您说得对, 先生... ";
			link.l1 = "没错。 但告诉我, 为什么总有人想追杀你? 这已经不是第一次了。 ";
			link.l1.go = "DTSG_Knippel_62";
		break;
		
		case "DTSG_Knippel_62":
			dialog.text = "我不知道, 船长。 老查理只是个普通的炮手。 ";
			link.l1 = "嗯, 好吧。 既然我们可怜的决斗者身上没什么有用的东西... 不, 我们去亚当斯家看看能不能找到什么。 ";
			link.l1.go = "DTSG_Knippel_63";
		break;
		
		case "DTSG_Knippel_63":
			DialogExit();
			
			LAi_RemoveCheckMinHP(npchar);
			LAi_SetImmortal(npchar, false);
			AddDialogExitQuestFunction("DTSG_Knippel_64");
		break;
		
		case "DTSG_Knippel_70":
			dialog.text = "看来这个女人也消失了... 也许他们准备在‘决斗’后立刻逃离城市? 而且很匆忙 —这里有这么多金子! ";
			link.l1 = "你说得对, 因为他们留下的不止是金子。 还有另一封信。 他们走得太急, 忘了烧掉。 看看吧, 你会喜欢里面的内容。 ";
			link.l1.go = "DTSG_Knippel_71";
		break;
		
		case "DTSG_Knippel_71":
			TakeItemFromCharacter(pchar, "letter_1");
			dialog.text = "(读信) 好吧, 我得反驳一下‘老’这个说法。 ";
			link.l1 = "现在不是纠结这个的时候。 这是第二次有人派雇佣兵追杀你, 还提供了资金和情报。 而且他们专门针对你。 告诉我, 你这个普通炮手, 到底得罪了谁? ";
			link.l1.go = "DTSG_Knippel_72";
		break;
		
		case "DTSG_Knippel_72":
			dialog.text = "我有一个猜想, 先生, 只有一个, 而且我真的不希望它是真的。 ";
			link.l1 = "所以这很可能就是真的。 说吧。 ";
			link.l1.go = "DTSG_Knippel_73";
		break;
		
		case "DTSG_Knippel_73":
			dialog.text = "我曾经在圣约翰欠过一些人的债, 而且... ";
			link.l1 = "... 所以你觉得是他们在追杀你? 有多少人能雇得起雇佣兵并拿出这么多钱? ";
			link.l1.go = "DTSG_Knippel_74";
		break;
		
		case "DTSG_Knippel_74":
			dialog.text = "您想得没错, 先生。 最后我从一个放贷人那里借钱, 几乎还清了所有债务。 他当然有能力做这些。 但是... ";
			link.l1 = "但是什么? 我们会帮你还清债务, 就这样。 你在担心什么? ";
			link.l1.go = "DTSG_Knippel_75";
		break;
		
		case "DTSG_Knippel_75":
			dialog.text = "您看, 船长, 理查德答应过我会帮我还清的。 ";
			link.l1 = "你觉得他没还? ";
			link.l1.go = "DTSG_Knippel_76";
		break;
		
		case "DTSG_Knippel_76":
			dialog.text = "我现在不知道该怎么想了, 先生。 我们认识这么久, 我一直把他当作模范绅士。 但自从他离开您, 带着阿比盖尔逃走后... 我不会感到惊讶。 这就是为什么我说不希望这是真的。 ";
			link.l1 = "猜测需要先验证, 然后再难过, 查理。 我们走, 你得再去一趟圣约翰。 ";
			link.l1.go = "DTSG_Knippel_77";
		break;
		
		case "DTSG_Knippel_77":			//阶段2结束
			DialogExit();
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			
			n = Findlocation("PortPax_town");
			locations[n].reload.l31.name = "houseF1";
			locations[n].reload.l31.go = "CommonRoom_MH9";
			locations[n].reload.l31.emerge = "reload1";
			locations[n].reload.l31.autoreload = "0";
			locations[n].reload.l31.label = "House";
			
			BackItemName("letter_1");
			BackItemDescribe("letter_1");
			AddQuestRecord("DTSG", "6");
			QuestOpenSeaExit()
			LAi_LocationDisableOfficersGen("PortPax_town", false);
			LAi_LocationDisableOfficersGen("PortPax_ExitTown", false);
			
			AddMapQuestMarkCity("SentJons", true);
			PChar.quest.DTSG_Etap3_Start.win_condition.l1 = "location";
			PChar.quest.DTSG_Etap3_Start.win_condition.l1.location = "Antigua";
			PChar.quest.DTSG_Etap3_Start.win_condition = "DTSG_Etap3_Start";
		break;
		
		case "DTSG_Knippel_PoPDuelTime":
			dialog.text = "船长!!! ";
			link.l1 = "怎么了, 查理, 发生什么事了? ";
			link.l1.go = "DTSG_Knippel_PoPDuelTime_2";
		break;
		
		case "DTSG_Knippel_PoPDuelTime_2":
			dialog.text = "发生什么事? ! 别告诉我你忘了决斗的事, 先生! 可能你还在这里悠闲的时候, 亚当斯已经被砍成碎片了! ";
			link.l1 = "对! .. 我马上出城。 ";
			link.l1.go = "DTSG_Knippel_PoPDuelTime_3";
		break;
		
		case "DTSG_Knippel_PoPDuelTime_3":
			DialogExit();
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			DoQuestReloadToLocation("PortPax_ExitTown", "reload", "reload3", "");
		break;
		
		case "DTSG_AntiguaArest":
			dialog.text = "查尔斯.德莫尔船长? 你旁边是查理.尼普尔吗? ";
			link.l1 = "不, 这位... ";
			link.l1.go = "DTSG_AntiguaArest_2";
		break;
		
		case "DTSG_AntiguaArest_2":
			dialog.text = "别否认了, 先生 —这个殖民地的每个人都认识查理。 ";
			link.l1 = "那何必问呢? 我能帮什么忙? ";
			link.l1.go = "DTSG_AntiguaArest_3";
		break;
		
		case "DTSG_AntiguaArest_3":
			dialog.text = "你帮不了。 请不要反抗 —查理在这里被通缉。 我们必须逮捕他。 ";
			link.l1 = "能告诉我指控我的人什么罪名吗? 是因为他的债务吗? 我可以替他偿还。 我们现在就去银行家那里, 你可以在场。 ";
			link.l1.go = "DTSG_AntiguaArest_4";
		break;
		
		case "DTSG_AntiguaArest_4":
			dialog.text = "债务? 我第一次听说。 我不清楚细节, 但请不要把事情复杂化 —我只是在执行命令。 ";
			link.l1 = "哦, 太好了... ";
			link.l1.go = "DTSG_AntiguaArest_5";
		break;
		
		case "DTSG_AntiguaArest_5":
			StartInstantDialog("Knippel", "DTSG_AntiguaArest_6", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_AntiguaArest_6":
			dialog.text = "船长... ";
			link.l1 = "查理, 如果我们现在逃跑, 我们头上的赏金会更高。 而且我们能杀出一条路吗? 我会想办法救你出来, 别做傻事! ";
			link.l1.go = "DTSG_AntiguaArest_7";
		break;
		
		case "DTSG_AntiguaArest_7":
			DialogExit();
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			AddQuestRecord("DTSG", "8");
			pchar.questTemp.DTSG_KnippelDolg = true;
			
			sld = CharacterFromID("Knippel");
			RemovePassenger(pchar, sld);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload_jail", "", "", "", "", -1);
			sld.location = "None";
			
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("DTSG_AntiguaSold_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload_jail", "", "", "", "", -1);
				sld.location = "None";
			}
		break;
		
		case "DTSG_AntiguaStrazhBank":
			dialog.text = "立即停止吵闹并威胁这位先生, 先生。 放下武器, 马上跟我走! ";
			link.l1 = "我没有威胁任何人, 这是个误会。 这是商业事务, 不是谋杀未遂。 ";
			link.l1.go = "DTSG_AntiguaStrazhBank_2";
		break;
		
		case "DTSG_AntiguaStrazhBank_2":
			dialog.text = "在我看来不是这样。 你必须接受法律的制裁。 ";
			link.l1 = "如果我道歉然后离开呢? ";
			link.l1.go = "DTSG_AntiguaStrazhBank_3";
		break;
		
		case "DTSG_AntiguaStrazhBank_3":
			dialog.text = "这样你就可以偷偷回来完成我打断的事? 你以为我很蠢吗? ";
			link.l1 = "如果你不想和平解决, 那就是蠢。 天知道, 我不想事情变成这样... ";
			link.l1.go = "DTSG_AntiguaStrazhBank_4";
		break;
		
		case "DTSG_AntiguaStrazhBank_4":
			DialogExit();
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
			
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_bank")], false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_AntiguaStrazhBank_Ubili");
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki":
			dialog.text = "你杀了他! ..";
			link.l1 = "就当是你自己动手的吧, 先生。 你本可以回答我的问题, 而不是歇斯底里。 我发誓, 再叫一声我就把你的脑浆打出来。 ";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_V1";
			link.l2 = "是的, 我杀了他。 是他逼我的。 但你不像他那么愚蠢, 不会重蹈覆辙, 对吗? ";
			link.l2.go = "DTSG_AntiguaUsurer_PosleDraki_V2";
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_V1":
			dialog.text = "你想干什么? ! ";
			link.l1 = "不久前, 查理.尼普尔向你借了钱。 他的朋友答应帮他还债, 但显然没有。 我要求你立即停止派雇佣兵追杀我们。 如果我能负担得起, 我准备现在就偿还查理的债务。 ";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_3";
			AddComplexLandExpToScill(100, 0, 0);
			AddComplexSeaExpToScill(0, 0, 0, 0, 0, 0, 100);
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_V2":
			dialog.text = "你想干什么? ! ";
			link.l1 = "不久前, 查理.尼普尔向你借了钱。 他的朋友答应帮他还债, 但显然没有。 我要求你立即停止派雇佣兵追杀我们。 如果我能负担得起, 我准备现在就偿还查理的债务。 ";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_3";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_3":
			dialog.text = "查理? ! 我绝不会那样对他; 他是个善良诚实的人。 而且, 他的债务早就还清了。 ‘瓦尔基里’号的船长弗利特伍德先生把最后一个比索都付清了。 ";
			link.l1 = "真的吗? 我知道他是谁。 你早该这么说。 抱歉打扰了, 再见。 ";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_4";
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_4":
			dialog.text = "就这样? ! 你威胁我! 还杀了人! ..";
			link.l1 = "你忘了我说的话了? 再叫一声你就去陪他。 再见。 ";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_5";
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_5":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_town")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_bank")], true);
			//LAi_LocationDisableOfficersGen("SentJons_town", false);
			LAi_LocationDisableOfficersGen("SentJons_bank", false);
			npchar.dialog.filename = "Usurer_dialog.c";
			npchar.dialog.currentnode = "First time";
			LAi_SetOwnerType(npchar);
			
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "fame", 2);
			
			chrDisableReloadToLocation = false;
			AddQuestRecord("DTSG", "9");
			PChar.quest.DTSG_AntiguaTrevoga.win_condition.l1 = "location";
			PChar.quest.DTSG_AntiguaTrevoga.win_condition.l1.location = "SentJons_town";
			PChar.quest.DTSG_AntiguaTrevoga.win_condition = "DTSG_AntiguaTrevoga";
		break;
		
		case "DTSG_Killer":
			dialog.text = "还在这儿, 还没被吊死? 好吧, 代萨塞克斯向你问好, 查理。 ";
			link.l1 = "也向你问好, 不管你是谁。 ";
			link.l1.go = "DTSG_Killer_2";
			CharacterTurnToLoc(npchar, "goto", "goto9");
		break;
		
		case "DTSG_Killer_2":
			dialog.text = "啊, 查尔斯.德莫尔。 你来看可怜的查理, 真是太好了。 我们就料到你会来。 ";
			link.l1 = "我们是谁? ";
			link.l1.go = "DTSG_Killer_3";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "DTSG_Killer_3":
			dialog.text = "这不重要。 你让我们花费了大量时间和金钱, 德莫尔先生。 我想他们不会介意我在这里同时解决掉查理和你。 ";
			link.l1 = "好吧, 既然我们反正都得死, 能否出于好心告诉我们到底惹了谁? 我们保证不会再犯。 还有, 萨塞克斯是谁? ";
			link.l1.go = "DTSG_Killer_4";
		break;
		
		case "DTSG_Killer_4":
			dialog.text = "不行。 职责所在, 而且不像你, 我是行动派, 不是空谈家。 ";
			link.l1 = "该死的! 到底有没有人能告诉我发生了什么? ! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DTSG_Killer_5");
		break;
		
		case "DTSG_KnippelDaySpasen":
			dialog.text = "好吧, 我真该死, 船长, 你在这里制造了一场屠杀! ";
			link.l1 = "你有意见吗? 你更喜欢绞刑架? 还是想在这里无限期腐烂? ";
			link.l1.go = "DTSG_KnippelDaySpasen_2";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_KnippelDaySpasen_2":
			dialog.text = "不, 先生。 感谢您救了我。 说实话, 我很惊讶您会来, 考虑到您那么轻易地让他们抓走了我。 也惊讶您如此轻易地解决了守卫 —他是‘海狐’。 一名海军陆战队员。 ";
			link.l1 = "我告诉过你我会救你出来, 你不该怀疑。 现在趁整个驻军还没到, 快离开这个牢房。 ";
			link.l1.go = "DTSG_KnippelDaySpasen_3";
		break;
		
		case "DTSG_KnippelDaySpasen_3":
			dialog.text = "是, 船长。 ";
			link.l1 = "... ";
			link.l1.go = "DTSG_KnippelDaySpasen_4";
		break;
		
		case "DTSG_KnippelDaySpasen_4":
			DialogExit();
			
			Pchar.GenQuest.Hunter2Pause = true;
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("DTSG_TurmaDayPobeda_2", 1.0);
		break;
		
		case "DTSG_KnippelDaySpasen_5":
			dialog.text = "该死, 先生, 我几乎不敢相信... ";
			link.l1 = "顺便问一下, 告诉我, 他们指控你什么? 还有, 萨塞克斯是谁? ";
			link.l1.go = "DTSG_KnippelDaySpasen_6";
		break;
		
		case "DTSG_KnippelDaySpasen_6":
			dialog.text = "我不知道, 先生。 我不知道他们指的是谁... ";
			link.l1 = "好吧, 我们以后再查。 现在我们需要离开这里。 ";
			link.l1.go = "DTSG_KnippelDaySpasen_7";
		break;
		
		case "DTSG_KnippelDaySpasen_7":
			DialogExit();
			
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			AddPassenger(pchar, npchar, false);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			AddQuestRecord("DTSG", "12");
			
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition = "DTSG_KnippelRazgovorVKaute";
		break;
		
		case "DTSG_AntiguaNightPirs":
			dialog.text = "您下一步打算做什么, 先生? 在光天化日之下痛揍那个吸血鬼太冒险了。 ";
			link.l1 = "你刚给了我一个主意。 为什么要在白天痛揍他, 我们现在就可以在夜色掩护下动手? ";
			link.l1.go = "DTSG_AntiguaNightPirs_2";
		break;
		
		case "DTSG_AntiguaNightPirs_2":
			dialog.text = "该死, 这是个绝妙的主意, 船长! ";
			link.l1 = "没错。 告诉我, 查理, 你在这里住过一段时间。 你知道那个放贷人住在哪里吗? ";
			link.l1.go = "DTSG_AntiguaNightPirs_3";
		break;
		
		case "DTSG_AntiguaNightPirs_3":
			dialog.text = "我以前知道, 先生, 但上次我在这里时, 他正在卖房子。 不知道新家在哪里。 ";
			link.l1 = "好吧, 这是个问题... ";
			link.l1.go = "DTSG_AntiguaNightPirs_4";
		break;
		
		case "DTSG_AntiguaNightPirs_4":
			dialog.text = "我相信您会想出办法的, 船长, 毕竟您打败了可怕的卢卡斯.罗登伯格! ";
			link.l2 = "好吧, 我会处理。 不过, 如果你知道放贷人的房子在哪里, 那就更好了! ";
			link.l2.go = "DTSG_AntiguaIskat_1";
			link.l1 = "我确实打败了他。 但早晨比晚上更明智, 查理。 我们旅途劳累, 先休息一下, 白天再去 —毕竟我们不是来谋杀那个人的。 ";
			link.l1.go = "DTSG_AntiguaSpat_1";
		break;
		
		case "DTSG_AntiguaSpat_1":
			dialog.text = "您确定吗, 先生? 我们会失去突袭的优势。 ";
			link.l1 = "我确定, 而且我累了。 此外, 我只是想谈谈。 必要时吓唬他一下。 ";
			link.l1.go = "DTSG_AntiguaSpat_2";
		break;
		
		case "DTSG_AntiguaSpat_2":
			TavernWaitDate("wait_day");
			DoQuestReloadToLocation("SentJons_tavern_upstairs", "goto", "goto2", "DTSG_AntiguaSpat_3");
		break;
		
		case "DTSG_AntiguaIskat_1":
			dialog.text = "我不知道的事 —就是不知道, 抱歉, 先生。 ";
			link.l1 = "啊, 没关系, 我们去找他。 ";
			link.l1.go = "DTSG_AntiguaIskat_2";
		break;
		
		case "DTSG_AntiguaIskat_2":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			
			AddQuestRecord("DTSG", "13");
			pchar.questTemp.DTSG_NightIskat = true;
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			pchar.GenQuest.CannotWait = true;
			pchar.questTemp.TimeLock = true;
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood":
			dialog.text = "您和我想的一样吗, 先生? ";
			link.l1 = "恐怕是的, 查理。 加勒比海没有其他著名船长叫这个名字。 而且理查德确实去了伦敦。 所以, 这不太可能是巧合。 ";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_2";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_2":
			dialog.text = "太可怕了... 虽然我对他说了很多严厉的话, 但我从未希望他遭遇这种事! 还有可怜的阿比! .. 她当时还怀着孩子。 希望她还活着... ";
			link.l1 = "的确, 不希望任何人遭遇这种事。 希望阿比没事。 迪克有没有提到过什么强大的敌人? ";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_3";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_3":
			dialog.text = "您一定是在开玩笑, 船长。 我不了解欧洲的情况, 但在这里每个荷兰人都想让理查德死。 ";
			link.l1 = "没错。 也许这里有人花大价钱派刺客去旧大陆追杀他。 会不会是追杀你的不是这个 petty 放贷人, 而是理查德的某个神秘敌人? ";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_4";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_4":
			dialog.text = "我不知道, 先生。 现在一切皆有可能。 但这会让我们所有人的处境更复杂... ";
			link.l1 = "是的, 你说得对, 我也不喜欢这种可能性。 ";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_5";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_5":
			DialogExit();
			npchar.location = "None";
			
			AddQuestRecord("DTSG", "14");
			pchar.questTemp.DTSG_Nastoroje2 = true;
			chrDisableReloadToLocation = false;
			
			PChar.quest.DTSG_NightDom.win_condition.l1 = "locator";
			PChar.quest.DTSG_NightDom.win_condition.l1.location = "SentJons_town";
			PChar.quest.DTSG_NightDom.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_NightDom.win_condition.l1.locator = "houseSp3";
			PChar.quest.DTSG_NightDom.win_condition = "DTSG_NightDom";
		break;
		
		case "DTSG_NightRostovshik":
			dialog.text = "什么, 谁... 什么? ! 发生了什么? .. 你是谁? ! ..";
			link.l1 = "哦, 得了吧。 如果我想杀你, 会在你睡觉的时候动手。 所以别把事情复杂化, 也别缩短我们的寿命。 明白就点头。 ";
			link.l1.go = "DTSG_NightRostovshik_2";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_NightRostovshik_2":
			dialog.text = "嗯嗯... ";
			link.l1 = "很好。 冷静点 —我来这里不是为了抢劫。 绑架或伤害你。 ";
			link.l1.go = "DTSG_NightRostovshik_3";
		break;
		
		case "DTSG_NightRostovshik_3":
			dialog.text = "那... 你为什么来? 为什么不能早上来? ";
			link.l1 = "因为有个有钱有势的人在追杀我的朋友。 我们有理由相信是你, 所以他白天在街上走可能不安全。 ";
			link.l1.go = "DTSG_NightRostovshik_4";
		break;
		
		case "DTSG_NightRostovshik_4":
			dialog.text = "但我真的不明白您在说什么, 先生... ";
			link.l1 = "查理.尼普尔。 镇上的人都认识他。 仔细想想。 他欠你钱。 ";
			link.l1.go = "DTSG_NightRostovshik_5";
		break;
		
		case "DTSG_NightRostovshik_5":
			dialog.text = "我们的老查理? ! 没错, 但他的债务早就还清了, 虽然不是他自己还的。 ";
			link.l1 = "那个恩人是谁? ";
			link.l1.go = "DTSG_NightRostovshik_6";
		break;
		
		case "DTSG_NightRostovshik_6":
			dialog.text = "他的船长, 理查德.弗利特伍德勋爵。 如果您不信, 我可以给您看记录。 ";
			link.l1 = "你是说弗利特伍德? 那我相信你。 那么, 你没有派雇佣兵追杀查理? ";
			link.l1.go = "DTSG_NightRostovshik_7";
		break;
		
		case "DTSG_NightRostovshik_7":
			dialog.text = "当然没有, 我为什么要那样做? 告诉我, 这有什么意义? ";
			link.l1 = "的确。 好吧, 抱歉深夜打扰。 晚安。 ";
			link.l1.go = "DTSG_NightRostovshik_8";
		break;
		
		case "DTSG_NightRostovshik_8":
			DialogExit();
			
			PChar.quest.DTSG_NightDom_3.win_condition.l1 = "locator";
			PChar.quest.DTSG_NightDom_3.win_condition.l1.location = "SentJons_houseSP3";
			PChar.quest.DTSG_NightDom_3.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_NightDom_3.win_condition.l1.locator = "reload1";
			PChar.quest.DTSG_NightDom_3.win_condition = "DTSG_NightDom_3";
			
			LAi_CharacterDisableDialog(npchar);
			Pchar.GenQuest.Hunter2Pause = true;
			AddQuestRecord("DTSG", "15");
		break;
		
		case "DTSG_NightKiller":
			dialog.text = "怎么, 查理, 今晚想和你以前的赞助人躲在一起? 他不在那里。 但你很快就会见到他了。 代萨塞克斯向你问好。 ";
			link.l1 = "我们已经知道了。 萨塞克斯是谁? 你又是谁? ";
			link.l1.go = "DTSG_NightKiller_2";
		break;
		
		case "DTSG_NightKiller_2":
			dialog.text = "这不关你的事, 德莫尔先生。 遗憾的是, 你卷入这件事的程度超出了我们的预期。 你很碍事。 ";
			link.l1 = "碍谁的事? 别告诉我我睡了某个非常有权势。 非常愤怒的英国男人的妻子。 ";
			link.l1.go = "DTSG_NightKiller_3";
		break;
		
		case "DTSG_NightKiller_3":
			dialog.text = "真有趣。 还有时间开玩笑。 看来关于你的传闻是真的\n我们想要什么? 查理的人头就够了。 但考虑到你给我们添了这么多麻烦, 这次也涉及你了 —你总是管闲事。 ";
			link.l1 = "我想我们是被捕了? ";
			link.l1.go = "DTSG_NightKiller_4";
		break;
		
		case "DTSG_NightKiller_4":
			dialog.text = "逮捕? 不, 亲爱的先生, 现在不是采取折中措施的时候。 这是处决, 德莫尔船长。 ";
			link.l1 = "同意。 唯一的问题是, 谁被处决。 ";
			link.l1.go = "DTSG_NightKiller_5";
		break;
		
		case "DTSG_NightKiller_5":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_town")], false);
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("Knippel");
			LAi_SetOfficerType(sld);
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("DTSG_Killers_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_NightKiller_Pobeda");
		break;
		
		case "DTSG_Knippel_80":
			dialog.text = "我没想到会有‘海狐’参与... ";
			link.l1 = "嗯, 凡事都有第一次。 告诉我, 查理, 萨塞克斯是谁? ";
			link.l1.go = "DTSG_Knippel_81";
		break;
		
		case "DTSG_Knippel_81":
			dialog.text = "我... ";
			link.l1 = "你没看到事情发展到什么地步了吗? 而且看来我们处境相同, 查理。 所以我有权知道细节。 ";
			link.l1.go = "DTSG_Knippel_82";
		break;
		
		case "DTSG_Knippel_82":
			dialog.text = "当然, 船长。 但不是在这里, 对吗? 我们离开这个岛, 在船上谈。 ";
			link.l1 = "你说得对。 好吧, 我们快点。 ";
			link.l1.go = "DTSG_Knippel_83";
		break;
		
		case "DTSG_Knippel_83":
			DialogExit();
			AddQuestRecord("DTSG", "16");
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			DeleteAttribute(pchar,"questTemp.TimeLock");
			chrDisableReloadToLocation = false;
			//LAi_LocationDisableOfficersGen("SentJons_town", false);
			LAi_LocationDisableOfficersGen("SentJons_bank", false);
			
			sld = CharacterFromID("Knippel");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition = "DTSG_KnippelRazgovorVKaute";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom":
			dialog.text = "您叫我, 船长? ";
			link.l1 = "是的, 查理。 我们需要谈谈。 我想你已经猜到是关于什么了。 ";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_2";
			DelLandQuestMark(npchar);
			//LAi_LocationDisableOfficersGen("SentJons_town", true);
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_2":
			dialog.text = "是, 先生... ";
			link.l1 = "很好。 告诉我, 为什么你的同胞, 包括精锐部队, 会追杀你, 而你又不是罪犯或其他什么人。 ";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_3";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_3":
			dialog.text = "我真的不知道, 先生... ";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				link.l1 = "这不是玩笑, 查理。 追杀你的人可以命令‘海狐’。 他可能也是杀害理查德的幕后黑手。 所以如果你有任何想法, 就分享出来。 萨塞克斯的问候是什么意思, 它是谁? ";
			}
			else
			{
				link.l1 = "别回避了, 查理。 我知道你有事瞒着。 作为你的船长, 我命令你告诉我一切。 萨塞克斯是谁? ";
			}
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_4";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_4":
			dialog.text = "好吧, 船长。 萨塞克斯不是一个人。 它是... 一艘船。 ";
			link.l1 = "一艘船的问候? 这太荒谬了。 ";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_5";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_5":
			dialog.text = "让我解释。 我可以坐下吗, 先生? 这个故事很长, 而且不太愉快。 ";
			link.l1 = "当然可以, 查理。 说吧。 ";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_6";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_6":
			DialogExit();
			SetCurrentTime(2, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			SetMainCharacterIndex(GetCharacterIndex("Knippel"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			SetLaunchFrameFormParam(StringFromKey("Knippel_11", NewStr()), "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("SentJons_houseH1", "goto", "goto2", "DTSG_KnippelDoma");
			LaunchFrameForm();
			//DoQuestReloadToLocation("SentJons_houseH1", "goto", "goto2", "DTSG_KnippelDoma");
		break;
		
		case "DTSG_Kurier":
			dialog.text = "嘿, 查理, 我是弗利特伍德船长派来的。 他想见你。 ";
			link.l1 = "谢谢, 伙计。 发生什么事了吗? 通常他都是通过你直接传达的。 ";
			link.l1.go = "DTSG_Kurier_2";
		break;
		
		case "DTSG_Kurier_2":
			dialog.text = "我不知道。 他说想和你当面谈。 这是你们的事, 自己解决吧。 ";
			link.l1 = "哦, 我有种不祥的预感... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DTSG_Kurier_3");
		break;
		
		case "DTSG_Cortny":
			dialog.text = "... ";
			link.l1 = "晚安, 先生! ";
			link.l1.go = "DTSG_Cortny_2";
		break;
		
		case "DTSG_Cortny_2":
			dialog.text = "晚安。 让我过去。 ";
			link.l1 = "当然, 请吧, 抱歉, 先生。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DTSG_Cortny_3");
		break;
		
		case "DTSG_Fleetwood":
			dialog.text = "啊, 是你啊, 查理。 进来, 进来。 把身后的门关上。 ";
			link.l1 = "晚安, 船长。 出什么事了? 还有那个人是谁? 一只自负的孔雀... ";
			link.l1.go = "DTSG_Fleetwood_2";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_Fleetwood_2":
			dialog.text = "那个, 我不能说。 也不能让任何人偷听我们的谈话。 别跟任何人提这事, 明白吗? ";
			link.l1 = "明白, 先生。 出什么事了吗? 您看起来异常忧虑, 这可不像您。 ";
			link.l1.go = "DTSG_Fleetwood_3";
		break;
		
		case "DTSG_Fleetwood_3":
			dialog.text = "你这么觉得啊。 你看起来也不太好 —毕竟是晚上了。 但恐怕你今晚睡不成了, 我的朋友 —我们有项紧急且机密的任务。 ";
			link.l1 = "那任务是什么, 船长? ";
			link.l1.go = "DTSG_Fleetwood_4";
		break;
		
		case "DTSG_Fleetwood_4":
			dialog.text = "铲除一个叛徒。 我们自己人里的。 很快, 一艘来自旧大陆的外交船会出现在多米尼加海岸 —护卫舰‘萨塞克斯’号。 官方说法是, 他们要和荷兰人谈笔好交易。 但实际上... ";
			link.l1 = "... 他们要给我们的敌人传递情报吗, 先生? ";
			link.l1.go = "DTSG_Fleetwood_5";
		break;
		
		case "DTSG_Fleetwood_5":
			dialog.text = "更糟。 彻底叛逃到对方那边。 虽然穿越大西洋后他们会很疲惫, 但说到底, 那是艘不错的护卫舰, 如果我们用重型船攻击, 它肯定会试图逃跑\n所以我们得迅速果断行动。 只能靠‘瓦尔基里’号了 —只有她能胜任这任务。 ";
			link.l1 = "老‘瓦尔基里’能对付护卫舰吗? ..";
			link.l1.go = "DTSG_Fleetwood_6";
		break;
		
		case "DTSG_Fleetwood_6":
			dialog.text = "哈哈, 查理, 你怀疑你的船长? 而且, 就像我说的, 他们会很疲惫。 如果我们突然袭击, 所有优势都在我们这边。 ";
			link.l1 = "我绝不会! 但我希望您知道自己在做什么, 先生... ";
			link.l1.go = "DTSG_Fleetwood_7";
		break;
		
		case "DTSG_Fleetwood_7":
			dialog.text = "我确定。 还有一件事。 这个叛徒在议会里地位很高, 明白吗? 他可能到处都有眼线 —不只是在国内, 这里, 在加勒比也有。 所以别在镇上提萨塞克斯号或我们任务的任何细节。 ";
			link.l1 = "您不必告诉我, 先生。 老查理永远靠得住。 ";
			link.l1.go = "DTSG_Fleetwood_8";
		break;
		
		case "DTSG_Fleetwood_8":
			dialog.text = "我知道。 只是这次的风险比以往都高。 收拾东西准备好 —我们黎明起航。 ";
			link.l1 = "是, 先生。 晚安, 先生。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DTSG_Fleetwood_9");
		break;
		
		case "DTSG_Knippel_SamSoboi":
			dialog.text = "我从没见过理查德这样... 他那么忧虑, 甚至... 害怕? ";
			link.l1 = "但为什么? 他甚至都没跟我分享。 不过没关系。 他是个伟大的船长, 我们肯定能对付这艘护卫舰和她疲惫的船员。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DTSG_Knippel_SamSoboi_2");
			DeleteAttribute(pchar, "questTemp.lockedMusic");
		break;
		
		case "DTSG_Fleetwood_10":
			dialog.text = "‘萨塞克斯’号在天际线上, 查理, 准备好。 ";
			link.l1 = "时刻准备着, 船长。 ";
			link.l1.go = "DTSG_Fleetwood_11";
		break;
		
		case "DTSG_Fleetwood_11":
			dialog.text = "很好。 我指望你和你的链弹。 尽量尽快撕碎他们的船帆, 或者更好, 打掉一根桅杆。 进行一场冒险的战斗去击沉他们没意义, 所以我会尝试登船\n另外, 我们得确保叛徒已死 —如果我们击沉他们, 还是得靠近并确保没人幸存。 ";
			link.l1 = "为了一个叛徒杀这么多同胞... ";
			link.l1.go = "DTSG_Fleetwood_12";
		break;
		
		case "DTSG_Fleetwood_12":
			dialog.text = "可悲。 我也很痛心, 查理。 但命令就是命令。 至少我们不是为了好玩才这么做。 所以赶紧结束吧。 ";
			link.l1 = "是, 先生... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DTSG_Fleetwood_13");
		break;
		
		case "DTSG_Graf_Sheffild_1":
			dialog.text = "够了! 我准备交出我的剑并讨论你的要求。 但首先, 介绍你自己! 你是谁, 怎么敢攻击我们? ! 这是叛国! ";
			link.l1 = "... ";
			link.l1.go = "DTSG_Graf_Sheffild_2";
			SetCameraDialogMode(npchar);
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_2":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_3";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_3":
			dialog.text = "理查德.弗利特伍德船长。 你一定是谢菲尔德伯爵吧? 你说得完全正确, 这是叛国。 ";
			link.l1 = "... ";
			link.l1.go = "DTSG_Graf_Sheffild_5";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;
		case "DTSG_Graf_Sheffild_5":
			DialogExit();
			sld = CharacterFromID("DTSG_Graf_Sheffild");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_6";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_6":
			dialog.text = "你知道我是谁? 该死! 我就知道会发生这种事, 到处都是老鼠, 所以我请求, 甚至乞求派艘战船... ";
			link.l1 = "... ";
			link.l1.go = "DTSG_Graf_Sheffild_7";
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_7":
			DialogExit();
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_8";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_8":
			dialog.text = "这救不了你, 只是拖延不可避免的结局, 因为我会找到另一种方法。 而且没错, 说到叛国, 我指的是你, 谢菲尔德伯爵。 ";
			link.l1 = "... ";
			link.l1.go = "DTSG_Graf_Sheffild_9";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;
		case "DTSG_Graf_Sheffild_9":
			DialogExit();
			sld = CharacterFromID("DTSG_Graf_Sheffild");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_10";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_10":
			dialog.text = "那你对我一无所知, 先生! 人人都知道没有比我更忠于英格兰的人了! 你会后悔这个错误的, 记住我的话。 ";
			link.l1 = "... ";
			link.l1.go = "DTSG_Graf_Sheffild_12";
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_12":
			DialogExit();
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_13";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_13":
			dialog.text = "我没什么可后悔的, 因为我不是那个叛逃到荷兰人的人。 ";
			link.l1 = "... ";
			link.l1.go = "DTSG_Graf_Sheffild_15";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;
		case "DTSG_Graf_Sheffild_15":
			DialogExit();
			sld = CharacterFromID("DTSG_Graf_Sheffild");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_16":
			dialog.text = "什么? ! 你在胡说八道什么? ! 你被误导了, 像只疯狗一样追踪错误的线索\n咳咳, 没错, 我确实要去和荷兰西印度公司谈判。 但这是为了我们英格兰的利益, 船长。 这是个可怕的错误, 但我们还能纠正。 ";
			link.l1 = "... ";
			link.l1.go = "DTSG_Graf_Sheffild_17";
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_17":
			DialogExit();
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_18";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_18":
			dialog.text = "恐怕这不由我决定。 当然也不由你决定。 你们选错边了, 先生们。 再见。 ";
			link.l1 = "... ";
			link.l1.go = "DTSG_Graf_Sheffild_19";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;

		case "DTSG_Graf_Sheffild_19":
			DialogExit();
			LAi_SetActorType(pchar);
			sld = CharacterFromID("Fleetwood");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "1", 1.8);
			DoQuestCheckDelay("DTSG_Graf_Sheffild_20", 0.9);
		break;
		
		case "DTSG_Graf_Sheffild_22":
			dialog.text = "我们完事了。 我还以为那个胖子永远不会停止尖叫。 哦, 这些伯爵, 对吧, 查理? ";
			link.l1 = "我只是在想, 先生, 如果上校错了呢? 或者, 上帝保佑, 他骗我们来摆脱伯爵? ";
			link.l1.go = "DTSG_Graf_Sheffild_23";
		break;
		
		case "DTSG_Graf_Sheffild_23":
			dialog.text = "听我说, 我的朋友。 仔细听。 我们的服务在各方面都极其危险和困难。 任何事情都可能发生 —一个可悲的错误, 一个荒谬的巧合, 或者一次背信弃义的背叛\n为国家服务不只是给大炮装炮弹, 查理。 对当权者来说, 这是做出艰难决定。 而对我们这样的士兵来说 —是执行这些决定。 ";
			link.l1 = "但如果有一天我们流了无辜者的血呢, 船长? 那将落在我们手上, 我们的良心上。 ";
			link.l1.go = "DTSG_Graf_Sheffild_24";
		break;
		
		case "DTSG_Graf_Sheffild_24":
			dialog.text = "那么血将同样落在他们手上, 甚至更多。 让这安慰你吧。 关键是我们的意图是纯洁的 —铲除祖国的敌人\n现在帮我一把, 查理, 我们还需要让它看起来像荷兰人的攻击。 ";
			link.l1 = "是, 先生... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DTSG_Graf_Sheffild_25");
		break;
		
		case "DTSG_Knippel_101":
			dialog.text = "所以, 我们留下了假证据, 让它看起来像是荷兰人干的。 理查德和我再也没有讨论过那一天。 ";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				link.l1 = "嗯, 现在很多事情都说得通了。 我认为伯爵的某个亲戚或支持者是理查德之死的幕后黑手。 但为什么针对你? 你只是个炮手, 在那个悲伤的日子里没有做任何决定。 ";
				link.l1.go = "DTSG_Knippel_ZS_102";
				AddComplexLandExpToScill(50, 50, 50);
				Log_info("获得经验奖励");
			}
			else
			{
				link.l1 = "确实。 这是糟糕的交易, 而且臭气熏天。 也许有人发现了并决定为伯爵报仇。 但一个炮手值得这么大的花费吗? 金钱, 雇佣兵, 雇佣海狐... 不可能, 查理。 ";
				link.l1.go = "DTSG_Knippel_NS_102";
			}
		break;
		
		case "DTSG_Knippel_ZS_102":
			dialog.text = "也许这个人正在追捕理查德以前的所有船员。 你怎么看, 先生? ";
			link.l1 = "我认为我们应该远离安提瓜, 越快越好。 ";
			link.l1.go = "DTSG_Knippel_103";
		break;
		
		case "DTSG_Knippel_NS_102":
			dialog.text = "我也问过自己这个问题, 船长, 但我没有找到答案。 ";
			link.l1 = "该死。 有人来了。 我要求过不要打扰! ";
			link.l1.go = "DTSG_Knippel_103";
		break;
		
		case "DTSG_Knippel_103":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena"))
			{
				sld = characterFromId("Helena");
				ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
				sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
				sld.dialog.currentnode = "DTSG_Helena_1";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", 0, 0);
				break;
			}
			if (GetCharacterIndex("Tichingitu") != -1 && CheckPassengerInCharacter(pchar, "Tichingitu"))
			{
				sld = characterFromId("Tichingitu");
				ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
				sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
				sld.dialog.currentnode = "DTSG_Tichingitu_1";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", 0, 0);
				break;
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("Alonso", "Alonso", "man", "man", sti(pchar.rank), pchar.nation, 0, true, "soldier"));
				sld.name 	= "阿隆索";
				sld.lastname = "";
				ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
				sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
				sld.dialog.currentnode = "DTSG_Alonso_1";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", 0, 0);
				sld.location = "None";
			}
		break;
		
		case "DTSG_Helena_1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "查尔斯! ..";
				link.l1 = "怎么了, 海伦??";
				link.l1.go = "DTSG_Helena_2";
			}
			else
			{
				dialog.text = "查尔斯, 我记得你让我不要让任何人进来, 也不要打扰你和查理, 但是... ";
				link.l1 = "... 你决定自己来了。 好吧, 没关系, 海伦。 ";
				link.l1.go = "DTSG_Helena_2";
			}
		break;
		
		case "DTSG_Helena_2":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "一艘英国战船! 之前就发现了。 一开始我没在意, 但她随时都会到达我们这里! 我从未见过这么快的船。 ";
				link.l1 = "那谢谢你告诉我。 希望我们有时间在她靠近前做好准备。 海伦, 查理, 各就各位! ";
				link.l1.go = "DTSG_GotovimsyKBitve";
			}
			else
			{
				dialog.text = "... 你们可以稍后继续秘密会议。 一艘英国战船正朝我们驶来。 我觉得这很重要。 ";
				link.l1 = "好吧, 我去看看。 谢谢, 海伦。 ";
				link.l1.go = "DTSG_GotovimsyKBitve";
			}
		break;
		
		case "DTSG_Tichingitu_1":
			dialog.text = "船长, 一艘快船正朝我们驶来。 非常快。 神灵告诉我他们意图邪恶。 ";
			link.l1 = "谢谢你和神灵的警告。 以防万一, 准备战斗。 并把我的话传达给其他人。 ";
			link.l1.go = "DTSG_GotovimsyKBitve";
		break;
		
		case "DTSG_Alonso_1":
			dialog.text = "抱歉打扰了, 船长, 但事情紧急。 ";
			link.l1 = "哦, 希望真的很重要, 阿隆索。 报告。 ";
			link.l1.go = "DTSG_Alonso_2";
		break;
		
		case "DTSG_Alonso_2":
			dialog.text = "一艘英国船正在靠近。 是... ‘幻影’号, 船长。 ";
			link.l1 = "什么? 你确定吗? 又喝酒了, 嗯? ";
			link.l1.go = "DTSG_Alonso_3";
		break;
		
		case "DTSG_Alonso_3":
			dialog.text = "我确定, 船长 —加勒比没有其他船像她一样, 您知道的。 ";
			link.l1 = "的确。 我自己去看看 —让我们看看这艘‘幻影’是否是真的。 ";
			link.l1.go = "DTSG_GotovimsyKBitve";
		break;
		
		case "DTSG_GotovimsyKBitve":
			DialogExit();
			AddQuestRecord("DTSG", "17");
			
			if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena"))
			{
				sld = characterFromId("Helena");
				LAi_SetOfficerType(sld);
				sld.Dialog.Filename = "Quest\Saga\Helena.c";
				sld.Dialog.CurrentNode = "Helena_officer";
			}
			if (GetCharacterIndex("Tichingitu") != -1 && CheckPassengerInCharacter(pchar, "Tichingitu"))
			{
				sld = characterFromId("Tichingitu");
				LAi_SetOfficerType(sld);
				sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
				sld.Dialog.CurrentNode = "Tichingitu_officer";
			}
			if (GetCharacterIndex("Knippel") != -1 && CheckPassengerInCharacter(pchar, "Knippel"))
			{
				sld = characterFromId("Knippel");
				LAi_SetOfficerType(sld);
				sld.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
				sld.Dialog.CurrentNode = "Knippel_officer";
			}
			
			PChar.quest.DTSG_KortniPotopil.win_condition.l1 = "Character_sink";
			PChar.quest.DTSG_KortniPotopil.win_condition.l1.character = "DTSG_Kortni";
			PChar.quest.DTSG_KortniPotopil.win_condition = "DTSG_KortniPotopil";
			
			chrDisableReloadToLocation = false;
			bDisableCharacterMenu = false;
			InterfaceStates.Buttons.Save.enable = true;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			DeleteAttribute(pchar, "GenQuest.CannotWait");
		break;
		
		case "DTSG_Kortni":
			dialog.text = "哦... 但这还没有结束! 布莱恩, 你来了! 你到底去哪了? ";
			link.l1 = "这只会拖延不可避免的结局。 ";
			link.l1.go = "DTSG_Kortni_Pikar";
		break;
		
		case "DTSG_Kortni_Pikar":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			LAi_SetWarriorType(npchar);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetCheckMinHP(npchar, 10, true, "DTSG_KortniRanen");
			LAi_SetImmortal(npchar, false);
			
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_Mrt_Rocur", "citiz_8", "man", "man", sti(pchar.rank), ENGLAND, -1, false, "soldier"));
			sld.name = "布莱恩";
			sld.lastname = "塔瑟";
			GiveItem2Character(sld, "blade_20");
			EquipCharacterByItem(sld, "blade_20");
			GiveItem2Character(sld, "pistol5");
			EquipCharacterByItem(sld, "pistol5");
			AddItems(sld, "purse2", 1);
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
			LAi_SetHP(sld, 300.0, 300.0);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetCheckMinHP(sld, 10, true, "DTSG_PikarRanen");
			sld.location = "None";
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		break;
		
		case "DTSG_Kortni_1":
			dialog.text = "查尔斯.德莫尔。 没想到你走到了这一步。 可惜。 我本希望在这艘船上趁你不备抓住你。 ";
			link.l1 = "你知道我是谁? 那么, 是你在背后搞鬼 —你看起来像一只被迫离开舒适巢穴。 亲自出马而不是再派一只秃鹫的高空飞鸟。 ";
			link.l1.go = "DTSG_Kortni_2";
			
			Island_SetReloadEnableGlobal("Antigua", true);
			bQuestDisableMapEnter = false;
			LAi_LocationDisableOfficersGen("SentJons_town", false);
			DeleteQuestCondition("DTSG_KortniPotopil");
		break;
		
		case "DTSG_Kortni_2":
			dialog.text = "没错, 两点都对。 我想一个贵族可以从远处认出另一个贵族。 托马斯.林奇上校。 看来是时候像绅士一样交谈, 而不是试图摧毁彼此了。 也许我们可以达成一项互利的协议。 ";
			link.l1 = "我不能保证什么, 但我以贵族的名义向你保证, 至少我们会像文明人一样交谈, 上校。 ";
			link.l1.go = "DTSG_Kortni_3";
		break;
		
		case "DTSG_Kortni_3":
			dialog.text = "很好。 我无法和弗利特伍德进行这样的对话。 不过, 我们找到了对付他的筹码, 他不会再麻烦我们了。 很遗憾你这边没成功, 但没关系。 ";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				link.l1 = "整个加勒比都在谈论理查德的死。 那么, 是你干的! 我猜你提到的筹码是阿比盖尔? 顺便问一下, 她怎么样了? ";
				AddComplexLandExpToScill(50, 50, 50);
				Log_info("获得经验奖励");
			}
			else
			{
				link.l1 = "不是威胁, 你说? .. 那么, 你杀了他? 你是伯爵的支持者吗? ";
			}
			link.l1.go = "DTSG_Kortni_4";
		break;
		
		case "DTSG_Kortni_4":
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				dialog.text = "阿比盖尔? 啊, 那个年轻的犹太女人, 他的未婚妻。 再一次, 你证明了自己是个相当有洞察力的人。 她还活着, 很好 —我们答应了并为此交换了弗利特伍德的合作。 ";
				link.l1 = "相当的合作, 我得说。 但你为什么要这么做? 你是伯爵的支持者吗? ";
			}
			else
			{
				dialog.text = "支持者? 哦, 恰恰相反。 但你看, 有些牌不能再打了, 因为它们成为玩家的负担。 不幸的是, 理查德成为了其中之一。 ";
				link.l1 = "我明白了。 你铲除所有证人。 阿比盖尔怎么样了? 你也杀了她吗? ";
			}
			link.l1.go = "DTSG_Kortni_5";
		break;
		
		case "DTSG_Kortni_5":
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				dialog.text = "完全没有。 恰恰相反。 但理查德知道得太多了, 回到旧大陆后, 他变得危险。 他应该留在这里, 我们就不会取他的性命。 ";
				link.l1 = "你会铲除所有为你工作过的人吗, 上校? ";
			}
			else
			{
				dialog.text = "谁? 啊, 我想是他的未婚妻。 她是筹码。 他的命换她的命。 她很好, 我以名誉发誓。 ";
				link.l1 = "考虑到你所做的一切, 我怀疑你知道什么是名誉, 上校。 ";
			}
			link.l1.go = "DTSG_Kortni_6";
		break;
		
		case "DTSG_Kortni_6":
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				dialog.text = "我不会回答这个挑衅, 先生。 ";
				link.l1 = "那么回答这个 —你怎么得到这艘船的? 是... ‘幻影’号吗? ";
			}
			else
			{
				dialog.text = "我会忽略这个侮辱, 因为它来自一个从未不得不运用权力和影响事物秩序的人。 ";
				link.l1 = "说到事物, 你从哪里得到‘幻影’号的? 这是她吗? ";
			}
			link.l1.go = "DTSG_Kortni_7";
		break;
		
		case "DTSG_Kortni_7":
			dialog.text = "不完全是。 一艘宏伟的船, 嗯? 可惜她没能完成对付你的使命。 你知道这艘船的历史吗, 德莫尔船长? ";
			link.l1 = "你是指幽灵船和猎杀英国商人? ";
			link.l1.go = "DTSG_Kortni_8";
		break;
		
		case "DTSG_Kortni_8":
			dialog.text = "那个? 哦, 不。 我不是在说众所周知的事情。 我是说隐藏在视线之外的事情。 这艘双桅船是由约翰.范.默登和卢卡斯.罗登堡设计的\n那对搭档创造了一系列计划, 这艘船最终从哈瓦那的造船厂下水。 我们很幸运得到了原始蓝图。 最后, 我们全面重建了‘幻影’号, 甚至改进了她, 纠正了她设计中的一些缺陷。 ";
			link.l1 = "可惜, 正如你自己所说, 这对你帮助不大, 上校。 ";
			link.l1.go = "DTSG_Kortni_9";
		break;
		
		case "DTSG_Kortni_9":
			dialog.text = "你在笑吗? 别笑。 我承认, 你在船长和战士两方面都超越了我。 但我在这里仍然占上风。 ";
			link.l1 = "这是垂死的虚张声势吗? 还是像你这样的人通常的过度自信? 这些话背后是什么? ";
			link.l1.go = "DTSG_Kortni_10";
		break;
		
		case "DTSG_Kortni_10":
			dialog.text = "好问题。 在我看来, 你不仅仅是个像我研究中所说的好色之徒和决斗者。 我为这次会议的所有结果都采取了措施。 甚至包括我死于你的刀刃。 子弹或流弹的情况。 如果我今天死了, 你和查理会后悔没有加入弗利特伍德。 ";
			link.l1 = "更多的赏金猎人? 拜托。 这很不愉快和乏味, 但不是致命的。 我们当时击退了他们 —我们会再次击退他们。 ";
			link.l1.go = "DTSG_Kortni_11";
		break;
		
		case "DTSG_Kortni_11":
			dialog.text = "我毫不怀疑。 现在我又听到了那个无忧无虑的决斗者的声音。 不仅仅是赏金猎人。 海狐和英国海军情报部门的全部力量将像风暴一样降临在你头上, 就像海浪拍打渔船。 ";
			link.l1 = "你想从我这里得到什么? 你不指望我投降吧? ";
			link.l1.go = "DTSG_Kortni_12";
		break;
		
		case "DTSG_Kortni_12":
			dialog.text = "当然不。 这段时间我们对你研究得很好。 我想给你提供一个互利的交易。 一个拒绝是不明智的。 作为两个贵族, 我希望我们能达成协议。 ";
			link.l1 = "那么我重复这个问题, 上校, 你想要什么? 我猜是查理? .. 你认为你可以给我一些东西作为回报? 我不会为了几个金币而出卖。 ";
			link.l1.go = "DTSG_Kortni_13";
		break;
		
		case "DTSG_Kortni_13":
			dialog.text = "又对了。 这不仅仅是你所说的几个金币, 而是整座山 —10,000杜布隆。 如果我们达成协议, 定金将在皇家港的银行等你\n但我提供的最重要的东西是你的生命, 德莫尔船长。 你听到了。 如果我们现在都放下武器, 你把查理交给我们, 我们将停止所有追捕\n你听说过‘人与社会’的说法吗? 就你而言, 如果拒绝, 将是‘人与国家’。 决定吧, 查尔斯。 此时此地。 ";
			link.l1 = "你可以轻易地用你的头衔和影响力恐吓一两个傻瓜。 但我不是傻瓜。 我一英里外就能感觉到绝望。 出去。 并且庆幸我没有杀你 —你罪有应得。 ";
			link.l1.go = "DTSG_Kortni_PkCh_1";
			link.l2 = "你并不真的需要查理, 上校。 你需要他的沉默。 ";
			link.l2.go = "DTSG_Kortni_LT_1";
			link.l3 = "为了我和我手下的安全, 我同意这个, 不是因为贪图你的钱, 只是让你知道。 ";
			link.l3.go = "DTSG_Kortni_Sdat";
		break;
		
		case "DTSG_Kortni_PkCh_1":
			dialog.text = "你做出了一生中最糟糕的决定之一, 德莫尔船长。 我不羡慕你。 说真的。 你只能怪自己 —不会再有人给你类似的提议了。 尤其是我。 再见。 ";
			link.l1 = "等等, 上校。 ";
			link.l1.go = "DTSG_Kortni_PkCh_2";
		break;
		
		case "DTSG_Kortni_PkCh_2":
			dialog.text = "怎么, 你改变主意了? 我的话终于起作用了? ";
			link.l1 = "对, 恰恰相反。 ";
			link.l1.go = "DTSG_Kortni_PkCh_3";
		break;
		
		case "DTSG_Kortni_PkCh_3":
			dialog.text = "你什么意思? 解释一下。 ";
			link.l1 = "你的话只会坚定我对抗你的决心。 别那样看着我 —我不会杀你。 而且正如我所说, 我甚至会放你走。 但我想你不需要船也能应付。 ";
			link.l1.go = "DTSG_Kortni_PkCh_4";
		break;
		
		case "DTSG_Kortni_PkCh_4":
			dialog.text = "我不需要, 因为我有船。 ";
			link.l1 = "你说得对。 但只是关于不需要船。 你可能是个有影响力的人。 但你缺乏分寸感。 还有策略。 我会做你习惯做的事 —掌控局面。 ";
			link.l1.go = "DTSG_Kortni_PkCh_5";
		break;
		
		case "DTSG_Kortni_PkCh_5":
			dialog.text = "你没有, 德莫尔船长。 别自欺欺人了。 ";
			link.l1 = "完全掌控? 也许没有。 但你也没有 —你的生命现在在我手中, 上校。 以后我会怎么样不重要 —现在我可以为所欲为。 而我... 要这艘船。 你自由了。 海岸不远了。 ";
			link.l1.go = "DTSG_Kortni_PkCh_6";
		break;
		
		case "DTSG_Kortni_PkCh_6":
			dialog.text = "你不敢。 但从你的表情判断... 享受你的小胜利吧。 你已经做出... ";
			link.l1 = "是, 是, 我一生中最糟糕的决定之一。 我已经听过了。 离开这艘船。 我的船。 你自己跳下去, 还是我们把你扔到海里? ";
			link.l1.go = "DTSG_Kortni_PkCh_7";
		break;
		
		case "DTSG_Kortni_PkCh_7":
			DialogExit();
			
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto4", "", "", "", "DTSG_Kortni_Vyprygnul", 7);
			npchar.lifeday = 0;
			npchar.location = "None";
		break;
		
		case "DTSG_Kortni_PkCh_8":
			dialog.text = "我从没想过会看到他这样 —受辱, 从窗户跳出去, 四肢并用地游向岸边。 ";
			link.l1 = "看到了? 满意了? 太好了。 下一个就是你。 ";
			link.l1.go = "DTSG_Kortni_PkCh_9";
		break;
		
		case "DTSG_Kortni_PkCh_9":
			dialog.text = "您在说什么, 先生? 我们不是敌人; 我只是服从命令! .. 我至少可以要一艘船吗? 您再也不会见到我了! ";
			link.l1 = "如果我处在你的位置, 刚刚输给你, 你也不会放过我。 所以庆幸我没有杀你。 从窗户出去。 现在。 也许你能追上你的赞助人。 ";
			link.l1.go = "DTSG_Kortni_PkCh_10";
		break;
		
		case "DTSG_Kortni_PkCh_10":
			dialog.text = "我宁死也不愿受此屈辱, 先生! ";
			link.l1 = "如你所愿。 ";
			link.l1.go = "DTSG_Kortni_PkCh_11";
		break;
		
		case "DTSG_Kortni_PkCh_11":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			LAi_RemoveCheckMinHP(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_Kortni_Vyprygnul_3");
		break;
		
		case "DTSG_Kortni_PkCh_12":
			dialog.text = "那是上校, 对吧, 船长? ";
			link.l1 = "对。 往窗外看, 查理, 你不会后悔的。 ";
			link.l1.go = "DTSG_Kortni_PkCh_13";
		break;
		
		case "DTSG_Kortni_PkCh_13":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto4", "DTSG_Kortni_Vyprygnul_5", 6);
		break;
		
		case "DTSG_Kortni_PkCh_14":
			dialog.text = "上校? .. 我从没想过会看到这种事, 先生。 有人敢把这样头衔的人像普通水手一样扔到海里! 理查德绝不会这么做 —尊重军衔是他的核心原则。 ";
			link.l1 = "这是多年训练灌输给他的。 他是军人, 有相应的思维模式。 我不是, 我思考更广泛, 没有那样的... 限制。 ";
			link.l1.go = "DTSG_Kortni_PkCh_15";
		break;
		
		case "DTSG_Kortni_PkCh_15":
			dialog.text = "我们这样对他不会有麻烦吗? ";
			link.l1 = "呵, 你责备理查德, 却像他一样思考。 我们敢于反抗, 所以会被追捕一段时间。 但迟早, 即使是英国海军也会放弃我们。 对林奇来说, 这将变成个人恩怨。 但我们确保他下次不会再获得国家资源支持。 ";
			link.l1.go = "DTSG_Kortni_PkCh_16";
		break;
		
		case "DTSG_Kortni_PkCh_16":
			dialog.text = "你知道吗, 船长, 从今天起, 我更尊重你了。 我从不后悔没有和迪克一起乘‘瓦尔基里’号离开, 而是决定加入你。 ";
			link.l1 = "谢谢你, 我的朋友! 准备好 —风暴正在聚集。 但你知道吗? 有预感我们会再次胜利。 走吧, 该回到甲板了。 ";
			link.l1.go = "DTSG_Kortni_PkCh_17";
		break;
		
		case "DTSG_Kortni_PkCh_17":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			
			DoQuestCheckDelay("DTSG_Kortni_Vyprygnul_7", 3.0);
			Achievment_Set("ach_CL_114");
		break;
		
		case "DTSG_Kortni_LT_1":
			dialog.text = "并不完全正确, 不过就我个人而言, 如果查理从现在起保持沉默, 我不在乎他。 但我的同事们想看到他的尸体。 他们知道他长什么样\n这是现实生活, 查尔斯, 不是童年保姆给我们读的童话或骑士诗歌, 我看不出让所有人都满意的解决方案。 ";
			link.l1 = "但我有。 你总能找到相似的尸体。 买相似的衣服。 疏通关系。 我会和查理谈谈。 我以我的名誉作保证。 ";
			link.l1.go = "DTSG_Kortni_LT_2";
		break;
		
		case "DTSG_Kortni_LT_2":
			if (sti(pchar.reputation.nobility) > 70)
			{
				notification("声望检查通过", "None");
				dialog.text = "这... 是个大风险。 不仅关乎我是否能信任你的话。 还关乎我的同事看到像查理的尸体时是否会相信我。 我不会平白无故冒这个险... ";
				link.l1 = "多少? ";
				link.l1.go = "DTSG_Kortni_LT_4";
			}
			else
			{
				notification("声望太低! ("+XI_ConvertString(GetReputationName(71))+")", "None");
				dialog.text = "像你这样声望的人的话? 你在开玩笑。 光有贵族出身不足以让人信任。 ";
				link.l1 = "请原谅, 上校, 这话从另一个有着相似出身和行为的人嘴里说出来。 ";
				link.l1.go = "DTSG_Kortni_LT_3";
			}
		break;
		
		case "DTSG_Kortni_LT_3":
			dialog.text = "当然, 你说得对。 但在这种情况下, 这关乎我的信任, 不是别人的。 而你作为担保人不适合我\n我最后一次告诉你。 把查理给我。 当然, 如果你不想重蹈弗利特伍德的覆辙。 ";
			link.l1 = "你可以轻易地用你的头衔和影响力恐吓一两个傻瓜。 但我不是傻瓜。 我一英里外就能感觉到绝望。 出去。 并且庆幸我没有杀你 —你罪有应得。 ";
			link.l1.go = "DTSG_Kortni_PkCh_1";
		break;
		
		case "DTSG_Kortni_LT_4":
			dialog.text = "终于直奔主题了。 一百万比索。 最终报价。 ";
			if (sti(pchar.Money) >= 1000000)
			{
				link.l1 = "我会把钱给你。 别以为我穷或者不珍惜手下的生命。 两者都不是。 拿着。 ";
				link.l1.go = "DTSG_Kortni_LT_7";
			}
			else
			{
				link.l1 = "你胃口不小, 虽然我没抱太大期望。 但现在我没有那么多, 而且... ";
				link.l1.go = "DTSG_Kortni_LT_5";
			}
		break;
		
		case "DTSG_Kortni_LT_5":
			dialog.text = "没有银币 —没有交易。 你以为我会仁慈吗? 先生, 我看起来像圣人吗? ";
			link.l1 = "但也许你可以等一下? 你方便在哪里。 什么时候再见面? 我可以从放贷人那里借杜布隆。 ";
			link.l1.go = "DTSG_Kortni_LT_6";
		break;
		
		case "DTSG_Kortni_LT_6":
			dialog.text = "那你觉得我比想象中还要天真\n我不是乡下姑娘, 不会永远等待那个曾经与她有过关系的人\n没钱? 反正我也没要。 我只想要查理。 尽管你惹了这么多麻烦, 你对我没用。 ";
			link.l1 = "你可以轻易地用你的头衔和影响力恐吓一两个傻瓜。 但我不是傻瓜。 我一英里外就能感觉到绝望。 出去。 并且庆幸我没有杀你 —你罪有应得。 ";
			link.l1.go = "DTSG_Kortni_PkCh_1";
		break;
		
		case "DTSG_Kortni_LT_7":
			dialog.text = "你真的那么在意可怜的查理吗? 无论如何, 你的贵族精神值得尊重。 确保你的炮手像坟墓一样沉默。 否则你们俩都会进坟墓。 ";
			link.l1 = "我保证。 你也信守诺言, 停止所有追捕。 ";
			link.l1.go = "DTSG_Kortni_LT_8";
			AddMoneyToCharacter(pchar, -1000000);
		break;
		
		case "DTSG_Kortni_LT_8":
			dialog.text = "我也保证。 还有一件事。 尽管你赢得光明正大, 但我要把我的船带走。 你知道, 这是定制的。 而且非常昂贵。 ";
			link.l1 = "胜利者的权利呢? 但我不会得寸进尺。 这次就算了。 ";
			link.l1.go = "DTSG_Kortni_LT_9";
		break;
		
		case "DTSG_Kortni_LT_9":
			DialogExit();
			
			LAi_Fade("DTSG_Kortni_Otkup_1", "");
		break;
		
		case "DTSG_Kortni_LT_10":
			dialog.text = "我几乎遗憾地说, 布莱恩, 恐怕我们的合作到此结束。 ";
			link.l1 = "... ";
			link.l1.go = "DTSG_Kortni_LT_11";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Mrt_Rocur"));
		break;
		case "DTSG_Kortni_LT_11":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("DTSG_Mrt_Rocur");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_12";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_12":
			dialog.text = "我... 自由了吗, 上校? 你会取消对我的悬赏吗, 我可以像守法公民一样重新开始? ";
			link.l1 = "... ";
			link.l1.go = "DTSG_Kortni_LT_13";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_KortniClone"));
		break;
		case "DTSG_Kortni_LT_13":
			DialogExit();
			sld = CharacterFromID("DTSG_KortniClone");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_14";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_14":
			dialog.text = "我得说你见得太多了 —就像已故的弗利特伍德。 我刚才就在你面前收了贿赂。 ";
			link.l1 = "... ";
			link.l1.go = "DTSG_Kortni_LT_15";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Mrt_Rocur"));
		break;
		case "DTSG_Kortni_LT_15":
			DialogExit();
			sld = CharacterFromID("DTSG_Mrt_Rocur");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_16":
			dialog.text = "我... 我不会告诉任何人任何事, 我对上帝发誓! ";
			link.l1 = "... ";
			link.l1.go = "DTSG_Kortni_LT_17";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_KortniClone"));
		break;
		case "DTSG_Kortni_LT_17":
			DialogExit();
			sld = CharacterFromID("DTSG_KortniClone");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_18";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_18":
			dialog.text = "当然, 你不会。 ";
			link.l1 = "... ";
			link.l1.go = "DTSG_Kortni_LT_19";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Mrt_Rocur"));
		break;
		case "DTSG_Kortni_LT_19":
			DialogExit();
			sld = CharacterFromID("DTSG_Mrt_Rocur");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_20";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_20":
			dialog.text = "不! ..";
			link.l1 = "... ";
			link.l1.go = "DTSG_Kortni_LT_21";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_KortniClone"));
		break;
		case "DTSG_Kortni_LT_21":
			DialogExit();
			
			sld = CharacterFromID("DTSG_KortniClone");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "1", 1.8);
			DoQuestCheckDelay("DTSG_Kortni_Otkup_3", 0.9);
			
			LAi_SetActorType(NPChar);
			LAi_ActorAttack(NPChar, sld, "");
		break;
		
		case "DTSG_Kortni_LT_22":
			dialog.text = "别那样看着我, 查尔斯。 如果我一直担心布莱恩会不会泄密, 我根本睡不着。 ";
			link.l1 = "我甚至不知道是否该对所见之事感到惊讶。 ";
			link.l1.go = "DTSG_Kortni_LT_23";
		break;
		
		case "DTSG_Kortni_LT_23":
			dialog.text = "你不应该。 我是认真的。 我只要求你们俩对所发生的事保持沉默。 我会设法找个相似的尸体, 好好处理面容, 善用这笔钱, 说服我的同事。 ";
			link.l1 = "谢谢你, 上校。 ";
			link.l1.go = "DTSG_Kortni_LT_24";
		break;
		
		case "DTSG_Kortni_LT_24":
			dialog.text = "现在没什么可谢我的。 他们可能不信我, 到时候追捕会重新开始, 这总是有风险的。 现在再见, 德莫尔船长。 我要乘我的船离开了。 这里没有异议 —我已经帮了你和查理一个大忙。 ";
			link.l1 = "好吧, 再见。 ";
			link.l1.go = "DTSG_Kortni_LT_25";
			
			pchar.GenQuest.CannotTakeShip = true;
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition.l1 = "MapEnter";
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition = "DTSG_Kortni_KechNeNash";
		break;
		
		case "DTSG_Kortni_LT_25":
			DialogExit();
			
			//sld = CharacterFromID("Knippel");
			sld = GetCharacter(CreateCharacterClone(CharacterFromID("Knippel"), 0));
			sld.id = "KnippelClone";
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_26";
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
			LAi_SetActorType(pchar);
			LAi_SetActorType(sld);
			SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
			LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 2.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 2.0);
		break;
		
		case "DTSG_Kortni_LT_26":
			dialog.text = "你知道你在和谁说话吗, 船长? 一位上校! 是他策划了这一切吗? ";
			link.l1 = "我知道, 他做了自我介绍。 你说得对 —是他。 ";
			link.l1.go = "DTSG_Kortni_LT_27";
		break;
		
		case "DTSG_Kortni_LT_27":
			dialog.text = "很奇怪, 先生, 因为我曾知道他是理查德的上级。 这怎么可能? 为什么他像没事人一样离开? 他到底想要什么? ";
			link.l1 = "实际上, 这没什么奇怪的。 执行阴暗命令的人往往冒着生命危险, 不是因为敌人, 而是因为他们的上级。 他想要你的脑袋, 查理。 ";
			link.l1.go = "DTSG_Kortni_LT_28";
		break;
		
		case "DTSG_Kortni_LT_28":
			dialog.text = "我不明白, 船长。 那他为什么离开? 他接受失败了吗? ";
			link.l1 = "他才不会。 我不得不给他一堆金子, 差不多和你的脑袋一样重。 也许还多一点。 准确地说, 一百万比索。 ";
			link.l1.go = "DTSG_Kortni_LT_29";
		break;
		
		case "DTSG_Kortni_LT_29":
			dialog.text = "而你... 为我付了那么一大笔钱? ";
			link.l1 = "嗯, 不只是为你。 也为我自己。 还有所有弟兄。 但没错, 查理, 主要是为你。 如果我们杀了他, 之后会面临永恒的惩罚性远征。 ";
			link.l1.go = "DTSG_Kortni_LT_30";
		break;
		
		case "DTSG_Kortni_LT_30":
			dialog.text = "我... 不敢相信, 先生。 只是... 谢谢你。 我认为如果换作弗利特伍德, 他不会这么做。 ";
			link.l1 = "在他逃跑后你对他太有偏见了。 理查德只是想和阿比盖尔过平静的生活。 很遗憾他没能如愿。 另外, 他信守诺言, 还清了你的债务。 呵, 我, 弗利特伍德 —你肯定和船长们很有缘, 嗯, 查理? ";
			link.l1.go = "DTSG_Kortni_LT_31";
		break;
		
		case "DTSG_Kortni_LT_31":
			dialog.text = "可不是嘛, 船长。 那么, 现在一切都结束了? ";
			link.l1 = "是的, 我那昂贵的朋友。 至少现在是。 战斗结束了 —你可以告诉弟兄们收起武器。 让他们准备升帆。 ";
			link.l1.go = "DTSG_Kortni_LT_32";
		break;
		
		case "DTSG_Kortni_LT_32":
			DialogExit();
			
			InterfaceStates.Buttons.Save.enable = true;
			LAi_SetPlayerType(pchar);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			
			AddQuestRecord("DTSG", "19");
			CloseQuestHeader("DTSG");
			LAi_ReloadBoarding();
			Achievment_Set("ach_CL_114");
			sld = CharacterFromID("Knippel");
			SetCharacterPerk(sld, "Bombardier");
			notification("解锁炮手", "链弹");
		break;
		
		case "DTSG_Kortni_Sdat":
			dialog.text = "我不在乎你为什么同意 —无论是出于贪婪。 恐惧还是对部下的责任。 关键是你同意了。 我会派我的人去皇家港给银行家下达指示。 ";
			link.l1 = "好吧。 真不敢相信这终于结束了。 ";
			link.l1.go = "DTSG_Kortni_Dengi_1";
			link.l2 = "你知道吗, 去他的钱。 钱总能再赚。 我想从你这里换查理, 上校, 还有别的东西。 ";
			link.l2.go = "DTSG_Kortni_Kech_1";
		break;
		
		case "DTSG_Kortni_Kech_1":
			dialog.text = "哦? 我得承认, 你让我惊讶, 德莫尔船长。 在你看来, 如果一堆金子不适合你, 什么能等价于老炮手的秃头? ";
			link.l1 = "你自己说的 —一艘宏伟的船, 设计缺陷已修正。 我渴望亲自试试她。 你还有蓝图。 但查理只有一个。 另外, 让我满意符合你的利益。 ";
			link.l1.go = "DTSG_Kortni_Kech_2";
		break;
		
		case "DTSG_Kortni_Kech_2":
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) > 70)
			{
				dialog.text = "你是个强硬的谈判者。 你知道我们造一艘这样的船花了多少钱吗? ";
				link.l1 = "(值得信赖) (荣誉) 我非常清楚, 所以我才问。 你的手已经伸进狼的嘴里直到肘部。 你可以试试射杀这只狼。 但你会失去这只手。 不止是手。 ";
				dialog.text = "你真是个难缠的谈判者。 你知道我们建造其中一个花了多少钱吗? ";
				link.l1 = "(值得信赖) (荣誉) 我心里非常清楚, 所以才这么问。 你的手已经伸到狼的嘴里, 直到肘部。 你可以试着朝这只狼开枪, 但你会失去那只手, 而且不止是手。 ";
			}
			else
			{
				dialog.text = "恐怕造一艘这样的船花费远超我们为你准备的金子。 但你逗乐了我, 查尔斯。 以一种好的方式。 ";
				link.l1 = "值得一试。 ";
				if (!IsCharacterPerkOn(pchar, "Trustworthy")) notification("特质检查失败", "Trustworthy");
				if (sti(pchar.reputation.nobility) < 71) notification("声望太低! ("+XI_ConvertString(GetReputationName(71))+")", "None");
			}
			link.l1.go = "DTSG_Kortni_Kech_3";
		break;
		
		case "DTSG_Kortni_Kech_3":
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) > 70)
			{
				dialog.text = "我看你知道自己想要什么, 并在生活中追求目标\n好吧。 双桅船是你的了。 但别想那笔钱 —放贷人会告诉你他什么都不知道。 ";
				link.l1 = "这适合我。 ";
				link.l1.go = "DTSG_Kortni_Kech_4";
				pchar.questTemp.DTSG_Kech = true;
			}
			else
			{
				dialog.text = "当然。 我的人生就是抓住机会并保护自己免受风险的故事\n所以把查理带到这里, 我们和平分手。 之后, 你甚至可以拿走定金。 但我要乘这艘船离开。 ";
				link.l1 = "那我们解决吧。 ";
				link.l1.go = "DTSG_Kortni_VizyvaemKnippel";
				pchar.questTemp.DTSG_depozit = true;
			}
		break;
		
		case "DTSG_Kortni_Kech_4":
			dialog.text = "我不能说完全满意。 但我想尽快结束这一切。 现在把我想要的给我。 ";
			link.l1 = "不是‘什么’, 而是‘谁’。 但如你所愿。 ";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel";
		break;
		
		case "DTSG_Kortni_Dengi_1":
			dialog.text = "我也不能。 我开始相信, 这不仅关乎一个人是谁, 还关乎他周围的人 —抓一个老炮手的简单工作, 因为他的船长, 也就是你, 查尔斯, 变成了头疼的事\n把查理叫来。 这堆烂摊子将彻底结束 —我们起锚, 我们的船将分开。 ";
			link.l1 = "分开, 你说? ";
			link.l1.go = "DTSG_Kortni_Dengi_2";
		break;
		
		case "DTSG_Kortni_Dengi_2":
			dialog.text = "你看起来很惊讶? 你一定以为双桅船是你应得的战利品? 我们不是海盗, 德莫尔船长。 文明人遵循不同的。 复杂得多的规则。 船归我。 ";
			link.l1 = "那么... ";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel";
			pchar.questTemp.DTSG_depozit = true;
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel":
			DialogExit();
			
			//sld = CharacterFromID("Knippel");
			sld = GetCharacter(CreateCharacterClone(CharacterFromID("Knippel"), 0));
			sld.id = "KnippelClone";
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_VizyvaemKnippel_2";
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_2":
			dialog.text = "你没事吧, 先生? 那是... 上校吗? ";
			link.l1 = "是的, 查理, 是上校。 你来得正是时候 —我正要自己去叫你。 ";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_3";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_3":
			dialog.text = "叫我, 船长? .. 现在? 你为什么和这个... 人谈了这么久? 我以为你有麻烦了, 所以自己来了。 ";
			link.l1 = "没错。 尽管胜利了, 我们仍有麻烦。 如果上校和我没有找到解决方案, 我们会继续麻烦。 ";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_4";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_4":
			dialog.text = "你设法说服他放过我们了吗, 先生? ";
			link.l1 = "不幸的是, 只是我。 不是我们。 你... 要和他走, 查理。 ";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_5";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_5":
			dialog.text = "什么? .. 但为什么? .. 我们赢了! ";
			link.l1 = "你不明白吗? 我们不能一直赢下去 —他们不拿到你的脑袋不会罢休。 ";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_6";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_6":
			dialog.text = "我不敢相信你会这样对老查理, 船长。 你就像迪克。 你们俩都曾告诉我是我的朋友。 结果都抛弃了我和所有亲近的人。 ";
			link.l1 = "这是船长的负担, 他的责任。 我看你无法理解, 因为你只需要给大炮装炮弹。 ";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_7";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_7":
			dialog.text = "无法理解? .. 也许我只是不像你一样是叛徒? 你知道你该去哪里吗? ";
			link.l1 = "下地狱? 也许你是对的。 我们都活该。 ";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_8";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_8":
			dialog.text = "去你的, 先生。 ";
			link.l1 = "... ";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_9";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_9":
			DialogExit();
			
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_VizyvaemKnippel_10";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			
			sld = CharacterFromID("KnippelClone");
			LAi_SetActorType(sld);
			sld = CharacterFromID("Knippel");
			RemovePassenger(pchar, sld);
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_10":
			dialog.text = "滑稽。 我差点笑了。 你听到了吗, 布莱恩? \n有时听普通农民说话感觉如沐春风, 一点也不烦躁。 你做了正确的决定, 查尔斯。 我知道这对你有多难。 但请放心, 你和你的人现在都不会受苦了。 ";
			link.l1 = "我希望你遵守这个承诺, 上校。 ";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_11";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_11":
			dialog.text = "我是信守诺言的人。 阿比盖尔的命运就是证明。 也看看布莱恩。 一个法国海盗, 但他在该加入正确一方时做出了正确的选择。 只要他忠诚为我们服务, 就没人碰他。 像他一样, 你也在朝正确的方向前进, 德莫尔船长。 ";
			if (CheckAttribute(pchar, "questTemp.DTSG_Kech"))
			{
				link.l1 = "说到前进。 我想尽快离开这里。 乘你答应我的这艘, 无疑很快的船, 上校。 ";
			}
			else
			{
				link.l1 = "我不是海盗。 我也不打算现在加入英国海军。 但我打算领取承诺的奖励。 ";
			}
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_12";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_12":
			if (CheckAttribute(pchar, "questTemp.DTSG_Kech"))
			{
				dialog.text = "我不隐瞒 —这感觉就像从心里撕掉她。 我得花钱买新的, 但也许值得 —查理可能泄密的想法困扰我太久了\n如果你不谈论或对英国犯下严重罪行, 就认为我们不再是敌人。 享受新船吧; 她确实很美。 再见, 查尔斯。 布莱恩 —给我们准备一艘船。 查理 —跟我来, 你对此没有发言权。 ";
				link.l1 = "再见。 你们所有人。 ";
				link.l1.go = "DTSG_Kortni_VizyvaemKnippel_13";
			}
			else
			{
				dialog.text = "可惜, 我们总是需要有能力的人, 不管他们的国籍如何。 但当然, 你仍然应得奖励。 你可以安全地去皇家港 —我会乘这艘双桅船比任何其他船先到那里。 ";
				link.l1 = "希望如此。 我希望在皇家港不会有武装护卫等着我。 ";
				link.l1.go = "DTSG_Kortni_VizyvaemKnippel_14";
			}
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_13":
			DialogExit();
			
			AddQuestRecord("DTSG", "20");
			CloseQuestHeader("DTSG");
			ChangeOfficersLoyality("bad_all", 5);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "fame", -10);
			AddCrewMorale(Pchar, -10);
			LAi_ReloadBoarding();
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_14":
			dialog.text = "又怀疑我的话? 你应感到羞耻。 你已经赢得了整个英国海军的感激。 如果你需要什么, 或者决定加入我们, 联系我, 德莫尔船长。 ";
			link.l1 = "有一次, 我试图获得英国情报部门的支持和联系。 没有成功。 所以再见, 上校。 ";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_15";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_15":
			DialogExit();
			
			if (CheckAttribute(pchar, "questTemp.DTSG_depozit"))
			{
				ChangeCharacterNationReputation(pchar, ENGLAND, 30);
			}
			pchar.GenQuest.CannotTakeShip = true;
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition.l1 = "MapEnter";
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition = "DTSG_Kortni_KechNeNash";
			AddQuestRecord("DTSG", "21");
			CloseQuestHeader("DTSG");
			ChangeOfficersLoyality("bad_all", 5);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "fame", -10);
			AddCrewMorale(Pchar, -10);
			LAi_ReloadBoarding();
			Achievment_Set("ach_CL_114");
		break;
		
	}
}