// 运输乘客
void ProcessDialogEvent()
{
	ref NPChar, d;
	aref Link, Diag, arAll;
	string NPC_Meeting, sTemp, sTitle, sTavern;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		
		case "prepare_convoy_quest":
			if (isBadReputation(pchar, 40)) 
			{
				dialog.text = RandPhraseSimple("啊, 见鬼! 我知道你是谁! 只有十足的傻瓜才会作为乘客上你的船! 再见! ", "哦, 我知道你是谁! 我永远不会踏上你的船。 我不是傻瓜... ");
				link.l1 = RandPhraseSimple("呵, 真是个懦夫! ", "现在的人都这么胆小! ");
				link.l1.go = "convoy_refused";
			}
			else
			{
				dialog.text = TimeGreeting() + ", " + GetAddress_Form(NPChar) + "! 我是" + GetFullName(NPChar) + "。 听说你在搭载乘客? ";
				link.l1 = "也许吧。 这取决于我的利润。 ";
				link.l1.go = "prepare_convoy_quest_3";
			}
		break;
		
		case "prepare_convoy_quest_3":
			LookShipPassenger();
			GenerateConvoyPassengerQuest(npchar);
			dialog.text = "我需要被送到" + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + "的酒馆, 在" + XI_ConvertString(GetIslandByCityName(npchar.GenQuest.GetPassenger_Destination) + "Dat") +
						  ", 耗时" + FindRussianDaysString(sti(npchar.GenQuest.GetPassenger_Time)) + ", 为此我会付你" + FindRussianMoneyString(sti(npchar.GenQuest.GetPassenger_Money)) + "。 你同意吗? ";
			link.l1 = "是的, 我同意。 ";
			link.l1.go = "convoy_agreeded";
			link.l2 = "我认为这不是个有趣的提议。 ";
			link.l2.go = "convoy_refused";
		break;
		
		case "convoy_refused":
			chrDisableReloadToLocation = false;
			sTemp = npchar.id + "_TimeOver";
			pchar.quest.(sTemp).over = "yes";
			sTemp = npchar.id + "_dead";
			pchar.quest.(sTemp).over = "yes";			
			DeleteAttribute(npchar, "GenQuest.GetPassenger");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		
		case "convoy_agreeded":
			sTitle = npchar.index + "convoy_passenger";
			AddQuestRecordEx(sTitle, "Gen_convoy_passenger", "1");
			sTemp = XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + ", 位于" + XI_ConvertString(GetIslandByCityName(npchar.GenQuest.GetPassenger_Destination) + "Dat") + ", ";
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sDay", FindRussianDaysString(sti(npchar.GenQuest.GetPassenger_Time)));
            AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(npchar.GenQuest.GetPassenger_Money)));
			// 按城市将其送回酒馆
			sTavern = npchar.GenQuest.GetPassenger_Destination + "_tavern";
			sTemp = npchar.id + "_complited";
			pchar.quest.(sTemp).win_condition.l1 = "location";
			pchar.quest.(sTemp).win_condition.l1.location = sTavern;
			pchar.quest.(sTemp).win_condition = "AllPassangersComplited";	
			pchar.quest.(sTemp).Idx	= npchar.index; 
			if (rand(2) == 1) TraderHunterOnMap(false);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);			
			Diag.CurrentNode = "convoy_DeskTalk";
			DialogExit();
		break;
		
		case "complete_convoy_quest":
			dialog.text = "谢谢你。 你履行了你的义务。 我到达了目的地, 这是你的报酬。 给你。 ";
			Link.l1 = "谢谢你。 ";
			link.l1.go = "complete_convoy_quest_1";
		break;

		case "complete_convoy_quest_1":
			// 传闻
			AddSimpleRumour(LinkRandPhrase("一个名叫" + GetFullName(npchar) + "的人说" + GetMainCharacterNameDat() + "船长值得信赖, 因为" + GetSexPhrase("他","她") + "轻松地将他送到了" + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + "。 ", 
				"名叫" + GetFullName(npchar) + "的乘客说" + GetMainCharacterNameDat() + "船长值得信赖。 " + GetSexPhrase("他把","她把") + "他安全送到了" + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + "。 ", 
				"我听说你是一位信守对乘客承诺的船长。 名叫" + GetFullName(npchar) + "的小贩对你赞不绝口。 "), sti(npchar.nation), 40, 1);
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.ConvoyPassenger." + npchar.id); //извлeкаeм из структуры нeдовольных
			//--> смотрим Deck
    		makearef(arAll, pchar.GenQuest.ConvoyPassenger);
			if (GetAttributesNum(arAll) == 0) pchar.quest.ConvoyMapPassenger.over = "yes";
			//< —смотрим Deck
			AddMoneyToCharacter(pchar, makeint(npchar.GenQuest.GetPassenger_Money));
			ChangeCharacterComplexReputation(pchar, "nobility",1);
			ChangeCharacterComplexReputation(pchar, "fame",1);
			RemovePassenger(PChar, npchar);
			OfficersReaction("good");						
			AddCharacterExpToSkill(pchar, "Sailing", 80);
			AddCharacterExpToSkill(pchar, "Leadership", 20);			
			sTitle = npchar.index + "convoy_passenger";
			AddQuestRecordEx(sTitle, "Gen_convoy_passenger", "4");			
            CloseQuestHeader(sTitle);	
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);	
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		
		case "convoy_DeskTalk":
			dialog.text = NPCStringReactionRepeat(LinkRandPhrase(RandSwear() + "船长, 时间到了。 该死的, 我到底什么时候才能到" + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Acc") + "? ", 
						  RandSwear() + "船长, 你到底还要在鬼知道的地方徘徊多久? 我们什么时候才能到" + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + "? " , 
						  RandSwear() + "听着, 船长, 我需要到" + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + ", 我想要一个清楚简单的答案, 这什么时候能发生! "), 
				RandPhraseSimple("船长, 我再次不得不提出关于你义务的问题。 我们什么时候能到" + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + "? ", "船长, 我第二次不得不提出我的旅程问题。 我们最终什么时候能看到" + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + "的海岸? "), 
				RandPhraseSimple(RandSwear() + "船长, 我第三次问 - 我们什么时候能到" + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Acc") + "? ", "船长, 我们浪费了太多时间! 你什么时候把我带到" + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Acc") + "? "), 
				"听着船长, 这真的太过分了! ", "block", 0, npchar, Dialog.CurrentNode);
            if (sti(npchar.GenQuest.GetPassenger_Money) > 100)
            {
				link.l1 = HeroStringReactionRepeat(RandPhraseSimple("请原谅, 我有太多事情要做... 七天后你肯定会到达你需要去的地方。 ", "对不起, " + GetAddress_Form(NPChar) + ", 我真的没能履行对你的义务。 但别担心, 我们一周后到达。 "),
					RandPhraseSimple("我必须再次向你道歉。 我们将在一周后到达你的目的地。 ", "再次, 我很抱歉。 我们将在一周后到达你的目的地。 "),
					RandPhraseSimple("我必须再次请求你的原谅... 我们将在一周后到达你的目的地。 ", "再次, 我很抱歉。 我们将在一周后到达你的目的地, 我保证。 "),
					"我明白, " + GetAddress_Form(NPChar) + ", 但请耐心... 最多七天我就把你送到目的地! ", npchar, Dialog.CurrentNode);
				link.l1.go = "convoy_DeskTalk_1";
			}
			link.l2 = HeroStringReactionRepeat(RandPhraseSimple("哦... 一个乘客... 我把你忘了... 我想你在货舱里会更舒服, 在那里你不会再烦我了。 ", "好吧好吧, 我不敢相信自己的眼睛! 船上有陌生人! 好吧, 闭嘴, 现在去我的货舱! "),
				"第二次? 哦, 确实... 但你知道, 也许我会送你去货舱'游览'一下。 ",
				"第三次? 那太糟糕了, 嘿嘿... 好吧, 伙计, 欢迎来到我的货舱。 你不该在我的船甲板上走来走去烦我。 ",
				"哦, 我明白了, 这是最高程度的 irritation! 好吧, 够了这场闹剧。 欢迎来到货舱, " + GetAddress_Form(NPChar) + "。 ", npchar, Dialog.CurrentNode);
			link.l2.go = "convoy_Prison_1";
			pchar.quest.Munity = "Deads"; // 门将打开
		break;
		
		case "convoy_DeskTalk_1":
			dialog.text = LinkRandPhrase("好吧, 但我会因为延误削减你的付款。 ", "好吧, 我会试着相信你... 但记住我要削减你的费用! ", "嗯, 反正我也无处可去, 但记住我要削减你的付款... .");
			Link.l1 = LinkRandPhrase("好吧。 ", "那好吧... ", "好吧, 如你所说。 ");
			link.l1.go = "convoy_DeskTalk_2";
		break;

		case "convoy_DeskTalk_2":
			dialog.text = RandPhraseSimple("我希望这次你会履行你的义务。 ", "我真的希望这是我们关于这个不愉快话题的最后一次谈话。 ");
			Link.l1 = "当然。 ";
			link.l1.go = "convoy_DeskTalk_exit";
		break;

		case "convoy_DeskTalk_exit":
			DeleteAttribute(pchar, "GenQuest.ConvoyPassenger." + npchar.id); // 从不满意结构中提取
			sTemp = npchar.id + "_TimeOver";
			SetTimerCondition(sTemp, 0, 0, 7, false);
			pchar.quest.(sTemp).win_condition              = "AllPassangersTimeOver";
			pchar.quest.(sTemp).Idx						   = npchar.index; 
			npchar.GenQuest.GetPassenger_Money = makeint(sti(npchar.GenQuest.GetPassenger_Money) / 1.5);			
			sTitle = npchar.index + "convoy_passenger";
			AddQuestRecordEx(sTitle, "Gen_convoy_passenger", "5");
			AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(npchar.GenQuest.GetPassenger_Money)));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 4.0);	
			Diag.CurrentNode = "convoy_DeskTalk";
			DialogExit();
		break;

		case "convoy_Prison_1":
			dialog.text = RandSwear() + "什么货舱? 我不明白! ";
			if (GetPrisonerQty() < PRISONER_MAX)
			{
				Link.l1 = "还有什么不明白的? 从现在起你是我的囚犯! 到该死的货舱去, 走! ";
				link.l1.go = "convoy_Prison_2";
            }
			Link.l2 = "只是个玩笑... 七天后我们将到达你的城镇。 ";
			link.l2.go = "convoy_DeskTalk_1";
		break;
		
		case "convoy_Prison_2":
			dialog.text = RandSwear() + "你会为此付出代价的, " + GetSexPhrase("混蛋","臭家伙") + "! ";
			Link.l1 = "每个人都这么说 - 但最后他们都向我付款! ";
			link.l1.go = "convoy_Prison_3";
		break;
		
		case "convoy_Prison_3":
			AddSimpleRumour(LinkRandPhrase("据报道, 一位名叫" +GetFullName(pchar)+ "的船长有义务运送一位名叫" + GetFullName(npchar) + "的乘客, 但没有遵守" + GetSexPhrase("他的","她的") + "承诺。 此外, " + GetSexPhrase("他","她") + "监禁了一个可怜的人。 这就是相信陌生人的后果... ", 
				"这个世界怎么了? ! " +GetFullName(pchar)+ "船长监禁了一个名叫" + GetFullName(npchar) + "的可怜人, 尽管他是船上的乘客... ", 
				"人们说, 船长, 你是" + GetSexPhrase("一个真正的恶棍","一个非常卑鄙的婊子") + "。 他们说可怜的" + GetFullName(npchar) + "在你的船上被囚禁。 而你答应把他送到" + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + "。 非常非常丑陋... "), sti(npchar.nation), 40, 1);
            RemovePassenger(PChar, NPChar);
        	LAi_SetActorType(NPChar);
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 5.0);
        	ChangeCharacterComplexReputation(pchar,"nobility", -5);
            OfficersReaction("bad");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(NPChar.nation)) + "hunter", GetIntByCondition(HasShipTrait(pchar, "trait23"), 10 + rand(10), 5 + rand(5)));// награда
			DeleteAttribute(pchar, "GenQuest.ConvoyPassenger." + npchar.id); //извлeкаeм из структуры нeдовольных
			sTemp = npchar.id + "_complited";
            pchar.quest.(sTemp).over = "yes";
			sTemp = npchar.id + "_dead";
			pchar.quest.(sTemp).over = "yes";
			sTemp = npchar.id + "_TimeOver";
			pchar.quest.(sTemp).over = "yes";
			sTitle = npchar.index + "convoy_passenger";
			AddQuestRecordEx(sTitle, "Gen_convoy_passenger", "6");			
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
            CloseQuestHeader(sTitle);			
			AddCharacterExpToSkill(pchar, "COMMERCE", 25);
            SetCharToPrisoner(NPChar);
        	DialogExit();
		break;
	}
} 

