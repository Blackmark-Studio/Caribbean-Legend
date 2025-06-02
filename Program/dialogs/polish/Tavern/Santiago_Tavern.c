// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie masz pytania?","Jak mogę ci pomóc, "+GetAddress_Form(NPChar)+"?"),"Próbowałeś zadać mi jakieś pytanie niedawno, "+GetAddress_Form(NPChar)+"...","Przez cały ten dzień, to już trzeci raz, gdy mówisz o jakimś pytaniu...","Więcej pytań, jak mniemam?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniłem zdanie...","Nie mam teraz o czym rozmawiać."),"Umph, gdzież to mi pamięć uciekła...","Tak, to naprawdę już trzeci raz...","Nie, jakie pytania?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Jason Долго и счастливо
			if (CheckAttribute(pchar, "questTemp.LongHappy.Santiago"))
			{
				link.l1 = "Słyszałem, że święci ojcowie przybyli tutaj z francuskiej kolonii z jakąś delegacją, aby się na coś zgodzić? Prawdopodobnie, aby wymienić więźniów po tej krwawej kąpieli na Martynice?";
				link.l1.go = "LH_tavern";
			}
		break;
		
		// Jason Долго и счастливо
		case "LH_tavern":
			dialog.text = "Nie señor, ta historia została rozstrzygnięta dawno temu bez żadnych duchownych. Widzisz, żyjesz całkowicie pod palmą, skoro nie słyszałeś, że papież Innocenty X z kardynałem Mazarin w końcu się zgodził. Europa ze swoimi wojnami to jedno, ale wszyscy chrześcijanie powinni walczyć razem przeciwko pogańskiej ciemności na końcu świata\nI tak, żabojady przybyli do nas. Ale po prostu nie zgodzili się na nic - nasi szanowni goście siedzą w rezydencji gubernatora, pod strażą, piją kawę i grzeją krzesło. Już prawie miesiąc! Ludzie plotkowali, długo rozmawiali i się przyzwyczaili - zobacz, francuski opat odprawia nabożeństwa wieczorne w kościele. Prawie jak atrakcja ahah!";
			link.l1 = "Interesujące! Powinienem przyjrzeć się temu Francuzowi, przynajmniej to jest zabawniejsze niż wpatrywanie się w kufel.";
			link.l1.go = "LH_tavern_1";
		break;
		
		case "LH_tavern_1":
			DialogExit();
			LongHappy_SantiagoBenua();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
