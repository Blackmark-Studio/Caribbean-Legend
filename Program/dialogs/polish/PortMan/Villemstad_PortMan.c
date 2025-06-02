// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakiego rodzaju pytania?","Czego chcesz, "+GetAddress_Form(NPChar)+"?"),"Już próbowałeś zadać mi pytanie "+GetAddress_Form(NPChar)+"...","Już trzeci raz dzisiaj mówisz o tej samej kwestii...","Spójrz, jeśli nie masz nic do powiedzenia na temat spraw portowych, to nie zawracaj mi głowy swoimi pytaniami.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniam zdanie.","Nie mam o czym rozmawiać."),"Nieważne.","Rzeczywiście, już trzeci raz...","Przykro mi, ale na razie nie interesują mnie sprawy portu.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";

			//работорговец
			if (pchar.questTemp.Slavetrader == "EscapeSlaveVillemstad_P")
            {
    			link.l1 = "Chciałbym się dowiedzieć o barku, który zniknął po buncie niewolników.";
    			link.l1.go = "EscapeSlave_Villemstad_P1";
            }
			//Голландский гамбит, против всех
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "SeekFleut")
            {
    			link.l1 = "Chcę znaleźć kapitana o imieniu Toff Keller. Posiada on fluitę o nazwie 'Leiden'. Powiedziano mi, że często odwiedza Willemstad, więc nie będzie trudno ci mi pomóc.";
    			link.l1.go = "SeekTradeFleut";
            }
		break;

		//работорговец
		case "EscapeSlave_Villemstad_P1":
				dialog.text = "Hm... A dlaczego cię to interesuje? Murzyni to twoja specjalność?";
				link.l1 = "Jestem tu na rozkaz Mathiasa Becka, gubernatora. Mam wszelkie powody podejrzewać, że zbiegli Murzyni ukradli ten statek i uciekli nim. Dlatego proszę cię o wszelką możliwą pomoc w moich poszukiwaniach.";
				link.l1.go = "EscapeSlave_Villemstad_P2";
		break;
		
		case "EscapeSlave_Villemstad_P2":
				dialog.text = "Widzę. Cóż, nie mogę ci pomóc. Bryg ' "+pchar.questTemp.Slavetrader.ShipName+"' zniknął do rana, nikt nic nie widział. Byłem w domu, śpiąc. Strażnik przystani też zniknął i nie zostawił śladu.\nGubernator wysłał slup, by spróbować ich dogonić, póki ślad był jeszcze świeży, ale wrócili z pustymi rękami. Ani śladu murzynów ani '"+pchar.questTemp.Slavetrader.ShipName+"'. Szczerze mówiąc, slup nie przeszukiwał ich zbyt dokładnie, wszyscy byli jeszcze w panice i myśleli, że kafirzy wypadną z dżungli z widłami i maczetami - głodni białej krwi.";
				link.l1 = "To nie było zbyt pomocne, ale mimo wszystko dziękuję. Do widzenia.";
				link.l1.go = "exit";
				AddQuestRecord("Slavetrader", "22_3");
				AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
				pchar.questTemp.Slavetrader = "EscapeSlaveVillemstad_H";
		break;				
		//Голландский гамбит
		case "SeekTradeFleut":
			DelLandQuestMark(npchar);
			dialog.text = "Toff Keller? Pewnie, że go znam! Regularnie odbywa rejsy do San Jose, które znajduje się na Trynidadzie, oraz do Cumana. Ostatnio płynął na Trynidad. Myślę, że możesz go tam znaleźć.";
			link.l1 = "Dzięki!";
			link.l1.go = "SeekTradeFleut_1";
		break;
		
		case "SeekTradeFleut_1":
			DialogExit();
			AddMapQuestMarkIsland("Trinidad", true);
			pchar.questTemp.HWIC.Self = "FleutOnTrinidad";
			AddQuestRecord("Holl_Gambit", "3-59");
			pchar.quest.Seek_Fleut.win_condition.l1 = "location";
			pchar.quest.Seek_Fleut.win_condition.l1.location = "Trinidad";
			pchar.quest.Seek_Fleut.function = "CreateTradeFleut";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
