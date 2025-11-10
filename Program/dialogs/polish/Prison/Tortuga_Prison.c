// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Mów, słucham";
			link.l1 = "Pomyliłem się. Żegnaj.";
			link.l1.go = "Exit";
		break;
		
		case "tonzag_bail":
			NextDiag.TempNode = "First_officer";
		
			dialog.text = "Jaki jest cel twojej wizyty na Tortudze, Kapitanie?";
			link.l1 = "Błagam cię! Pomóż mojemu towarzyszowi, a odpowiem na wszystkie twoje pytania!";
			link.l1.go = "tonzag_bail_a";
			link.l2 = "Jesteś tak ważną osobą, a przyszedłeś tu bez żadnej eskorty, zaraz po tym, jak całe więzienie usłyszało strzał?!";
			link.l2.go = "tonzag_bail_b";
		break;
		
		case "tonzag_bail_a":
			dialog.text = "Podczas gdy opóźniasz swoją odpowiedź, on wykrwawia się. Powtarzam pytanie.";
			link.l1 = "";
			link.l1.go = "tonzag_bail_1";
		break;
		
		case "tonzag_bail_b":
			dialog.text = "Wiem wystarczająco o tym, co się stało. Powtarzam pytanie.";
			link.l1 = " ";
			link.l1.go = "tonzag_bail_1";
		break;
		
		case "tonzag_bail_1":
			dialog.text = "Ostatnia szansa, Kapitanie.";
			link.l1 = "Realizuję zadanie powierzone mi przez gubernatora generalnego!";
			link.l1.go = "tonzag_bail_truth";
			link.l2 = "Doskonale wiesz, że jestem kapitanem własnego statku i pracuję na umowy. Odwiedzam waszą piękną wyspę kilka razy w roku!";
			link.l2.go = "tonzag_bail_lies";
		break;
		
		case "tonzag_bail_truth":
			dialog.text = "Miałem swoje podejrzenia, ale nie byłem całkowicie pewien. Masz szczęście, że zaledwie kilka dni temu odbyło się ważne spotkanie w Capsterville. Niektórzy bardzo wpływowi ludzie zdołali osiągnąć porozumienie. Zatem, nie jesteś już moim wrogiem.";
			link.l1 = "Czy nam pomożesz?";
			link.l1.go = "tonzag_bail_truth_1";
			
			AddDialogExitQuestFunction("Tonzag_GetOut");
		break;
		
		case "tonzag_bail_truth_1":
			dialog.text = "Wypuszczę cię natychmiast. Twój towarzysz zostanie przeniesiony na statek i otrzyma opiekę.";
			link.l1 = "Dziękuję...";
			link.l1.go = "tonzag_bail_truth_2";
		break;
		
		case "tonzag_bail_truth_2":
			dialog.text = "Prawie wpłynąłeś na mieliznę, Charles! Opuść Tortugę i nie wracaj przez co najmniej miesiąc. Pozwól, by kurz opadł, a głowy się ochłodziły.";
			link.l1 = "Zrobię to. Do zobaczenia!";
			link.l1.go = "exit";
			link.l2 = "Nie wyjaśnisz niczego? Nawet trochę? ...";
			link.l2.go = "tonzag_bail_truth_3";
		break;
		
		case "tonzag_bail_truth_3":
			dialog.text = "Ktoś cię zgłosił. Rzekomo jesteś fanatycznym katolikiem, który przybył na naszą piękną wyspę, by złośliwie zabić jej honorowego gubernatora.";
			link.l1 = "Nie jestem fanatykiem!";
			link.l1.go = "tonzag_bail_truth_4";
		break;
		
		case "tonzag_bail_truth_4":
			dialog.text = "To jest napisane zręcznie, uwierz mi. Znam się na takich rzeczach - najlepsze paszkwile to te, które zawierają przynajmniej ziarno prawdy.";
			link.l1 = "Kto napisał raport?";
			link.l1.go = "tonzag_bail_truth_a";
			link.l2 = "Kto wpuścił mordercę do więzienia?";
			link.l2.go = "tonzag_bail_truth_b";
		break;
		
		case "tonzag_bail_truth_a":
			dialog.text = "Ktoś, kto chciał, abyś spędził kilka dni w więzieniu, zamiast natychmiast wysłać cię na stół tortur hugenotów w piwnicy La Roche.\nDość, Charles. Odejdź. Najpierw zajmij się tym, co masz przed sobą, a potem... cóż, rozumiesz mnie!";
			link.l1 = "Tak. Zrobię to. Do widzenia, komendancie.";
			link.l1.go = "exit";
		break;
		
		case "tonzag_bail_truth_b":
			dialog.text = "Zrobiłem to.";
			link.l1 = "Lepiej wyślij po kolejnego, zanim stąd odejdę.";
			link.l1.go = "tonzag_bail_truth_b_threat";
			link.l2 = "Zamieniam się w słuch, komendancie.";
			link.l2.go = "tonzag_bail_truth_b_charm";
		break;
		
		case "tonzag_bail_truth_b_threat":
			AddComplexSelfExpToScill(100, 100, 100, 100);
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 60) {
				dialog.text = "Nie jestem zobowiązany do wyjaśniania ci czegokolwiek, Charles. Ciesz się, że trafiłeś w moje ręce, a nie w ręce mojego bezpośredniego przełożonego. I ciesz się, że to twój szef będzie tym, który wynagrodzi mi wszystkie te zakłócenia, a nie ty.";
				link.l1 = "Riiiiiiight... Nie znasz mojego szefa tak dobrze, jak ja. Do widzenia, komendancie.";
				link.l1.go = "exit";
				
				Notification_Skill(false, 60, SKILL_LEADERSHIP);
				AddQuestRecord("Tonzag", "3.1");
			} else {
				dialog.text = "Wiesz co? Myślę, że ci powiem. Hojna, wolna od podatku darowizna została przekazana na specjalny fundusz emerytalny garnizonu. W geście wdzięczności, darczyńcy pozwolono przyczynić się do szybkiego i zgodnego z prawem wykonania wyroku na notorycznym przestępcy!";
				link.l1 = "Mój oficer?";
				link.l1.go = "tonzag_bail_truth_b_1";
				link.l2 = "Mój przyjacielu?";
				link.l2.go = "tonzag_bail_truth_b_1";
				
				Notification_Skill(true, 60, SKILL_LEADERSHIP);
			}
		break;
		
		case "tonzag_bail_truth_b_charm":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 60) {
				dialog.text = "Nie jestem zobowiązany niczego ci wyjaśniać, Charles. Ciesz się, że trafiłeś w moje ręce, a nie w ręce mojego bezpośredniego przełożonego. I ciesz się, że to twój szef będzie tym, który mi zrekompensuje wszystkie te zakłócenia, a nie ty.";
				link.l1 = "Riiiiiiight... Ty nie znasz mojego szefa tak jak ja. Do zobaczenia, komendancie.";
				link.l1.go = "exit";
				
				Notification_Skill(false, 60, SKILL_LEADERSHIP);
				AddQuestRecord("Tonzag", "3.1");
			} else {
				dialog.text = "Wiesz co? Myślę, że ci powiem. Hojna, wolna od podatku darowizna została przekazana na specjalny fundusz emerytalny garnizonu. W geście wdzięczności, darczyńca został dopuszczony do przyczynienia się do szybkiej i zgodnej z prawem egzekucji notorycznego przestępcy!";
				link.l1 = "Mój oficer?";
				link.l1.go = "tonzag_bail_truth_b_1";
				link.l2 = "Mój przyjacielu?";
				link.l2.go = "tonzag_bail_truth_b_1";
				
				Notification_Skill(true, 60, SKILL_LEADERSHIP);
			}
		break;
		
		case "tonzag_bail_truth_b_1":
			dialog.text = "Odejdź, Charles. I zabierz ze sobą tę hołotę. Twój wybór towarzyszy... jest rozczarowujący.";
			link.l1 = "Przynajmniej powiedz mi, gdzie znaleźć twojego... dobroczyńcę?";
			link.l1.go = "tonzag_bail_truth_b_2";
		break;
		
		case "tonzag_bail_truth_b_2":
			dialog.text = "Na kontynencie. Żegnaj, Charles.";
			link.l1 = "";
			link.l1.go = "exit";
			
			pchar.questTemp.TonzagQuest.KnowMain = true;
			AddQuestRecord("Tonzag", "3.2");
		break;
		
		case "tonzag_bail_lies":
			dialog.text = "Złożono na ciebie raport. Bardzo paskudny. Kapitanie, wyraźnie cię wrabiają, ale... mam pełne prawo trzymać cię tutaj przez kolejne kilka tygodni i zostawić twojego przyjaciela na pastwę losu. Chyba że...";
			link.l1 = "Ile to kosztuje?";
			link.l1.go = "tonzag_bail_lies_a";
			link.l2 = " Kto mnie wrobił? Czy wpuściłeś zabójcę do więzienia?";
			link.l2.go = "tonzag_bail_lies_b";
			
			AddDialogExitQuestFunction("Tonzag_Bailed");
		break;
		
		case "tonzag_bail_lies_a":
			pchar.questTemp.TonzagQuest.Bail = 500;
			dialog.text = "Proszę wpłacić pięćset doblonów na fundusz emerytalny garnizonu Tortuga u lokalnego pożyczkodawcy.";
			if (CheckAttribute(pchar, "questTemp.FMQT") && pchar.questTemp.FMQT == "end") {
				pchar.questTemp.TonzagQuest.Bail = 600;
				dialog.text = dialog.text+" A dodajmy jeszcze sto dublonów za stare kłopoty, które wywołałeś, mieszając się z jedną wysoko postawioną damą na tej wyspie.";
			}
			link.l1 = "Otwórz te przeklęte drzwi już!";
			link.l1.go = "exit";
			
			AddQuestRecord("Tonzag", "3.3");
		break;
		
		case "tonzag_bail_lies_b":
			pchar.questTemp.TonzagQuest.Bail = 500;
			dialog.text = "Już zabrałeś zbyt dużo mojego czasu. Idź do pożyczkodawcy i wpłać pięćset dublonów do funduszu emerytalnego garnizonu w Tortudze.";
			if (CheckAttribute(pchar, "questTemp.FMQT") && pchar.questTemp.FMQT == "end") {
				pchar.questTemp.TonzagQuest.Bail = 600;
				dialog.text = dialog.text+" A dodajmy jeszcze sto dubloonów za dawne kłopoty, które narobiłeś, wplątując się w sprawy jednej wysoko postawionej damy na tej wyspie.";
			}
			link.l1 = "Otwórz te przeklęte drzwi już!";
			link.l1.go = "exit";
			
			AddQuestRecord("Tonzag", "3.3");
		break;
		
		case "tonzag_bailed":
			dialog.text = "";
			link.l1 = "Fundusze zostały zdeponowane. Gdzie jest Hercule?";
			link.l1.go = "tonzag_bailed_1";
		break;
		
		case "tonzag_bailed_1":
			dialog.text = "Udzieliliśmy mu pierwszej pomocy i wysłaliśmy na twój statek. Drań jest twardy, najprawdopodobniej da sobie radę. Żegnaj, Kapitanie, i nie daj mi się złapać na naszej wyspie przez jakiś czas!";
			link.l1 = "Cóż, po takim przyjęciu będę się trzymać z daleka od tego miejsca! Żegnaj, komendancie.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "First time";
			AddDialogExitQuestFunction("Tonzag_GetOut");
		break;
		
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
