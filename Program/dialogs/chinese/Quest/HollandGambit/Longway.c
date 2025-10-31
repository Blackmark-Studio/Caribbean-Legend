// китаец Лонгвэй, подручный Роденбурга
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	string 	sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "船长。 我叫龙威。 龙威将他的船交给你指挥。 龙威也归你指挥。 这是罗登堡先生的命令。 ";
			link.l1 = "你好, 龙威。 查尔斯.德.莫尔, 为你效劳。 你对铲除雅各布.范.贝格的行动有什么线索吗? ";
			link.l1.go = "Longway_friend";
			link.l2 = "很高兴见到你, 龙威。 我叫查尔斯.德.莫尔。 没时间浪费了 —罗登堡先生欣赏快速高质量的工作。 雅各布.范.贝格现在藏在哪里? ";
			link.l2.go = "Longway_neutral";
			link.l3 = "嗯, 我是查尔斯.德.莫尔! 希望我们能合作愉快! 那么, 龙威先生, 请告诉我, 我们该去哪里找雅各布.范.贝格? ";
			link.l3.go = "Longway_enemy";
			NextDiag.TempNode = "First time";
			pchar.questTemp.HWIC.Holl.JacobCity = SelectJacobCity();
		break;
		
//-----------------------------------------------за Голландию-----------------------------------------------
		case "Longway_neutral":
			dialog.text = "龙威相信我们会合作愉快, 船长。 雅各布.范.贝格目前在" + XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Gen") + "。 我已经安排了和他在当地酒馆见面。 他会在那里。 ";
			link.l1 = "我们起航吧! ";
			link.l1.go = "Longway_JacobGo";	
			pchar.questTemp.HWIC.Holl.LongwayNeutral = "true";//признак враждебности китайца
		break;
		
		case "Longway_enemy":
			dialog.text = "罗登堡先生的命令对龙威来说就是法律... 雅各布.范.贝格目前在" + XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Gen") + "。 我已经安排了和他在当地酒馆见面。 他会在那里。 ";
			link.l1 = "我们起航吧! ";
			link.l1.go = "Longway_JacobGo";	
			pchar.questTemp.HWIC.Holl.LongwayEnemy = "true";//признак враждебности китайца
			Notification_Approve(false, "Longway");
		break;
		
		case "Longway_friend":
			dialog.text = "龙威会尽力而为, 船长。 而雅各布.范.贝格目前在" + XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Dat") + "。 我已经安排了和他在当地酒馆见面。 他会在那里。 ";
			link.l1 = "我们起航吧! ";
			link.l1.go = "Longway_JacobGo";	
			pchar.questTemp.HWIC.Holl.LongwayFriend = "true";//признак враждебности китайца
			Notification_Approve(true, "Longway");
		break;
		
		case "Longway_JacobGo":
			//Лонгвэя - в офицеры
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.HalfImmortal = true;//полубессмертен
			npchar.loyality = 18;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", -1);
			AddQuestRecord("Holl_Gambit", "1-8");
			ForceHeroAutolevel(npchar);
			SetCharacterPerk(npchar, "Captain");
			AddQuestUserData("Holl_Gambit", "sCity", XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Dat"));
			AddMapQuestMarkCity(pchar.questTemp.HWIC.Holl.JacobCity, true);
			AddLandQuestMark(characterFromId(""+pchar.questTemp.HWIC.Holl.JacobCity+"_tavernkeeper"), "questmarkmain");
			pchar.questTemp.HWIC.Holl = "JacobOnMain";
			if(bImCasual)
			{
				NewGameTip("探索模式: 任务持续时间加倍");
				SetFunctionTimerCondition("JacobOnMainOver", 0, 0, 30, false);
			}
			else SetFunctionTimerCondition("JacobOnMainOver", 0, 0, 15, false);
		break;
		
		case "hired":
			dialog.text = "龙威能做什么, 船长? ";
			link.l1 = "目前没什么事。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "hired";
		break;
		
		case "MC_GoAway":
			PlaySound("Voice\English\hambit\Longway-02.wav");
			if (pchar.questTemp.HWIC.Holl == "MirageFail")
			{
				dialog.text = "你这个愚蠢的蒙古人, 船长! 我们的任务很简单 —在不损失'美凤'号的情况下捕获'幻影'号。 没有船长的情况下, 她是个容易的目标, 但你却没能完成任务\n龙威既不会为你服务, 也不会再见到你。 龙威相信罗登堡先生会赞成他的决定。 ";
				link.l1 = "去你的和你的主人! ";
				link.l1.go = "exit";
				AddQuestRecord("Holl_Gambit", "1-10");
			}
			if (pchar.questTemp.HWIC.Holl == "JacobOnMain" || pchar.questTemp.HWIC.Holl == "JacobInRoom")
			{
				dialog.text = "你这个蒙古蠢货, 船长! 我们浪费了太多时间解决你自己的事情, 而没有去见雅各布.范.贝格。 他已经从" + XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Dat") + "离开了\n你未能完成任务。 龙威既不想为你服务, 也不想再见到你。 龙威相信罗登堡先生会赞成他的决定。 ";
				link.l1 = "去你的和你的主人! ";
				link.l1.go = "exit";
				AddQuestRecord("Holl_Gambit", "1-9");
			}
			if (pchar.questTemp.HWIC.Holl == "lateVillemstad")
			{
				dialog.text = "船长, 你浪费了太多时间, 没有结果。 这不是你的船, 龙威也不是你的苦力。 龙威返回威廉斯塔德\n龙威既不会为你服务, 也不会再见到你。 龙威确信罗登堡先生会赞成他的决定。 ";
				link.l1 = "去你的和你的主人! ";
				link.l1.go = "exit";
			}
			PChar.quest.Munity = "Deads";
			LAi_LocationFightDisable(&Locations[FindLocation("Ship_deck")], false);
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_MAYFANG)//если сам на Мейфенг
			{
			pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
			pchar.Ship.name = "Boat";
			SetBaseShipData(pchar);
			SetCrewQuantityOverMax(PChar, 0);
			}
			else
			{
				for(i=1; i < COMPANION_MAX; i++)
				{
					int iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							pchar.questTemp.HWIC.Holl.CompanionIndex = sld.Index;
							sld = GetCharacter(sti(pchar.questTemp.HWIC.Holl.CompanionIndex));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			LAi_CharacterDisableDialog(npchar);
			LAi_SetImmortal(npchar, true);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Holl = "end";
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Detector = "holl_fail";
		break;
		
		case "Longway_hire":
			PlaySound("Voice\English\hambit\Longway-03.wav");
			dialog.text = "船长, 龙威离开了罗登堡先生。 龙威再也不会回到他身边。 你对龙威很好, 你是勇敢的船长。 龙威想加入你的船员, 成为你的仆人, 船长阁下。 ";
			link.l1 = "不是作为仆人, 而是作为军官! 欢迎登船, 朋友! ";
			link.l1.go = "Longway_hire_1";	
			link.l2 = "不了, 谢谢, 龙威。 你是自由人。 我不需要你的服务。 ";
			link.l2.go = "Longway_exit";	
		break;
		
		case "Longway_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "", 30.0);
			AddQuestRecord("Holl_Gambit", "1-37");
		break;
		
		case "Longway_hire_1"://нанимаем китайца
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "HalfImmortal");
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
		
			npchar.CanTakeMushket = true;
			npchar.Payment = true;
			LAi_SetOfficerType(npchar);
			NextDiag.CurrentNode = "Longway_officer";
			npchar.quest.meeting = true;
			npchar.HoldEquip = true;
			LAi_SetImmortal(npchar, false);
			LAi_SetHP(npchar, 200, 200);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			AddQuestRecord("Holl_Gambit", "1-38");
			ForceHeroAutolevel(npchar);
			
			//Sinistra - квест Лонгвэя "Путеводная звезда"
			PChar.quest.PZ_Start.win_condition.l1 = "location";
			PChar.quest.PZ_Start.win_condition.l1.location = "Curacao";
			PChar.quest.PZ_Start.win_condition = "PZ_Start";
		break;
		
//---------------------------------------------против всех-------------------------------------------------
		case "Longway_abordage":
			PlaySound("Voice\English\hambit\Longway-02.wav");
			dialog.text = "你为什么停下来? 杀吧。 龙威累了, 龙威想死。 兴... 原谅我。 ";
			link.l1 = "没那么快, 中国佬。 如果我想杀你, 我会杀了你, 但我需要先和你谈谈。 你的命运取决于你未来的行动。 现在, 欢迎来到我的货舱! ";
			link.l1.go = "Longway_abordage_1";			
		break;
		
		case "Longway_abordage_1":
			AddQuestRecord("Holl_Gambit", "3-45");
		    DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
            DialogExit();
			LAi_SetPlayerType(pchar);
			pchar.questTemp.HWIC.Self = "LongwayPrisoner";
			npchar.lifeday = 0;
			SetFunctionTimerCondition("RemoveLongwayOver", 0, 0, 1, false);//таймер до конца суток, ибо нефиг
		break;
		
		case "Longway_prisoner":
			DelLandQuestMark(npchar);
			dialog.text = "";
			link.l1 = "现在我们可以谈话了, 没有钢铁碰撞的声音在我耳边响起。 听着, 龙威, 我需要信息, 我毫不怀疑你知道我需要知道的。 问题是: 你是想轻松地告诉我, 还是艰难地告诉我? ";
			link.l1.go = "Longway_prisoner_1";			
		break;
		
		case "Longway_prisoner_1":
			dialog.text = "";
			link.l1 = "保持沉默? 很好。 我给你一个交易。 我会饶你一命, 把你送到下一个海岸。 作为回报, 你要告诉我卢卡斯.罗登堡派你去哪里和为什么。 成交? ";
			link.l1.go = "Longway_prisoner_2";			
		break;
		
		case "Longway_prisoner_2":
			dialog.text = "";
			link.l1 = "我知道你懂英语。 荷兰语和法语。 你也是个好的倾听者。 现在是时候开始说了。 你最终会告诉我你知道的一切。 我知道你们中国人以酷刑艺术为荣, 但我们西方人在这门古老的科学上也有自己的进步。 阿隆索在这里是让人们开口的大师。 在他加入我的船之前, 他是圣地亚哥神圣宗教裁判所的审讯者。 他知道各种技巧, 这些技巧是他从完善了让人们忏悔艺术的神父那里学来的... 你甚至不必是新教徒! ";
			link.l1.go = "Longway_prisoner_3";			
		break;
		
		case "Longway_prisoner_3":
			dialog.text = "";
			link.l1 = "我的智慧在你身上浪费了。 你会告诉我一切, 我的斜眼朋友... 一切... 但之后你活不了多久, 不, 你不会。 在见到阿隆索之后, 你的身体会遭受很多痛苦。 在架子上痛苦不堪。 明白了吗? 别担心, 我会确保有一个牧师在场为你施洗成为基督徒, 以拯救你异教的灵魂免受地狱的永恒之火。 ";
			link.l1.go = "Longway_prisoner_4";
		break;
		
		case "Longway_prisoner_4":
			dialog.text = "";
			link.l1 = "我看到你黑色的眼睛里开始怀疑。 你为什么要为你主人的罪孽而死? 他值得吗? 罗登堡真的值得让你的灵魂从你痛苦的身体中被撕裂吗? ";
			link.l1.go = "Longway_prisoner_5";			
		break;
		
		case "Longway_prisoner_5":
			dialog.text = "龙威说。 但首先, 龙威想确定你遵守诺言, 船长。 ";
			link.l1 = "哈! 明智的话! 我向你保证, 孩子。 ";
			link.l1.go = "Longway_prisoner_6";			
		break;
		
		case "Longway_prisoner_6":
			dialog.text = "抱歉, 船长, 你的诺言不够。 你得到信息后会杀了龙威! 龙威需要保证。 ";
			link.l1 = "你像犹太人一样讨价还价。 你想要什么保证? ";
			link.l1.go = "Longway_prisoner_7";			
		break;
		
		case "Longway_prisoner_7":
			dialog.text = "瓜德罗普岛南部有一个小岛。 不可接近的海角。 把龙威送到那里, 给他武器。 只有这样, 龙威才会告诉你他所知道的关于卢卡斯.罗登堡的一切。 ";
			link.l1 = "你没有资格和我讨价还价, 中国佬。 ";
			link.l1.go = "Longway_prisoner_8";			
		break;
		
		case "Longway_prisoner_8":
			dialog.text = "如果你是龙威, 你也会这样做, 船长。 即使有酷刑, 你的人也不容易从龙威这里得到话。 龙威不是软弱的白人。 ";
			link.l1 = "好吧。 成交。 但我警告你 —不要试图耍我, 否则我会亲自把你切成碎片。 一千片, 慢慢地... 就像你们的皇帝那样。 阿隆索! ";
			link.l1.go = "Longway_prisoner_9";
			// belamour legendary edition -->
			link.l2 = "你说得对。 但请记住 —我已经走了太远, 你不能把这件事搞砸。 如果你试图阻止我, 我会像踩死一只昆虫一样结束你的生命。 ";
			link.l2.go = "Longway_prisoner_9a";
		break;
		
		case "Longway_prisoner_9a":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			DialogExit();
			NextDiag.Currentnode = "Longway_prisoner_0";
			npchar.greeting = "longway";
			sld = characterFromId("Sailor_3");
			sld.dialog.currentnode = "Sailor_deck_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);	
			pchar.quest.RemoveLongwayOver.over = "yes";//снять таймер
			pchar.quest.RemoveLongwayTimer.win_condition.l1 = "Timer";
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.function = "RemoveLongwayOver";
			pchar.questTemp.HWIC.Self = "GotoGuadeloupe";
		break;
		
		case "Longway_prisoner_9":
			ChangeCharacterComplexReputation(pchar, "nobility",-5);
			AddCharacterExpToSkill(pchar, "FencingL", 30);
			AddCharacterExpToSkill(pchar, "FencingS", 30);
			AddCharacterExpToSkill(pchar, "FencingH", 30);
			AddCharacterExpToSkill(pchar, "Pistol", 30);
			// < —legendary edition
			DialogExit();
			NextDiag.Currentnode = "Longway_prisoner_0";
			npchar.greeting = "longway";
			sld = characterFromId("Sailor_3");
			sld.dialog.currentnode = "Sailor_deck_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);	
			pchar.quest.RemoveLongwayOver.over = "yes";//снять таймер
			pchar.quest.RemoveLongwayTimer.win_condition.l1 = "Timer";
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.function = "RemoveLongwayOver";
			pchar.questTemp.HWIC.Self = "GotoGuadeloupe";
		break;
		
		case "Longway_prisoner_0":
			dialog.text = "我们到达马里加朗特了吗, 船长?";
			link.l1 = "冷静点, 我们很快就到了。 ";
			link.l1.go = "exit";
			NextDiag.Tempnode = "Longway_prisoner_0";
		break;
		
		case "Longway_prisoner_10":
			dialog.text = "你遵守了诺言, 船长。 龙威也会的。 你想知道龙威的任务吗? ";
			link.l1 = "是的。 但请允许我提醒你自己对我的承诺: 你会告诉我你所知道的一切。 ";
			link.l1.go = "Longway_prisoner_11";			
		break;
		
		case "Longway_prisoner_11":
			dialog.text = "龙威记得。 他会回答你问的关于罗登堡的一切, 船长。 ";
			link.l1 = "开始说。 ";
			link.l1.go = "Longway_prisoner_12";			
		break;
		
		case "Longway_prisoner_12":
			dialog.text = "'美凤'号从威廉斯塔德港向北航行到圣克里斯托弗海岸。 五天后将有一艘由彼得.斯特伊弗桑特指挥的大帆船。 龙威的命令是连船长一起击沉这艘船。 ";
			link.l1 = "天啊! 罗登堡命令你杀了斯特伊弗桑特? 这太疯狂了! ";
			link.l1.go = "Longway_prisoner_13";			
		break;
		
		case "Longway_prisoner_13":
			dialog.text = "龙威说的是实话, 船长。 这是罗登堡先生的命令。 龙威不喜欢, 但龙威不质疑命令。 ";
			link.l1 = "非常像中国人。 你的主人在玩什么游戏? ";
			link.l1.go = "Longway_prisoner_14";			
		break;
		
		case "Longway_prisoner_14":
			dialog.text = "不再是我的主人了, 船长。 龙威不打算回到罗登堡先生那里。 罗登堡已经在库拉索夺取了权力。 马蒂亚斯.贝克很容易成为猎物, 罗登堡的权威和与指挥官的关系足以将总督投入监狱\n剩下的唯一障碍是西印度公司董事斯特伊弗桑特先生。 一旦斯特伊弗桑特被铲除, 罗登堡将在荷兰殖民地拥有所有权力职位。 ";
			link.l1 = "告诉我, 龙威, 是什么让像罗登堡这样受人尊敬和有权势的人对他的公司和共和国采取如此激进的行动? 别告诉我是因为晒太阳或一时发疯。 ";
			link.l1.go = "Longway_prisoner_15";			
		break;
		
		case "Longway_prisoner_15":
			dialog.text = "龙威自己也想从你这里知道, 船长。 是你俘获了公司的邮船, 并给罗登堡带去了信件, 对吗? 原因就在那封信里。 ";
			link.l1 = "我现在明白了... 看来约翰.默多克的档案里有很多精彩的东西, 足以让罗登堡害怕到发动反对自己国家的叛乱。 ";
			link.l1.go = "Longway_prisoner_16";			
		break;
		
		case "Longway_prisoner_16":
			dialog.text = "还想知道别的吗, 船长? ";
			link.l1 = "是的。 罗登堡还做了什么? ";
			link.l1.go = "Longway_prisoner_17";			
		break;
		
		case "Longway_prisoner_17":
			dialog.text = "罗登堡先生下令杀你。 龙威在追捕斯特伊弗桑特之前在加拉加斯, 与船长雅各布见了面, 并给了他命令。 ";
			link.l1 = "雅各布.范.贝格船长? ";
			link.l1.go = "Longway_prisoner_18";			
		break;
		
		case "Longway_prisoner_18":
			dialog.text = "你消息灵通。 是的。 船长雅各布.范.贝格在追捕你, 船长。 他最终会找到你。 没有人能长时间躲避范.贝格。 ";
			link.l1 = "如果他流血, 我就能杀了他。 我会对付范.贝格和他那艘自吹自擂的幽灵船。 ";
			link.l1.go = "Longway_prisoner_19";			
		break;
		
		case "Longway_prisoner_19":
			dialog.text = "你知道的很多, 船长。 龙威没有什么可补充的了。 如果你还有什么要问的, 就问吧。 ";
			link.l1 = "斯特伊弗桑特会在圣克里斯托弗海岸附近吗? ";
			link.l1.go = "Longway_prisoner_20";			
		break;
		
		case "Longway_prisoner_20":
			dialog.text = "是的, 船长。 你可以在大约一周的时间里在这个岛的海岸附近找到他的大帆船。 ";
			link.l1 = "太好了! 让我们在它自己的陷阱里抓住这只狐狸... 我没有进一步的问题了。 我已经知道了我想知道的一切。 ";
			link.l1.go = "Longway_prisoner_21";			
		break;
		
		case "Longway_prisoner_21":
			dialog.text = "最后一个建议, 船长。 如果你想接近大帆船而不被攻击, 你必须乘坐'美凤'号。 ";
			link.l1 = "明白了。 谢谢你的信息。 ";
			link.l1.go = "Longway_prisoner_22";			
		break;
		
		case "Longway_prisoner_22":
			dialog.text = "龙威现在离开。 再见, 船长。 ";
			link.l1 = "祝你顺风, 我的东方伙伴。 ";
			link.l1.go = "Longway_prisoner_23";			
		break;
		
		case "Longway_prisoner_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "ReturnShoreToNormal", -1);
			npchar.lifeday = 0;
			AddQuestRecord("Holl_Gambit", "3-49");
			pchar.questTemp.HWIC.Self = "MeetingStivesant";
			pchar.quest.Seek_Piter.win_condition.l1 = "location";
			pchar.quest.Seek_Piter.win_condition.l1.location = "Nevis";
			pchar.quest.Seek_Piter.function = "CreatePiterHalleon";
			pchar.quest.RemoveLongwayTimer.over = "yes";//снять прерывание
			SetFunctionTimerCondition("QuestShipsTerms_Over", 0, 0, 8, false); // таймер
			AddMapQuestMarkIsland("Nevis", true);
		break;
		
		//--> --------------------------------- —офицерский блок ------------------------------------------
		case "Longway_officer":
			dialog.text = "龙威在听, 船长。 ";
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "龙威, 我要去一座古老的印第安城市泰亚萨尔。 我直说吧, 这将是一次非常危险的旅行, 也是一次神秘的旅行 —我们将通过传送偶像到达那里。 你会... 加入我吗? ";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "龙威, 给我一份完整的船舶报告。 ";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship。 Автозакупка товара
				Link.l12 = "我希望你每次靠岸时都购买特定的货物。 ";
				Link.l12.go = "QMASTER_2";
			}

			if (CheckAttribute(NPChar, "IsCompanionClone"))//////////////////компаньон//////////////////////////////////////////////
			{
				//dialog.text = "Я прибыл по вашему распоряжению, капитан.";
				Link.l2 = "我需要给你几个命令。 ";
				Link.l2.go = "Companion_Tasks";
				NextDiag.TempNode = "Longway_officer";// не забыть менять в зависисомости от оффа
				break;
			}
			Link.l1 = "听我的命令! ";
            Link.l1.go = "stay_follow";
			link.l2 = "没什么。 解散! ";
			link.l2.go = "exit";
			NextDiag.TempNode = "Longway_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "龙威从未当过军需官, 船长。 龙威可以告诉你从特立尼达到哈瓦那如何导航, 需要多长时间。 但龙威从不计算货物。 销售和贸易。 ";
			Link.l1 = "我想你是对的。 浪费一个优秀的导航员太可惜了。 ";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "龙威不与外国佬交易, 船长。 龙威总是站在舵轮旁, 而不是在老钩鼻讨价还价到最后一个八里亚尔的商店里。 ";
			link.l1 = "嗯, 你说得对。 你可能会吓跑商人。 ";
			link.l1.go = "exit";
		break;

		//Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "我在听。 ";
			Link.l1 = "我们谈谈登船作战。 ";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "我们谈谈你的船。 ";
			Link.l2.go = "Companion_TaskChange";
			if (bBettaTestMode) // Только при бета-тесте
			{
				Link.l3 = "我希望你暂时离开我的中队, 自己去寻找财富。 ";
				Link.l3.go = "CompanionTravel";
			}
			Link.l8 = "目前没什么。 ";
			Link.l8.go = "exit";
		break;

		case "Companion_TaskBoarding":
			dialog.Text = "你有什么愿望。 ";
			Link.l1 = "不要登敌船。 照顾好自己和船员。 ";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "我希望你积极登敌船。 ";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;

		case "Companion_TaskChange":
			dialog.Text = "你有什么愿望。 ";
			Link.l1 = "登船后不要把你的船换成另一艘。 她太有价值了。 ";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "当你登敌船时, 如果它们还不错, 你可以自己拿下它们。 ";
			Link.l2.go = "Companion_TaskChangeYes";
		break;

		case "Companion_TaskBoardingNo":
			dialog.Text = "是, 是。 ";
			Link.l1 = "稍息。 ";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;

		case "Companion_TaskBoardingYes":
			dialog.Text = "遵命。 ";
			Link.l1 = "稍息。 ";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;

		case "Companion_TaskChangeNo":
			dialog.Text = "是, 是。 ";
			Link.l1 = "会完成的。 ";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;

		case "Companion_TaskChangeYes":
			dialog.Text = "会完成的。 ";
			Link.l1 = "稍息。 ";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
	//	<========////////////////////////////////////////
		case "stay_follow":
            dialog.Text = "命令, 船长? ";
            Link.l1 = "坚守岗位! ";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "跟我来, 跟上! ";
            Link.l2.go = "Boal_Follow";
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "更换你的火器弹药类型。 ";
					Link.l3.go = "SetGunBullets";
				}	
			}
			if(CheckAttribute(NPChar, "equip.musket"))
			{
				if(CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l4 = "更换你的步枪弹药类型。 ";
					Link.l4.go = "SetMusketBullets";
				}
					Link.l5 = "更改你战斗的优先武器。 ";
					Link.l5.go = "SetPriorityMode";
					Link.l6 = "我希望你在特定距离向敌人开火, 龙威。 ";
					Link.l6.go = "TargetDistance";
			}	
		break;
		
		case "SetGunBullets":
			Dialog.Text = "选择弹药类型: ";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;

		case "SetMusketBullets":
			Dialog.Text = "选择弹药类型: ";
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.musket.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetMusketBullets2":
			i = sti(NPChar.SetMusketBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, MUSKET_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, MUSKET_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetMusketBullets");
			DialogExit();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "战斗开始时你将使用: ";
			Link.l1 = "刀剑";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "步枪";
			Link.l2.go = "MusketPriorityMode";
		break;
		
		case "BladePriorityMode":
			SetPriorityMode(NPChar, 1);
			DialogExit();
		break;
		
		case "MusketPriorityMode":
			SetPriorityMode(NPChar, 2);
			DialogExit();
		break;
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "部署变更! ";
            Link.l1 = "解散。 ";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "部署变更! ";
            Link.l1 = "解散。 ";
            Link.l1.go = "Exit";
        break;
		
		//--> задать дистанцию стрельбы
		case "TargetDistance":
			dialog.text = "那会是什么距离呢? 记住, 船长阁下, 步枪在二十米外打不中任何东西。 ";
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";			
		break;
		
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = "你是什么意思, 船长阁下? ";
				link.l1 = "抱歉, 有时我忘了你不太擅长开玩笑。 ";
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "我会坚守阵地, 但会向任何靠近的敌人开火。 这是你想要的吗? ";
				link.l1 = "是的, 正是这样, 龙威。 ";
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "太远了, 船长阁下。 你可能会击中人群, 但瞄准单个目标 —没机会。 ";
				link.l1 = "值得一试, 但好吧。 ";
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = "我明白了, 船长阁下。 ";
			link.l1 = "太好了。 ";
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;
		//< —задать дистанцию стрельбы
	//< —--------------------------------- —офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "龙威跟随你很久了。 龙威会一如既往地跟随你。 龙威不会离开他的船长。 ";
			link.l1 = "谢谢你, 龙威! 我很高兴我对你的看法是对的。 ";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "我们什么时候开始? ";
			link.l1 = "稍后。 我们必须为此做好准备。 ";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "24");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string SelectJacobCity()
{
	string sTemp;
	switch (hrand(4))
	{
		case 0: sTemp = "Cumana" break;
		case 1: sTemp = "Caracas" break;
		case 2: sTemp = "Maracaibo" break;
		case 3: sTemp = "Cartahena" break;
		case 4: sTemp = "Portobello" break;
	}
	return sTemp;
}