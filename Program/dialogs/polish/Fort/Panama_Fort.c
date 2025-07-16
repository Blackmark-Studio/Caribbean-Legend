// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Co myślisz o naszej twierdzy? Wygląda dobrze, prawda? A garnizon jeszcze się trzyma, ha...","Życie żołnierza fortu jest dość nudne... Pilnowanie i patrolowanie, spanie i odpoczynek, a potem znowu to samo. Ale w mieście jest inaczej... Czego chcesz, "+GetAddress_Form(NPChar)+"?"),"Natręctwo żołnierza głupimi pytaniami nie jest mile widziane, "+GetAddress_Form(NPChar)+"... ","To już trzeci raz, kiedy próbujesz mnie dziś o to zapytać...","Niełatwo być żołnierzem, a jednak znów tu jesteś"+GetSexPhrase(", głupcze,  "," ")+" próbujesz mnie wkurzyć. Uważaj, bo skończysz w piwnicy fortu...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniłem zdanie, przepraszam za kłopot.","Nie mam nic do powiedzenia, przepraszam."),"Masz rację, przepraszam.","Masz rację, to już trzeci raz. Wybacz mi.","Przepraszam, to nic.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
