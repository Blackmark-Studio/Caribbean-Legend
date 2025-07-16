// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué tipo de preguntas, " + GetSexPhrase("hijo mío", "hija mía") + "?", "Pregunta lo que quieras, estoy escuchando..."), "Estoy escuchando, habla ahora, " + GetSexPhrase("hijo mío", "hija mía") + "... ", "Por tercera vez, " + GetSexPhrase("hijo mío", "hija mía") + ", pide lo que necesitas.", "Un clérigo tiene mucho trabajo y me estás distrayendo, " + GetSexPhrase("hijo mío", "hija mía") + "...", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión...", "No en este momento, padre..."), "No tengo nada que decir, mis disculpas.", "Preguntaré, pero más tarde. Perdóname, padre.", "Perdóneme, santo padre...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}
