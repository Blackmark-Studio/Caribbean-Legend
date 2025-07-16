// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat("Todos los rumores de " + GetCityName(npchar.city) + " a su servicio. ¿Qué le gustaría saber?", "Justo estábamos hablando de eso. Debes haberlo olvidado...", "Esta es la tercera vez hoy que hablas de alguna pregunta...", "Te repites como un loro...", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat("Sabes, " + NPChar.name + ", tal vez la próxima vez.", "Correcto, lo he olvidado por alguna razón...", "Sí, realmente es la tercera vez...", "Sí...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		if (CheckAttribute(pchar, "questTemp.Slavetrader") && pchar.questTemp.Slavetrader == "FindRatHavana")
		{
			link.l1 = "¿Ha pasado por casualidad Francois Gontier por tu pueblo? Tiene una corbeta, llamada '" + pchar.questTemp.Slavetrader.ShipName + ", por si acaso... ";
			link.l1.go = "Havana_ratT_1";
		}
		if (CheckAttribute(npchar, "quest.batabano"))
		{
			link.l1 = "Dime, compañero, ¿dónde podría encontrar a Don Diego de Montoya? ¿Llego tarde? ¿Ya ha partido hacia el continente?";
			link.l1.go = "guardoftruth";
		}
		// калеуче
		if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
		{
			link.l1 = "Escucha, ¿ha pasado por aquí un hombre llamado Joachim Merriman? Un médico de mediana edad, portugués, con bigote, barba imperial y ojos penetrantes. ¿Quizás quería alquilar una habitación?";
			link.l1.go = "caleuche";
		}
		break;

	case "Havana_ratT_1":
		dialog.text = "Ajá, ¿ese tipo sombrío? Sí, se detuvo en este lugar. Te diré algo: tenía una cita con Oregon-y-Haskon. Solicitó recibir una patente. Pero no le salió bien y se largó de allí.";
		Link.l1 = "¿Y a dónde zarpó? ¿Lo sabes? Lo he estado persiguiendo desde Portobello y no puedo encontrarlo.";
		Link.l1.go = "Havana_ratT_2";
		break;

	case "Havana_ratT_2":
		dialog.text = "¿Qué necesitas de él? Le tiene miedo a los forasteros, siempre se esconde de todos, tan pronto como ve a un extraño armado agarra una espada. Solo anda rodeado de cuatro guardias. ¿Acaso eres el hombre del que se protege?";
		Link.l1 = "¡Por Dios, la gente no deja de decir eso una y otra vez! ¿Qué, acaso parezco un asesino? Es mi viejo camarada, tengo prisa por pasarle algunas noticias, se alegrará mucho al saber que ya no necesita esconderse, nadie lo está buscando.";
		Link.l1.go = "Havana_ratT_3";
		break;

	case "Havana_ratT_3":
		dialog.text = "¿No necesita esconderse? ¡Ja-ja-ja! Justo un día antes de su partida de La Habana, una banda entera de matones intentó matarlo en la jungla... Por supuesto, él tenía a su propia gente, y los convirtieron en carne picada en un segundo. Y aquí estás diciendo...";
		Link.l1 = "Oh, vamos. Probablemente solo fueron algunos bandidos locales tratando de quedarse con su billetera. Tú mismo sabes cuántos sinvergüenzas andan por la jungla. Entonces, ¿a dónde fue?";
		Link.l1.go = "Havana_ratT_4";
		break;

	case "Havana_ratT_4":
		dialog.text = "Bueno, después de que lo enviaron lejos y por mucho tiempo de la residencia, seguía insistiendo en que se entregaría a los comedores de ranas, a sus compatriotas. Se ha marchado a Tortuga, a algún tal d'Ogeron... También murmuró algo sobre su amante, pero no pude entenderlo del todo.";
		Link.l1 = "Entonces, ¿Tortuga? ¡Genial! Espero atraparlo allí. Gracias, " + npchar.name + ", has sido de gran ayuda. Adiós.";
		Link.l1.go = "exit";
		AddQuestRecord("Slavetrader", "21_7");
		pchar.questTemp.Slavetrader = "FindRatTortuga";
		pchar.quest.Slavetrader_findTortugaRat.win_condition.l1 = "location";
		pchar.quest.Slavetrader_findTortugaRat.win_condition.l1.location = "Tortuga_HouseHut";
		pchar.quest.Slavetrader_findTortugaRat.win_condition = "Slavetrader_findTortugaRat";
		break;

	case "guardoftruth":
		dialog.text = "Mm... ¿Y por qué un francés estaría interesado en Don Diego, eh?";
		link.l1 = "El hecho de que sea francés es irrelevante. Lo que importa es este documento firmado por el Inquisidor. Echa un vistazo... ¿lo ves ahora? Tengo un mensaje urgente para Diego.";
		link.l1.go = "guardoftruth_1";
		break;

	case "guardoftruth_1":
		dialog.text = "¡Ajá!, ¿así que trabajas para Su Reverencia, Padre Vincento? Esto cambia las cosas. Don Diego de Montoya partió hace dos días con su escuadrón, pero pronto regresó en su balandra de mensajería. Uno de sus barcos naufragó en los arrecifes al sur de Cuba, así que hoy mismo ha estado comprando material para reparaciones.\nRevisa la bahía al sur, allí encontrarás un barco y al mismísimo hombre. Dudo que ya hayan logrado reparar los agujeros.";
		link.l1 = "¡Gracias, compañero! ¡Has sido de gran ayuda!";
		link.l1.go = "guardoftruth_2";
		break;

	case "guardoftruth_2":
		dialog.text = "En absoluto, en cualquier momento. Siempre estoy feliz de ayudar a un hermano jesuita.";
		link.l1 = "¡Pax vobiscum y todo eso!";
		link.l1.go = "guardoftruth_3";
		break;

	case "guardoftruth_3":
		DialogExit();
		DeleteAttribute(npchar, "quest.batabano");
		AddQuestRecord("Guardoftruth", "47");
		pchar.quest.GuardOT_Batabano.win_condition.l1 = "location";
		pchar.quest.GuardOT_Batabano.win_condition.l1.location = "Shore13";
		pchar.quest.GuardOT_Batabano.function = "GuardOT_SanAntonioPrepare";
		break;

	// калеуче
	case "caleuche":
		dialog.text = "El diablo lo sabe, camarada. Podría haber llegado, pero yo no sé nada de eso. Lo siento.";
		link.l1 = "Ya veo. Lástima. Continuaré mi búsqueda...";
		link.l1.go = "exit";
		npchar.quest.caleuche = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}
