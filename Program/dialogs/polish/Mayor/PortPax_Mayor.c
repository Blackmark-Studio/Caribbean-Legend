// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Czego chcesz? Pytaj śmiało.","Słucham cię, o co chodzi?"),"To już drugi raz, gdy próbujesz zapytać...","To już trzeci raz, kiedy próbujesz zapytać...","Kiedy to się skończy?! Jestem zajętym człowiekiem, zajmuję się sprawami kolonii, a ty wciąż mi przeszkadzasz!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniłem zdanie...","Nie teraz. Nieodpowiednie miejsce i czas."),"Prawda... Ale później, nie teraz...","Zapytam... Ale trochę później...","Przykro mi, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_2" && !CheckAttribute(npchar, "quest.patria") && !CheckAttribute(pchar, "questTemp.Patria.Visiter_Late"))
			{
				link.l1 = TimeGreeting()+" Monsieur. Jestem tutaj na rozkaz gubernatora generalnego Chevaliera de Poincy. Moim zadaniem jest dostarczenie barona o imieniu Noel Forget na Tortugę, który przybył z metropolii z zadaniem inspekcji kolonii, a jego głównym celem jest założenie Francuskiej Kompanii Zachodnioindyjskiej. Pozwólcie, że go przedstawię... On sam wyjaśni wszystkie szczegóły.";
                link.l1.go = "patria_portpax";
			}
			// Rebbebion, квест "Путеводная звезда"
			if (CheckAttribute(pchar, "questTemp.PZ.PortPaxMayorTalk"))
			{
				link.l1 = "Wasza Lordowska Mość, chciałeś mnie widzieć?";
				link.l1.go = "PZ1";
			}
			// Украденное воспоминание
			if (CheckAttribute(pchar, "questTemp.UV_DialogMayor"))
			{
				link.l1 = "Monsieur, mam do pana sprawę o wyjątkowo delikatnym charakterze.";
				link.l1.go = "UV_1";
			}
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("Zabrałeś już wszystko. Czego jeszcze chcesz?","Czy zostało coś, czego nie zdążyłeś zagrabić?");
            link.l1 = RandPhraseSimple("Tylko się rozglądam...","Tylko sprawdzam, mogę zapomnieć coś wziąć...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		// Jason НСО
		case "patria_portpax":
			dialog.text = "Bardzo się cieszę, że mogę cię poznać, Kapitanie Charles de Maure, oraz Barona. Zrobię wszystko, aby pobyt Monsieur Forget w naszej kolonii był jak najbardziej komfortowy. A korzystając z faktu, że tak wysokiej rangi Monsieur zaszczycił mnie wizytą, zwrócę się do was z pewną sprawą.";
			link.l1 = "Najciekawsze! Opowiedz nam o swojej sprawie, Wasza Wysokość.";
			link.l1.go = "patria_portpax_1";
		break;
		
		case "patria_portpax_1":
			dialog.text = "W ostatnich miesiącach naszą kolonię nie odwiedził żaden przedstawiciel generała-gubernatora, jakby całkowicie o nas zapomnieli na Saint Kitts! A tymczasem Hiszpanie, pragnący uczynić całą Hispaniolę czysto hiszpańską i którym francuscy osadnicy oraz bukanierzy na zachodzie wyspy są poważnym utrapieniem, szykują atak! Moi oficerowie patrolowi, nasi kapitanowie handlowi, a nawet zwykli rybacy donoszą, że w Santiago zbiera się potężna hiszpańska eskadra, która przygotowuje się do ataku na Port-au-Prince!";
			link.l1 = "Czy dowody są wystarczająco jasne, Wasza Królewska Mość?";
			link.l1.go = "patria_portpax_2";
		break;
		
		case "patria_portpax_2":
			dialog.text = "Nie mam dokładnych informacji, ale taka ilość informacji od zupełnie przypadkowych ludzi nie może być tylko plotką. Nasza kolonia jest bardzo ważna dla Francji, mamy tutaj najlepsze plantacje, które Baron może osobiście zobaczyć. Utrata tej kolonii lub nawet narażenie jej na ryzyko grabieży jest nie do przyjęcia!";
			link.l1 = "Wezmę pod uwagę twoje dowody i poinformuję Chevaliera de Poincy. Jestem pewien, że podejmie natychmiastowe kroki.";
			link.l1.go = "patria_portpax_3";
		break;
		
		case "patria_portpax_3":
			dialog.text = "Dziękuję, kapitanie...";
			link.l1 = "";
			link.l1.go = "patria_portpax_4";
		break;
		
		case "patria_portpax_4":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_9";
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "governor1");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
			npchar.quest.patria = "true";
		break;
		
		case "PZ1":
			DeleteAttribute(pchar, "questTemp.PZ.PortPaxMayorTalk");
			dialog.text = "Nie, nie wzywałem cię, monsieur. Czy chciałeś czegoś?";
			link.l1 = "How could I? But your messenger met us; he said you had prepared one of the houses in the town for me...";
			link.l1.go = "PZ2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ2":
			dialog.text = "Jaki dom, jaki posłaniec, co to za zuchwalstwo?!";
			link.l1 = "Co masz na myśli, jaki posłaniec... Nazywa się Henri Thibaut, i...";
			link.l1.go = "PZ3";
		break;
		
		case "PZ3":
			dialog.text = "CO? Czy ty w ogóle wiesz, kim on jest? Najwyraźniej nie. Ale to nie ma znaczenia. Co siostrzeniec Levasseura robi w moim mieście?";
			link.l1 = "O mój Boże...";
			link.l1.go = "PZ4";
		break;
		
		case "PZ4":
			dialog.text = "De Maure, czy mnie słyszysz? Monsieur?";
			link.l1 = "...";
			link.l1.go = "PZ5";
		break;
		
		case "PZ5":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocator(pchar, "reload", "reload1", "PZ_SharleBezhitObratno", -1);
			bDisableCharacterMenu = true;
			InterfaceStates.Buttons.Save.enable = false;
			SetMusic("music_teleport");
			pchar.questTemp.lockedMusic = true;
		break;
		
		//--> Украденное воспоминание
		case "UV_1":
			dialog.text = "Sprawa delikatna, powiadasz? Bardzo interesujące. Słucham uważnie.";
			link.l1 = "Wie pan, pańska bratanica Julie zwróciła się do mnie z prośbą o pomoc w odnalezieniu pewnego naszyjnika.";
			link.l1.go = "UV_2";
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			DelLandQuestMark(npchar);
		break;
		
		case "UV_2":
			dialog.text = "Naszyjnik? Nie przypominam sobie, żeby go posiadała.";
			link.l1 = "Zaraz wszystko wyjaśnię, panie gubernatorze, krok po kroku. Naszyjnik znalazł"+GetSexPhrase("em","am")+". Okazało się, że złodziejką jest służąca pańskiej bratanicy, Giselle. Po zachowaniu osoby, której przekazywała skradzione dobra, wnioskuję, że to nie jej pierwszy – i obawiam się, że nie ostatni – taki występek.";
			link.l1.go = "UV_3";
		break;
		
		case "UV_3":
			dialog.text = "Proszę kontynuować.";
			link.l1 = "Julie nie zwróciła się do pana po pomoc, ponieważ naszyjnik był prezentem od osoby, z którą zabronił jej pan się kontaktować. Ja natomiast, będąc przekonan"+GetSexPhrase("ym","ą")+", że pańska decyzja wynikała z jak najlepszych intencji, uznał"+GetSexPhrase("em","am")+", że moim obowiązkiem jest pana o tym poinformować i zwrócić naszyjnik.";
			link.l1.go = "UV_4";
			TakeItemFromCharacter(pchar, "SM_necklace_Julie");
		break;
		
		case "UV_4":
			dialog.text = "Postąpił"+GetSexPhrase("eś","aś")+" mądrze"+GetSexPhrase(", kapitanie","")+". Cieszy mnie, że postanowił"+GetSexPhrase("eś","aś")+" powiedzieć mi prawdę, zamiast dogadzać kaprysom Julie.";
			link.l1 = "Życzę jej jak najlepiej i jestem przekonan"+GetSexPhrase("y","a")+", że pańskie zamiary są równie szlachetne.";
			link.l1.go = "UV_5";
		break;
		
		case "UV_5":
			dialog.text = "Oczywiście, kapitanie, jako jej wuj życzę jej tylko dobra. Proszę przyjąć moją wdzięczność za pańską rozwagę. Oto sto pięćdziesiąt dublonów oraz coś jeszcze – kompas, który, mam nadzieję, okaże się przydatnym towarzyszem w pańskich podróżach.";
			link.l1 = "Dziękuję, monsieur. To naprawdę nie było konieczne. Ale teraz muszę się pożegnać – obowiązki wzywają.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("UV_End");
			AddItems(pchar, "gold_dublon", 150);
			GiveItem2Character(PChar, "compass1");
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
		break;
		//<-- Украденное воспоминание
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
