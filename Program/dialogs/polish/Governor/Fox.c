// полковник Фокс - бравый командир морской пехоты 'морские лисы'.
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
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Terrapin_KathyReward"))
			{
				dialog.text = " Czego chcesz, panie?  Och... mój... poczekaj!  Jesteś tym francuskim kapitanem, który uratował moją córkę z brudnych rąk sług Levasseura! ";
				link.l1 = "Widzę, że Catherine już ci o mnie opowiedziała...";
				link.l1.go = "terrapin";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Usurer") && !CheckAttribute(npchar, "quest.utensil"))
			{
				dialog.text = "Czego chcesz, panie?";
				link.l1 = "Dzień dobry, pułkowniku. Przyszedłem do pana w sprawie pewnego 'niezwykłego' interesu. Czy mógłbyś poświęcić mi trochę czasu?";
				link.l1.go = "guardoftruth";
				break;
			}
			// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
			if (CheckAttribute(pchar, "questTemp.FMQN") && pchar.questTemp.FMQN == "eng_reward")
			{
				dialog.text = "Z tego co rozumiem, jesteś francuskim kapitanem, który wspomógł moich ludzi w ich misji na Sint-Maarten? "+TimeGreeting()+"!";
				link.l1 = TimeGreeting()+", Pułkowniku. Tak, to ja.";
				link.l1.go = "FMQN";
				break;
			}
			dialog.text = "Czego chcesz, sir?";
			link.l1 = "Niczego, pułkowniku. Zatem się oddalam.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "guardoftruth":
			dialog.text = "Wypluj to już, skoro zaszedłeś tak daleko...";
			link.l1 = "Niedawno przejąłeś szkuner pod dowództwem Rolliego Kapra, holenderskiego pirata, i przyprowadziłeś kapitana tutaj, do St. John's.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Kapitan? Och, nie rozśmieszaj mnie! Ta kryminalna hołota nie ma prawa być nazywana tym zaszczytnym tytułem. Złapałem tego przeklętego pirata, głowę stada wilków, który rabował i mordował angielskich handlowców i kupców. I upewniłem się, że on i jego degeneraci dostali to, na co zasłużyli - całe St. John's oglądało ich powieszenie na molo!";
			link.l1 = "Chyba nie będę mógł przesłuchać tego łotra... Pułkowniku, może mógłbyś mi pomóc? Pirat miał przy sobie coś, co do niego nie należało - złoty trybularz. Czy znalazłeś przy nim coś, co wygląda jak to?";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Nie, przeszukaliśmy go i ten łotr nie miał żadnych rzeczy, poza tym, wszystkie z nich na pewno zostały zabrane uczciwym handlarzom! A co do twojej troski... hmm nie, nie znaleźliśmy tego. I co kadzielnica mogłaby robić na pirackim statku? Naprawdę myślisz, że był wśród nich ksiądz?";
			link.l1 = "Nie, nie sądze. Rollie Kapitan kupił go od lichwiarza w Willemstad, który kupił go od innego pirata. Kadzielnica jest piękna i droga, a ja próbuję zwrócić ją jej prawowitym właścicielom. Przypuszczam, że Rollie patrzył na nią jak sroka.";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "W rzeczywistości Rollie miał puste ładownie i kilka skrzyń z dublonami, gdy abordażowaliśmy i przejęliśmy jego statek. Nic poza śmieciami. Żadnych kosztowności, żadnego złotego trybularza. Zapamiętałbym taki nieodpowiedni przedmiot dla pirata.\nPodejrzewam, że ten cholerny pirat ukrył swoje oszczędności na Dominice. Nawet tam wylądowaliśmy i przeszukaliśmy teren, ale nic nie znaleźliśmy. Ale nie zostaliśmy na wyspie ani nie zbadaliśmy jej głębi z powodu dużej liczby tamtejszych dzikusów.";
			link.l1 = "Hm... Pirat mógł ukryć kadzielnicę wraz z resztą swoich skradzionych rzeczy gdzieś na Dominice... Szkoda. Czy przesłuchałeś pirata przed egzekucją?";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "Zrobiłem to... a on po prostu zaczął się śmiać mi w twarz. Ale nie obchodziły mnie jego skrytki. Rollie Kapitan został powieszony i to jest najważniejsze.";
			link.l1 = "Rozumiem. Dziękuję za twoją opowieść i twój czas, pułkowniku. Żegnaj...";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			DialogExit();
			npchar.quest.utensil = "true";
			AddQuestRecord("Guardoftruth", "24");
			Island_SetReloadEnableGlobal("Dominica", true);//patch-7
			// заполняем сундук
			pchar.GenQuestBox.Shore27 = true;
			pchar.GenQuestBox.Shore27.box1.money = 30000;
			pchar.GenQuestBox.Shore27.box1.items.gold_dublon = 100;
			pchar.GenQuestBox.Shore27.box1.items.chest = 1;
			pchar.GenQuestBox.Shore27.box1.items.icollection = 1;
			pchar.GenQuestBox.Shore27.box1.items.jewelry40 = 15;
			pchar.GenQuestBox.Shore27.box1.items.jewelry41 = 22;
			pchar.GenQuestBox.Shore27.box1.items.jewelry42 = 8;
			pchar.GenQuestBox.Shore27.box1.items.jewelry43 = 20;
			pchar.GenQuestBox.Shore27.box1.items.jewelry44 = 33;
			pchar.GenQuestBox.Shore27.box1.items.jewelry45 = 16;
			pchar.GenQuestBox.Shore27.box1.items.jewelry46 = 58;
			pchar.GenQuestBox.Shore27.box1.items.jewelry35 = 1; // кадило
			pchar.quest.GuardOT_finddominicachest.win_condition.l1 = "item";
			pchar.quest.GuardOT_finddominicachest.win_condition.l1.item = "jewelry35";
			pchar.quest.GuardOT_finddominicachest.function = "GuardOT_DominicaChest";
		break;
		
		case "terrapin":
			dialog.text = "Kilka razy, kapitanie! Twój honorowy i odważny czyn był trudny do przewidzenia po Francuzie. Jestem ci wdzięczny jako żołnierz i jako ojciec. Nie ma nic bardziej cennego dla mnie na tym świecie niż moja córka...";
			link.l1 = "Cieszę się, że mogłem pomóc i mam nadzieję, że z czasem moje działania zmienią twoje zdanie o Francuzach.";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = "Obecność tak honorowego i hojnego dżentelmena jak Waszmość, który zaryzykował życie dla nieznajomej angielskiej dziewczyny, spowoduje istotne ocieplenie moich relacji z Waszymi rodakami!";
			link.l1 = "Są uczciwi ludzie wśród szczurów w każdym narodzie, pułkowniku...";
			link.l1.go = "terrapin_2";
		break;
		
		case "terrapin_2":
			dialog.text = "I dowiodłeś tego! Nagroda czeka na ciebie, kapitanie. Oczywiście, życie córki jest bezcenne, ale Jonathan Fox zawsze spłaca swoje długi, przysięgam! Jesteś prawdziwym żołnierzem, dlatego mój dar dla ciebie jest darem żołnierza. Spójrz tutaj.\nTo jest garłacz, doskonały muszkiet marynarski, można go używać jedną ręką. Możesz załadować go specjalnymi strzałami, które zawsze przebiją nawet najtrwalszy kirys. Strzela również kartaczami, a jego solidna konstrukcja pozwala załadować go ładunkami gwoździ. Weź, to teraz twoje.";
			link.l1 = "Tak wspaniały dar dla żołnierza, dziękuję ci, pułkowniku!";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			Log_Info("Otrzymałeś garłacz");
			Log_Info("Otrzymałeś 10 strzałek");
			Log_Info("Otrzymałeś 10 ładunków gwoździowych");
			Log_Info("Otrzymałeś instrukcje dotyczące tworzenia strzał harpunowych");
			Log_Info("Otrzymałeś instrukcje dotyczące tworzenia ładunku gwoździ");
			GiveItem2Character(pchar, "pistol8");
			TakeNItems(pchar, "harpoon", 10);
			TakeNItems(pchar, "GunEchin", 10);
			GiveItem2Character(pchar, "recipe_harpoon"); 
			GiveItem2Character(pchar, "recipe_GunEchin"); 
			PlaySound("interface\important_item.wav");
			dialog.text = "Przekazuję również niewielką partię amunicji oraz instrukcje ich wytwarzania. Byłoby szkoda, gdybyś nie wykorzystał ich mocy na maksa!";
			link.l1 = "Dziękuję, pułkowniku. Nie odrzucę takiego daru, ale chcę, byś wiedział, że nie uratowałem Catherine dla nagrody. Po prostu nie mógłbym pozwolić, by bezbronna dziewczyna doznała krzywdy.";
			link.l1.go = "terrapin_4";
		break;
		
		case "terrapin_4":
			dialog.text = "Wiem o tym, kapitanie. To podwójnie cię zaszczyca. Catherine była naprawdę zachwycona tobą, a nie jest łatwo zrobić na niej pozytywne wrażenie. Jeszcze raz, jesteśmy ci wdzięczni za jej uratowanie. Jestem ci dłużny!";
			link.l1 = "Cóż, dziękuję za prezent, pułkowniku. Przekaż Catherine moje pozdrowienia i życzę, by następnym razem posłuchała ojca.";
			link.l1.go = "terrapin_5";
		break;
		
		case "terrapin_5":
			dialog.text = "Oczywiście, Kapitanie! Żegnaj, i bezpiecznej podróży!";
			link.l1 = "Żegnaj, pułkowniku.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Terrapin_KathyReward");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 5);
			ChangeCharacterNationReputation(pchar, ENGLAND, 20);
		break;
		
		// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
		case "FMQN":
			DelLandQuestMark(npchar);
			dialog.text = "Przeczytałem raport. Twoje działania są wysoko oceniane, dlatego musisz zostać nagrodzony. Trzydzieści tysięcy pesos za usługi ekspedycyjne i broń za bohaterstwo w żołnierstwie. Przyjmij ten miecz i ten arkebuz. Teraz są twoje!";
			link.l1 = "Dziękuję, sir.";
			link.l1.go = "FMQN_1";
		break;
		
		case "FMQN_1":
			dialog.text = "Jak najbardziej, Kapitanie. Zyskujesz również miłość i szacunek brytyjskich kolonii, władz oraz mój osobisty. Dziękuję za to, że nie opuściłeś moich ludzi i pomogłeś im w ich misji!";
			link.l1 = "Z przyjemnością, pułkowniku...";
			link.l1.go = "FMQN_2";
		break;
		
		case "FMQN_2":
			dialog.text = "Teraz, proszę mnie wybaczyć - mam inne sprawy do załatwienia. Szczęśliwej drogi, Kapitanie.";
			link.l1 = "Żegnaj, Panie.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_EnglandComplete");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
