// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Pytania, "+GetAddress_Form(NPChar)+"?","Jak mogę ci pomóc, "+GetAddress_Form(NPChar)+"?"),""+GetSexPhrase("Hm, o co chodzi, "+GetAddress_Form(NPChar)+"? ","Znowu z tymi dziwnymi pytaniami? Skarbie, idź napij się rumu czy coś...")+" ","Przez cały ten dzień, to już trzeci raz, kiedy mówisz o jakimś pytaniu..."+GetSexPhrase(" Czy to jakieś oznaki uwagi?","")+"","Więcej pytań, jak sądzę, "+GetAddress_Form(NPChar)+"?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniłem zdanie","Nie mam teraz o czym rozmawiać."),"Nie, nie piękna...","Nie ma mowy, kochanie...","Nie, jakie pytania?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		case "helendrinking":
			dialog.text = "Jak się pan wyspał, monsieur? Panna MacArthur kazała nam zadbać o pański pełny komfort!";
			link.l1 = "Miałem bardzo dziwny sen...";
			link.l1.go = "helendrinking_1";
		break;

		case "helendrinking_1":
			dialog.text = "Ah!...";
			link.l1 = "Co się stało, mademoiselle? Czy mogę w czymś pomóc?";
			link.l1.go = "helendrinking_2";
		break;

		case "helendrinking_2":
			dialog.text = "Przepraszam, Kapitanie... To grzech, ale nie mogę się oprzeć! Nie mam dużego doświadczenia, ale nie odmawiaj dziewczynie, Kapitanie! Jesteś taki przystojny! Chcę cię zadowolić, dotknąć...";
			link.l1 = "Rzeczywiście, pełen komfort... Jesteś także bardzo piękna! No dalej, nie bądź nieśmiała.";
			link.l1.go = "helendrinking_sex";
			link.l2 = "Teraz lepiej mnie nie dotykaj, mademoiselle - śmierdzę rumem. Ale możesz mnie uszczęśliwić - śniadanie byłoby bardzo mile widziane!";
			link.l2.go = "helendrinking_nosex";
		break;
		
		case "helendrinking_sex":
			dialog.text = "O ja, o ja!";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "exit";
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
			notification("Helen disapproves", "Helena");
			AddDialogExitQuestFunction("HelenDrinking_WaitressSex");
		break;

		case "helendrinking_nosex":
			dialog.text = "Niegrzeczny!";
			link.l1 = "Więc nie będzie śniadania?";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "exit";
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
			notification("Helen approves", "Helena");
			AddDialogExitQuestFunction("HelenDrinking_WaitressNoSex");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
