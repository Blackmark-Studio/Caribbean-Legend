// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Czego chcesz? Pytaj śmiało.","Słucham cię, o co chodzi?"),"To już drugi raz, kiedy próbujesz zapytać...","To już trzeci raz, kiedy próbujesz zapytać...","Kiedy to się skończy?! Jestem zajętym człowiekiem, zajmuję się sprawami kolonii, a ty wciąż mi przeszkadzasz!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniam zdanie...","Nie teraz. Złe miejsce i czas."),"Prawda... Ale później, nie teraz...","Zapytam... Ale trochę później...","Przykro mi, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";
			//Jason, Португалец
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "ToGovernor")
			{
				link.l1 = "Wasza Łaskawość, mam absolutnie doskonałe i pilne wieści dla Was! Pojmałem Bartolomeo Portugalczyka, skurczybyk jest pod strażą i czeka na sprawiedliwy proces! A ja liczę na jakąś skromną wdzięczność ze strony Kompanii...";
				link.l1.go = "Portugal";
			}
			//Португалец
			
			// Addon-2016 Jason ФМК-Сент-Кристофер
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "governor")
			{
				link.l1 = "Obstawałeś przy spotkaniu ze mną, Panie gubernatorze...";
				link.l1.go = "FMQN";
			}
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "hol_battle_complete")
			{
				link.l1 = "Jestem tutaj w sprawie angielskich szpiegów, panie gubernatorze...";
				link.l1.go = "FMQN_7";
			}
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("Już wszystko zabrałeś. Czego jeszcze chcesz?","Czy zostało coś, czego nie zagrabiłeś?");
            link.l1 = RandPhraseSimple("Po prostu się rozglądam...","Tylko sprawdzam, mogę zapomnieć coś zabrać...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		//Jason, Португалец
		case "Portugal":
			dialog.text = "Bartolomeo... Bart Portugalczyk jest w moim mieście?! Żywy?!!";
			link.l1 = "Jest, Wasza Łaskawość, i znajduje się pod niezawodną strażą. Przekażę go Wam po otrzymaniu weksla za głowę Barta, co obiecała Kompania. Złote dublony też byłyby dobre...";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "Bill, дублоны? Oszalałeś?! Co cię napadło, by przyprowadzić tego potwora do mojego miasta?! Jeśli on tu jest, to jego fregata nie jest daleko od wyspy, a jej załoga może być już w samym mieście, właśnie teraz!";
			link.l1 = "Zabiłem tych, którzy z nim byli, nie wiem o innych, ale to chyba nie ma większego znaczenia, bo Bartolomeo jest...";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			dialog.text = "Tak jest! Naprawdę nie rozumiesz, co zrobiłeś?! 'Albatros' jest blisko wyspy, a ty pojmałeś pirata, którego brutalność przeraża nawet jego własnych krwiożerczych ludzi! Wynoś się stąd! Wynoś się z wyspy! I zabierz tego potwora ze sobą!";
			link.l1 = "Ale posłuchaj, co z obiecaną nagrodą i...";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			dialog.text = "Nie chcę oglądać, jak moje miasto płonie z powodu twojej chciwości i mściwości Kompanii! W mojej fortecy są tylko świeże rekruty, a połowa z nich ucieknie, gdy tylko dowiedzą się, kto i dlaczego atakuje ich raweliny! A potem zacznie się rzeź... Nie zamierzam ryzykować, słyszysz mnie?! Wynoś się i dostarcz go na Curaçao sam, jeśli Kompania tak bardzo chce jego głowy!\nZrób to natychmiast, zanim będzie za późno! A możesz z nim zrobić, co tylko zechcesz, nawet wyrzucić go z pokładu swojego statku, byle nie w moim mieście!\nHans! Hans, gdzie jesteś, ty leniwy idioto! Przynieś mi napar z waleriany czy coś, i na miłość boską, niech ktoś wyrzuci tego awanturnika z mojej rezydencji!";
			link.l1 = "Ale Wasza Łaskawość...";
			link.l1.go = "Portugal_4";
		break;
		
		case "Portugal_4":
			DialogExit();
			DoQuestReloadToLocation("Marigo_town", "reload", "reload3_back", "PortugalOutResidence");
		break;
		
		// Addon-2016 Jason ФМК-Сент-Кристофер
		case "FMQN":
			DelLandQuestMark(npchar);
			dialog.text = "Bardzo dobrze! Powiedz mi kapitanie, czy spotkałeś jakieś angielskie okręty wojskowe lub handlowe podczas zbliżania się do naszej wyspy?";
			link.l1 = "Nie, panie. Nie widziałem ani wojennych, ani handlowych statków pod angielską banderą na waszych wodach.";
			link.l1.go = "FMQN_1";
		break;
		
		case "FMQN_1":
			dialog.text = "Rozumiem. Jak długo zamierzasz tu zostać?";
			link.l1 = "Trzy dni lub około tego...";
			link.l1.go = "FMQN_2";
		break;
		
		case "FMQN_2":
			dialog.text = "W takim razie mam dla ciebie propozycję. Według naszych informacji, istnieje ryzyko obecności angielskich szpiegów. Dam dziesięć tysięcy peso za wszelkie informacje dotyczące podejrzanych statków i ludzi na wyspie, w mieście, jego okolicach, na brzegach itp. Nagroda zostanie znacznie zwiększona w przypadku pomocy władzom w zatrzymaniu lub eliminacji wroga.\nKażdy cywilny kapitan jest mile widziany, aby wziąć udział w śledztwie i przeszukać lokalne wybrzeża i dżunglę w poszukiwaniu szpiegów.\nMożliwe, że natkniesz się na naszą wojenną korwetę, Zeepard, nie obawiaj się, jest na patrolu. Masz pełne prawo zwrócić się do jej kapitana, jeśli znajdziesz Brytyjczyków.";
			link.l1 = "Niestety, Wasza Ekscelencjo, lecz jestem tu jedynie z pokojowymi zamiarami handlowymi. Będę musiał opuścić tę wyspę, jak tylko uzupełnię zapasy i zakończę swoje interesy tutaj.";
			link.l1.go = "FMQN_3";
			link.l2 = "Kusząca oferta! Myślę, że wezmę udział i napadnę na wody i brzegi twojej wyspy. Może nawet zostanę tu na jakiś czas.";
			link.l2.go = "FMQN_5";
		break;
		
		case "FMQN_3":
			dialog.text = "To tylko informacja za nic, kapitanie. Bez nacisku. Wiesz, do kogo się zwrócić, jeśli zauważysz coś podejrzanego.";
			link.l1 = "Dobrze, Mynheer, zrozumiałem. Żegnaj!";
			link.l1.go = "FMQN_4";
		break;
		
		case "FMQN_4":
			DialogExit();
			pchar.questTemp.FMQN = "way_eng_1";
			AddQuestRecord("FMQ_Nevis", "8");
			chrDisableReloadToLocation = false;
			FMQN_SetSoldiersInCave();
		break;
		
		case "FMQN_5":
			dialog.text = "Wspaniale, kapitanie! Skoro jesteś tak poważny, koniecznie porozmawiaj również z naszym komendantem. On jest odpowiedzialny za łapanie szpiegów i może dostarczyć ci dodatkowych informacji.";
			link.l1 = "Dobrze, Mijnheer. Pójdę go zobaczyć.";
			link.l1.go = "FMQN_6";
		break;
		
		case "FMQN_6":
			DialogExit();
			pchar.questTemp.FMQN = "way_div";
			AddQuestRecord("FMQ_Nevis", "9");
			chrDisableReloadToLocation = false;
			AddLandQuestMarkToPhantom("marigo_prison", "marigoJailOff");
		break;
		
		case "FMQN_7":
			DelLandQuestMark(npchar);
			dialog.text = "Czekaliśmy na ciebie, Mynheer "+GetFullName(pchar)+"Proszę przyjąć nasze wyrazy wdzięczności za działania w eliminowaniu niebezpiecznego angielskiego oddziału rajdowego. Przyjmij te dziesięć tysięcy pesos. Ponadto: 200 jedwabnych płacht zostanie załadowanych do ładowni twojego statku oraz bardzo specjalna nagroda - trzyletnia licencja Holenderskiej Kompanii Zachodnioindyjskiej. To niezwykle cenny dokument, mam nadzieję, że zdajesz sobie z tego sprawę?";
			link.l1 = "Oczywiście! Trzyletnia licencja - to z pewnością coś dużego.";
			link.l1.go = "FMQN_8";
		break;
		
		case "FMQN_8":
			dialog.text = "Proszę, przyjmij swoją nagrodę. Poza tym możesz liczyć na wdzięczność wszystkich obywateli i władz Holandii. Jesteś sensacją w Philipsburgu, chętnie zobaczymy cię ponownie.";
			link.l1 = "Słyszenie takich ciepłych słów jest bardziej wartościowe niż licencja. Dziękuję, to była przyjemność. A teraz muszę już wyruszyć. Do widzenia!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_HollandBattleComplete");
		break;
		
		// Jason НСО
		case "tomas":
			dialog.text = "Poddajemy się! Na miłość boską, błagam cię, nie plądruj i nie morduj Philipsburga i jego obywateli! Jestem gotów wysłuchać twoich żądań!";
			link.l1 = "Nie martw się o obywateli, Mynheer. Poddani francuskiej korony nie powinni obawiać się francuskich żołnierzy.";
			link.l1.go = "tomas_1";
		break;
		
		case "tomas_1":
			dialog.text = "Korona francuska?";
			link.l1 = "Oczywiście. Ta wyspa należy do Francji, a wy jesteście tutaj tylko najemcami. Bezczelni najemcy, którzy uwierzyli, że ta wyspa może być ich własnością. Od dzisiaj holenderska władza na Saint Maarten dobiegła końca. Czy to jasne?";
			link.l1.go = "tomas_2";
		break;
		
		case "tomas_2":
			dialog.text = "Ale... Ale co się z nami stanie, z holenderskimi żołnierzami, którzy ci się poddali, i rannymi? A co...";
			link.l1 = "To będzie zależało tylko od ciebie, Mynheer Thomas. Jeśli wyświadczysz mi przysługę, pozwolę wszystkim, którzy się poddali, zabrać rannych i odpłynąć stąd na statku lub statkach, które znajdziemy w dokach, do Curaçao, do Mynheer Stuyvesanta.";
			link.l1.go = "tomas_2_1";
		break;
		
		case "tomas_2_1":
			dialog.text = " ";
			link.l1 = "Jeśli nie, to zostaniesz trzymany w ładowniach moich statków i kazamatach Saint Kitts. Ponadto, kilku ważnych holenderskich urzędników będzie musiało zostać powieszonych, aby upewnić się, że Stuyvesant straci zainteresowanie podbojem naszych kolonii...";
			link.l1.go = "tomas_3";
		break;
		
		case "tomas_3":
			dialog.text = "(jąkanie) Co... Co... z ja...kimś ro...dza...jem p-przysł...ugi?";
			link.l1 = "W głębinach wyspy leży kość niezgody - kopalnia soli. Wiem, że są tam nie tylko górnicy i niewolnicy, ale i holenderscy żołnierze, uzbrojeni po zęby. Muszą być z Kompanii Strażników, prawda, Mynheer? Zaproponuję im poddanie się, albo użyję siły w razie ich odmowy. Potrzebuję przewodnika, który pokaże mi drogę do kopalni. Znajdź mi takiego przewodnika.";
			link.l1.go = "tomas_4";
		break;
		
		case "tomas_4":
			dialog.text = "S-Sól....k-kopalnia?";
			link.l1 = "Dokładnie. Nie bój się, Mynheer Thomas, jeśli strażnicy kopalni będą na tyle mądrzy, by złożyć broń, dam im możliwość opuszczenia wyspy. Nie potrzebuję niepotrzebnego rozlewu krwi. Nie martw się, twoje sumienie będzie czyste: nawet jeśli nie powiesz mi, gdzie jest kopalnia, wyspa Saint Maarten jest na tyle mała, że mogę znaleźć kopalnię bez twojej pomocy, po prostu nie chcę tracić czasu, włócząc się po zaroślach i bagnach. Tak więc ta umowa jest dla ciebie bardziej korzystna niż dla mnie.";
			link.l1.go = "tomas_5";
		break;
		
		case "tomas_5":
			dialog.text = "Do-dobrze, powiem ci, jak dotrzeć do kopalni, a-ale musisz da-dać mi słowo, że wszyscy... wszyscy opuścimy tę wyspę!";
			link.l1 = "Daję ci moje słowo jako oficer i szlachcic.";
			link.l1.go = "tomas_6";
		break;
		
		case "tomas_6":
			dialog.text = "W zatoce Grand Case... na jej krańcu, blisko wody, są... są kamienie. Tam... tam, za nimi, wzdłuż linii brzegowej, jest przejście wzdłuż wody, tam... jest płytko, do pasa lub mniej. Musisz obejść skałę i dotrzesz do dużej plaży, gdzie... gdzie nie możesz przybić statku z powodu raf wokół niej. Z tej plaży prowadzi ścieżka bezpośrednio... do... do kopalni.";
			link.l1 = "Doskonale. Wyruszam. A ty, panie, pozostaniesz tutaj pod czujnym okiem moich żołnierzy, dopóki nie wrócę.";
			link.l1.go = "tomas_7";
		break;
		
		case "tomas_7":
			DialogExit();
			SetReturn_Gover_Dialog_Exit(NPChar);
			LAi_SetActorType(npchar);
			pchar.quest.Patria_BastionGate.win_condition.l1 = "location";
			pchar.quest.Patria_BastionGate.win_condition.l1.location = "Shore40";
			pchar.quest.Patria_BastionGate.function = "Patria_BastionShore";
			AfterTownBattle();
			AddQuestRecord("Patria", "50_1");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
