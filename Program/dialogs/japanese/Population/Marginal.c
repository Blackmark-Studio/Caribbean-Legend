//Jason общий диалог уличных контриков
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "何の用だ？";
			link.l1 = "「何もない。」";
			link.l1.go = "exit";
			link.l2 = RandPhraseSimple("お前に聞きたいことがあるんだ。","情報が必要だ。");
			link.l2.go = "quests";//(перессылка в файл города)
			
			if (npchar.quest.meeting == "0")
			{
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Marginpassenger"))//захват пассажира
				{
					dialog.text = "おい、船長！そう、お前だ。こっちに来い、いい話があるんだ……";
					link.l1 = "「それで、どういう話だ？」";
					link.l1.go = "passenger";
					link.l2 = "急いでいるんだ、友よ。次の機会にしよう。";
					link.l2.go = "exit_quest";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				dialog.text = LinkRandPhrase("おい、船長、今はちょっと忙しいんだ。何の用だ？","何の用だ、船長？","船長、今は話す気分じゃねえんだ。何の用だ？");
				link.l1 = "「ご挨拶を」 "+GetAddress_FormToNPC(NPChar)+"。ちょっと待て、聞きたいことがあるんだ。";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("お前に質問がある。","情報が必要だ。");
				link.l2.go = "quests";//(перессылка в файл города)
				link.l3 = "たいしたことじゃねえ、今から酒場に行くところさ……";
				link.l3.go = "exit";
				npchar.quest.meeting = "1";
			}
			NextDiag.TempNode = "First time";
		break;

//----------------------------------------захват пассажиров для выкупа------------------------------------------
			case "passenger":
				DeleteAttribute(npchar, "talker");
				dialog.text = "ふむ。お前は船の船長だが、商人には見えねえな。懐にいくらか金貨が入ってるようだ……面白い情報を一握りのドゥブロン金貨と交換しねえか？";
				link.l1 = "まずは、お前の情報がエイト金貨一枚の価値があるって証明してみろ。";
				link.l1.go = "passenger_1";
			break;
		
			case "passenger_1":
				dialog.text = "そうさ、船長、そうだぜ。俺が言ってる額よりずっと価値があるんだ。金貨を渡してくれりゃ、いつ、どの船で、 とある重要人物が航海するか教えてやる。その人間をうまく身代金にできるぜ……買い手の名前まで教えてやる。どうだ、取引するか？";
				link.l1 = "ありえねえ！俺は誘拐犯じゃねえんだ。失せろ！";
				link.l1.go = "exit_quest";
				link.l2 = "「どうやってお前が本当のことを言ってると俺が分かるんだ？」";
				link.l2.go = "passenger_2";
			break;
		
			case "passenger_2":
				pchar.GenQuest.Marginpassenger.Dublon = 70+hrand(5)*10;
				dialog.text = "お前を騙すなんて、とんでもなく愚かなことだぜ、海の野郎。俺はこの町に住んでるし、面倒ごとはご免だ。たったの\n "+sti(pchar.GenQuest.Marginpassenger.Dublon)+" ドゥブロン金貨をくれれば、全ての情報を教えてやる。もっと稼げるぜ。";
				if (PCharDublonsTotal() >= sti(pchar.GenQuest.Marginpassenger.Dublon))
				{
					link.l1 = "一理あるな。金を受け取って、さあ話せ。";
					link.l1.go = "passenger_4";
				}
				link.l2 = "今は手元に十分なコインがないんだ。";
				link.l2.go = "passenger_3";
				link.l3 = "ふざけてんのか？口先だけの約束に本物の金を払えって？消え失せろ…";
				link.l3.go = "exit_quest";
			break;
		
			case "passenger_3":
				dialog.text = "そうかい？まあいいさ、船長。俺はあと数日ぐらい待てるし、この情報もな。金が用意できたら俺のところに来な。 俺を見つけるのは簡単だぜ……今日ならな、ははは！";
				link.l1 = "そんなに歯をむき出しにするな。わかったよ、金貨を持ってきてやる……気が変わらなければな。 ";
				link.l1.go = "passenger_wait";
			break;
			
			case "passenger_wait":
			DialogExit();
				SetFunctionTimerCondition("Marginpassenger_Over", 0, 0, 2, false);
				npchar.dialog.currentnode = "passenger_repeat";
			break;

			case "passenger_repeat":
				dialog.text = "俺の金を持ってきたか？";
				if (PCharDublonsTotal() >= sti(pchar.GenQuest.Marginpassenger.Dublon))
				{
					link.l1 = "ああ、持っていけ。今さら嘘なんかつくんじゃねえぞ……";
					link.l1.go = "passenger_4";
				}
				link.l2 = "まだだ。あとでもしかしたらな…";
				link.l2.go = "exit";
				Nextdiag.Tempnode = "passenger_repeat";
			break;
			
			case "passenger_4"://установка параметров
				pchar.quest.Marginpassenger_Over.over = "yes"; //снять возможный таймер
				RemoveDublonsFromPCharTotal(sti(pchar.GenQuest.Marginpassenger.Dublon));
				pchar.GenQuest.Marginpassenger.Name = GetFullName(npchar);
				pchar.GenQuest.Marginpassenger.City = npchar.city;
				pchar.GenQuest.Marginpassenger.Targetcity = SelectAnyColony(npchar.city); 
				pchar.GenQuest.Marginpassenger.Nation = npchar.nation;
				pchar.GenQuest.Marginpassenger.Days = 10+hrand(5);
				pchar.GenQuest.Marginpassenger.ShipName = GenerateRandomNameToShip(sti(npchar.nation));
				pchar.GenQuest.Marginpassenger.q2Name = GenerateRandomName(sti(npchar.nation), "man");
				pchar.GenQuest.Marginpassenger.Chance = 0.8+frand(0.4);
				SelectMarginpassengerParameter();
				log_testinfo(pchar.GenQuest.Marginpassenger.Targetcity);
				dialog.text = "火薬は乾いたままにしておけよ、すぐに必要になるぜ、船長。さて、聞け、今からだが\n "+FindRussianDaysString(sti(pchar.GenQuest.Marginpassenger.Days))+" 我々の植民地から船が出航する、その船は "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType),"Name")))+" 『』という名の"+pchar.GenQuest.Marginpassenger.ShipName+"「』そしてそれは向かうことになる」 "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Targetcity+"Gen")+"。乗客がいるぞ―  "+pchar.GenQuest.Marginpassenger.Text+"、名付けられた "+pchar.GenQuest.Marginpassenger.q1Name+"\n船長 "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType),"Name")+"Gen"))+" すべての商人と同じく、腰抜けの臆病者だぜ、ははは！もしかしたら戦いを避けることもできるかもな。 悪魔のように脅してやれば、奴は自分から標的を差し出すはずだ、へへ\n分かるだろう、 "+pchar.GenQuest.Marginpassenger.Text1+"、たぶん金貨は手に入るだろうが、その後で現地の役人に追われることになるぜ。獲物は に連れて行ったほうがいいぞ "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Targetcity)+"。そこに という男がいるはずだ "+pchar.GenQuest.Marginpassenger.q2Name+"\n"+pchar.GenQuest.Marginpassenger.Text2+" 名前を名乗る必要さえないさ。どこで仲間を身代金で取り戻すかはお前の判断だが、無理はするなよ……しかし "+sti(pchar.GenQuest.Marginpassenger.Dublon)*4+" ドゥブロンなら要求してもいいぜ。わかったか？";
				link.l1 = "ああ。これから自分の船に戻って航海日誌に書き記すつもりだ。";
				link.l1.go = "passenger_5";
			break;
		
			case "passenger_5":
				dialog.text = "その通り！正しい選択だ。よし、船長、この簡単な仕事、うまくやってくれよ。ああ、そうだ、 もう少しで忘れるところだった： "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType),"Name")))+" 港からではなく、近くの入り江の一つから出航することになる。だから注意して見張っておけ。幸運を祈るぜ、 そして金貨もありがとな！";
				link.l1 = "どういたしまして。一晩で全部使い切るなよ。";
				link.l1.go = "exit_quest";
				npchar.lifeday = 0;
				ReOpenQuestHeader("Marginpassenger");
				AddQuestRecord("Marginpassenger", "1");
				AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City));
				AddQuestUserData("Marginpassenger", "sTargetCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Targetcity));
				AddQuestUserData("Marginpassenger", "sName", pchar.GenQuest.Marginpassenger.Name);
				AddQuestUserData("Marginpassenger", "sName1", pchar.GenQuest.Marginpassenger.q1Name);
				AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
				AddQuestUserData("Marginpassenger", "sDay", FindRussianDaysString(sti(pchar.GenQuest.Marginpassenger.Days)));
				AddQuestUserData("Marginpassenger", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name")+"Voc")));
				AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName);
				AddQuestUserData("Marginpassenger", "sText", pchar.GenQuest.Marginpassenger.Text1);
				pchar.GenQuest.Marginpassenger = "begin";
				SetFunctionTimerCondition("Marginpassenger_InWorld", 0, 0, sti(pchar.GenQuest.Marginpassenger.Days), false);
			break;
			
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"聞け、落ち着いて武器を納めろ。","聞け、落ち着いて武器を収めろ。");
			link.l1 = LinkRandPhrase("「よし。」","結構だ。","ご希望の通りに。");
			link.l1.go = "exit";
		break;
		
		case "question":
			dialog.text = LinkRandPhrase("回りくどいことは言うなよ、船長。言いたいことをはっきり言え！","ああ、わかったよ。何の用だ？","質問か？よし、水夫、聞いてやるぜ。");
			link.l1 = LinkRandPhrase("最近の噂話を教えてくれないか？","最近ここで何か面白いことがあったかい？","カリブで何が起きているんだ？");
			link.l1.go = "rumours_marginal";
		break;
		
		case "exit_quest":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

