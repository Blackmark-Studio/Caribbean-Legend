// 城市监狱
void ProcessDialogEvent()
{
	int amount, iGunQty, iGunGoods, iGunPrice, iTemp;
	int iTest;
	ref NPChar, sld, location;
	ref arItem;
	ref rColony;
	aref Link, NextDiag;
	string sTemp;
	float locx, locy, locz;
	bool  ok;
	// belamour 用于夜间冒险 -->
	int i;
	int SoldQty = 0;
	int SoldNum[10];
	// <--

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // 调用按城市的对话 -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Prison\" + NPChar.City + "_Prison.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // 调用按城市的对话 <--

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "NoMoreTalkExit":
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;
		//-------------- —监狱长 ------------------
		case "First_officer":
			dialog.text = RandPhraseSimple("我是监狱长。 你在这里需要什么? ", "你需要什么? 为什么来监狱? ");
			NextDiag.TempNode = "First_officer";
			if(startHeroType == 4 && NPChar.location == "SantaCatalina_prison" && !CheckAttribute(pchar, "questTemp.HelenSCprison"))
			{
				dialog.text = "麦克阿瑟小姐? 见到你很惊讶。 据我所知, 我们没有逮捕你或斯温森船长的任何船员。 ";
				link.l1 = "我只是在这里, 先生。 这不允许吗? 我没有背着你和囚犯聊天。 ";
				link.l1.go = "Helen_meeting";
				pchar.questTemp.HelenSCprison = true;
				break;
			}
			// --> Sinistra 旧罪的长影
			if(CheckAttribute(pchar,"questTemp.DTSG_AntiguaTrevoga") && npchar.city == "SentJons")
			{
				dialog.text = "啊, 查尔斯.德.莫尔... 你应该被逮捕并和你的军官关在一起, 但是... 银行的事件被认为是一个令人遗憾的误会。 ";
				link.l1 = "我喜欢你开始这次谈话的方式, " + GetFullName(NPChar) + "先生。 我可以解释一切。 ";
				link.l1.go = "DTSG_AntiguaTrevoga_2";
				break;
			}
			// < —旧罪的长影
			
			//--> 加斯科涅的枷锁
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "jailskiper")
			{
				link.l1 = "警官, 我听说你的监狱里有个叫福尔克.德鲁克的人。 我能做些什么来释放他吗? ";
                link.l1.go = "Sharlie";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "freeskiper")
			{
				link.l1 = "警官, 我又来谈囚犯福尔克.德鲁克的事。 我已经买下了他的债务权, 我希望释放这个人并交给我。 这是他的债务文件, 看看。 ";
                link.l1.go = "Sharlie_3";
				break;
			}	
			//< —加斯科涅的枷锁
			
			//belamour legendary edition 对话, 如果英雄有军衔和国家功勋 -->
			// 有许可证的军官
			if(IsOfficerFullEquip())
			{
				dialog.text = "问候你, 船长。 什么风把你吹到这里? ";
			}
			// 舰队副司令
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "问候你, 舰队副司令! 我能为你做什么? ";
			}
			// 总督将军
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				dialog.text = "大人, 总督将军! 你有什么命令吗? ";
			}
			// < —legendary edition
			link.l1 = "哦, 没什么特别的, 你知道, 只是在城里看看, 所以顺便逛到这里。 ";
			link.l1.go = "exit";
			link.l2 = "我想谈点生意。 ";
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakFort"))
			{
				if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
				{
					link.l2.go = "F_ShipLetters_1";
				}
				else
				{
					link.l2.go = "quests";
				}		
			}
			else
			{
				if(CheckAttribute(pchar,"questTemp.ReasonToFast") && !CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
				{
					link.l2.go = "ReasonToFast_Prison1";
				}
				else
				{
					link.l2.go = "quests";
				}	
			}
			if (!sti(pchar.questTemp.jailCanMove))
			{
				link.l4 = "我想进入监狱里面。 ";
				link.l4.go = "ForGoodMove";		
			}
			if (CheckAttribute(pchar, "questTemp.jailCanMove.City") && npchar.city == pchar.questTemp.jailCanMove.City)
			{
				link.l5 = "嘿, 你能告诉我名叫 " + GetFullName(characterFromId(pchar.questTemp.jailCanMove.prisonerId)) + "的囚犯因什么罪服刑吗? ";
				link.l5.go = "KnowAboutPrisoner";	
			}
			
			if(CheckAttribute(pchar,"GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
			{
				if(!CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
				{
					bool zMsm = (CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour")) && (!CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor"));
					if(pchar.GenQuest.CaptainComission == "MayorTalkBad" || zMsm) //和市长谈过并拒绝或听到传闻, 但没和市长谈过
					{
						link.l6 = "我听说 " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + "巡逻队的前队长 " + pchar.GenQuest.CaptainComission.Name + "被关押在这里。 我能和他谈谈吗? ";
						link.l6.go = "CapComission_PrisonBad1";
					}
					if(pchar.GenQuest.CaptainComission == "MayorTalkGood")
					{
						link.l6 = "我 " +GetFullName(pchar)+ ", 代表总督 " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen") + "并按其命令, 需要与前队长 " + pchar.GenQuest.CaptainComission.Name + "谈话。 ";
						link.l6.go = "CapComission_PrisonGood1";
					}
				}	
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if(pchar.GenQuest.EncGirl.Father == "fort_keeper"  && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = "这是关于你女儿的... ";
						link.l9.go = "EncGirl_1";
					}
				}
			}
			
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "begin" && NPChar.location == pchar.GenQuest.Marginpassenger.City + "_prison")
			{
				link.l12 = "我和你有生意, 警官。 我相信这会让你感兴趣, 因为它与你的职责有关。 ";
				link.l12.go = "Marginpassenger";
			}
			
			// Warship, 16.05.11。 生成器 "正义出售".
			if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.PrisonWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_prison")
			{
				link.l13 = "我想和你谈谈某个人 - " + PChar.GenQuest.JusticeOnSale.SmugglerName + "。 如果我没弄错, 他是你的囚犯。 ";
				link.l13.go = "JusticeOnSale_1";
			}
			
			// --> belamour 夜间冒险者
			if(CheckAttribute(pchar,"GenQuest.NightAdventureToJail"))
			{
				link.l14 = "你好, 警官。 据我所知, 不久前, 一个醉酒的市民在试图与街上的警卫打架后被拘留。 "; 
				link.l14.go = "NightAdventure_CitizenHomie";
			}
			
			if(CheckAttribute(pchar,"GenQuest.NightAdventureToPrisoner"))
			{
				link.l14 = "警官, 我和哨兵谈过, 他撤回了指控。 这是他的凭证。 "; 
				link.l14.go = "NightAdventure_HomieToPrisoner";
			}
			// < —冒险者
			NextDiag.TempNode = "First_officer";
		break;
		
		// --> Jason 绑架者
		case "Marginpassenger":
			dialog.text = "是吗? 你愿意告诉我什么? ";
			link.l1 = "最近, 我在街上被 " + pchar.GenQuest.Marginpassenger.Name + "拦住, 他提议我安排一件肮脏的事: 绑架一个名叫 " + pchar.GenQuest.Marginpassenger.q1Name + "的人然后勒索赎金。 这是 " + pchar.GenQuest.Marginpassenger.Text + "... ";
			link.l1.go = "Marginpassenger_1";
		break;
		
		case "Marginpassenger_1":
			dialog.text = "嗯... 这很有趣 - 请继续! ";
			link.l1 = "他知道 " + pchar.GenQuest.Marginpassenger.q1Name + "计划乘坐的船名。 是 " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name"))) + ", 名叫'" + pchar.GenQuest.Marginpassenger.ShipName + "'。 此外, 他告诉我那艘船计划起航的时间。 ";
			link.l1.go = "Marginpassenger_2";
		break;
	
		case "Marginpassenger_2":
			dialog.text = "他建议你绑架乘客然后勒索赎金? ";
			link.l1 = "正是。 为了收取赎金, 我会去 " + XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.Targetcity) + ", 去找一个名叫 " + pchar.GenQuest.Marginpassenger.q2Name + "的人。 我为此信息付了钱, 但当然, 我不打算绑架那个人。 ";
			link.l1.go = "Marginpassenger_3";
		break;
		
		case "Marginpassenger_3":
			dialog.text = "所以你决定来见我并让我知道? ";
			link.l1 = "正是。 我确信那个恶棍的行为正在威胁你们镇上的公民, 我希望你会采取适当的措施。 ";
			link.l1.go = "Marginpassenger_4";
		break;
		
		case "Marginpassenger_4":
			dialog.text = "你来找我是对的, " + GetAddress_Form(NPChar) + "! 这个流氓, " + pchar.GenQuest.Marginpassenger.Name + ", 长期以来一直在我们的追踪之下。 我会调查, 如果所有你说的都得到证实, 我们会把这个混蛋关进监狱半年。 这会教训他不要对受尊敬的公民策划那种阴谋! \n好吧, 为了你的诚实和愿意为正义事业服务, 我当然会向我们的总督报告你的行为, 这当然会影响他对你的态度... 你知道, 是积极的。 谢谢你的帮助, 船长! ";
			link.l1 = "嗯... 不客气, 很高兴能帮忙。 再见! ";
			link.l1.go = "Marginpassenger_5";
		break;
		
		case "Marginpassenger_5":
			DialogExit();
			NextDiag.CurrentNode = "First_officer";
			AddQuestRecord("Marginpassenger", "20");
			AddQuestUserData("Marginpassenger", "sName", pchar.GenQuest.Marginpassenger.Name);
			CloseQuestHeader("Marginpassenger");
			pchar.quest.Marginpassenger_InWorld.over = "yes"; //取下计时器
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 5);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//权威
			ChangeContrabandRelation(pchar, -25);
			if (GetCharacterIndex("MarginCap") != -1)
			{
				sld = characterFromId("MarginCap");
				sld.lifeday = 0;
				Map_ReleaseQuestEncounter(sld.id);
				Group_DeleteGroup("Sea_MarginCap1");
			}
		break;
		//< —绑架者

		case "EncGirl_1":
			dialog.text = "我洗耳恭听。 ";
			link.l1 = "我把你的逃犯带来了。 ";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "哦, 船长, 太感谢你了! 她怎么样? 受伤了吗? 她为什么逃跑? 为什么? \n她不明白吗? 新郎是个富有而重要的人! 年轻是天真愚蠢的... 甚至是残忍的。 记住这一点! ";
			link.l1 = "好吧, 你是她的父亲, 最终决定在你, 但我不会急于举行婚礼... ";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "你知道什么? 你有自己的孩子吗? 没有? 当你有了一个, 来找我, 我们再谈。 \n我向任何把她带回给家人的人承诺了奖励。 ";
			link.l1 = "谢谢。 你应该留意她。 我有一种预感, 她不会就此罢休。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;
		
		// ----------------------- —匆忙的理由 -----------------------------
		case "ReasonToFast_Prison1":
			pchar.questTemp.ReasonToFast.SpeakOther = true;
			dialog.text = "我洗耳恭听, 船长。 ";
			link.l1 = "我想告诉你关于你的驻军一名军官和海盗之间的犯罪勾结 (解释此事) 。 ";
			if(makeint(pchar.reputation.nobility) < 41)
			{
				link.l1.go = "ReasonToFast_Prison_BadRep";			
			}
			else
			{
				link.l1.go = "ReasonToFast_Prison_GoodRep";	
			}
		break;
		case "ReasonToFast_Prison_GoodRep":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 
				// 叉子_A
				dialog.text = "谢谢你, " + GetSexPhrase("先生","小姐") + "! 我会立即下令逮捕这个恶棍。 \n然而, 你已经产生了费用, 而市政金库, 唉, 是空的... ";
				link.l1 = "先生! 我不是为了钱... ";
				link.l1.go = "ReasonToFast_Prison_GoodRep_11";
				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// 获得地图
				dialog.text = "谢谢你, " + GetSexPhrase("先生","小姐") + "! 我会立即下令逮捕这个恶棍。 \n想想看! 我们想奖励他个人武器以表彰他的出色服务。 很高兴一切都解决了, 我没有什么可羞愧的! ";
				link.l1 = "总是很高兴为正义服务。 ";
				link.l1.go = "ReasonToFast_Prison_GoodRep_21";			
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// 巡逻队被击败
				dialog.text = "  " + GetSexPhrase("先生","女士") + "! 我们一直怀疑那个军官和他的混蛋们有肮脏的行为, 但我认为你在没有证人的情况下处理他们是轻率的举动。 ";
				link.l1 = "先生! 但我必须自卫... ";
				link.l1.go = "ReasonToFast_Prison_GoodRep_31";	
				pchar.questTemp.ReasonToFast.speakAfterPatrolDied = true;	
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";	
			}
		break;
		
		case "ReasonToFast_Prison_BadRep":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 
				// 叉子_A
				dialog.text = "船长, 你意识到你做了什么吗? ! 我们已经尝试设置这个陷阱一个多月了! 现在, 只是为了你的娱乐, 你破坏了我们巡逻队与信使 " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN) + "的会面, 现在你到这里来吹嘘? ! 也许你现在可以告诉我, 我该如何解释这次行动的所有费用? ! ";
				link.l1 = "大人! 你只是拒绝看到重点... ";
				link.l1.go = "ReasonToFast_Prison_BadRep1";
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// 获得地图
				dialog.text = "让我看看这张地图... \n你在开玩笑吗? 这张破烂的羊皮纸是证据? ";
				link.l1 = "大人! 你只是拒绝看到重点... ";
				link.l1.go = "ReasonToFast_Prison_BadRep1";
				TakeItemFromCharacter(pchar, "mapQuest");	
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_B";	
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// 巡逻队被击败
				dialog.text = "这是破坏整个巡逻队的一个原始理由。 好吧, 至少你到这里来省去了我们寻找凶手的需要。 ";
				link.l1 = "大人! 你只是拒绝看到重点... ";
				link.l1.go = "ReasonToFast_Prison_BadRep1";			
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
			}		
		break;
		
		case "ReasonToFast_Prison_GoodRep_11":
			dialog.text = "尽管如此, 我认为你的努力仍然应该得到奖励。 拿着, 这张地图; 它是在一个最近被绞死的海盗的物品中发现的。 上帝保佑, 也许你真的会找到那个宝藏, 尽管我觉得不太可能... ";
			link.l1 = "谢谢你, 你真慷慨! ";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "15");
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			GiveItem2Character(pchar, "mapQuest"); 
			arItem = ItemsFromID("mapQuest");
			ReasonToFast_GenerateTreasureMap(arItem);
			pchar.questTemp.ReasonToFast.state = "chain_A"; // 叉子_A, 不生成提示
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		case "ReasonToFast_Prison_GoodRep_21":
			dialog.text = "你的热情值得称赞。 请接受这把刀作为奖励 - 这是我能为你做的最少的事。 哦, 你可以自己保留这张地图。 我相信群岛上有很多这样的假货。 ";
			link.l1 = "谢谢你, 你真慷慨! ";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "14");
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
			pchar.questTemp.ReasonToFast.state = "chain_B"; // 已经获得地图
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		case "ReasonToFast_Prison_GoodRep_31":
			dialog.text = "可能, 可能... 好吧, 我们就说这笔交易是由神圣的正义和我们主的意志决定的。 ";
			link.l1 = "谢谢你, 你真慷慨! ";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			AddQuestRecord("ReasonToFast", "16");
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar,"ReasonToFast");			
		break;
		
		case "ReasonToFast_Prison_BadRep1":
			dialog.text = "别敢教训我! 对我来说, 很明显你和这些恶棍是一伙的! 卫兵, 抓住这个'好心人'! ";
			link.l1 = "没门! ";
			link.l1.go = "fight";
			
			pchar.quest.ReasonToFast_ExitFromTown.win_condition.l1			= "EnterToSea";           	
            pchar.quest.ReasonToFast_ExitFromTown.function    				= "ReasonToFast_ExitFromTownFight";
			pchar.questTemp.ReasonToFast.canSpeakSailor = true;			
			pchar.TownEscape = true;
			Flag_PIRATE();
		break;
		// ----------------------- —匆忙的理由 -----------------------------
		
		// ------------------------ —操作'大帆船'----------------------------
		case "CapComission_PrisonBad1":
			dialog.text = "你和他有什么事? ";
			link.l1 = "我有几件私事要讨论。 ";
			link.l1.go = "CapComission_PrisonBad2";
		break;
		
		case "CapComission_PrisonBad2":
			dialog.text = "船长, 我有直接命令, 拘留任何询问 " + pchar.GenQuest.CaptainComission.Name + "的人, 并将其送到官邸进一步审讯。 ";
			link.l1 = "你这里设置得真好! 让囚犯自己来向你自首! ";
			link.l1.go = "CapComission_PrisonBad3";
		break;
		
		case "CapComission_PrisonBad3":
			dialog.text = "尽管如此, 我还是请求你交出武器! ";
			link.l1 = "去你的! 有本事就强行拿! ";
			link.l1.go = "fight";
			CaptainComission_GenerateCaptainInPrison(); // 丹妮拉 。 以防万一, 以便正常生成。 
			AddDialogExitQuest("CaptainComission_GenerateCapJail");
		break;
		
		case "CapComission_PrisonGood1":
			dialog.text = "是的, 当然。 我有总督的命令, 在这件事上为你提供协助。 你现在可以探望囚犯了。 ";
			link.l1 = "谢谢... ";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			AddDialogExitQuest("CaptainComission_GenerateCapJail");
		break;
		
		case "CapComission_PrisonFree1":
		if(CheckAttribute(pchar,"GenQuest.CaptainComission"))// 林务员 。 如果船长被杀或没有, 对话分开
		{
			dialog.text = "嗯, 船长, 我没有权力释放这个囚犯。 你必须请求总督的许可。 ";
			link.l1 = "警官, 我是为了调查的利益行事。 囚犯同意与当局合作并透露藏匿处。 时间紧迫 - 走私者可以找到贵重货物, 然后它将为民众所失去。 ";
			link.l1.go = "CapComission_PrisonFree2";
		}
         else
		 {
         	dialog.text = "你不应该杀了他, 船长... 不过这对我来说没关系。 我们将不得不处决你而不是他。 卫兵! 抓住他! ";
            link.l2 = "你选错了惹的人... !";
             link.l2.go = "fight";
			 NextDiag.TempNode = "First_officer";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			AddDialogExitQuest("OpenTheDoors");
		 }			 
		break;
		
		case "CapComission_PrisonFree2":
			dialog.text = "但我可以给他派护卫。 ";
			link.l1 = "不需要 - 我有足够的护卫。 此外, 我不希望藏匿处的位置公开。 ";
			link.l1.go = "CapComission_PrisonFree3";
		break;
		
		case "CapComission_PrisonFree3":
			dialog.text = "嗯... 哦, 好吧。 但你将用你的脑袋为他负责。 ";
			link.l1 = "当然。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "First_officer";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			AddDialogExitQuest("OpenTheDoors");
		break;
		// ------------------------ —操作'大帆船'----------------------------
		
		case "F_ShipLetters_1":
			dialog.text = "现在说, 我在听。 ";
			link.l1 = "我身上有一些船只文件。 它的主人一定是丢了, 我相信这可能会让你感兴趣。 ";
			link.l1.go = "F_ShipLetters_2";
			pchar.questTemp.different.GiveShipLetters.speakFort = true;
		break;
		
		case "F_ShipLetters_2":			
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "胡说! 不要分散我工作的注意力! 如果你在意的话, 去港口当局那里! ";
				link.l1 = "好吧, 我想谢谢... ";
				link.l1.go = "exit";
			}
			else
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					dialog.text = "是的, 是当地的主人。 也许 " + sti(pchar.questTemp.different.GiveShipLetters.price2) + " 比索的奖金将作为对你警惕性的充分奖励, 船长。 ";
					link.l1 = "也许不是。 ";
					link.l1.go = "F_ShipLetters_3";	
					link.l2 = "慷慨的提议。 那么文件是你的了! ";
					link.l2.go = "F_ShipLetters_4";
				}
				else
				{
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
					{
						dialog.text = "哦, 现在这真的很有趣! 我相信城市财政部会很高兴为你在打击非法贸易中的贡献支付你 " + sti(pchar.questTemp.different.GiveShipLetters.price4) + " 比索。 ";
						link.l1 = "也许不是。 ";
						link.l1.go = "F_ShipLetters_3";
						link.l2 = "慷慨的提议。 那么文件是你的了! ";
						link.l2.go = "F_ShipLetters_4";
					}
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
					{
						dialog.text = "哦, 主啊! 你来找我是多么好的机会。 我想我不幸的同事会很高兴支付你 " + sti(pchar.questTemp.different.GiveShipLetters.price3) + " 比索, 以避免这件事的公开。 ";
						link.l1 = "也许不是。 ";
						link.l1.go = "F_ShipLetters_3";
						link.l2 = "慷慨的提议。 那么文件是你的了! ";
						link.l2.go = "F_ShipLetters_4";
					}
				}
			}
		break;
		
		case "F_ShipLetters_3":
			dialog.text = "这是我的城市, 船长。 ";
			link.l1 = "我会记住的。 ";
			link.l1.go = "exit";
		break;
		
		case "F_ShipLetters_4":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price4)); 
				}
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price3)); 
				}
			}
						
			if((sti(pchar.questTemp.different.GiveShipLetters.variant) == 0) || (sti(pchar.questTemp.different.GiveShipLetters.variant) == 2))
			{	
				ChangeCharacterComplexReputation(pchar,"nobility", -1); 
				OfficersReaction("bad"); 
			}	
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //取下计时器 
			AddQuestRecord("GiveShipLetters", "8");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		
        case "ForGoodMove":
			//belamour legendary edition 对话, 如果英雄有军衔和国家功勋 -->
			// 总督将军
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				dialog.text = "当然, 你可以看到一切 - 我这里秩序井然! ";
				link.l1 = "好吧, 让我们检查一下, 中尉。 ";
				link.l1.go = "exit";
				pchar.questTemp.jailCanMove = true;
				break;
			}
			// 舰队副司令
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "当然, 大人。 你可以通过。 ";
				link.l1 = "谢谢你, 警官。 ";
				link.l1.go = "exit";
				pchar.questTemp.jailCanMove = true;
				break;
			}
			// 有许可证的军官
			if(IsOfficerFullEquip() && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "嗯, 我认为没有理由拒绝你 - 毕竟, 你是为 " + NationNameGenitive(sti(npchar.nation)) + "服务的船只的船长。 进来吧。 "; 
				link.l1 = "谢谢你, 警官。 ";
				link.l1.go = "exit";
				pchar.questTemp.jailCanMove = true;
				break;
			}
			// < —legendary edition
			dialog.text = NPCStringReactionRepeat("但你为什么需要它? 相信我, 除了小偷和强盗, 没有什么值得感兴趣的。 ", "我们已经讨论过你的那个愿望了。 ", 
				"又来? 我们已经谈过两次了! ", "嗯, 又来... ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("尽管如此, 我还是想加入你的地牢之旅。 我非常感兴趣! ", "是的, 正是。 但我想谈谈这个。 ", 
				"好吧, 也许第三次... ", "希望见到你的囚犯不会让我失望。 ", npchar, Dialog.CurrentNode);
			link.l1.go = "ForGoodMove_1";
		break;
		
        case "ForGoodMove_1":
			pchar.questTemp.jailCanMove.money = 20+hrand(3)*10;
			if (sti(colonies[FindColony(npchar.city)].jail))
			{
				dialog.text = "嗯, 我认为没有理由拒绝。 " + FindRussianDublonString(sti(pchar.questTemp.jailCanMove.money)) + " - 直到你离开监狱, 你可以自由地沿着走廊走, 甚至和囚犯交谈。 ";
				if (PCharDublonsTotal() >= sti(sti(pchar.questTemp.jailCanMove.money)))
				{
					link.l1 = "我同意, 这是你的硬币! ";
					link.l1.go = "ForGoodMove_agree";
				}
				link.l2 = "那不行。 对于沿着走廊漫无目的地游荡来说, 这太多了。 ";
				link.l2.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple("不, 这被规定严格禁止。 什么? 你认为我们这里有马戏团吗? 走开, 不要分散我工作的注意力。 ", "我不能允许陌生人在我的监狱里走来走去。 请停止打扰我! ");
				link.l1 = "好吧, 如你所说... ";
				link.l1.go = "exit";
			}
		break;
		
        case "ForGoodMove_agree":
            dialog.text = "好的, 你现在可以开始你的游览了... ";
			link.l1 = "谢谢你, 警官。 ";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			RemoveDublonsFromPCharTotal(sti(pchar.questTemp.jailCanMove.money)));
		break;
		
        case "KnowAboutPrisoner":
			switch (pchar.questTemp.jailCanMove.ownerPrison)
			{
				case "0": sTemp = "因谋杀。 "; break;
				case "1": sTemp = "他被指控海盗罪。 "; break;
				case "2": sTemp = "因土匪和抢劫罪。 "; break;
				case "3": sTemp = "他因偷窃被抓。 "; break;
				case "4": sTemp = "因小偷小摸。 "; break;
				case "5": sTemp = "因欺诈。 "; break;
				case "6": sTemp = "因流浪和乞讨。 "; break;
			}
			dialog.text = sTemp;
			// 总督将军
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				link.l1 = "我明白了... 把他交给我, 警官, 然后我会自己决定这个囚犯的命运。 ";
				link.l1.go = "KnowAboutPrisoner_gengov";
			DeleteAttribute(pchar, "questTemp.jailCanMove.City");
		break;
			}
			// 舰队副司令
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				link.l1 = "我明白了... 把他交给我, 警官, 然后我会自己决定这个囚犯的命运。 ";
				link.l1.go = "KnowAboutPrisoner_admiral";
				DeleteAttribute(pchar, "questTemp.jailCanMove.City");
				break;
			}
			link.l1 = "我明白了... 有没有可能保释。 担保... 或以其他方式释放他? ";
			link.l1.go = "KnowAboutPrisoner_" + pchar.questTemp.jailCanMove.ownerPrison;
			DeleteAttribute(pchar, "questTemp.jailCanMove.City");
		break;
		
        case "KnowAboutPrisoner_0":
			dialog.text = "当然不行。 那个该上绞架的家伙会直接下地狱。 总督特别关注他的案子! ";
			link.l1 = "呵呵, 我知道了... ";
			link.l1.go = "notFree_exit";
		break;	
		
		case "KnowAboutPrisoner_1":
			dialog.text = "你在开玩笑吗? 他早就该上绞架了! 他肯定很快就会和绳子结婚。 忘了吧。 ";
			link.l1 = "知道了。 已经忘了... ";
			link.l1.go = "notFree_exit";
		break;
		
        case "KnowAboutPrisoner_2":
			dialog.text = "我不这么认为。 他给我们市民带来了很多麻烦。 所以别问了。 ";
			link.l1 = "嗯, 我知道了。 ";
			link.l1.go = "notFree_exit";
		break;
		
        case "KnowAboutPrisoner_3":
			dialog.text = "可能不会。 他是个小偷, 小偷必须待在监狱里。 ";
			link.l1 = "哦! 说得好, 中尉! ";
			link.l1.go = "notFree_exit";
		break;
		
        case "KnowAboutPrisoner_4":
			dialog.text = "真的, 我不知道。 他只是偷了一件小事。 我不能放他走, 但让他在监狱里腐烂肯定也不对。 ";
			link.l1 = "那么, 把他交给我, 中尉。 我会为他支付保释金 - 当然是合理的数额。 ";
			link.l1.go = "KnowAboutPrisoner_free";
		break;
		
        case "KnowAboutPrisoner_5":
			dialog.text = "释放? 这似乎有可能。 在我看来, 把那个小混混关在这里没有意义。 ";
			link.l1 = "那么, 把他交给我, 中尉。 我会为他支付保释金 - 当然是合理的数额。 ";
			link.l1.go = "KnowAboutPrisoner_free";
		break;
		
		case "KnowAboutPrisoner_6":
			dialog.text = "嗯... 你的话有道理。 这个流浪汉不属于这里 - 他只是传播污秽和疾病... ";
			link.l1 = "那么, 把他交给我, 中尉。 我会为他支付保释金 - 当然是合理的数额。 ";
			link.l1.go = "KnowAboutPrisoner_free";
		break;
		
        case "KnowAboutPrisoner_free":
			pchar.questTemp.jailCanMove.ownerPrison.money = 50+hrand(10)*10;
			dialog.text = "好吧, 我们成交。 " + FindRussianDublonString(sti(pchar.questTemp.jailCanMove.ownerPrison.money)) + " 现金, 你现在就可以带他走。 ";
			if (PCharDublonsTotal() >= sti(pchar.questTemp.jailCanMove.ownerPrison.money))
			{
				link.l1 = LinkRandPhrase("太好了! 我同意! ","你有交易, 警官! ","太好了。 我准备支付那笔捐款。 ");
				link.l1.go = "KnowAboutPrisoner_agree";
			}
			link.l2 = "不, 那太贵了。 我想我会放弃。 ";
			link.l2.go = "KnowAboutPrisoner_exit";
		break;
		
        case "KnowAboutPrisoner_agree":
			dialog.text = "好的, 你可以去他的牢房, 把那个流浪汉带走。 ";
			link.l1 = "谢谢。 ";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			RemoveDublonsFromPCharTotal(sti(pchar.questTemp.jailCanMove.ownerPrison.money));
			Log_Info("你已经给了 " + FindRussianDublonString(sti(pchar.questTemp.jailCanMove.ownerPrison.money)) + "");
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId)
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_canMove";
		break;
		
        case "KnowAboutPrisoner_exit":
			dialog.text = "嗯, 这是你的选择。 我不会再给你机会... ";
			link.l1 = "不需要。 ";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId);
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_expansive";
		break;
		
        case "notFree_exit":
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId);
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_notFree";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		// belamour legendary edition -->
		// 总督将军
		case "KnowAboutPrisoner_gengov":
			dialog.text = "当然, 大人, 如果你愿意, 那就带走这个不幸的人。 只是要小心, 他仍然是个罪犯... ";
			link.l1 = "那太好了。 别担心, 中尉, 我知道我在做什么。 ";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId)
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_canMove";
		break;
		// 舰队副司令
		case "KnowAboutPrisoner_admiral":
			dialog.text = "嗯... 我甚至不知道... 实际上, 我不能就这样放囚犯走。 但你仍然是舰队副司令, 所以你可能有权带走这个罪犯。 ";
			link.l1 = "那太好了。 别担心, 中尉, 我知道我在做什么。 ";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId)
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_canMove";
		break;
		// < —legendary edition
		//-------------- —守护者 ------------------
        case "First_protector":
			// 总督将军
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				dialog.text = "总督将军, 大人! 进来, 但要小心: 你可以从这些罪犯那里期待任何事情... ";
				link.l1 = "别担心, 士兵, 如果发生什么事, 我会处理的。 ";
				link.l1.go = "exit";
				NextDiag.TempNode = "First_protector";
				break;
			}
			// 舰队副司令
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "问候你, 舰队副司令! 我在这里值班: 我确保没有人未经允许进入或离开。 但你, 当然, 有权自由通过这里。 ";
				link.l1 = "那太好了。 ";
				link.l1.go = "exit";
				NextDiag.TempNode = "First_protector";
				break;
			}
			if (sti(pchar.questTemp.jailCanMove))
			{
				dialog.text = RandPhraseSimple("你可以通过, 监狱长给了他的许可。 ", "我收到了监狱长的命令。 你可以自由通过。 ");
				link.l1 = "非常好。 ";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison.money");
			}
			else
			{
				dialog.text = RandPhraseSimple("没有监狱长的特别许可, 你不能再往前走! ", "我只对监狱长负责! 如果你试图在没有他许可的情况下再往前走, 你就完了! ");
				link.l1 = RandPhraseSimple("我知道", "好吧") + ", 士兵。 ";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First_protector";
		break;
		//-------------- —士兵 ------------------
        case "First_soldier":
            dialog.text = RandPhraseSimple("我在值班, 别打扰我。 ", "走开, 我不允许和你说话。 ");
			link.l1 = "好的, 士兵。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "First_soldier";
		break;
		//-------------- —囚犯 ------------------
        case "First_prisoner": 
			if (GetNationRelation2MainCharacter(sti(npchar.nation)) == RELATION_ENEMY)
			{
				dialog.text = LinkRandPhrase("呵呵, 这不是个好时机吗! ", "砍他们, " + GetSexPhrase("伙计","姑娘") + ", 砍! ", "哦, 见鬼! 我已经失去了看到我狱卒尸体的所有希望! ");
				link.l1 = RandPhraseSimple("嘿! ", "啊! ");
				link.l1.go = "NoMoreTalkExit";
				if (rand(10) > 6 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && !CheckAttribute(pchar, "GenQuest.PrisonQuestLock") && !CheckAttribute(pchar, "quest.GivePrisonFree") && !CheckAttribute(pchar, "quest.GivePrisonFree_Over") && !CheckAttribute(pchar, "quest.DeliverToBander")) // Addon 2016-1 Jason 海盗线
				{
					dialog.text = RandPhraseSimple("等等, " + GetSexPhrase("伙计","姑娘") + "! 释放我! ", "听着, " + GetSexPhrase("伙计","姑娘") + ", 请打开牢房。 ");
					link.l1 = "为什么? ";
					link.l1.go = "Prisoner_1"; // 关于释放囚犯的任务
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("我被指控抢劫, 但我是无辜的! ", "啊, 你这个衣冠楚楚的人渣... 你想在我的牢房里坐一会儿吗? ! 呵呵呵... ", "我是无辜的! ");
				link.l1 = RandPhraseSimple("闭嘴! ", "我他妈的不在乎你... ");
				link.l1.go = "NoMoreTalkExit";
				if (rand(10) > 6 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && !CheckAttribute(pchar, "GenQuest.PrisonQuestLock") && !CheckAttribute(pchar, "quest.GivePrisonFree_Over") && !CheckAttribute(pchar, "quest.GivePrisonFree") && !CheckAttribute(pchar, "quest.DeliverToBander") && !sti(colonies[FindColony(npchar.city)].HeroOwn)) // Addon 2016-1 Jason 海盗线
				{
					dialog.text = RandPhraseSimple("等等, " + GetSexPhrase("伙计","姑娘") + ", 别这么快过来! ", "别着急, " + GetSexPhrase("伙计","姑娘") + ", 我们谈谈。 ");
					link.l1 = "为什么? ";
					if (rand(1))
					{
						link.l1.go = "Prisoner_1"; // 关于释放囚犯的任务
					}
					else
					{
						link.l1.go = "Deliver_1"; // 关于传递消息的任务
					}
				}
			}
		break;
		// ------------------ —释放囚犯 --------------------
        case "Prisoner_1":
            dialog.text = "听我说, 伙计。 别以为我看起来不好什么的。 我只是需要离开这里... ";
			link.l1 = "什么? ! ";
			link.l1.go = "Prisoner_2";
			GetChestPlaceName();
			pchar.questTemp.jailCanMove.prisonerId = npchar.id; //记住Id
			pchar.questTemp.jailCanMove.IsTrue = rand(4); //宝藏类型
			pchar.questTemp.jailCanMove.Item1 = GenQuestPrison_GenerateArtefact();
			pchar.questTemp.jailCanMove.Item2 = GenQuestPrison_GenerateBlade();
			pchar.questTemp.jailCanMove.Name = GetFullName(npchar); //角色名字
			npchar.nation = PIRATE;
		break;
        case "Prisoner_2":
            dialog.text = "你听到的! 帮助我, 我就能报答... ";
			link.l1 = "现在这很有趣。 你是谁, 你能给我什么? ";
			link.l1.go = "Prisoner_3";
		break;
        case "Prisoner_3":
            dialog.text = "我的名字是 " + GetFullName(npchar) + "。 我在一个安全的地方藏了一些东西。 只要把我弄出去, 带我到 " + XI_ConvertString(pchar.questTemp.jailCanMove.islandId + "Acc") + "。 在那里, 在一个洞穴里, 我有宝藏。 我们去拿并分享! ";
			link.l1 = "你的藏匿处有什么? 我怎么知道你说的是实话? ";
			link.l1.go = "Prisoner_4";
		break;
        case "Prisoner_4":
            dialog.text = "我发誓我说的是实话! 至于藏匿处 - 有宝藏和钱... ";
			link.l1 = "不, 伙计。 我不会为了一个可疑的藏匿处冒我的风险。 对不起... ";
			link.l1.go = "Prisoner_5";
			if (GetNationRelation2MainCharacter(sti(npchar.nation)) != RELATION_ENEMY)
			{			
				// belamour legendary edition舰队司令和 governor 可以不用钱达成协议
				bool bAdmiral = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation);
				bool bGenGov = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == GetBaseHeroNation());
				if(!bAdmiral && !bGenGov)
				{
				link.l2 = "嗯, 这可能值得冒险... 我建议如下: 我可以消灭监狱里的警卫, 把你带到我的船上。 如果一切顺利, 我希望你一直待在我身边, 直到我们到达 " + XI_ConvertString(pchar.questTemp.jailCanMove.islandId + "Voc") + "的洞穴。 成交? "; // belamour gen
				link.l2.go = "Prisoner_agree"; //武力释放方式
				}
				link.l3 = "好吧, 我会试着帮助你。 我会和监狱长谈谈。 也许, 我能保释你出来。 ";
				link.l3.go = "ToPrisonHead_agree"; //和平释放方式
			}
			else
			{
				link.l2 = "好吧, 我会相信你并打开你的牢房。 我希望你一直待在我身边, 直到我们到达 " + XI_ConvertString(pchar.questTemp.jailCanMove.islandId + "Voc") + "的洞穴。 成交? ";
				link.l2.go = "Prisoner_agree_3"; //武力释放方式, 当狱警被杀时
			}
		break;
        case "Prisoner_5":
            dialog.text = RandPhraseSimple("该死的你, 你这个流氓! ", "该死的你骗了我,人渣... ");
			link.l1 = RandPhraseSimple("你也一样, 再见... ", "月亮不需要狗的吠叫... ");
			link.l1.go = "NoMoreTalkExit";
		break;
        case "Prisoner_agree":
            dialog.text = "好吧。 我不是处于挑剔的位置。 ";
			link.l1 = "好的。 我现在就打破你的锁让你出来, 我们突围。 你准备好了吗? ";
			link.l1.go = "Prisoner_agree_1";
		break;
        case "Prisoner_agree_1":
            dialog.text = "是的, " + GetSexPhrase("伙计","姑娘") + ", 我准备好了! ";
			link.l1 = "那我们开始吧! ";
			link.l1.go = "Prisoner_agree_2";
		break;
        case "Prisoner_agree_2":
			string slai_group = GetNationNameByType(sti(npchar.nation))  + "_citizens";
			LAi_group_AttackGroup(slai_group, LAI_GROUP_PLAYER);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
            AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			Pchar.quest.GivePrisonFree.win_condition.l1 = "location";
			Pchar.quest.GivePrisonFree.win_condition.l1.location = pchar.questTemp.jailCanMove.placeId;
			Pchar.quest.GivePrisonFree.win_condition = "GivePrisonFree";			
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			//LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

        case "Prisoner_agree_3":
            dialog.text = "好吧。 我不是处于挑剔的位置。 ";
			link.l1 = "好的。 尽快跟着我 - 我们仍然需要到达我的船。 不要拖延! ";
			link.l1.go = "Prisoner_agree_4";
		break;
        case "Prisoner_agree_4":
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
            AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			Pchar.quest.GivePrisonFree.win_condition.l1 = "location";
			Pchar.quest.GivePrisonFree.win_condition.l1.location = pchar.questTemp.jailCanMove.placeId;
			Pchar.quest.GivePrisonFree.win_condition = "GivePrisonFree";
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			//LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
		break;

        case "ToPrisonHead_agree":
            dialog.text = "好吧, 你可以试试。 希望我们能成功! 但不要浪费时间 - 几天后我就会离开这里... ";
			link.l1 = "在这里等着, 我会安排一切。 ";
			link.l1.go = "NoMoreTalkExit";
			pchar.questTemp.jailCanMove.City = npchar.City; //城市
			pchar.questTemp.jailCanMove.ownerPrison = rand(6); //犯罪性质
			SetTimerCondition("GivePrisonFree_Over", 0, 0, 2, false);
			AddQuestRecord("GivePrisonFree", "5");
			AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("",""));
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
		break;

		case "ToPrisonHead_canMove":
            dialog.text = "那么, 你觉得怎么样, " + GetSexPhrase("伙计", "姑娘") + "? ";
			link.l1 = "一切都安排好了, 我可以带你离开这里。 ";
			link.l1.go = "ToPrisonHead_canMove_1";
		break;
        case "ToPrisonHead_canMove_1":
            dialog.text = "那我们离开这里吧! 哦, 主啊, 我太高兴了! ";
			link.l1 = "我们说清楚。 我希望你一直待在我身边, 直到我们到达 " + XI_ConvertString(pchar.questTemp.jailCanMove.islandId + "Dat") + "的洞穴, 你一步都不能落在后面。 以防万一。 你同意吗? ";
			link.l1.go = "ToPrisonHead_canMove_2";
		break;
        case "ToPrisonHead_canMove_2":
            dialog.text = "当然, 我同意! 更何况我也没有选择的余地。 ";
			link.l1 = "那你自由了。 ";
			link.l1.go = "ToPrisonHead_canMove_exit";
		break;
        case "ToPrisonHead_canMove_exit":
			pchar.quest.GivePrisonFree_Over.over = "yes";
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
            AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			Pchar.quest.GivePrisonFree.win_condition.l1 = "location";
			Pchar.quest.GivePrisonFree.win_condition.l1.location = pchar.questTemp.jailCanMove.placeId;
			Pchar.quest.GivePrisonFree.win_condition = "GivePrisonFree";			
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			//LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
		break;

        case "ToPrisonHead_notFree":
			switch (pchar.questTemp.jailCanMove.ownerPrison)
			{
				case "0": sTemp = "谋杀"; break;
				case "1": sTemp = "海盗罪"; break;
				case "2": sTemp = "土匪行为"; break;
				case "3": sTemp = "偷窃"; break;
			}
            dialog.text = "那么, 你觉得怎么样, " + GetSexPhrase("伙计", "姑娘") + "? ";
			link.l1 = "我无法安排你的释放。 你被指控犯有 " + sTemp + ", 所以无法保释。 ";
			link.l1.go = "ToPrisonHead_notFree_1";
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
		break;
		
        case "ToPrisonHead_notFree_1":
            dialog.text = "但我是被诽谤的! 哦, 魔鬼! 现在我该怎么办? 我会在这里活活腐烂! ";
			link.l1 = "对不起, 伙计, 但我帮不了你。 ";
			link.l1.go = "ToPrisonHead_notFree_2";
			link.l2 = "只剩下一个机会了 —用武力释放你。 我现在就打破你的锁让你出来, 我们突围。 你准备好了吗? ";
			link.l2.go = "Prisoner_agree_1";
			pchar.quest.GivePrisonFree_Over.over = "yes";
		break;
		
        case "ToPrisonHead_notFree_2":
            dialog.text = RandPhraseSimple("诅咒你! ", "该死的, 你骗了我, 婊子... ");
			link.l1 = "也祝你一切顺利。 再见... ";
			link.l1.go = "NoMoreTalkExit";
			AddQuestRecord("GivePrisonFree", "7");
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			DeleteAttribute(pchar, "questTemp.jailCanMove.islandId");	
			DeleteAttribute(pchar, "questTemp.jailCanMove.placeId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.prisonerId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.IsTrue");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Sum");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Name");
		break;

        case "ToPrisonHead_expansive":
			dialog.text = "那么, 有什么好消息吗, " + GetSexPhrase("伙计", "姑娘") + "? ";
			link.l1 = "释放你的保释金太高了, 我没有那么多钱。 我不得不停止帮助你。 ";
			link.l1.go = "ToPrisonHead_notFree_2";
			pchar.quest.GivePrisonFree_Over.over = "yes";
		break;
		//==> 在宝藏藏匿的地方
        case "PrisonerInPlace":
			switch (sti(pchar.questTemp.jailCanMove.IsTrue))
			{
				case 0:
					dialog.text = "听着, 我都检查过了, 但没有找到宝藏。 真遗憾会是这样。 一定是有人在我们之前挖走了。 ";
					link.l1 = "怎么会这样? ! ";
					link.l1.go = "PrisonerInPlace_1";
				break;
				case 1:
					dialog.text = "我找到了! 宝藏还在我原来放的地方。 ";
					link.l1 = "太好了。 那么, 我们分了吧? ";
					link.l1.go = "Node_1";
				break;
				case 2:
					dialog.text = "嗯, 这是我的藏匿处。 没什么值钱的, 但这是我的全部了。 按照约定, 一半是你的。 ";
					link.l1 = "是啊, 宝藏确实不多。 不过总比什么都没有好。 ";
					link.l1.go = "Node_2";
				break;
				case 3:
					dialog.text = "船长, 对不起, 但是... 没有宝藏。 ";
					link.l1 = "什么? ! 你骗了我, 你这个恶棍! 我把你带到那个岛上 —为了什么? 你不会就这样逃脱的! ";
					link.l1.go = "Node_3";
				break;
				case 4:
                    ok = GetCharacterItem(pchar, "map_full") == 0 && GetCharacterItem(PChar, "map_part2") == 0;
                    if(GetCharacterItem(PChar, "map_part1") > 0 && !ok) // 第一部分存在, 但不能给第二部分
                    {
                        dialog.text = "听着, 我都检查过了, 但没有找到宝藏。 真遗憾会是这样。 一定是有人在我们之前挖走了。 ";
                        link.l1 = "怎么会这样? ! ";
                        link.l1.go = "PrisonerInPlace_1";
                    }
                    else
                    {
                        dialog.text = "该死的... 怎么会这样? 不可能! ";
                        link.l1 = "怎么了, 伙计? 宝藏在哪里? 别告诉我没有! ";
                        link.l1.go = "Node_4";
                    }
				break;
			}
		break;
			
		case "Node_1":
			dialog.text = "当然, 按照约定。 一半的宝藏是你的。 ";
			link.l1 = "天哪, 现在肯定有很多贵重物品! ";
			link.l1.go = "PrisonerInPlace_3";
			Log_Info("你收到了你的宝藏份额");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "icollection", 1+hrand(1));
			TakeNItems(pchar, "chest", 4+hrand(4));
			TakeNItems(pchar, "jewelry1", 70+rand(15));
			TakeNItems(pchar, "jewelry2", 50+rand(15));
			TakeNItems(pchar, "jewelry3", 60+rand(15));
			TakeNItems(pchar, "jewelry4", 40+rand(10));
			TakeNItems(pchar, "jewelry5", 10+rand(10));
			TakeNItems(pchar, "jewelry46", 60+rand(20));
			TakeNItems(pchar, "jewelry47", 40+rand(15));
			TakeNItems(pchar, "jewelry40", 60+rand(20));
			AddQuestRecord("GivePrisonFree", "3_1");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
		case "Node_2":
			dialog.text = "船长, 除了你的份额外, 还有那件印第安物品。 你可以收下它。 ";
			link.l1 = "嗯, 至少有值钱的东西作为释放你的回报! 把它给我。 ";
			link.l1.go = "PrisonerInPlace_3";
			Log_Info("你收到了你的宝藏份额");
			PlaySound("interface\important_item.wav");
			sTemp = pchar.questTemp.jailCanMove.Item1;
			TakeNItems(pchar, sTemp, 1);
			TakeNItems(pchar, "jewelry5", 40+rand(10));
			TakeNItems(pchar, "jewelry6", 20+rand(20));
			TakeNItems(pchar, "jewelry17", 80+rand(20));
			TakeNItems(pchar, "jewelry13", 10+rand(10));
			TakeNItems(pchar, "jewelry10", 20+rand(20));
			TakeNItems(pchar, "jewelry12", 50+rand(20));
			TakeNItems(pchar, "jewelry11", rand(2)+1);
			AddQuestRecord("GivePrisonFree", "3_2");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
		case "Node_3":
			dialog.text = "等等, 船长, 别激动, 听我说。 我也和你一样是个水手。 我发誓我是被冤枉入狱的。 你是我唯一的逃跑机会, 我不得不骗你说有宝藏。 \n其实没有宝藏, 但我在那里藏了一件好东西。 拿着它, 让我平静地走吧。 也许有一天在战斗中, 它会帮你活下来。 ";
			link.l1 = "好吧, 反正我也没对你抱多大期望。 谢天谢地, 我不记仇。 ";
			link.l1.go = "PrisonerInPlace_3";
			Log_Info("你收到了装备");
			PlaySound("interface\important_item.wav");
			sTemp = pchar.questTemp.jailCanMove.Item2;
			TakeNItems(pchar, sTemp, 1);
			AddQuestRecord("GivePrisonFree", "3_3");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
		case "Node_4":
			dialog.text = "不!!! 它不在那里! 该死的纸片... 船长, 我本来绝对肯定能在这里找到的! 但显然我错了! 那张纸片上的东西实在太不清楚了... ";
			link.l1 = "哦, 好吧... 你有大麻烦了, 伙计。 但我还是想听听你的解释。 ";
			link.l1.go = "Node_4_1";
		break;
			
		case "Node_4_1":
			dialog.text = "我有一张地图碎片。 我发誓那是真地图! 但很难说上面画的是哪个岛... 我以为是这里... 但如你所见, 我错了。 ";
			link.l1 = "什么纸片? 马上给我! ";
			link.l1.go = "Node_4_2";
		break;
			
		case "Node_4_2":
			AddMapPart();
			dialog.text = "当然, 拿着。 船长, 放了我吧... 求你了? 我真的以为宝藏在那里。 也许你会弄清楚它在哪里, 然后自己拿走。 我求你了。 ";
			link.l1 = "我明白了... 的确, 仅凭那块碎片很难弄清楚什么。 需要地图的另一半。 好吧, 滚吧。 我现在知道这不是你的错。 ";
			link.l1.go = "PrisonerInPlace_4";
		break;
			
		case "PrisonerInPlace_1":
			dialog.text = "很简单, " + GetSexPhrase("伙计", "姑娘") + "。 生活中什么事都可能发生。 \n嗯, 你在这里 —如果你想的话: 留下, 再找找看。 嗯, 我得走了! \n再见, " + GetSexPhrase("我的朋友", "姑娘") + ", 谢谢你救了我的命。 我会永远记住你! ";
			link.l1 = "无赖! 你以为我会让你就这么走掉吗? ! 嘿! 站住, 胆小鬼! ";
			link.l1.go = "PrisonerInPlace_2";
			AddQuestRecord("GivePrisonFree", "4");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
        case "PrisonerInPlace_2":
			LAi_group_Delete("EnemyFight");
			DeleteAttribute(pchar, "questTemp.jailCanMove.islandId");	
			DeleteAttribute(pchar, "questTemp.jailCanMove.placeId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.prisonerId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.IsTrue");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Sum");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Name");
			chrDisableReloadToLocation = false;
			LAi_LocationDisableMonstersGen(pchar.location, false);
			npchar.lifeDay = 0;
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", -1);
			DialogExit();

            Pchar.quest.DeletePrisonGroup.win_condition.l1 = "ExitFromLocation";
            Pchar.quest.DeletePrisonGroup.win_condition.l1.location = pchar.location;
            Pchar.quest.DeletePrisonGroup.win_condition = "DeletePrisonGroup";
		break;
		
        case "PrisonerInPlace_3":
			dialog.text = "给你。 谢谢! ";
			link.l1 = "再见... ";
			link.l1.go = "PrisonerInPlace_2";
		break;
		
        case "PrisonerInPlace_4":
			dialog.text = "谢谢你, 船长! 我会为你祈祷一辈子! ";
			link.l1 = "哦, 闭嘴! 安静地走吧... ";
			link.l1.go = "PrisonerInPlace_2";
			AddQuestRecord("GivePrisonFree", "3_4");
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
        
		// ------------------ —释放囚犯 --------------------
		// ---------------------- —传递密信 --------------------------
        case "Deliver_1":
			dialog.text = "我叫 " + GetFullName(npchar) + "。 我有个请求, 嘿嘿... ";
			link.l1 = "怎么了? ";
			link.l1.go = "Deliver_2";
		break;
        case "Deliver_2":
			dialog.text = "我需要把一封信送出监狱。 你能帮我吗? ";
			link.l1 = "我能得到什么好处? ";
			link.l1.go = "Deliver_3";
		break;
        case "Deliver_3":
			dialog.text = "伙计们不会让你失望的, 保证... 那么? 你愿意吗? ";
			link.l1 = "不, 我不感兴趣。 ";
			link.l1.go = "Prisoner_5";
			link.l2 = "好吧, 如果不需要我费太多力气, 我可以做。 ";
			link.l2.go = "Deliver_agree";
		break;
        case "Deliver_agree":
			dialog.text = "好的。 现在仔细听我说。 有两个伙计在一所房子里等我的信, 这样他们就不会在突袭中被抓。 但我不清楚具体是哪所房子。 你需要去搜查。 ";
			link.l1 = "你说‘搜查’是什么意思? ";
			link.l1.go = "Deliver_4";
		break;
        case "Deliver_4":
			dialog.text = "就是搜查的意思。 你要在镇上跑来跑去, 窥视那些房子。 当你找到正确的地方, 他们不会让你不谈话就出来。 但要记住, 我最多还能在那里待两天。 所以不要拖延。 ";
			link.l1 = "我明白了。 那么, 把你的信给我。 ";
			link.l1.go = "Deliver_5";
		break;
        case "Deliver_5":
			pchar.questTemp.jailCanMove.Deliver.locationId = GetBanderLocation(npchar); // 平民区ID
			if (pchar.questTemp.jailCanMove.Deliver.locationId == "none")
			{
				dialog.text = "嗯, 你知道, 我就是不喜欢你。 我改变主意了。 过来, 别站在那里! ";
				link.l1 = "看看你! 好吧, 随你便... ";
				link.l1.go = "NoMoreTalkExit";
				DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
			}
			else
			{
				dialog.text = "给你。 谢谢你, " + GetSexPhrase("伙计", "姑娘") + "! ";
				link.l1 = "不客气。 ";
				link.l1.go = "NoMoreTalkExit";
				GiveItem2Character(Pchar, "Malyava");
				pchar.questTemp.jailCanMove.Deliver.Id = npchar.id; // 囚犯ID
				pchar.questTemp.jailCanMove.Deliver.name = GetFullName(npchar); // 囚犯名字
				pchar.questTemp.jailCanMove.Deliver.City = npchar.city; // 城市 (殖民地ID) 
				pchar.questTemp.jailCanMove.Deliver.good = rand(3); // 是否被击倒
				pchar.questTemp.jailCanMove.Deliver.price = rand(6)*500+500; // 服务价格
				pchar.quest.DeliverToBander.win_condition.l1 = "location";
				pchar.quest.DeliverToBander.win_condition.l1.location = pchar.questTemp.jailCanMove.Deliver.locationId;
				pchar.quest.DeliverToBander.win_condition = "DeliverToBander";
				pchar.quest.DeliverToBander.again = true; 
				SetTimerCondition("DeliverToBander_over", 0, 0, 2, false);
				ReOpenQuestHeader("GivePrisonFree");
				AddQuestRecord("GivePrisonFree", "8");
				AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("",""));
				AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
				AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Deliver.name);
			}
		break;
		
		// Warship, 16.05.11。 生成 "正义可售"。 
		case "JusticeOnSale_1":
			dialog.text = "是的, 他因走私罪被捕。 但你为什么关心那个死囚, " + GetAddress_Form(NPChar) + "? ";
			link.l1 = "他的团伙正计划安排他逃跑, 并继续他们的肮脏勾当。 ";
			link.l1.go = "JusticeOnSale_2";
			link.l2 = "我听说他是无辜的。 ";
			link.l2.go = "JusticeOnSale_3";
			
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.PrisonWait");
		break;
		
		case "JusticeOnSale_2":
			dialog.text = "你必须通知总督, " + GetAddress_Form(NPChar) + ", 这些恶棍必须全部抓获! ";
			link.l1 = "我会的。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "First_officer";
		break;
		
		case "JusticeOnSale_3":
			dialog.text = "听着, " +GetFullName(PChar)+ ", 那家伙在镇上试图出售禁品时被抓! 你怎么能说他是无辜的? ";
			link.l1 = "我听说指控是没有根据的, 而且你们没有证据, 对吗? 你不能拘留一个被冤枉的人。 ";
			link.l1.go = "JusticeOnSale_4";
		break;
		
		case "JusticeOnSale_4":
			dialog.text = "我们既没有证人也没有货物, 但这并不改变什么, " +GetFullName(pchar)+ "船长! 那个人肯定有罪 —也许不止是非法交易。 不管怎样 —你为什么关心这个囚犯? ";
			link.l1 = "也许, 我的话可以作为那个不幸囚犯的保释? ";
			link.l1.go = "JusticeOnSale_5_WithoutMoney";
			
			if(sti(PChar.money) >= 5000)
			{
				link.l2 = "也许, 这5000比索可以作为那个不幸囚犯的保释金? ";
				link.l2.go = "JusticeOnSale_5";
			}
		break;
		
		case "JusticeOnSale_5_WithoutMoney":
			if(GetCharacterSkill(PChar, SKILL_LEADERSHIP) > hrand(100) || sti(PChar.money) < 5000)
			{
				dialog.text = "好吧, " + GetAddress_Form(NPChar) + ", 带上那个无赖离开, 趁我还没改变主意。 ";
				link.l1 = "看到正义的胜利, 你不觉得很棒吗? ";
				link.l1.go = "JusticeOnSale_6";
			}
			else
			{
				dialog.text = "不, " + GetAddress_Form(NPChar) + ", 那不行。 ";
				link.l1 = "那么, 也许这5000比索可以成为更有分量的论据? ";
				link.l1.go = "JusticeOnSale_5";
			}
		break;
		
		case "JusticeOnSale_5":
			dialog.text = "好吧, " + GetAddress_Form(NPChar) + ", 带上那个无赖离开, 趁我还没改变主意。 ";
			link.l1 = "看到正义的胜利, 你不觉得很棒吗? ";
			link.l1.go = "JusticeOnSale_6";
			AddMoneyToCharacter(PChar, -5000);
			PChar.GenQuest.JusticeOnSale.PrisonMoney = true;
		break;
		
		case "JusticeOnSale_6":
			DialogExit();
			sld = GetCharacter(NPC_GenerateCharacter("JusticeOnSale_Smuggler", "mercen_"+(rand(9)+1), "man", "man", sti(PChar.rank)+5, PIRATE, -1, true, "marginal"));
			SetFantomParamFromRank(sld, sti(PChar.rank)+5, true);
			sld.name = PChar.GenQuest.JusticeOnSale.SmugglerName;
			sld.lastName = "";
			sld.dialog.filename = "GenQuests_Dialog.c";
			sld.dialog.currentnode = "First time";
			sld.greeting = "Enc_Raiders"; 
			AddPassenger(PChar, sld, false);
			SetCharacterRemovable(sld, false);
			PChar.GenQuest.JusticeOnSale.SmugglerModel = sld.model;
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait");
			sld = &Locations[FindLocation(PChar.GenQuest.JusticeOnSale.ShoreId)];
			sld.DisableEncounters = true;
			PChar.Quest.JusticeOnSale_ShoreEnterWithSmuggler.win_condition.l1  = "location";
			PChar.Quest.JusticeOnSale_ShoreEnterWithSmuggler.win_condition.l1.location = PChar.GenQuest.JusticeOnSale.ShoreId;
			PChar.Quest.JusticeOnSale_ShoreEnterWithSmuggler.function = "JusticeOnSale_ShoreEnterWithSmuggler";
			Log_Info("走私船长已登船");
			PlaySound("interface\notebook.wav");
			LAi_Fade("", "");
			WaitDate("",0,0,0,0,60); // 280313 // 林务员。 时间流逝原为 WaitDate("",0,0,0,2,5);
		break;
		// --> belamour 夜间冒险
		case "NightAdventure_CitizenHomie":
			dialog.text = "是的, 有过这样一个粗暴的人。 他对哨兵无礼, 然后打了一架。 没什么大不了的: 他会在牢里待几天 —他会清醒过来的。 你为什么关心他? 你好像是个船长, 而这个醉汉看起来不像水手。 ";
			link.l1 = "是的, 没错, 我是船长。 问题是, 这个醉汉是我的老熟人。 请不要告诉任何人。 如果我没理解错的话, 他甚至没有拿武器。 也许你这次能应我的请求释放他? ";
			link.l1.go = "NightAdventure_CitizenHomie_1";
		break;
		
		case "NightAdventure_CitizenHomie_1":
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomie") // 凭诚信释放
			{
				dialog.text = "是的, 我的好朋友。 别担心, 我不会告诉任何人。 事实上, 他甚至打不准, 只是尝试了一下 —所以他们才把他关进监狱。 既然你请求, 出于对你的尊重, 我会释放他。 只是警告他下次要控制自己。 或者更好的是, 让他少喝点。 ";
				link.l1 = "谢谢你, 警官。 ";
				link.l1.go = "NightAdventure_CitizenHomieOK";
			}
			
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieSolderNM" || pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieSolderGM") // 与士兵交谈
			{
				dialog.text = "是的, 好朋友。 别担心, 我不会告诉任何人。 只是, 他在被绑起来之前设法打了哨兵的脸。 所以我不能放他出去。 当然, 除非哨兵同意撤回指控。 你可以自己和他谈谈, 他今天在城里巡逻。 ";
				link.l1 = "不, 恐怕如果他打了卫兵, 那我也帮不了他。 他得坐几天牢。 很抱歉打扰你, 警官。 ";
				link.l1.go = "CitizenHomieEnd";
				link.l2 = "好吧, 我去试着和哨兵谈谈。 ";
				link.l2.go = "NightAdventure_CitizenHomieSolder";
			}
			
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieOfficer") // 向警官付款
			{
				dialog.text = "是的, 好朋友。 别担心, 我不会告诉任何人。 问题是, 袭击一名正在执勤的武装部队成员是犯罪。 我可以通融一下释放他, 但只能保释。 ";
				link.l1 = "我需要付多少钱? ";
				link.l1.go = "NightAdventure_CitizenHomieOfficer";
			}
		break;
		
		case "NightAdventure_CitizenHomieOK":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.NightAdventureToJail");
			SetFunctionLocationCondition("NightAdventure_CitizenHomieOK", npchar.City+"_town", false);
		break;
		
		case "NightAdventure_CitizenHomieEnd":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.NightAdventureToJail");
			pchar.quest.NightAdventure_SeaExit.over = "yes";
			pchar.quest.NightAdventure_JungleExit.over = "yes";
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		case "NightAdventure_CitizenHomieSolder":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.NightAdventureToJail");
			for(i=0; i<MAX_CHARACTERS; i++)
			{
				if(Characters[i].location != npchar.City+"_town") continue;
				if(Characters[i].chr_ai.type != "patrol") continue;
				while(SoldQty < 10) // 以防万一, 避免数组越界
				{                   // 生成7名士兵 + 3名火枪手
					SoldNum[SoldQty] = Characters[i].index;
					SoldQty++;
				}
			}
			iTemp = rand(SoldQty);
			pchar.GenQuest.NightAdventureSolNum = SoldNum[iTemp];
		break;
		
		case "NightAdventure_HomieToPrisoner":
			DeleteAttribute(pchar,"GenQuest.NightAdventureToPrisoner");
			pchar.quest.NightAdventure_SeaExit.over = "yes";
			pchar.quest.NightAdventure_JungleExit.over = "yes";
			SetFunctionLocationCondition("NightAdventure_CitizenHomieOK", npchar.City+"_town", false);
			dialog.text = "*阅读* 所以... 所以... 好吧, 既然哨兵没有投诉, 那我也没有。 你可以带走你的朋友。 只是警告他下次要控制自己。 或者更好的是, 让他少喝点。 ";
			link.l1 = "谢谢你, 警官。 ";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_CitizenHomieOfficer":
			dialog.text = "嗯, 考虑到他没有拿武器, 只要1500比索。 ";
			link.l1 = "恐怕我不准备给那么多。 嗯, 考虑到他只在这里待几天, 我想这对他没什么伤害。 也许他会少喝点。 ";
			link.l1.go = "NightAdventure_CitizenHomieEnd";
			if(sti(pchar.money) >= 1500)
			{
				link.l2 = "好吧, 我准备保释。 ";
				link.l2.go = "NightAdventure_CitizenHomieOfficer_1";
			}
		break;
		
		case "NightAdventure_CitizenHomieOfficer_1":
			AddMoneyToCharacter(pchar, -1500);
			DeleteAttribute(pchar,"GenQuest.NightAdventureToJail");
			pchar.quest.NightAdventure_SeaExit.over = "yes";
			pchar.quest.NightAdventure_JungleExit.over = "yes";
			SetFunctionLocationCondition("NightAdventure_CitizenHomieOK", npchar.City+"_town", false);
			dialog.text = "你可以去接你的朋友了。 只是警告他下次要控制自己。 或者更好的是, 让他少喝点。 ";
			link.l1 = "谢谢你, 警官。 ";
			link.l1.go = "exit";
		break;
		// < —夜间冒险
		
		// --> Sinistra 导航星
		case "PZ_BasTer_ComendantDialog":
			if (CheckAttribute(pchar, "questTemp.PZ_BasTerOpozdal"))
			{
				dialog.text = "谢谢你同意来而不是开始一场屠杀。 至少现在还有人讲道理。 ";
				link.l1 = "那么, 警官先生, 我有什么荣幸? 这和我在镇上寻找一个中国人有关吗? ";
				link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_1";
			}
			else
			{
				dialog.text = "你自愿来找我们真是太好了。 我们最近受够了吵闹的人。 ";
				link.l1 = "嗯, 如你所见, 我不是暴力分子。 但是... 我为什么在这里, 警官? 我已经问过你的人了, 但没有得到答案 —是因为我在镇上寻找某个中国人吗? ";
				link.l1.go = "PZ_BasTer_ComendantDialog_1";
			}
			DeleteQuestCondition("PZ_BasTerPeshera");
			npchar.Dialog.Filename = "Common_Prison.c";
			npchar.Dialog.CurrentNode = "First_officer";
		break;
		// < —导航星
		case "Helen_meeting":
			dialog.text = "哦, 当然不! 请进。 我们的地牢总是欢迎你。 呃, 当然, 我是从好的方面说的。 那么, 你在这里需要什么? ";
			link.l1 = "哦, 没什么特别的, 你知道, 只是在城里四处看看, 所以偶尔逛到这里。 ";
			link.l1.go = "exit";
			link.l2 = "我想谈点生意。 ";
			link.l2.go = "quests";
			if (!sti(pchar.questTemp.jailCanMove))
			{
				link.l4 = "我想进入监狱里面。 ";
				link.l4.go = "ForGoodMove";		
			}
			NextDiag.TempNode = "First_officer";
		break;
	}
}

