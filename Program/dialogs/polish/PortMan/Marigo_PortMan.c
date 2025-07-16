// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie pytania?","Czego chcesz, "+GetAddress_Form(NPChar)+"?"),"Już próbowałeś zadać mi pytanie "+GetAddress_Form(NPChar)+"...","Już trzeci raz dzisiaj wspominasz o tej kwestii...","Spójrz, jeśli nie masz nic do powiedzenia o sprawach portowych, to nie zawracaj mi głowy swoimi pytaniami.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniam zdanie.","Nie mam o czym rozmawiać."),"Nieważne.","Rzeczywiście, już trzeci raz...","Przykro mi, ale na razie nie interesują mnie sprawy portu.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "maarten1")
			{
				link.l1 = "Szukam galeonu o nazwie 'Admirable' pod francuską banderą. Kapitanem był Gaius Marchais. Czy możesz mi powiedzieć, dokąd wypłynął? Może zarejestrował się tutaj?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Hmmm, 'Admirable'? Galeon? Pamiętam go. Sprawdźmy... wynajęliśmy go, by dostarczył paprykę do Bridgetown na Barbados. Coś się stało?";
			link.l1 = "Nie, ale Gaius jest moim przyjacielem i nie mogę się doczekać, żeby go spotkać.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "W takim razie żegluj do Barbadosu. Ale wątpię, że go tam znajdziesz, to było dawno temu. Przynajmniej możesz poprosić miejscowego zarządcę portu o pomoc.";
			link.l1 = "No to w drogę, jak mniemam.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			DialogExit();
			AddQuestRecord("Guardoftruth", "12");
			pchar.questTemp.Guardoftruth = "barbados";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
