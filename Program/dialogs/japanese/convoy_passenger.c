//пассажир на доставку
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
				dialog.text = RandPhraseSimple("ああ、くそっ！お前が誰か知ってるぜ！お前の船に乗客として乗り込むなんて、よっぽどの馬鹿だけだ！じゃあな！","ああ、お前が誰か知ってるぜ！俺は絶対にお前の船には乗らねえ。馬鹿じゃねえんだ……");
				link.l1 = RandPhraseSimple("へっ、なんて腰抜けだ！","最近の人間は本当に腰抜けばかりだぜ！");
				link.l1.go = "convoy_refused";
			}
			else
			{
				dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"！俺は "+GetFullName(NPChar)+"。乗客を乗せるって聞いたんだが？";
				link.l1 = "たぶんね。俺の儲け次第だぜ。";
				link.l1.go = "prepare_convoy_quest_3";
			}
		break;
		
		case "prepare_convoy_quest_3":
			LookShipPassenger();
			GenerateConvoyPassengerQuest(npchar);
			dialog.text = "私は の酒場まで連れて行ってほしい "+XI_ConvertString("Colony"+npchar.GenQuest.GetPassenger_Destination+"Gen")+"、その上で "+XI_ConvertString(GetIslandByCityName(npchar.GenQuest.GetPassenger_Destination)+"Dat")+"、のために "+FindRussianDaysString(sti(npchar.GenQuest.GetPassenger_Time))+"、それに対して報酬を払う "+FindRussianMoneyString(sti(npchar.GenQuest.GetPassenger_Money))+"。賛成か？";
			link.l1 = "ああ、そうだ。";
			link.l1.go = "convoy_agreeded";
			link.l2 = "面白い提案だとは思わねえな。";
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
			sTemp = XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + ", which is on " + XI_ConvertString(GetIslandByCityName(npchar.GenQuest.GetPassenger_Destination) + "Dat") + ",";
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sDay", FindRussianDaysString(sti(npchar.GenQuest.GetPassenger_Time)));
            AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(npchar.GenQuest.GetPassenger_Money)));
            // по городу вернём его таверну
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
			dialog.text = "ありがとう。約束を果たしてくれたな。俺は目的地に着いた、これが報酬だ。さあ、受け取れ。";
			Link.l1 = "ありがとうございます。";
			link.l1.go = "complete_convoy_quest_1";
		break;

		case "complete_convoy_quest_1":
			//слухи
			AddSimpleRumour(LinkRandPhrase("One person by the name of " + GetFullName(npchar) + " says that captain " + GetMainCharacterNameDat() + " can be trusted, since "+ GetSexPhrase("he","she") +" had easily delivered him to " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + ".", 
				"Passenger named " + GetFullName(npchar) + " says that captain " + GetMainCharacterNameDat() + " can be trusted. "+ GetSexPhrase("He delivered","She delivered") +" him to " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + " absolutelly safely.", 
				"I heard that you are a captain who keeps his word given to passengers. Huckster named " + GetFullName(npchar) + " is giving high praises to you."), sti(npchar.nation), 40, 1);
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.ConvoyPassenger." + npchar.id); //извлекаем из структуры недовольных
			//--> смотрим Deck
    		makearef(arAll, pchar.GenQuest.ConvoyPassenger);
			if (GetAttributesNum(arAll) == 0) pchar.quest.ConvoyMapPassenger.over = "yes";
			//<-- смотрим Deck
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
			dialog.text = NPCStringReactionRepeat(LinkRandPhrase(RandSwear()+"船長、時間切れだ。いつになったら、くそっ、俺はやっと\n "+XI_ConvertString("Colony"+npchar.GenQuest.GetPassenger_Destination+"Acc")+"?",RandSwear()+"船長、一体いつまでどこをさまよってるんだ！？いつになったら俺たちは到着するんだよ\n "+XI_ConvertString("Colony"+npchar.GenQuest.GetPassenger_Destination+"Gen")+"?",RandSwear()+"聞いてくれ、船長、俺はそこへ行く必要があるんだ "+XI_ConvertString("Colony"+npchar.GenQuest.GetPassenger_Destination+"Gen")+"、それがいつ起こるのか、はっきり簡単に答えてほしいんだ！"),RandPhraseSimple("船長、またしてもあなたの義務について質問しなければなりません。いつになったら我々は "+XI_ConvertString("Colony"+npchar.GenQuest.GetPassenger_Destination+"Gen")+"?","船長、これで二度目ですが、私の旅についてまたお伺いしなければなりません。いったいいつになったら、 私たちは海岸を見ることができるのでしょうか\n "+XI_ConvertString("Colony"+npchar.GenQuest.GetPassenger_Destination+"Gen")+"?"),RandPhraseSimple(RandSwear()+"船長、三度目だが、いつになったら着くんだ "+XI_ConvertString("Colony"+npchar.GenQuest.GetPassenger_Destination+"Acc")+"?","船長、ものすごく時間を無駄にしたじゃねえか！いつになったら俺を連れて行ってくれるんだ "+XI_ConvertString("Colony"+npchar.GenQuest.GetPassenger_Destination+"Acc")+"?"),"聞いてくれ、船長、これは本当にやりすぎだぜ！","ブロック",0,npchar,Dialog.CurrentNode);
            if (sti(npchar.GenQuest.GetPassenger_Money) > 100)
            {
				link.l1 = HeroStringReactionRepeat(RandPhraseSimple("どうかお許しください、やるべきことが山ほどあったもので……七日後には必ず目的地に到着します。","申し訳ない。 "+GetAddress_Form(NPChar)+"、本当にあなたへの義務を果たせなかっただろう。しかし心配しないでくれ、1週間で到着する。"),RandPhraseSimple("改めてお詫び申し上げます。\n目的地には一週間で到着いたします。","改めてお詫び申し上げます。\n目的地には一週間で到着いたします。"),RandPhraseSimple("そしてもう一度、お詫び申し上げます……目的地には一週間で到着いたします。","そしてもう一度、申し訳ありません。必ず一週間以内に目的地へお連れします、約束します。"),"承知しました。 "+GetAddress_Form(NPChar)+"しかし、どうかご辛抱を……遅くとも七日以内に目的地までお連れします！",npchar,Dialog.CurrentNode);
    			link.l1.go = "convoy_DeskTalk_1";
			}
			link.l2 = HeroStringReactionRepeat(RandPhraseSimple("ああ…乗客か…お前のことはすっかり忘れてたぜ…船倉の方が快適だろうよ、もう俺を煩わせることもできねえからな。","ほうほう、自分の目を疑うぜ！俺の船に見知らぬ奴がいるとはな！よし、黙ってさっさと俺の船倉に入れ、今すぐだ！"),"二度目か？ああ、確かに……だがな、もしかしたらお前を“見学”と称して船倉に送り込んでやるかもしれねえぞ。","三度目かい？そりゃ残念だな、へへ……まあ、相棒、俺の船倉へようこそ。俺の船の甲板をうろついて、俺の邪魔なんかするもんじゃねえぞ。","ああ、なるほど、それは最高に苛立つってことか！よし、もう茶番は終わりだ。船倉へようこそ。 "+GetAddress_Form(NPChar)+".",npchar,Dialog.CurrentNode);
			link.l2.go = "convoy_Prison_1";
			pchar.quest.Munity = "Deads"; //дверцы откроем
		break;
		
		case "convoy_DeskTalk_1":
			dialog.text = LinkRandPhrase("わかったが、遅れた分だけ報酬を減らすぞ。","わかった、信じてやるよ……だがな、お前の報酬は減らすから覚えておけよ！","まあ、どこにも行くあてはないが、とにかく、お前の報酬は減らすつもりだからな……");
			Link.l1 = LinkRandPhrase("「よし。」","……そうか、なら……","「わかった、あんたの言う通りだ。」");
			link.l1.go = "convoy_DeskTalk_2";
		break;

		case "convoy_DeskTalk_2":
			dialog.text = RandPhraseSimple("今回はあなたがちゃんと義務を果たしてくれると信じたい。","この不愉快な話題については、これが最後の会話になることを願っています。");
			Link.l1 = "もちろんだ。";
			link.l1.go = "convoy_DeskTalk_exit";
		break;

		case "convoy_DeskTalk_exit":
			DeleteAttribute(pchar, "GenQuest.ConvoyPassenger." + npchar.id); //извлекаем из структуры недовольных
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
			dialog.text = RandSwear()+"何の船倉だ？俺にはわからねえ！";
			if (GetPrisonerQty() < PRISONER_MAX)
			{
    			Link.l1 = "「他に何を理解しろってんだ？これからはお前は俺の捕虜だ！さっさと船倉に行け、動け！」";
    			link.l1.go = "convoy_Prison_2";
            }
			Link.l2 = "冗談さ……七日後にお前の町に到着するぜ。";
			link.l2.go = "convoy_DeskTalk_1";
		break;
		
		case "convoy_Prison_2":
			dialog.text = RandSwear()+"「この報いは受けてもらうぜ」 "+GetSexPhrase("クズ","くさい野郎")+"!";
			Link.l1 = "みんなそう言うが、結局はみんな俺に金を払うんだぜ！";
			link.l1.go = "convoy_Prison_3";
		break;
		
		case "convoy_Prison_3":
			AddSimpleRumour(LinkRandPhrase("It has been reported that a captain named " + GetFullName(pchar) + " obliged to deliver a passenger by the name of " + GetFullName(npchar) + ", but didn't stay true to "+ GetSexPhrase("his","her") +" word. Besides, "+ GetSexPhrase("he","she") +" imprisoned a poor guy. That's what happens when you trust strange people...", 
				"What's wrong with this world?! Captain " + GetFullName(pchar) + " imprisoned a poor guy by the name of " + GetFullName(npchar) + ", despite him being a passenger on his ship...", 
				"People say, captain, that you are "+ GetSexPhrase("a real scoundrel","a really vile bitch") +". They say that poor " + GetFullName(npchar) + " was taken prisoner on board your ship. And you promised to deliver him to " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + ". Very, very ugly ..."), sti(npchar.nation), 40, 1);
            RemovePassenger(PChar, NPChar);
        	LAi_SetActorType(NPChar);
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 5.0);
        	ChangeCharacterComplexReputation(pchar,"nobility", -5);
            OfficersReaction("bad");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(NPChar.nation)) + "hunter", GetIntByCondition(HasShipTrait(pchar, "trait23"), 10 + rand(10), 5 + rand(5)));// награда
			DeleteAttribute(pchar, "GenQuest.ConvoyPassenger." + npchar.id); //извлекаем из структуры недовольных
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

	iNation = GetRelation2BaseNation(sti(npchar.nation)); //если привезти нужно во вражеский город
	npchar.GenQuest.GetPassenger_Destination = sGlobalTemp;
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.GetPassenger_City), GetArealByCityName(sGlobalTemp));
	if (sti(daysQty) > 14) daysQty = 14;
	npchar.GenQuest.GetPassenger_Time  = makeint(sti(daysQty)*(frand(1.3)+0.7));
	iTradeMoney = (sti(daysQty)*500*sti(pchar.GenQuest.GetPassenger.Shipmod)+rand(100))*sti(daysQty)/sti(npchar.GenQuest.GetPassenger_Time);
	if (iNation == RELATION_ENEMY && sti(npchar.nation != PIRATE)) iTradeMoney = makeint(iTradeMoney * 1.3); //то размер награды увеличивается
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
