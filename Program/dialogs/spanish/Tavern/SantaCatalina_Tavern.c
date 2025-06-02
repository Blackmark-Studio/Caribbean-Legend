// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		if (startHeroType == 4)
		{
			dialog.text = NPCStringReactionRepeat("Por supuesto, Helen. ¿Qué sucede?", "Ah, ¿finalmente recordaste lo que querías?", "¿Estás seguro de que estás bien? Comienzas a preocuparme. ¿Quizás deberías ver a un médico? ", "Está bien, Helen. Descansa un poco, respira aire fresco, en resumen, tómate un respiro. Luego regresa. ¿Mhm?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("No, nada en realidad.", "No, no, siento molestarte.", "Probablemente tienes razón...", "Sí, probablemente tengas razón. Eso es lo mejor que se puede hacer.", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		}
		else
		{
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué preguntas tienes?", "¿En qué puedo ayudarte, " + GetAddress_Form(NPChar) + "?"), "Intentaste hacerme una pregunta hace no mucho, " + GetAddress_Form(NPChar) + "...", "En todo este día, esta es la tercera vez que hablas de alguna pregunta...", "Más preguntas, supongo?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión...", "No tengo nada de qué hablar en este momento."), "Umph, a dónde se ha ido mi memoria...", "Sí, realmente es la tercera vez...", "No, ¿qué preguntas?...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		}
		if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "blueveld")
		{
			link.l1 = "Escucha, " + npchar.name + ", ¿quién es Jan Svenson y cómo puedo encontrarlo?";
			link.l1.go = "Svenson";
		}
		//<-- Бремя гасконца
		// Страж Истины
		if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
		{
			link.l1 = "Escucha, ¿ha llegado aquí a este pueblo un alquimista, o un médico? Es italiano, tiene unos treinta años, se llama Gino Gvineili. ¿Has oído algo sobre eso?";
			link.l1.go = "guardoftruth";
		}
		break;

	case "Svenson":
		dialog.text = "Es la primera vez que conozco a un hombre que no sabe quién es Forest Devil. Ese apodo se lo dieron los españoles y ofrecieron una bolsa llena de oro por la cabeza de ese corsario de la Isla de Providencia hace quince años atrás. ¡Sí, los años pasan volando! La gente ya ha empezado a olvidarse de nuestro Jan. Tal vez realmente sea hora de que descanse.";
		link.l1 = "He llegado aquí recientemente y no sé mucho...";
		link.l1.go = "Svenson_1";
		break;

	case "Svenson_1":
		dialog.text = "Si estás interesado en el pasado, puedo venderte un libro de historia. Muchos darían una fortuna por él, pero yo...";
		link.l2 = "¡No me des rodeos! Te hice una pregunta. Repito. ¿Dónde vive Jan Svenson? Tengo una conversación seria para él.";
		link.l2.go = "Svenson_2";
		break;

	case "Svenson_2":
		dialog.text = "Vive en una mansión frente a la residencia de nuestro alcalde, junto a la fuente. Pero en este momento está pasando por tiempos difíciles y no recomendaría molestarlo a menos que sea de suma importancia.";
		link.l1 = "¿Y a qué se debe?";
		link.l1.go = "Svenson_3";
		break;

	case "Svenson_3":
		dialog.text = "Su chica favorita Helen, también conocida como Rumba, la hija de su difunto viejo amigo Shawn McArthur, ha desaparecido. Descansa en paz, viejo... Jan trata a la joven diablilla como si fuera su propia hija, ya que no tiene hijos propios. Pero la chica se ha desvanecido junto con su goleta 'Arcoíris' y toda la tripulación.\nSiento pena por la chica. Una belleza rara, inteligente también. Ardiente y fogosa como el fuego, ¡por eso la llamaban Rumba! Su padre le enseñó todo lo que sabía, ella heredó el barco y cada uno de los tripulantes se quedó a su lado. Incluso los lobos marinos más viejos la reconocieron como capitana...";
		link.l1 = "¿Una dama pirata? ¿Qué podría haberle sucedido?";
		link.l1.go = "Svenson_4";
		break;

	case "Svenson_4":
		dialog.text = "Quién sabe... Una semana no es tanto tiempo, pero la viuda de MacArthur está segura de que algo malo le pasó a su hija y logró convencer a Svenson de ello. Él llamó a sus hombres y comenzó a buscarla él mismo sin resultado alguno. 'Arcoíris' y su tripulación simplemente desaparecieron.\nPuedo decirte dónde encontrar a Gladys por mil piezas de a ocho.";
		if (sti(pchar.money) >= 1000)
		{
			link.l1 = "Tu conocimiento es bastante costoso, pero has despertado mi interés. Aquí tienes tu dinero. ¿Dónde la encuentro?";
			link.l1.go = "Svenson_5";
		}
		else
		{
			link.l1 = "No. Lo manejaré yo mismo si lo necesito. ¡Adiós, gracias por la historia!";
			link.l1.go = "Svenson_6";
		}
		break;

	case "Svenson_5":
		AddMoneyToCharacter(pchar, -1000);
		dialog.text = "Su casa está junto al muelle, a la izquierda del amarre. Pero probablemente no esté allí. Pasa todo el día en las murallas del fuerte vigilando a su amada hija. Ya debe haber llorado hasta quedarse sin lágrimas.";
		link.l1 = "¡Gracias por la historia! ¡Adiós, camarada!";
		link.l1.go = "Svenson_6";
		break;

	case "Svenson_6": // устанавливаем Глэдис на форт
		DialogExit();
		ref sld = characterFromId("Gladis");
		ChangeCharacterAddressGroup(sld, "SantaCatalina_fort", "goto", "goto53");
		LAi_SetStayType(sld);
		sld.dialog.currentnode = "FindHelena";
		pchar.questTemp.Saga = "gladis";
		sld = characterFromId("JS_girl");
		sld.dialog.currentnode = "js_girl_8";
		DelLandQuestMark(npchar);
		DelLandQuestMark(characterFromId("JS_girl"));
		DelMapQuestMarkCity("SantaCatalina");
		break;

	case "guardoftruth":
		dialog.text = LinkRandPhrase("No, no lo he hecho. Tenemos herbolarios y médicos, pero ninguno con un nombre así.", "Es la primera vez que oigo un nombre tan raro. No, nunca hemos tenido la visita del hombre del que hablas.", "Ni siquiera tenemos alquimistas aquí en absoluto. Tenemos médicos, pero ninguno con un nombre extraño como ese.");
		link.l1 = "Ya veo. Eso es una lástima. ¡Seguiré buscando!";
		link.l1.go = "exit";
		npchar.quest.jino = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}
