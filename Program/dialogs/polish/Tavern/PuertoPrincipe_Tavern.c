// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie masz pytania?","Jak mogę ci pomóc, "+GetAddress_Form(NPChar)+"?"),"Próbowałeś zadać mi jakieś pytanie niedawno, "+GetAddress_Form(NPChar)+"...","Przez cały ten dzień, to już trzeci raz, kiedy mówisz o jakimś pytaniu...","Więcej pytań, jak mniemam?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniłem zdanie...","Nie mam w tej chwili nic do omówienia."),"Umph, gdzie podziała się moja pamięć...","Tak, to naprawdę trzeci raz...","Nie, jakie pytania?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Старые счёты
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_1"))
			{
				link.l1 = "Słyszałem, że ktoś pozbawił was waszego cennego ginu. To prawda?";
				link.l1.go = "OS_Tavern1_1";
			}
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_3"))
			{
				link.l1 = "Dobre wieści, "+npchar.name+"! Znalazł"+GetSexPhrase("em","am")+" waszą beczkę!";
				link.l1.go = "OS_Tavern3_1";
			}
			//<-- Старые счёты
		break;
		
		//--> Старые счёты
		case "OS_Tavern1_1":
			dialog.text = "Niestety to prawda. Co jeszcze słyszeliście? Wiecie coś więcej? Błagam, powiedzcie mi, że wiecie, gdzie ją znaleźć. Jeśli jej nie odzyskam... będę musiał opuścić miasto. Sam, albo wyniosą mnie w trumnie.";
			link.l1 = "Hm... Rzeczywiście, nie najlepiej się u was dzieje, przyjacielu. Nie, o waszym nieszczęściu tylko coś tam usłyszał"+GetSexPhrase("em","am")+". Jak to możliwe, że nie dopilnowaliście tak cennego towaru?";
			link.l1.go = "OS_Tavern1_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OS_Tavern1_2":
			dialog.text = "Eh... Co tu mówić... Ukradli mi ją sprzed nosa! Rano beczka na pewno była na miejscu. Przywieźli ją przedwczoraj, a ja – by spać spokojnie – zabrałem ją na noc do domu. Rano znów postawiłem ją pod ladą. A wieczorem – jakby ją wiatr porwał! Nikt nic nie widział, nikt nic nie słyszał.";
			link.l1 = "No proszę...";
			link.l1.go = "OS_Tavern1_3";
		break;
		
		case "OS_Tavern1_3":
			dialog.text = "Gdybym tylko miał jakikolwiek trop, już dawno bym ruszył jej szukać. Ale niestety – nic. Jakby ta beczka była zbyt cenna dla tego świata i sama wzniosła się do nieba. Dam sto pięćdziesiąt dublonów każdemu, kto mi ją zwróci. Ba, nawet zamieszczę jego imię na tabliczce w tawernie, by każdy znał jego czyn!";
			link.l1 = "Postaram się wam pomóc. A co do tabliczki – jeszcze porozmawiamy. Powiedzcie lepiej, kto wiedział o beczce? I kto, poza wami, mógł być za ladą?";
			link.l1.go = "OS_Tavern1_4";
			link.l2 = "Sto pięćdziesiąt dublonów za beczkę? Ciekawe. Ale to nie mój problem. Radźcie sobie sami.";
			link.l2.go = "OS_Tavern1_end";
		break;
		
		case "OS_Tavern1_end":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.OS_Tavern_1");
			CloseQuestHeader("OS");
			
			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.lifeday = 0;
				}
			}
			sld = CharacterFromID("OS_Pirate");
			sld.lifeday = 0;
		break;
		
		case "OS_Tavern1_4":
			dialog.text = "Właściwie nikt! No, może moja kelnerka – ale to niemożliwe. Tego dnia w tawernie był istny bal – załoga 'Sea Wolf' wróciła z łowów z niezłym łupem. Nie miała nawet chwili, by usiąść, nie mówiąc już o kręceniu się za ladą.";
			link.l1 = "Jesteś tego pewien?";
			link.l1.go = "OS_Tavern1_5";
		break;
		
		case "OS_Tavern1_5":
			dialog.text = "Zupełnie! Praca bez chwili wytchnienia nie przypadła jej do gustu i wieczorem była już wyraźnie spięta. Jeden z marynarzy zaczął się do niej przystawiać – podniosła taki wrzask, że wszystkim zatkało uszy. Musiałem sam wyjść zza lady, by uspokoić sytuację. Choć zazwyczaj reaguje znacznie spokojniej.";
			link.l1 = "I to wszystko? Nic więcej ciekawego się nie wydarzyło?";
			link.l1.go = "OS_Tavern1_6";
		break;
		
		case "OS_Tavern1_6":
			dialog.text = "Gdy jeszcze zajmowałem się pierwszym zamieszaniem, w rogu tawerny wybuchła bójka – dwóch marynarzy rzuciło się sobie do gardeł. Na szczęście nie trwało to długo – wyglądało na to, że są z jednej załogi i szybko ich rozdzielono. Potem zrobiło się naprawdę spokojnie – nic godnego uwagi więcej się nie wydarzyło.";
			link.l1 = "No cóż, jestem gotow"+GetSexPhrase("y","a")+" rozpocząć poszukiwania. Czekajcie. Myślę, że niedługo beczka znowu znajdzie się pod waszym – ekhm – czujnym okiem.";
			link.l1.go = "OS_Tavern1_7";
		break;
		
		case "OS_Tavern1_7":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.OS_Tavern_1");
			AddQuestRecord("OS", "2");
			
			sld = GetCharacter(NPC_GenerateCharacter("OS_Matros_1", "citiz_31", "man", "man", sti(pchar.rank), PIRATE, -1, true, "pirate"));
			sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
			sld.dialog.currentnode = "OS_Matros";
			LAi_SetImmortal(sld, true);
			sld.City = "PuertoPrincipe";
			ChangeCharacterAddressGroup(sld, "PuertoPrincipe_town", "goto", "goto14");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "OS_Tavern3_1":
			dialog.text = "Znalazł"+GetSexPhrase("eś","aś")+" ją?! Czy to może być prawda? Kapitanie, dosłownie uratował"+GetSexPhrase("eś","aś")+" mi życie! Kto za tym stoi? Muszę poznać nazwisko tego łajdaka!";
			link.l1 = "To był skrupulatnie zaplanowany spisek niejakiego Jacka Veilsa, działającego wspólnie z kapitanem 'Sea Wolf'. Zaangażowali swoich marynarzy i zainscenizowali wymyślną dywersję, by cię odciągnąć. Kiedy opuściłeś swoje stanowisko, beczka pozostała bez ochrony, a oni łatwo ją zabrali.";
			link.l1.go = "OS_Tavern3_2";
			DelLandQuestMark(npchar);
			pchar.questTemp.CameraDialogMode = true;
		break;

		case "OS_Tavern3_2":
			dialog.text = "Na niebiosa! Jack Veils! Więc powrócił... I wygląda na to, że próbował odzyskać karczmę takimi podstępnymi metodami. Ten lis nigdy nie przyznaje się do porażki!";
			link.l1 = "Więc był kiedyś właścicielem tej karczmy? Zapewniam cię, nie będzie już więcej knuł. Wysłał"+GetSexPhrase("em","am")+" go na spotkanie ze stwórcą.";
			link.l1.go = "OS_Tavern3_3";
		break;

		case "OS_Tavern3_3":
			dialog.text = "Kapitanie! To niezwykłe! Ty... uwolnił"+GetSexPhrase("eś","aś")+" mnie od ciągłego strachu, który kładł się cieniem na moich dniach! Zawsze wiedziałem, że prędzej czy później wróci... Kilka lat temu rywalizowaliśmy o własność tej karczmy, i udało mu się mnie pokonać\nAle radość ze zwycięstwa okazała się jego zgubą - w nadmiarze świętowania nieświadomie przegrał to miejsce na moją rzecz w karty. Oczywiście, następnego ranka przybiegł, błagając o odzyskanie karczmy, obiecując wszystko\nAle nie jestem kompletnym głupcem, by zgodzić się na takie warunki. Potem zniknął... Wiedziałem, że nie zostawi tej sprawy. Czułem, że pewnego dnia wróci. I teraz, ten dzień nadszedł.";
			link.l1 = "Trzeba mu przyznać - zrealizował swój plan sprytnie.";
			link.l1.go = "OS_Tavern3_4";
		break;

		case "OS_Tavern3_4":
			dialog.text = "Moment! Skąd w ogóle dowiedział się o beczce? Wydaje się... wydaje się, że zaczynam rozumieć! Kelnerka! Dlatego uciekła stąd jak oparzona, nawet się nie żegnając. Musiała się dowiedzieć, że rozprawił"+GetSexPhrase("eś","aś")+" się z Jackiem. Teraz wszystko układa się w całość. Kapitanie, jestem wobec ciebie niezmiernie zadłużony, ty...";
			link.l1 = "...";
			link.l1.go = "OS_Tavern3_5";
		break;
		
		case "OS_Tavern3_5":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.OS_Tavern_3");
			ChangeShowIntarface();
			
			sld = GetCharacter(NPC_GenerateCharacter("OS_Zaharia", "Marlow", "man", "man", sti(pchar.rank), PIRATE, 0, true, "pirate"));
			sld.name = GetCharacterName("Zachary");
			sld.lastname = GetCharacterName("Marlow");
			ChangeCharacterAddressGroup(sld, "PuertoPrincipe_tavern", "reload", "reload1");
			TeleportCharacterToPosAy(sld, -1.30, 0.00, -0.67, 1.50);
			sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
			sld.dialog.currentnode = "Zaharia_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		
		//<-- Старые счёты
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
