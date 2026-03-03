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
			dialog.text = "Porozmawiaj z naszym kapitanem. Nie mam ci nic do powiedzenia.";
			Link.l1 = "Dobrze.";
			Link.l1.go = "exit";
			
			NextDiag.TempNode = "first time";
		break;
		//  на палубе -->
		case "On_Deck":
			dialog.text = "Porozmawiaj z naszym kapitanem. Nie mam ci nic do powiedzenia.";
			Link.l1 = "Dobrze.";
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Deck";
/*			
			// Первый церковный генератор
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapWaitOnTavern"))
			{
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithSailors"))
				{
					dialog.text = "Panie, szukasz kogoś?";
					Link.l1 = "Tak, kumplu. Czy mogę zobaczyć kapitana?";
					Link.l1.go = "ChurchQuest1_Node1";
				}
				else
				{
					dialog.text = "Jeśli szukasz naszego kapitana. Niedawno zszedł na brzeg.";
					Link.l1 = "Dobrze";
					Link.l1.go = "exit";
				}
				break;
			}
*/			
			//--> eddy. квест мэра, закрываем выход с палубы и ноду даем нужную
			if (CheckAttribute(pchar, "GenQuest.DestroyPirate") && pchar.GenQuest.CaptainId == "MQPirate")
			{
	    		dialog.text = RandPhraseSimple("O, przyszedłeś tu sam. Ha! W takim razie idź do naszego kapitana. Opowiedz mu o swoich żałosnych czynach...","Wow, wydajesz się szalony, przyjacielu. Idź do naszego kapitana, a on z tobą porozmawia.");
				Link.l1 = "Szkoda...";
				Link.l1.go = "exit";
			}
			//<-- eddy. квест мэра, закрываем выход с палубы
		break;