void GetChestPlaceName()
{
	string islandId;
	int iTemp = rand(3);
	switch (iTemp)
	{
		case 0: 
			pchar.questTemp.jailCanMove.islandId = "Bermudes";
			pchar.questTemp.jailCanMove.placeId = "Bermudes_Cavern";
		break;
		case 1: 
			pchar.questTemp.jailCanMove.islandId = "Caiman";
			pchar.questTemp.jailCanMove.placeId = "Caiman_Grot";
		break;
		case 2: 
			pchar.questTemp.jailCanMove.islandId = "Dominica";
			pchar.questTemp.jailCanMove.placeId = "Dominica_Grot";
		break;
		case 3: 
			pchar.questTemp.jailCanMove.islandId = "Terks";
			pchar.questTemp.jailCanMove.placeId = "Terks_Grot";
		break;
	}
}

string GetBanderLocation(ref npchar)
{
    aref	arCommon, arRld, arRld2;
    int	i, n, Qty, Qty2;
	string LocId; 
	string	storeArray [50];
	int howStore = 0;
    makearef(arRld, Locations[FindLocation(npchar.city + "_town")].reload);
	Qty = GetAttributesNum(arRld);
    if (CheckAttribute(pchar, "GenQuest.SeekSpy.Location")) // 如果接受了市长的间谍搜索任务
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.GenQuest.SeekSpy.Location)
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
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.GenQuest.SeekSpy.Location && arCommon.name != "reload1") // mitrokosta 修复
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
					if (findsubstr(LocId, "Common" , 0) != -1 && arCommon.name != "reload1") // mitrokosta 修复
    				{
						storeArray[howStore] = LocId;
						howStore++; 
					}
				}
			}	
		}
	}
	if (howStore == 0) return "none";
	LocId = storeArray[rand(howStore-1)];
	SetOpenDoorCommonLoc(npchar.city, LocId); // 打开门
	for(n=0; n<MAX_CHARACTERS; n++)
	{
		if (CheckAttribute(&characters[n], "locations") && characters[n].locations == LocId) 
		{			
			characters[n].lifeDay = 0;
		}
	}
	return LocId;
}

