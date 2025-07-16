// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué deseas?", "¿Qué te gustaría saber?"), "¿Qué necesitas, " + GetAddress_Form(NPChar) + "?", "Esa es la tercera vez que intentas preguntarme...", "¡Estoy harto de ti, piérdete!", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Lo siento, he cambiado de opinión.", " No es nada, disculpas."), "Lo olvidé, mis disculpas...", "La tercera es la vencida, ¿eh? Disculpa...", "¡Lo siento, lo siento! Entonces me iré...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		if (CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
		{
			link.l1 = "Escucha, una fragata bajo el mando de Miguel Dichoso estuvo por aquí en abril de 1654, luego desapareció. ¿Puedes contarme más sobre su barco? ¿Quizás viste qué le sucedió o adónde fue? ¿Recuerdas algo?";
			link.l1.go = "guardoftruth";
		}
		break;

	case "guardoftruth":
		dialog.text = "¡Oh-ho... Ay, señor, eso fue un espectáculo digno de ver! ¡No se olvidan cosas así, ja!";
		link.l1 = "¿Puedes decirme qué pasó?";
		link.l1.go = "guardoftruth_1";
		break;

	case "guardoftruth_1":
		dialog.text = "El bergantín del señor Dichoso echó ancla en el puerto de San José. Tuve una buena vista para verlo todo, sí. Te lo aseguro, era un excelente bergantín, una obra maestra, ¡lo juro por mi sangrante corazón! La tripulación se jactaba de la velocidad, ¡podía acelerar hasta dieciséis nudos!\nPasaron un día aquí, luego zarparon directamente hacia la isla Tobago. Entonces, no lo creerías, cosas extrañas comenzaron a suceder con el clima tan pronto como desaparecieron tras el horizonte. El clima había sido bueno durante días, ¡ni una sola nube!\nY sin embargo, esta terrible tormenta surgió de la nada. ¡Parecía que el mismo Neptuno nos había visitado, eso sí! Subí a la cima de mi faro para encenderlo, pero entonces la vi... ¡la Santa Quiteria! ¡Se apresuraba sobre enormes olas acompañada por un gigantesco tornado!\n¡El bergantín pasó cerca de mi faro como una chispa, y luego fue llevado por la tormenta hacia el noroeste! Nadie ha visto a la Santa Quiteria desde entonces. Apenas una hora después, el viento y la lluvia y las nubes se habían ido y el sol brillaba, ¡ni una sola señal de la tormenta! ¡Nunca vi nada igual! Aunque recogí tanto ámbar de mi bahía ese día...";
		link.l1 = "¿Así que la tormenta ha llevado la fragata de vuelta al mar Caribe?";
		link.l1.go = "guardoftruth_2";
		break;

	case "guardoftruth_2":
		dialog.text = "¡Sí! Muy lejos por allá, hacia Martinica. Dudo que Dichoso haya podido sobrevivir a esa tormenta, ¡aunque hizo lo que pudo! La fragata no se hundía, pero la Santa Quiteria debe estar en el fondo del mar entre corales ahora... De hecho, no eres la primera persona que me pregunta por Dichoso y su fragata.";
		link.l1 = "¿De veras? ¿Quién más estaba interesado en Miguel?";
		link.l1.go = "guardoftruth_3";
		break;

	case "guardoftruth_3":
		dialog.text = "¡Algún apuesto capitán de la flota española, nada menos! Se presentó como... oh... ya se me olvidó... ¡Ah! Señor Diego. Su nombre era Diego, pero su apellido... de Montagna o de Montoya. Algo así. Me escuchó igual que tú, me agradeció y se fue. No lo he visto desde entonces.";
		if (sti(Pchar.money) >= 5000)
		{
			link.l1 = "Ya veo. Muchas gracias por tu historia, me has ayudado mucho. Acepta mi gratitud en monedas. Adiós.";
			AddMoneyToCharacter(pchar, -5000);
			AddCharacterExpToSkill(pchar, "Leadership", 250);
		}
		else
		{
			link.l1 = "Ya veo. Muchas gracias por tu historia, me has ayudado mucho. Adiós.";
		}
		link.l1.go = "guardoftruth_4";
		break;

	case "guardoftruth_4":
		DialogExit();
		AddQuestRecord("Guardoftruth", "41");
		pchar.questTemp.Guardoftruth.Trinidad = "mayak";
		pchar.quest.GuardOT_setDiego.win_condition.l1 = "ExitFromLocation";
		pchar.quest.GuardOT_setDiego.win_condition.l1.location = pchar.location;
		pchar.quest.GuardOT_setDiego.function = "GuardOT_SetDiegoOnMayak";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
