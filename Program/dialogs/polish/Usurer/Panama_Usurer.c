// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie masz pytania?","Jak mogę ci pomóc?"),"Próbowałeś zadać mi to pytanie niedawno...","Tak, niech zgadnę... Znowu kręcisz się w kółko?","Słuchaj, ja tu zajmuję się finansami, nie odpowiadam na pytania...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniłem zdanie...","Nie mam teraz nic do omówienia."),"Umph, gdzież podziała się moja pamięć...","Zgadłeś, przykro mi...","Rozumiem...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		// Реакция ростовщика Панамы на репутацию ГГ или на разграбление Картахены по сюжету
		case "Panama_Deposit_NoReputation":
			dialog.text = "To prawda... Człowiek honoru, kochany przez poddanych Króla, nigdy nie zostanie odprawiony z mojego banku, bez względu na jego narodowość.";
			link.l1 = "Rozumiem. Do widzenia.";
			link.l1.go = "exit";
		break;
		
		case "Panama_Deposit_Cartahena":
			dialog.text = "Ale niestety moja córka i teść mieli to. Mieszkali w Kartagenie. Idź precz, "+GetAddress_Form(NPChar)+"Nie jesteś tu mile widziany.";
			if (pchar.questTemp.Mtraxx.Retribution.Choice == "good")
			{
				link.l1 = "Proszę wybaczyć. Żegnaj.";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "Twoja strata. Żegnaj.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "NeHochuRazgovarivat";
		break;
		
		case "Panama_Deposit_SgorelVklad":
			dialog.text = "Fundusze zostały przejęte przez Koronę, aby wspomóc ofiary splądrowania miasta Cartagena. Nie mogę ci pomóc. Proszę cię natychmiast opuścić mój bank, zanim zawołam strażników!";
			link.l1 = "Pożałujesz tego...";
			link.l1.go = "exit";
			NextDiag.TempNode = "NeHochuRazgovarivat";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