void GenerateConvoyPassengerQuest(ref npchar)
{
	int iTradeMoney, iNation, irank;
	string sTemp, sR;

	iNation = GetRelation2BaseNation(sti(npchar.nation)); //eсли привeзти нужно во вражeский город
	npchar.GenQuest.GetPassenger_Destination = sGlobalTemp;
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.GetPassenger_City), GetArealByCityName(sGlobalTemp));
	if (sti(daysQty) > 14) daysQty = 14;
	npchar.GenQuest.GetPassenger_Time  = makeint(sti(daysQty)*(frand(1.3)+0.7));
	iTradeMoney = (sti(daysQty)*500*sti(pchar.GenQuest.GetPassenger.Shipmod)+rand(100))*sti(daysQty)/sti(npchar.GenQuest.GetPassenger_Time);
	if (iNation == RELATION_ENEMY && sti(npchar.nation != PIRATE)) iTradeMoney = makeint(iTradeMoney * 1.3); //то размeр награды увeличиваeтся
	npchar.GenQuest.GetPassenger_Money = iTradeMoney;

	//Log_Info(FindRussianDaysString(sti(daysQty)));
	//Log_Info(npchar.GenQuest.GetPassenger_Destination);
	//Log_Info(pchar.GenQuest.GetPassenger_City);
	

	sTemp = npchar.id + "_TimeOver";
	SetTimerCondition(sTemp, 0, 0, sti(npchar.GenQuest.GetPassenger_Time), false);
	pchar.quest.(sTemp).win_condition              = "AllPassangersTimeOver";
	pchar.quest.(sTemp).Idx						   = npchar.index; 

	sTemp = npchar.id + "_dead";
	pchar.quest.(sTemp).win_condition.l1           = "NPC_Death";
	pchar.quest.(sTemp).win_condition.l1.character = npchar.id;
	pchar.quest.(sTemp).win_condition              = "AllPassangersDead";
	pchar.quest.(sTemp).Idx						   = npchar.index; 	
}

void LookShipPassenger()
{
	switch(makeint(7-sti(RealShips[sti(Pchar.Ship.Type)].Class)))
	{
		case 0:
			pchar.GenQuest.GetPassenger.Shipmod = 0.8;
		break;
		case 1:
			pchar.GenQuest.GetPassenger.Shipmod = 1;
		break;
		case 2:
			pchar.GenQuest.GetPassenger.Shipmod = 1.2;
		break;
		case 3:
			pchar.GenQuest.GetPassenger.Shipmod = 1.5;
		break;
		case 4:
			pchar.GenQuest.GetPassenger.Shipmod = 2.2;
		break;
		case 5:
			pchar.GenQuest.GetPassenger.Shipmod = 3;
		break;
		case 6:
			pchar.GenQuest.GetPassenger.Shipmod = 3;
		break;
	}
}