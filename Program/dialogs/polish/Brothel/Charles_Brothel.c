// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakiego rodzaju pytania, "+GetSexPhrase("młody człowieku","młoda damo")+"?","Czego potrzebujesz, "+GetSexPhrase("przystojniaku","ślicznotko")+"Proszę pytać."),"Znowu pytania?","Tee-hee, jeśli to ci nie przeszkadza - jakie pytania..."," "+GetSexPhrase("Hm, czemuż to nie wybierzesz sobie piękności? Zaczynam mieć co do ciebie podejrzenia...","Hm, dlaczego nie wybierzesz sobie piękności? Obawiam się, że nie mamy tu chłopców, hi-hi...")+"","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniłem zdanie, przepraszam.","Właściwie, nieważne..."),"Ja... przepraszam, jednak nie mam pytań, do widzenia.","Masz rację, to już trzeci raz. Prosze o wybaczenie.","Może następnym razem, Droga Pani.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
