// реплики солдат на палубе при разговоре в море
// форт-стража и комендант форта
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
			dialog.text = "うちの船長に話せ。俺から言うことは何もねえ。";
			Link.l1 = "「いいだろう。」";
			Link.l1.go = "exit";
			
			NextDiag.TempNode = "first time";
		break;
		//  на палубе -->
		case "On_Deck":
			dialog.text = "うちの船長に話せ。俺から言うことは何もねえ。";
			Link.l1 = "「いいだろう。」";
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Deck";
/*			
			// Первый церковный генератор
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapWaitOnTavern"))
			{
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithSailors"))
				{
					dialog.text = "旦那、誰かお探しですか？";
					Link.l1 = "ああ、相棒。船長に会えるか？";
					Link.l1.go = "ChurchQuest1_Node1";
				}
				else
				{
					dialog.text = "もし俺たちの船長を探しているなら、ついさっき上陸したぜ。";
					Link.l1 = "Fine";
					Link.l1.go = "exit";
				}
				break;
			}
*/			
			//--> eddy. квест мэра, закрываем выход с палубы и ноду даем нужную
			if (CheckAttribute(pchar, "GenQuest.DestroyPirate") && pchar.GenQuest.CaptainId == "MQPirate")
			{
	    		dialog.text = RandPhraseSimple("おお、一人でここに来たのか。ははっ！だったら、俺たちの船長のところへ行け。自分の情けない所業を話してこい……","おったまげたぜ、どうやらお前はイカれてるみたいだな、相棒。うちの船長のところへ行けよ、 あいつが話をつけてくれるさ。");
				Link.l1 = "残念だな……";
				Link.l1.go = "exit";
			}
			//<-- eddy. квест мэра, закрываем выход с палубы
		break;