string GenQuestPrison_GenerateArtefact() // 文物
{
	string itemID;
	switch(rand(7))
	{
		case 0:
			itemID = "indian_5";
		break;
		case 1:
			itemID = "indian_7"; 
		break;
		case 2:
			itemID = "indian_8"; 
		break;
		case 3:
			itemID = "indian_9"; 
		break;
		case 4:
			itemID = "indian_10"; 
		break;
		case 5:
			itemID = "indian_11"; 
		break;
		case 6:
			itemID = "indian_3"; 
		break;
		case 7:
			itemID = "indian_6"; 
		break;
	}
	return itemID;
}

string GenQuestPrison_GenerateBlade() // 刀剑及其他
{
	string itemID;
	switch(rand(8))
	{
		case 0:
			itemID = GetGeneratedItem("blade_16");
		break;
		case 1:
			itemID = GetGeneratedItem("blade_15"); 
		break;
		case 2:
			itemID = GetGeneratedItem("blade_13"); 
		break;
		case 3:
			itemID = "cirass2"; 
		break;
		case 4:
			itemID = GetGeneratedItem("blade_10"); 
		break;
		case 5:
			itemID = "spyglass3"; 
		break;
		case 6:
			itemID = "cirass6"; 
		break;
		case 7:
			itemID = "cirass7"; 
		break;
		case 8:
			itemID = "cirass1"; 
		break;	
		
	}
	return itemID;
}