/*		
		case "ChurchQuest1_Node1":
			dialog.text = "Lepiej poszukaj go w porcie.";
			Link.l1 = "Dziękuję, mój przyjacielu.";
			Link.l1.go = "exit";
			NextDiag.TempNode = "On_Deck";
			PChar.GenQuest.ChurchQuest_1.CapWaitOnTavern = true; 
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithSailors"); // Не спрашиваем моряков
		break;
*/		
        //  на палубе <--
				
		// ugeen --> разговор с боцманом по генератору "Повод для спешки"
		case "On_MyShip_Deck":
			dialog.text = "Cóż, to było poważne zamieszanie, kapitanie! Byliśmy w karczmie, pijąc jak zwykle, gdy usłyszeliśmy krzyki. Wybiegliśmy z karczmy i zobaczyliśmy, że próbują cię aresztować. Do diabła z nimi! Więc zdecydowaliśmy się opuścić ten nieprzyjazny port.";
			link.l1 = "Tak, z pewnością niektórzy ludzie mają nieco dziwne postrzeganie sprawiedliwości.";
			link.l1.go = "On_MyShip_Deck_1";
		break;
		
		case "On_MyShip_Deck_1":
		    if(pchar.questTemp.ReasonToFast == "speakSuccess_chain_A") 
			{
				// карты не было
				dialog.text = "Kapitanie! Nie martw się tak! Było jasne, że nie da się uciec w spokoju, więc postanowiliśmy odwiedzić miejscowego bankiera, aby sprawdzić jego skrzynie. Oto twój udział - "+sti(pchar.questTemp.ReasonToFast.p9)+" pesos...";
			}
			if(pchar.questTemp.ReasonToFast == "speakSuccess_chain_B")
			{
				// карту отобрали
				GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
				dialog.text = "Kapitanie! Nie martw się tak! Było jasne, że nie ma szans na spokojną ucieczkę, więc postanowiliśmy odwiedzić miejscowego bankiera i sprawdzić jego skrzynie. W pudełku zastawów był też świetny miecz. Oto twój udział - "+sti(pchar.questTemp.ReasonToFast.p9)+" pesos i miecz...";
			}		
			link.l1 = "Dobra robota, chłopcy! Dobra robota! Jestem z was dumny.";
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
			dialog.text = "Kapitanie, twój przyjaciel uciekł.";
			link.l1 = "Jaki przyjaciel?";
			link.l1.go = "CapComission_OnShipDeck1";
		break;
		
		case "CapComission_OnShipDeck1":
			dialog.text = "Cóż, przyjaciel, którego uwolniłeś z lochów.";
			link.l1 = "Jak do licha udało ci się go zgubić?!";
			link.l1.go = "CapComission_OnShipDeck2";
		break;
		
		case "CapComission_OnShipDeck2":
			dialog.text = "To nie była nasza wina, kapitanie. Skoczył przez latrynę do morza... Próbowaliśmy do niego strzelać, ale było tam za ciemno...";
			link.l1 = "Do diabła! Naprawdę wymknęliście się spod kontroli! Wszyscy zostaniecie wyładowani i wysłani do pracy przy trzcinie cukrowej! Stracić tak cennego faceta! Niewiarygodne!";
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
			dialog.text = "Kapitanie, wybacz nam, to nasza wina - więzień uciekł.";
			link.l1 = "Jaki więzień? Kto uciekł?";
			link.l1.go = "Hold_GenQuest_OnShipDeck1";
		break;
				
		case "Hold_GenQuest_OnShipDeck1":
			dialog.text = "Cóż, och, zapomniałem jego imienia, "+pchar.GenQuest.Hold_GenQuest.CapName+", prawda?";
			link.l1 = "Cholera! Jak to się stało?";
			link.l1.go = "Hold_GenQuest_OnShipDeck2";
		break;
		
		case "Hold_GenQuest_OnShipDeck2":
			dialog.text = "Zszedł z ładowni i skoczył z burty. Nie zastrzeliliśmy go, by uniknąć hałasu, a gdy przygotowywaliśmy szalupę, został uratowany przez cholernych rybaków.";
			link.l1 = "Za co ja wam płace!? Wychłostać głowę straży i pozbawić go rumu na tydzień. Do dzieła! Podnosimy kotwicę...";
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
			dialog.text = "Witaj, kapitanie. Nie było żadnych wypadków podczas twojej...";
			link.l1 = " Dobrze, dobrze, zrozumiałem.... Jest więzień w naszej ładowni. Nazywa się "+pchar.GenQuest.Hold_GenQuest.CapName+" Weź kilku ludzi i dostarcz go do portu. Jest teraz wolny.";
			link.l1.go = "Hold_GenQuest_OnShipDeck5";
		break;
		
		case "Hold_GenQuest_OnShipDeck5":
			dialog.text = "Czy on jest naprawdę wolny? Mamy go dostarczyć na łodzi wiosłowej?";
			link.l1 = "Nie, na cholernym żółwiu... Myślałem, że byłem wystarczająco jasny. I pospiesz się! Musimy podnieść kotwicę na początku odpływu.";
			link.l1.go = "Hold_GenQuest_OnShipDeck3";
		break;
		
		// Warship 09.07.09 Базар с нашим матросом на палубе Мэри Селест -->
		case "On_MaryCeleste_Deck":
			Dialog.text = "Kapitanie, na statku nie ma w ogóle ludzi! Coś jest tu bardzo nie tak... Tommy powiedział, że jedyne co widział, to kota, i to była jedyna żywa dusza...";
			Link.l1 = "Idioto, koty nie mają dusz. Wygląda na to, że dawno nie odwiedzał kościoła albo nigdy tam nie był. Byłeś w kajucie kapitana? Potrzebuję dziennika pokładowego.";
			Link.l1.go = "On_MaryCeleste_Deck_1";
		break;
		
		case "On_MaryCeleste_Deck_1":
			Dialog.text = "Nie, one mają dusze. Nie było dziennika pokładowego ani jednego instrumentu nawigacyjnego. Nawet jednej łodzi.";
			Link.l1 = "Co? Czy to zostało zerwane przez burzę?";
			Link.l1.go = "On_MaryCeleste_Deck_2";
		break;
		
		case "On_MaryCeleste_Deck_2":
			Dialog.text = "Owszem, kapitanie. Koty mają dusze. Kapitanie, szalupa została odcięta i znaleźliśmy na pokładzie miecz. Jest zardzewiały i zakrwawiony. Proszę, spójrz...";
			Link.l1 = "Przestań mi wciskać te bzdury, wyrzuć to i przestań pieprzyć o kotach, do diabła! Sprawdźmy ładownię i zmykajmy... O, coś tu jest bardzo nie tak i cholernie mi się to nie podoba...";
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
					Dialog.text = "Kapitanie, mam złe przeczucia co do tego miejsca... Może czas już stąd odpłynąć?";
					Link.l1 = "Tak... Idź do łodzi okrętowej.";
					Link.l1.go = "exit";
				break;
				
				case 1:
					Dialog.text = "Kapitanie, nie zostanę na tym dziwnym statku, jeśli zamierzasz zabrać go do portu. Lepiej sam wskoczę do morza.";
					Link.l1 = "Nie jestem skłonny tego zrobić... Trochę się boję...";
					Link.l1.go = "exit";
				break;
				
				case 2:
					Dialog.text = "Może powinniśmy ją zatopić, kapitanie?";
					Link.l1 = "Aby dusze zmarłych marynarzy, które tu mieszkają, mogły odwiedzać nas w naszych koszmarach?";
					Link.l1.go = "On_MaryCeleste_Deck_SailorLast_1";
				break;
			}
			
			NextDiag.TempNode = "On_MaryCeleste_Deck_SailorLast";
		break;
		
		case "On_MaryCeleste_Deck_SailorLast_1":
			Dialog.text = "Na Boga, nie! Kapitanie... dlaczego to mówisz?";
			Link.l1 = "Nie blednij, żartowałem... Idź na szalupę. I chyba masz rację, może koty naprawdę mają dusze...";
			Link.l1.go = "exit";
		break;
		// <-- Базар с нашим матросом на палубе Мэри Селест
		
        //  на палубе <--
        case "On_Fort":
			dialog.text = RandPhraseSimple("Porozmawiaj z szefem. Nie mam ci nic do powiedzenia.","Jestem na swoim posterunku. Wszystkie pytania kieruj do komendanta fortu.");
			Link.l1 = "Dobrze.";
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Fort";
		break;
		
		case "On_Fort_Head":
			dialog.text = RandPhraseSimple("Jestem teraz naprawdę zajęty. Zostaw mnie w spokoju.","Nie rozpraszaj mnie w mojej pracy. Nie ma o czym rozmawiać.");
			Link.l1 = "Szkoda...";
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

			dialog.text = RandPhraseSimple("Morgan chciał ci powiedzieć 'coś niecoś'... Jest tu gdzieś, na pokładzie.","Heh, znajdź Morgana. Czekają na ciebie złe wieści...");
			Link.l1 = "Dobrze.";
			Link.l1.go = "exit";

			NextDiag.TempNode = "Morgan_wait_you";
		break;
	}
}