/*		
		case "ChurchQuest1_Node1":
			dialog.text = "港で彼を探した方がいいぜ。";
			Link.l1 = "ありがとう、友よ。";
			Link.l1.go = "exit";
			NextDiag.TempNode = "On_Deck";
			PChar.GenQuest.ChurchQuest_1.CapWaitOnTavern = true; 
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithSailors"); // Не спрашиваем моряков
		break;
*/		
        //  на палубе <--
				
		// ugeen --> разговор с боцманом по генератору "Повод для спешки"
		case "On_MyShip_Deck":
			dialog.text = "いやあ、ひどい騒ぎだったな、船長！俺たちはいつものように酒場で飲んでたんだが、叫び声が聞こえてきてな。 酒場から飛び出したら、お前を捕まえようとしてる連中がいたんだ。くそったれめ！だから、 こんなよそよそしい港はさっさと出ることにしたんだぜ。";
			link.l1 = "ああ、確かに正義の感覚がちょっと変わってる奴もいるもんだぜ。";
			link.l1.go = "On_MyShip_Deck_1";
		break;
		
		case "On_MyShip_Deck_1":
		    if(pchar.questTemp.ReasonToFast == "speakSuccess_chain_A") 
			{
				// карты не было
				dialog.text = "船長！そんなに気を揉むなよ！静かに逃げるのは無理だって最初から分かってたから、 地元の銀行家を訪ねて金庫を調べることにしたんだ。これがあんたの取り分だ― "+sti(pchar.questTemp.ReasonToFast.p9)+" ペソ……";
			}
			if(pchar.questTemp.ReasonToFast == "speakSuccess_chain_B")
			{
				// карту отобрали
				GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
				dialog.text = "船長！そんなに気を揉むなって！静かに逃げるのは無理だって最初から分かってたから、 地元の銀行家のところに寄って金庫を調べてきたんだ。質箱には立派な剣もあったぜ。これがあんたの取り分だ― "+sti(pchar.questTemp.ReasonToFast.p9)+" ペソと剣……";
			}		
			link.l1 = "よくやったな、野郎ども！よくやった！俺はお前たちを誇りに思うぜ。";
			link.l1.go = "On_MyShip_Deck_End";
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.ReasonToFast.p9));			
			pchar.Ship.Crew.Morale = MORALE_MAX;
			chrDisableReloadToLocation = false; // Откроем выход
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
		
		// разговор с боцманом по генератору 'Операция Галеон'
		case "CapComission_OnShipDeck":
			dialog.text = "船長、あなたの友人が逃げ出したぞ。";
			link.l1 = "「どの友達だ？」";
			link.l1.go = "CapComission_OnShipDeck1";
		break;
		
		case "CapComission_OnShipDeck1":
			dialog.text = "さて、あんたが地下牢から連れ出した友人のことだ。";
			link.l1 = "「どうやってあいつを見失ったんだよ、まったく！？」";
			link.l1.go = "CapComission_OnShipDeck2";
		break;
		
		case "CapComission_OnShipDeck2":
			dialog.text = "俺たちのせいじゃねえんだ、船長。あいつは便所から海に飛び込んじまったんだよ…撃とうとしたけど、中は暗すぎて無理だったんだ…";
			link.l1 = "くそっ！お前ら、本当に手に負えなくなったな！全員陸に上げてサトウキビ畑で働かせてやる！ あんな貴重な大物を失うなんて！信じられねえ！";
			link.l1.go = "CapComission_OnShipDeck3";
		break;
		
		case "CapComission_OnShipDeck3":
			chrDisableReloadToLocation = false; // Откроем выход
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
		// <-- ugeen
		
		// разговор с боцманом по ситуациям в трюме
		case "Hold_GenQuest_OnShipDeck":
			dialog.text = "船長、許してください、俺たちのせいです――囚人が逃げてしまいました。";
			link.l1 = "どの囚人だ？誰が逃げたんだ？";
			link.l1.go = "Hold_GenQuest_OnShipDeck1";
		break;
				
		case "Hold_GenQuest_OnShipDeck1":
			dialog.text = "「ええと、ああ、あいつの名前を忘れちまった」 "+pchar.GenQuest.Hold_GenQuest.CapName+"、だろ？";
			link.l1 = "くそっ！どこ見てやがったんだ？";
			link.l1.go = "Hold_GenQuest_OnShipDeck2";
		break;
		
		case "Hold_GenQuest_OnShipDeck2":
			dialog.text = "奴は貨物倉から抜け出してブルワークを飛び越えたんだ。\n騒ぎを避けるために撃たなかったんだが、俺たちがロングボートの準備をしている間に、あの忌々 しい漁師どもに助けられちまった。";
			link.l1 = "「それで俺はお前に給金を払ってるのか！見張り頭を鞭打って、一週間ラムを抜きにしろ。配置につけ！錨を上げるぞ…」";
			link.l1.go = "Hold_GenQuest_OnShipDeck3";
		break;
		
		case "Hold_GenQuest_OnShipDeck3":
			chrDisableReloadToLocation = false; // Откроем выход
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
			dialog.text = "ごきげんよう、船長。あなたの……の間に事故はありませんでした。";
			link.l1 = "わかった、わかったよ……うちの貨物室に囚人がいるんだ。名前は "+pchar.GenQuest.Hold_GenQuest.CapName+"。数人連れて彼を港まで護送しろ。もう自由の身だ。";
			link.l1.go = "Hold_GenQuest_OnShipDeck5";
		break;
		
		case "Hold_GenQuest_OnShipDeck5":
			dialog.text = "本当にあいつは自由の身なのか？俺たちがロングボートで送り届けるのか？";
			link.l1 = "いや、クソったれなカメの上じゃねえよ……ちゃんと言ったつもりだぜ。さっさとしろ！引き潮が始まる前に錨を上げなきゃならねえんだ。";
			link.l1.go = "Hold_GenQuest_OnShipDeck3";
		break;
		
		// Warship 09.07.09 Базар с нашим матросом на палубе Мэри Селест -->
		case "On_MaryCeleste_Deck":
			Dialog.text = "船長、船内には誰一人いません！何かがおかしいですよ……トミーが操舵室で猫を見たと言ってましたが、それだけが生きているものだったんです……";
			Link.l1 = "馬鹿野郎、猫に魂なんてねえよ。あいつはもう長いこと教会に行ってねえみたいだな、いや、 もしかしたら一度も行ったことがねえのかもな。\n船長室に行ったか？航海日誌が必要なんだ。";
			Link.l1.go = "On_MaryCeleste_Deck_1";
		break;
		
		case "On_MaryCeleste_Deck_1":
			Dialog.text = "いや、奴らにも魂はあるんだ。航海日誌もなければ、航海用の器具も一つもなかった。\nロングボートさえ一隻も……";
			Link.l1 = "奴らは違う。嵐で追い払われたのか？";
			Link.l1.go = "On_MaryCeleste_Deck_2";
		break;
		
		case "On_MaryCeleste_Deck_2":
			Dialog.text = "ああ、船長。猫にも魂はあるんだぜ。船長、ロングボートは切り離されてて、操舵室の床で剣を見つけたんだ。 錆びてて血まみれだ。ほら、見てくれ…";
			Link.l1 = "こんなガラクタはもうやめろ、捨てちまえ、そして猫の話もやめろ、くそっ！船倉を確認して出発しよう……おい、なんか様子がおかしいぞ、俺はまったく気に入らねえ……";
			Link.l1.go = "On_MaryCeleste_Last";
			NextDiag.TempNode = "On_MaryCeleste_Deck_SailorLast";
		break;
		
		case "On_MaryCeleste_Last":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetCitizenType(NPChar); // Чтоб по палубе ходил
			
			NPChar = GetRealShip(GetCharacterShipType(CharacterFromID("MaryCelesteCapitan")));
			NPChar.TurnRate = sti(PChar.QuestTemp.MaryCeleste.TurnRate); // Вернем манёвренность, для интерфейса
			
			chrDisableReloadToLocation = false; // Откроем выход
			
			LaunchTransferMain(PChar, CharacterFromID("MaryCelesteCapitan"), "MaryCelesteTransfer");
		break;
		
		case "On_MaryCeleste_Deck_SailorLast":
			switch(rand(2))
			{
				case 0:
					Dialog.text = "船長、俺はこの場所に嫌な予感がするぜ……そろそろ引き上げた方がいいんじゃねえか？";
					Link.l1 = "ああ……船のボートへ行け。";
					Link.l1.go = "exit";
				break;
				
				case 1:
					Dialog.text = "船長、もしこの見知らぬ船を港へ連れて行くつもりなら、俺はここには残らねえ。むしろ海に飛び込んだほうがマシだ。";
					Link.l1 = "俺にはそんなことできねえ……それに、ちょっと怖いんだ……";
					Link.l1.go = "exit";
				break;
				
				case 2:
					Dialog.text = "「沈めた方がいいんじゃねえか、船長？」";
					Link.l1 = "ここに住む死んだ船乗りたちの魂が、俺たちの悪夢に現れるようにするってのか？";
					Link.l1.go = "On_MaryCeleste_Deck_SailorLast_1";
				break;
			}
			
			NextDiag.TempNode = "On_MaryCeleste_Deck_SailorLast";
		break;
		
		case "On_MaryCeleste_Deck_SailorLast_1":
			Dialog.text = "なんてこった、いやだ！船長……なぜそんなことを言うんだ？";
			Link.l1 = "青ざめるなよ、冗談だって……船のボートへ行け。\nまあ、お前の言う通りかもしれねえな、猫にも魂があるのかも……";
			Link.l1.go = "exit";
		break;
		// <-- Базар с нашим матросом на палубе Мэри Селест
		
        //  на палубе <--
        case "On_Fort":
			dialog.text = RandPhraseSimple("親分に話せ。俺はお前に言うことなんかねえ。","俺は持ち場にいるぜ。質問があるなら全部砦の司令官に聞いてくれ。");
			Link.l1 = "「いいだろう。」";
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Fort";
		break;
		
		case "On_Fort_Head":
			dialog.text = RandPhraseSimple("今は本当に忙しいんだ。ほっといてくれ。","俺の仕事の邪魔をするな。話すことなんて何もねえ。");
			Link.l1 = "「哀れだな……」";
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

			dialog.text = RandPhraseSimple("モーガンが「ちょっと言いたいことがある」ってさ……どこかこの甲板にいるぜ。","へっ、モーガンを探せ。悪い知らせが待ってるぜ…");
			Link.l1 = "「いいだろう。」";
			Link.l1.go = "exit";

			NextDiag.TempNode = "Morgan_wait_you";
		break;
	}
}