void SelectMarginpassengerParameter()
{
	if (hrand(1) == 0)
	{
		pchar.GenQuest.Marginpassenger.q1Name = GenerateRandomName(sti(pchar.GenQuest.Marginpassenger.Nation), "woman");
		pchar.GenQuest.Marginpassenger.model = "women_"+(rand(5)+11);
		pchar.GenQuest.Marginpassenger.sex = "woman";
		pchar.GenQuest.Marginpassenger.ani = "towngirl";
		pchar.GenQuest.Marginpassenger.Text2 = "He wants to marry her and will pay a significant sum for the girl.";
		switch (hrand(4))
		{
			case 0: 
				pchar.GenQuest.Marginpassenger.Text = "store keeper's daughter";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the store keeper";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_store";
			break;
			case 1: 
				pchar.GenQuest.Marginpassenger.Text = "shipyard's master's daughter";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the shipyard's master";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_shipyard";
			break;
			case 2: 
				pchar.GenQuest.Marginpassenger.Text = "tavern keeper's daughter";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the tavern keeper";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_tavern";
			break;
			case 3: 
				pchar.GenQuest.Marginpassenger.Text = "banker's daughter";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the banker";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_bank";
			break;
			case 4: 
				pchar.GenQuest.Marginpassenger.Text = "harbor master's daughter";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the harbor master";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_portoffice";
			break;
		}
	}
	else
	{
		pchar.GenQuest.Marginpassenger.q1Name = GenerateRandomName(sti(pchar.GenQuest.Marginpassenger.Nation), "man");
		pchar.GenQuest.Marginpassenger.model = "citiz_"+(rand(9)+11);
		pchar.GenQuest.Marginpassenger.sex = "man";
		pchar.GenQuest.Marginpassenger.ani = "man";
		pchar.GenQuest.Marginpassenger.Text2 = "He has been planning to ingratiate himself with this family and he will pay a lot for the prisoner ";
		switch (hrand(4))
		{
			case 0: 
				pchar.GenQuest.Marginpassenger.Text = "trader's relative, shipmaster's";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the shipmaster";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_store";
			break;
			case 1: 
				pchar.GenQuest.Marginpassenger.Text = "shipyard's master's relative";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the shipyard's master";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_shipyard";
			break;
			case 2: 
				pchar.GenQuest.Marginpassenger.Text = "tavern keeper's relative";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the tavern keeper";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_tavern";
			break;
			case 3: 
				pchar.GenQuest.Marginpassenger.Text = "banker's relative";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the banker";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_bank";
			break;
			case 4: 
				pchar.GenQuest.Marginpassenger.Text = "harbor master's relative";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the harbor master";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_portoffice";
			break;
		}
	}
	if (sti(pchar.rank) < 5) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_6, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
	if (sti(pchar.rank) >= 5 && sti(pchar.rank) < 10) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
	if (sti(pchar.rank) >= 10 && sti(pchar.rank) < 17) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_4 + FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
	if (sti(pchar.rank) >= 17 && sti(pchar.rank) < 26) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_3 + FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
	if (sti(pchar.rank) >= 26) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_2 + FLAG_SHIP_CLASS_3, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
}
