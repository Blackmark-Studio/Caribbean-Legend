// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie masz pytania?","Jak mogę ci pomóc, "+GetAddress_Form(NPChar)+"?"),"Próbowałeś zadać mi jakieś pytanie nie tak dawno temu, "+GetAddress_Form(NPChar)+"...","Przez cały ten dzień, to już trzeci raz, kiedy mówisz o jakimś pytaniu...","Więcej pytań, jak sądzę?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniam zdanie...","Nie mam teraz o czym rozmawiać."),"Eh, gdzież to podziała się moja pamięć...","Tak, to naprawdę już trzeci raz...","Nie, jakie pytania?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Сага
			if(CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "valet")
			{
				link.l1 = "Szukam człowieka o przezwisku Lokaj. Znasz go?";
				link.l1.go = "valet_1";
				link.l2 = "Poszukuję kapitana polakry o nazwie 'Marlin'. Czy mógłbyś mi powiedzieć, gdzie go znaleźć?";
				link.l2.go = "valet_2";
			}
		break;
		
		case "valet_1":
			dialog.text = NPCStringReactionRepeat("Nie, nie wiem, kamracie. Niczym ci nie mogę pomóc.","Już ci mówiłem, że nie wiem!","Czy jesteś pijany, czy po prostu się wygłupiasz?","Zostaw mnie w spokoju!","blokada",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Widzę. To szkoda...","To szkoda. Myślałem, że będziesz pamiętać...","Jestem trzeźwy! Po prostu jestem uparty...","Hm...",npchar,Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;
		
		case "valet_2":
			dialog.text = NPCStringReactionRepeat("Ach, panie David Fackman! On wynajmuje dom niedaleko stoczni. Szukaj go tam.","Przecież ci odpowiedziałem. Jakżeś mnie słuchał?","Czy jesteś pijany, czy tylko się wygłupiasz?","Zostaw mnie w spokoju!","blokada",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Dziękuję!","Tak. Przykro mi.","Jestem trzeźwy! Po prostu jestem uparty...","Hm...",npchar,Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
