// Адольф Барбье - авантюрист
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && int(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Nie chcę z tobą rozmawiać. Atakujesz spokojnych cywilów bez powodu i prowokujesz ich do walki. Zgiń przepadnij!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Witaj, witaj... Nie widziałem cię wcześniej. Ostatnio?";
				link.l1 = "Masz na myśli ostatnio na Wyspie? Tak, masz rację. Nazywam się "+GetFullName(pchar)+", żeglarz i awanturnik.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"Chcesz czegoś?";
				link.l1 = LinkRandPhrase("Masz coś interesującego do powiedzenia?","Czy coś nowego wydarzyło się na wyspie?","Opowiesz mi najnowsze plotki?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Chcę zadać ci kilka pytań o wyspę.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Chciałem tylko zapytać, jak się masz. Do zobaczenia!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Ha, zupełnie jak ja. Nie jestem jednak żeglarzem, ale moja pasja do przygód przywiodła mnie tutaj. Teraz muszę gnić na tym cmentarzysku statków jak wszyscy inni. A tak przy okazji, nazywam się Adolf Barbier.";
			link.l1 = "Miło było cię poznać, Adolfie. Do zobaczenia.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Masz coś ciekawego do powiedzenia?","Czy coś nowego wydarzyło się na wyspie?","Czy opowiesz mi najnowsze plotki?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Chcę zadać ci kilka pytań dotyczących wyspy.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		//----------------------------------Адольф Барбье----------------------------------------
		case "Adolf":
			dialog.text = "Co do diabła robisz w moim domostwie bez mojego pozwolenia?";
			link.l1 = "Okazujesz złe maniery wobec swego gościa, Adolfie. A ja mam dla ciebie interes.";
			link.l1.go = "Adolf_1";
		break;
		
		case "Adolf_1":
			dialog.text = "Nie robię interesów z ludźmi, których nie znam! Wynoś się!";
			link.l1 = "Ot tak? Zatem robisz interesy z Narwalami, ale ze mną nie chcesz? Wstyd...";
			link.l1.go = "Adolf_2";
		break;
		
		case "Adolf_2":
			dialog.text = "O czym ty mówisz, błazenku? Co cię obchodzą Narwale? To twoja ostatnia szansa, żeby się stąd wynieść, inaczej sam cię wyrzucę!";
			link.l1 = "Nie masz jaj, by to zrobić, 'mistrzu rzucania'... Słuchaj mnie teraz. Gdzie jest stutzen, który zamierzasz użyć do zastrzelenia admirała? Powiesz mi sam, czy powinienem stać się bardziej przekonujący?";
			link.l1.go = "Adolf_3";
		break;
		
		case "Adolf_3":
			dialog.text = "Co? Co za stutzen? Jaki admirał? Czyś ty oszalał, kumplu? Sprzedałem mój stutzen i już go nie mam. I nie twoja sprawa, komu go sprzedałem. Nie obchodzi mnie, co z nim zrobią. I nie zamierzam strzelać do nikogo - ani do admirałów, ani do generałów. Rozumiesz mnie, draniu?";
			link.l1 = "Rozumiem tylko, że jesteś kłamcą i mordercą, Adolfie. Wiem, że go nie sprzedałeś, lecz odkupiłeś. Wiem też, że otrzymałeś ogromną sumę na spłatę swoich długów i zakup tej kajuty...";
			link.l1.go = "Adolf_4";
		break;
		
		case "Adolf_4":
			dialog.text = "To są moje pieniądze, draniu! Zarobiłem je! I sprzedałem mój stutzen!";
			link.l1 = "Kłamiesz, Adolfie. Zostałeś zatrudniony przez Narwali, by zastrzelić admirała. Dali ci pieniądze, by wykupić swój sztucer. Zapłacili również za to miejsce. Wiesz lepiej ode mnie, że bukszpryt za tymi drzwiami to jedyne miejsce na wyspie, z którego można strzelać do tylnego balkonu rezydencji Rekina.";
			link.l1.go = "Adolf_5";
		break;
		
		case "Adolf_5":
			dialog.text = "Jesteś szalony, łajdaku! Natychmiast trzeba cię odizolować! Czekałem na tę kajutę przez pół roku, zanim Sessile stąd odeszła...";
			link.l1 = "Dość. Przeszukam ciebie i twoją kajutę, znajdę stutzen i kilka innych dowodów, jestem tego pewien. A potem pójdziemy razem do Rekina. Będzie zadowolony, mogąc spojrzeć ci w oczy.";
			link.l1.go = "Adolf_6";
		break;
		
		case "Adolf_6":
			dialog.text = "Ach, ty chory draniu! Wolę umrzeć, niż pozwolić jakiemuś szalonemu łajdakowi dotknąć moich rzeczy!";
			link.l1 = "Wtedy dotknę ich bez twojego pozwolenia...";
			link.l1.go = "Adolf_7";
		break;
		
		case "Adolf_7":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetWarriorType(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "barmen", "stay");
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetImmortal(npchar, false);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_AdolfDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
	case "int_quests":
			dialog.text = "Cóż, porozmawiajmy. Co chcesz wiedzieć?";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Jak się tu dostałeś?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Co możesz mi powiedzieć o miejscowych klanach?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Zbadałeś zewnętrzny pierścień statków?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Czy wyspa ma jakieś powiązania z Kubą lub Kontynentem?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Bez pytań. Przepraszam...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Znalazłem rękopis jednego żeglarza - Alvarado, był Hiszpanem. Opisał Wyspę bardzo szczegółowo. Wspomniał o kilku interesujących statkach - San Augustine, San Geronimo i Tartarus. Wszystkie były częścią eskadry de Betancourta, która zaginęła ponad pięćdziesiąt lat temu\nZrobiłem badania na temat tej ekspedycji. Okazało się, że był czwarty statek o nazwie St. Anna, który przewoził skarb eskadry - stos dublonów! Poza tym, statki miały w ładowniach rudę złota. Zdecydowałem się odnaleźć Wyspę\nZawarłem umowę z kapitanem, którego znałem, i wypłynęliśmy na jego szkunerze. Jasne jest, jak ta historia się skończyła, przypuszczam. Znaleźliśmy Wyspę, statki Betancourta, nawet jego potomka - mieszka tu, nazywa się Antonio de Betancourt. Ale nie udało mi się stąd wydostać\nSzkuner został rozbity przez rafy, mój towarzysz zginął, a ja wraz z innymi ocalałymi dotarłem tutaj. Najgorsze jest to, że nie znalazłem tego, czego szukałem - ani skarbu St. Anny, ani rudy złota.";
			link.l1 = "Przeczytałem również notatki Alvarado. Intrygująca historia.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Rivados to przeklęci pogańscy łotrzy. Są potomkami murzyńskich niewolników, przywiezionych tutaj przez de Betancourt z Afryki. Choć nauczyli się używać ostrzy i muszkietów od białych ludzi, wciąż są dzikusami\nNarwale to dobrzy ludzie, mądrzy i porządni wojownicy. Mają wśród siebie wybitnych rzemieślników. Znam wielu z nich. Może pewnego dnia dołączę do ich klanu\nPiraci to wrzód na tyłku, niech ich diabli. Nie zapraszaliśmy ich, ale przybyli, przejęli nasze zapasy i ośmielili się sprzedać nam nasze własne jedzenie! Dranie, co? Szkoda, że nie możemy ich przepędzić i musimy znosić ich obecność.";
			link.l1 = "Interesujące...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Pewnie. Człowiek musi zarabiać. Cholerni piraci żądają złota, pesos lub innych wartościowych rzeczy za jedzenie. Sprzedają je dużo taniej takim mieszkańcom jak ja niż klanom, ale to nie jest żadna dobroczynność. Dzięki Bogu, jest wystarczająco dużo statków na zewnętrznym pierścieniu do złupienia, wiele z nich wciąż pozostaje nie tknętych przez nikogo od czasu ich zniszczenia\nCiekawa aktywność, lecz niebezpieczna: możesz wpaść do zalanej ładowni, połamać kości, utknąć w linach, zostać zmiażdżonym przez drewniane części lub spotkać gigantyczne kraby - często odwiedzają ładownie tam na zewnątrz.";
			link.l1 = "Widzę...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Niestety, nie. Mówią, że dawno temu bucaniery i przemytnicy z Kuby odwiedzali to miejsce - wymieniali zaopatrzenie na złoto i towary. Nawet Narwale odwiedzali osady. Ale to już historia. Nikt nie zaryzykowałby teraz żeglugi na kruche i małe łodzie. Burze niszczą małe łodzie w mgnieniu oka, a my tu lepszych statków nie mamy.";
			link.l1 = "Rozumiem...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Co tam robisz, co? Złodzieju!","Spójrz tylko na to! Ledwie pogrążyłem się w zadumie, a ty postanowiłeś sprawdzić moją skrzynię!","Postanowiłeś sprawdzić moje skrzynie? Nie ujdzie ci to na sucho!");
			link.l1 = "Cholera!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Co?! Zdecydowałeś się przeszukać moje skrzynie? Nie ujdzie ci to na sucho!";
			link.l1 = "Głupia dziewczyno!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Słuchaj, lepiej schowaj swoją broń. To mnie denerwuje.","Wiesz, bieganie z ostrzem nie jest tutaj tolerowane. Schowaj to.","Słuchaj, nie baw się w średniowiecznego rycerza biegającego z mieczem. Odłóż to, to do ciebie nie pasuje...");
			link.l1 = LinkRandPhrase("Dobrze.","Dobrze.","Jak powiadasz...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Słuchaj, jestem obywatelem miasta i proszę cię, abyś trzymał miecz na wodzy.","Słuchaj, jestem obywatelem miasta i proszę cię, byś trzymał swój miecz na wodzy.");
				link.l1 = LinkRandPhrase("Dobrze.","Dobrze.","Jak mówisz...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ostrożnie, przyjacielu, kiedy biegasz z bronią. Mogę się zdenerwować...","Nie lubię, gdy mężczyźni przechodzą przede mną z gotową bronią. To mnie przeraża...");
				link.l1 = RandPhraseSimple("Zrozumiano.","Zabieram to.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
