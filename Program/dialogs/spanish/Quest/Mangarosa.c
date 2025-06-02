// диалоги персонажей по квесту Мангароса
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "First time":
		dialog.text = "¿Qué quieres?";
		link.l1 = "Nada.";
		link.l1.go = "exit";
		break;

	// Амелия - знахарка-цыганка
	case "amelia":
		dialog.text = "¿Qué quieres en mi casa?";
		if (CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "amelia")
		{
			link.l1 = "¿Tu nombre es Amelia, verdad? Vine a preguntarte sobre una planta. Manga Rosa.";
			link.l1.go = "amelia_1";
		}
		else
		{
			link.l1 = "Todavía no tengo nada que decirte. Pero volveré algún día...";
			link.l1.go = "exit";
		}
		NextDiag.TempNode = "amelia";
		break;

	case "amelia_1":
		dialog.text = "¡Interesante! ¿Y quién te ha hablado de mí, valiente joven?";
		link.l1 = "Uno de los tuyos. Dijo que conoces los secretos de esta planta y que puedes enseñarme a hacer pociones especiales con ella...";
		link.l1.go = "amelia_2";
		break;

	case "amelia_2":
		dialog.text = "Primero, muéstrame la planta de la que estás hablando. Tal vez no sepas nada al respecto y solo estés perdiendo mi tiempo. ¿Dónde está tu Manga Rosa?";
		if (CheckCharacterItem(pchar, "cannabis7"))
		{
			link.l1 = "Aquí, echa un vistazo.";
			link.l1.go = "amelia_3";
		}
		else
		{
			link.l1 = "Mm...";
			link.l1.go = "amelia_exit";
		}
		break;

	case "amelia_exit":
		dialog.text = "¿Y qué ibas a mostrarme? No tienes Manga Rosa. Así que lárgate, amigo, antes de que me enfade. Esta charla ha terminado.";
		link.l1 = "Pero...";
		link.l1.go = "exit";
		NextDiag.TempNode = "amelia_wait";
		break;

	case "amelia_wait":
		dialog.text = "¿Tú otra vez? No causes problemas, muchacho...";
		if (CheckCharacterItem(pchar, "cannabis7"))
		{
			link.l1 = "Tranquilízate, Amelia. La dejé caer en algún lugar la última vez. Aquí, te he traído Manga Rosa. Echa un vistazo.";
			link.l1.go = "amelia_3";
		}
		else
		{
			link.l1 = "...";
			link.l1.go = "amelia_exit";
		}
		NextDiag.TempNode = "amelia_wait";
		break;

	case "amelia_3":
		dialog.text = "Veamos... Parece que sabes algo al respecto. ¿Y quieres que te cuente los secretos de mis pociones?";
		link.l1 = "Exactamente. Y no gratis, por lo que entiendo...";
		link.l1.go = "amelia_4";
		break;

	case "amelia_4":
		dialog.text = "¡Lo entiendes bien, joven! No pareces un completo idiota. Bueno, puedo enseñar a un hombre que busca conocimiento y que no desperdicia esta rara planta en cosas inútiles para fumar...";
		link.l1 = "Amelia, antes de que empecemos a negociar... ¿serías tan amable de contarme algunos conocimientos básicos sobre las pociones que puedo hacer con Manga Rosa?";
		link.l1.go = "amelia_5";
		break;

	case "amelia_5":
		dialog.text = "No hay regateo, amigo. Te diré el precio y será tu decisión pagarlo o no. No cuentes con ningún regateo o descuento, esto no es un mercado. Y respecto a tu pregunta... Puedes hacer pociones especiales de Manga Rosa que fortificarán tus habilidades físicas. Pueden hacerte más fuerte, más resistente o más rápido, o pueden alterar completamente tu cuerpo haciéndote más fuerte en todos los aspectos, pero tal poción tendría un efecto más débil que las dos anteriores.";
		link.l1 = "Muy interesante. Nombra tu precio.";
		link.l1.go = "amelia_6";
		break;

	case "amelia_6":
		dialog.text = "Puedo enseñarte tres recetas. Por cada receta te pido una planta y quinientas monedas de oro.";
		link.l1 = "Dime más sobre estas pociones. ¿Qué hace cada una de ellas?";
		link.l1.go = "amelia_7";
		break;

	case "amelia_7":
		dialog.text = "Tú debes ser un maestro del arte de la alquimia si quieres hacer una sola poción. Cada poción dura dos días o menos, depende de cuándo la bebas, si la bebes a medianoche durará cerca de dos días completos\nLa primera poción te añade fuerza y resistencia. Lucharás mejor, recibirás menos daño y podrás cargar más peso\nLa segunda poción te hará más rápido, ágil, incansable y también mejorará tu puntería\nLa tercera poción tiene efectos dos veces más débiles que las dos pociones anteriores. Pero también te da encanto, autoconfianza y suerte\nTodas las pociones basadas en Manga Rosa tienen un efecto positivo en tu salud. Debes beber solo una poción a la vez, nunca las mezcles, de lo contrario no te harán bien, por el contrario, sufrirás un fuerte envenenamiento\nEntonces, guapo, ¿estás listo para pagar por el conocimiento ahora mismo, o necesitas tiempo para pensarlo?";
		if (CheckCharacterItem(pchar, "cannabis7") && PCharDublonsTotal() >= 500)
		{
			link.l1 = "Sí, estoy listo.";
			link.l1.go = "amelia_8";
		}
		link.l2 = "Necesito pensar un poco. Esta es una gran decisión que tomar.";
		link.l2.go = "exit";
		NextDiag.TempNode = "amelia_next";
		break;

	case "amelia_next":
		if (!CheckAttribute(npchar, "quest.ChickenGod") && CheckCharacterItem(pchar, "talisman11"))
		{
			if (CheckAttribute(npchar, "quest.recipe_power") || CheckAttribute(npchar, "quest.recipe_fast") || CheckAttribute(npchar, "quest.recipe_total"))
			{
				link.chickengod = "Amelia, parece que tienes un don para estas cosas. ¿Puedes decirme si hay demanda de piedras así entre tu gente? Las encuentro por todas partes, ¡es como si todo el mundo estuviera obsesionado con ellas!";
				link.chickengod.go = "chickengod";
			}
		}

		if (CheckAttribute(npchar, "quest.ChickenGod") && !CheckAttribute(npchar, "quest.ChickenGod.Complete") && GetCharacterItem(pchar, "talisman11") >= 113)
		{
			link.chickengod = "Aquí tienes, Amelia. Tal como pediste: ciento trece piedras de víbora.";
			link.chickengod.go = "chickengod_collected";
		}

		if (CheckAttribute(npchar, "quest.recipe_all"))
		{
			dialog.text = "¡Ah, eres tú, joven! Entonces, ¿te ayudaron mis pociones?";
			link.l1 = "Realmente lo hicieron, Amelia. ¡Gracias!";
			link.l1.go = "exit";
		}
		else
		{
			dialog.text = "¡Ah, eres tú, joven! ¿Quieres comprar algunas recetas?";
			if (CheckCharacterItem(pchar, "cannabis7") && PCharDublonsTotal() >= 500)
			{
				link.l1 = "Exactamente. Por eso estoy aquí.";
				link.l1.go = "amelia_8";
			}

			link.l2 = "Aún no, Amelia. Solo te hago una visita.";
			link.l2.go = "exit";
		}
		NextDiag.TempNode = "amelia_next";
		break;

	case "amelia_8":
		dialog.text = "Muy bien. ¿Qué tipo de receta quieres comprar?";
		if (!CheckAttribute(npchar, "quest.recipe_power"))
		{
			link.l1 = "La receta de la poción de fuerza y resistencia.";
			link.l1.go = "power";
		}
		if (!CheckAttribute(npchar, "quest.recipe_fast"))
		{
			link.l2 = "La receta para la poción de agilidad e incansabilidad.";
			link.l2.go = "fast";
		}
		if (!CheckAttribute(npchar, "quest.recipe_total"))
		{
			link.l3 = "La receta de una poción compleja.";
			link.l3.go = "total";
		}
		break;

	case "power":
		dialog.text = "Bien. La he llamado la 'Ola de Marea'. Aquí, toma una instrucción. Léela cuidadosamente. ¡Y no olvides cómo usarla correctamente!";
		link.l1 = "Gracias, Amelia...";
		link.l1.go = "recipe_exit";
		AddQuestRecordInfo("Recipe", "mangarosapower");
		SetAlchemyRecipeKnown("mangarosapower");
		npchar.quest.recipe_power = true;
		break;

	case "fast":
		dialog.text = "Bien. Lo he nombrado 'Tormenta'. Aquí tienes una instrucción. Léela con cuidado. ¡Y no olvides cómo usarla correctamente!";
		link.l1 = "Gracias, Amelia...";
		link.l1.go = "recipe_exit";
		AddQuestRecordInfo("Recipe", "mangarosafast");
		SetAlchemyRecipeKnown("mangarosafast");
		npchar.quest.recipe_fast = true;
		break;

	case "total":
		dialog.text = "Bien. Lo he nombrado el 'Abrazo del Mar'. Aquí, toma una instrucción. Léela con cuidado. ¡Y no olvides cómo usarla correctamente!";
		link.l1 = "Gracias, Amelia...";
		link.l1.go = "recipe_exit";
		AddQuestRecordInfo("Recipe", "mangarosatotal");
		SetAlchemyRecipeKnown("mangarosatotal");
		npchar.quest.recipe_total = true;
		break;

	case "recipe_exit":
		DialogExit();
		NextDiag.CurrentNode = "amelia_next";
		RemoveDublonsFromPCharTotal(500);
		RemoveItems(pchar, "cannabis7", 1);
		Log_Info("Has regalado 500 doblones y una Manga Rosa");
		PlaySound("interface\important_item.wav");
		if (CheckAttribute(npchar, "quest.recipe_power") && CheckAttribute(npchar, "quest.recipe_fast") && CheckAttribute(npchar, "quest.recipe_total"))
		{
			npchar.quest.recipe_all = true;
			CloseQuestHeader("mangarosa");
		}
		break;

	case "chickengod":
		dialog.text = "¡Bax de adder, en verdad! Tiene poco valor, pero puede ser útil para aquellos que lo saben. Tráeme ciento trece de ellos, y abriré uno de mis cofres para ti.";
		link.l1 = "¡Eso es un montón de piedras! ¿Por qué no me dices primero por qué las necesitas?";
		link.l1.go = "chickengod_1";
		break;

	case "chickengod_1":
		dialog.text = "No, querida, si necesitas preguntar, entonces este conocimiento no te sirve de nada aún.";
		link.l1 = "¿Y qué hay dentro del cofre que tan generosamente prometiste abrir?";
		link.l1.go = "chickengod_2";
		break;

	case "chickengod_2":
		dialog.text = "Muchas cosas, útiles para capitanes que no desprecian el trabajo manual. No me hagas perder el tiempo, querida, de todos modos no puedes recoger tantas piedras.";
		link.l1 = "¡Ya veremos sobre eso!";
		link.l1.go = "exit";

		npchar.quest.ChickenGod = true;
		break;

	case "chickengod_collected":
		dialog.text = "¡Ja-ja-ja! ¡Era una broma, querida!";
		link.l1 = "¡Las bromas serán sobre ti cuando te quemen, bruja, en tu propia choza!";
		link.l1.go = "chickengod_collected_1";
		break;

	case "chickengod_collected_1":
		dialog.text = "Eso no es mi destino, querido... ¡Has hecho que esta gitana se sienta orgullosa! Aquí, este cofre es tuyo para saquear.";
		link.l1 = "Gracias, Amelia. Pero realmente espero que haya algo útil ahí dentro además de tu ropa interior vieja...";
		link.l1.go = "exit";

		TakeNItems(pchar, "talisman11", -113);
		npchar.quest.ChickenGod.Complete = true;
		AddDialogExitQuestFunction("ChickenGod_AmeliaOpenChest");
		break;
	}
}
