// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie pytania?","Czego chcesz, "+GetAddress_Form(NPChar)+"?"),"Już próbowałeś zadać mi pytanie "+GetAddress_Form(NPChar)+"... ","Rozmawiałeś o jakimś pytaniu już trzeci raz dzisiaj...","Patrz, jeśli nie masz nic do powiedzenia o sprawach portu, to nie zawracaj mi głowy swoimi pytaniami.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniam zdanie.","Nie mam o czym rozmawiać."),"Nieważne.","Rzeczywiście, to już trzeci raz...","Przykro mi, ale na razie nie interesują mnie sprawy portowe.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (pchar.questTemp.Slavetrader == "FindRatTortuga")
            {
                link.l1 = "Dzień dobry. Szukam François Gontiera. Jego korweta '"+pchar.questTemp.Slavetrader.ShipName+" musiał być tutaj w twoim porcie.";
                link.l1.go = "Tortuga_ratP_1";
            }
			
		break;

		case "Tortuga_ratP_1":
			dialog.text = NPCStringReactionRepeat("Hm... Muszę cię rozczarować. Korweta '"+pchar.questTemp.Slavetrader.ShipName+"nigdy tu nie był, a Francois Gontier również się tu nie zarejestrował.","Już o to pytałeś i odpowiedziałem.","Mówię ci, że już pytałeś o tego Gontiera.","Proszę, nie rozpraszaj mnie od mojej pracy!","block",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Dzięki. Będę dalej szukał.","Hm, cóż...","Tak, naprawdę zapytałem...","Wybacz, "+npchar.name+"... ",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
