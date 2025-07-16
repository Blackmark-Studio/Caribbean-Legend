// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie to pytania?","Czego chcesz, "+GetAddress_Form(NPChar)+"?"),"Już próbowałeś zadać mi pytanie "+GetAddress_Form(NPChar)+"...","Już trzeci raz dzisiaj mówisz o jakimś pytaniu...","Patrz, jeśli nie masz nic do powiedzenia o sprawach portu, to nie zawracaj mi głowy swoimi pytaniami.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniam zdanie.","Nie mam o czym rozmawiać."),"Nieważne.","Rzeczywiście, już trzeci raz...","Przykro mi, ale nie interesują mnie sprawy portowe na razie.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (pchar.questTemp.Slavetrader == "FindRatJamaica")
            {
                link.l1 = "Dzień dobry. Czy kapitan Francois Gontier zarejestrował się tutaj? Płynął z Porto Bello na korwecie nazwanej '"+pchar.questTemp.Slavetrader.ShipName+".";
                link.l1.go = "Jamaica_ratPP_1";
            }
			
		break;
		
		case "Jamaica_ratPP_1":
			dialog.text = NPCStringReactionRepeat("Nie, nie zrobił tego. A korweta '"+pchar.questTemp.Slavetrader.ShipName+"nie widziano w Port-Royal.","Już o to pytałeś i odpowiedziałem.","Powiadam ci, że już pytałeś o tego faceta Gontiera.","Proszę, nie rozpraszaj mnie w mojej pracy!","block",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Dzięki. Będę szukać dalej.","Hm, cóż...","Tak, naprawdę zapytałem...","Przepraszam, "+npchar.name+"...",npchar,Dialog.CurrentNode);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
