// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Cómo puedo ayudarte?","¿Qué puedo hacer por ti?"),"Dime, ¿qué te aflige, "+GetAddress_Form(NPChar)+"?","Por tercera vez, "+GetAddress_Form(NPChar)+", ¿qué necesitas?","Ya tuve suficiente de ti. ¡Fuera!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión, mis disculpas.","No es nada, discúlpame."),"Perdóname, no es nada.","Tienes razón, ya es la tercera vez. Perdóname...","Mis disculpas.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "Escucha, ¿has visto o conocido a un hombre llamado Joachim Merriman, aquí en La Habana o en sus alrededores? Es un señor de mediana edad, portugués con bigote, barba imperial y ojos penetrantes. ¿Quizás en una cala o en la jungla? Estoy buscándolo.";
				link.l1.go = "caleuche";
			}
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "N-no, marinero, c-ciertamente no. Rara vez recibo visitantes por aquí, ya ves, eh... y yo... yo no h-he visto a nadie como el hombre que describes, así que...";
			link.l1 = "¿De verdad? Entonces, ¿por qué tartamudeas y escondes los ojos? No me mientas ahora, tú conoces la verdad. Será mejor que lo pienses de nuevo: ¿has visto a ese hombre?";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "¡L-le digo, señor, que n-no he visto a nadie! H-he estado t-tartamudeando d-desde que era un niño...";
			link.l1 = "Mentiras, todas mentiras. Puedo verlo en tus ojos. ¿Dónde está, dónde está Merriman? ¡Dímelo, AHORA!";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "¡No conozco a ningún Merriman! ¡Nunca he oído ese nombre antes tampoco! ¡Y no intentes hacerme daño o el Comandante te colgará en el fuerte! Así que camina con cuidado, muchacho.";
			link.l1 = "¿Oh, eso crees? Está bien. Ahora, escúchame con mucha atención: Joachim Merriman es un brujo. La Santa Inquisición lo está buscando. Hace muchos años en Europa, fue condenado a la hoguera por profanar tumbas, mancillar a los muertos y brujería. Y sé con certeza que ahora se esconde en algún lugar por aquí, en las afueras de La Habana...";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = "...";
			link.l1 = "... recientemente he limpiado la cueva cercana de no-muertos, y sé quién es el responsable. Claro, ¿a dónde más iría Merriman, si no al cementerio? Tú sabes dónde está. Pero hazlo a tu manera... no te pondré un dedo encima, pero haré una visita a los Inquisidores en Santiago. Al Padre Vincento le resultará muy intrigante que Joachim Merriman se esté escondiendo en el cementerio de La Habana con su cómplice, el vigilante...";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "...";
			link.l1 = "... ¿Ya te has puesto pálido? Te doy mi palabra de noble: Un día después de que reporte mis hallazgos, toda la isla estará llena de soldados españoles. Y serás estirado en un potro, estarás suplicando y llorando hasta que reveles dónde se esconde ese hechicero. No mucho después serás quemado en la hoguera como su cómplice mientras yo veo el 'acto de fe'. ¿Cómo suena eso?";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "¡P-por favor, señor! ¡No estoy participando en nada de eso, lo juro! Yo... Yo simplemente no pude hacer nada... ¿Cómo podría enfrentarme a él? ¡Es un hombre terrible, él puede... no tienes idea de lo que puede hacer! ¡Misericordia, te lo suplico!";
			link.l1 = "Confía en mí, sé de lo que es capaz. Lo he visto con mis propios ojos. ¿Y bien? ¿Dónde está? Dímelo, y te prometo que no te involucraré en este asunto.";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = "Él... Él se esconde en una mazmorra, debajo del cementerio. Solo se puede llegar allí a través de la puerta de la capilla. Cuando sale, me escondo en mi casa y me quedo allí. ¡No tienes idea de cuánto me gustaría deshacerme de ese horror!\nPero no me atrevería ni siquiera a acercarme. Yo... Yo lo he visto cavar una tumba reciente, y luego... ¡luego el muerto se levantó y caminó por el cementerio a la luz de la luna! ¡Casi perdí la cordura! Pero Merriman me prohibió irme. Me amenazó con que si salía de mi casa sin su permiso, aunque fuera por medio día, me encontraría y me convertiría en esa abominación... ¡un esqueleto andante!";
			link.l1 = "¿Con qué frecuencia sale de su cueva?";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "Bueno, le traigo comida y pociones curativas de la ciudad y... lo que sea que me demande. Se va una o dos veces al mes... cuando la luna está llena. Deja una nota en la puerta, escribe lo que necesita... y-yo lo traigo y lo pongo en la puerta, y él lo toma una vez que ha regresado.";
			link.l1 = "Ya veo. Esa puerta a su guarida... ¿está cerrada de alguna manera?";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			dialog.text = "Lo está. Siempre está cerrada. Es muy robusta y la cerradura es enorme y compleja.";
			link.l1 = "Mm... Merriman no es tonto, seguramente debe tener otra salida de su guarida, como su casa en Europa. Si forzáramos la puerta, se escabulliría y nunca más lo encontraríamos. Hmmm...";
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = "Señor, ¿juras que no me entregarás a la Inquisición?";
			link.l1 = "Te di mi palabra, y la palabra de un noble es sagrada. Juro que no te delataré.";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			dialog.text = "¡Oh, que Dios te bendiga, señor! Sé cómo llegar a la cueva. Hay una llave, una segunda llave... La tengo yo. Merriman no sabe que hay dos llaves para esa cerradura. Nunca me atrevería a entrar, pero tú...";
			link.l1 = "Dame la llave, y te libraré de esta pesadilla.";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			GiveItem2Character(pchar, "kaleuche_key");
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key_crypt");
			dialog.text = "Aquí tienes, señor. ¿En serio vas a entrar en su guarida?";
			link.l1 = "Así es. Enciérrate en tu casa y espera cuando entre. Si no regreso, deja todo y corre lo más rápido que puedas.";
			link.l1.go = "caleuche_12";
		break;
		
		case "caleuche_12":
			dialog.text = "Pero tenga cuidado, señor. Se han escuchado sonidos aterradores desde su cueva, y temo incluso al pensar quién podría habitarla. Pero Merriman no está solo, de eso estoy seguro.";
			link.l1 = "Tomaré todas las medidas que pueda. Adiós.";
			link.l1.go = "caleuche_13";
		break;
		
		case "caleuche_13":
			DialogExit();
			AddQuestRecord("Caleuche", "30");
			pchar.questTemp.Caleuche = "merriman";
			pchar.quest.caleuche_merriman_cave.win_condition.l1 = "locator";
			pchar.quest.caleuche_merriman_cave.win_condition.l1.location = "Havana_CryptBig2";
			pchar.quest.caleuche_merriman_cave.win_condition.l1.locator_group = "reload";
			pchar.quest.caleuche_merriman_cave.win_condition.l1.locator = "reload2";
			pchar.quest.caleuche_merriman_cave.function = "Caleuche_OpenMerrimanCave";
			pchar.quest.caleuche_merriman_cave1.win_condition.l1 = "location";
			pchar.quest.caleuche_merriman_cave1.win_condition.l1.location = "Havana_CryptDungeon";
			pchar.quest.caleuche_merriman_cave1.function = "Caleuche_InMerrimanCave";
			if(bImCasual) NewGameTip("Modo exploración: El temporizador no está desactivado. ¡Cumple con los plazos!");
			SetFunctionTimerCondition("Caleuche_MerrimanCaveOver", 0, 0, 3, false); // таймер
			npchar.quest.caleuche = "true";
			// логово Мерримана
			int n = Findlocation("Havana_CryptDungeon");
			locations[n].id.label = "Merrimancave";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}
