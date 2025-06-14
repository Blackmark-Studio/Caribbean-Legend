void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i, n, iTemp, addGold;
	string attrL, sStr;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Vous vouliez quelque chose ?";
			link.l1 = "Non, rien.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// --> Шарль на носу корабля, Алонсо подходит с диалогом
		case "StartSailor":
			dialog.text = "Hermoso, ¿verdad?";
			link.l1 = "Esta belleza lleva dos meses tratando de matarme. Hasta ahora sin éxito.";
			link.l1.go = "StartSailor_1_fencing";
			link.l2 = "Así es. A veces el océano nos recuerda lo pequeños que somos en realidad.";
			link.l2.go = "StartSailor_1_leadership";
			link.l3 = "He aprendido que en el mar solo hay dos estados: aburrimiento o terror. Esto... es diferente.";
			link.l3.go = "StartSailor_1_fortune";
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "tutorial_4", "", -1);
			CharacterTurnByLoc(pchar, "quest", "quest6");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "tutorial_5", "", -1);
			CharacterTurnByLoc(npchar, "quest", "quest7");
		break;

		case "StartSailor_1_fencing":
			dialog.text = "¡Ja! ¿Primera vez en el mar, monsieur? Cuando está así de calmado, cualquiera puede jugar a ser capitán. Así que aproveche el momento.";
			link.l1 = ""+GetFullName(pchar)+". Un noble, por cierto. No 'monsieur', sino señor.";
			link.l1.go = "StartSailor_2";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;
		
		case "StartSailor_1_leadership":
			dialog.text = "¡Ja! ¿Primera vez en el mar, monsieur? Cuando está así de calmado, cualquiera puede jugar a ser capitán. Así que aproveche el momento.";
			link.l1 = ""+GetFullName(pchar)+". Un noble, por cierto. No 'monsieur', sino señor.";
			link.l1.go = "StartSailor_2";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;

		case "StartSailor_1_fortune":
			dialog.text = "¡Ja! ¿Primera vez en el mar, monsieur? Cuando está así de calmado, cualquiera puede jugar a ser capitán. Así que aproveche el momento.";
			link.l1 = ""+GetFullName(pchar)+". Un noble, por cierto. No 'monsieur', sino señor.";
			link.l1.go = "StartSailor_2";
			AddCharacterSkillPoints(pchar, "Fortune", 1);
		break;

		case "StartSailor_2":
			dialog.text = "Como guste, señor. Entonces, ¿primer viaje por mar para usted, señor "+pchar.lastname+"?";
			link.l1 = "¿Es tan obvio? Sí, es mi primer viaje. Y no estoy hecho para camarotes estrechos y galletas mohosas.";
			link.l1.go = "StartSailor_3";
		break;

		case "StartSailor_3":
			dialog.text = "Se ve a la legua que usted es un hombre de tierra, señor.";
			link.l1 = "¡Modera tu lengua! A un hombre de honor le arrojaría el guante y exigiría satisfacción. Pero a un patán como tú - simplemente te cortaré las orejas.";
			link.l1.go = "StartSailor_4";
		break;

		case "StartSailor_4":
			dialog.text = "Quizás en París. Pero aquí, palabras así pueden mandar a uno a alimentar a los peces. No andaría blandiendo esa hoja por ahí, señor - y no haga que el capitán se arrepienta de dejarle caminar armado por su cubierta. Al último alborotador lo mandó a la bodega - a galleta mohosa y agua de sentina que ni las ratas querían beber. ¿Y sabe qué? El pobre diablo tuvo que pagar extra cuando llegamos a puerto.";
			link.l1 = "Qué se puede esperar... Bien, olvidemos este malentendido. Tengo que recordarme constantemente que este barco no es precisamente el Louvre.";
			link.l1.go = "StartSailor_5";
		break;

		case "StartSailor_5":
			dialog.text = "¿Eh? ¿El Louvre? ¿Qué se supone que es eso?";
			link.l1 = "¡Ja! El Louvre es un palacio para los elegidos. Bailes, recepciones, intrigas...";
			link.l1.go = "StartSailor_6";
		break;

		case "StartSailor_6":
			dialog.text = "Ah... un burdel entonces. De esos tenemos de sobra. No diría que son para elegidos - paga tu moneda y todo es tuyo.";
			link.l1 = "¡Ja! No andas muy lejos de la verdad, marinero.";
			link.l1.go = "StartSailor_7";
		break;
		
		case "StartSailor_7":
			dialog.text = "Por cierto, me llamo Alonso. ¿Y qué hace usted en este rincón del mundo, señor? Dudo que haya cruzado el Atlántico solo para discutir con un simple marinero.";
			link.l1 = "Mi padre está enfermo y no puede abandonar nuestra finca en Gascuña. Me encargaron encontrar a mi... hermano mayor. Vino aquí por negocios y hace tiempo que no hay noticias suyas.";
			link.l1.go = "StartSailor_8";
		break;

		case "StartSailor_8":
			dialog.text = "¿Por qué no enviar simplemente a alguien de confianza, en lugar de sufrir usted mismo las penurias del mar?";
			link.l1 = "La familia está por encima de todo. No puedo confiarle su destino al primer desconocido.";
			link.l1.go = "StartSailor_9_nobilityplus";
			link.l2 = "Me encantaría hacerlo - pero según mi padre, debo ocuparme yo mismo. No tengo ni idea de por qué.";
			link.l2.go = "StartSailor_9_nobilityminus";
		break;

		case "StartSailor_9_nobilityplus":
			dialog.text = "¿Y cómo se llama su hermano?";
			link.l1 = "Michelle de Monper.";
			link.l1.go = "StartSailor_10";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "StartSailor_9_nobilityminus":
			dialog.text = "¿Y cómo se llama su hermano?";
			link.l1 = "Michelle de Monper.";
			link.l1.go = "StartSailor_10";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;

		case "StartSailor_10":
			dialog.text = "¿De Monper? ¿Y usted es "+pchar.lastname+"? ¿Cómo es eso?";
			link.l1 = "Y no me mires así. Soy hijo legítimo. Solo llevo el apellido de mi madre.";
			link.l1.go = "StartSailor_11";
		break;

		case "StartSailor_11":
			dialog.text = "No hay nada de qué avergonzarse. Encajará bien aquí - en el Nuevo Mundo, cada segundo tiene alguna historia. Yo, por ejemplo...";
			link.l1 = "¡No me avergüenzo de nada! Mejor dime, ¿cómo es Martinica? ¿Es una ciudad grande? ¿Como Toulouse?";
			link.l1.go = "StartSailor_12";
		break;
		
		case "StartSailor_12":
			dialog.text = "¿Ciudad? ¡Ja! Martinica es una isla entera. Una de las más grandes bajo dominio francés en el Caribe. Allí cultivan un café ardiente, extraen azufre infernal y nacen las mujeres más hermosas del mundo. Una mezcla excelente, si me lo preguntas.";
			link.l1 = "El café y el azufre no me interesan. Pero espera... ¿una isla? ¿Cómo voy a encontrar a mi hermano en toda una isla?";
			link.l1.go = "StartSailor_13";
		break;

		case "StartSailor_13":
			dialog.text = "No se preocupe tanto. Saint-Pierre es una ciudad pequeña, no es el Louvre, claro, pero tampoco la jungla. Ahora, en el bandido Le François, que Dios nos libre... un caballero no tiene nada que hacer allí.";
			link.l1 = "Si hace falta - iré incluso con los bandidos. Michel siempre me sacó de los líos. Ahora me toca a mí.";
			link.l1.go = "StartSailor_14";
		break;

		case "StartSailor_14":
			dialog.text = "Bien dicho... para un lobo de tierra.";
			link.l1 = "¿Otra vez con eso? ¿Cuánto falta para llegar a esa maldita Martinica?";
			link.l1.go = "StartSailor_15";
		break;

		case "StartSailor_15":
			dialog.text = "Cinco días.";
			link.l1 = "¿Cinco?!";
			link.l1.go = "StartSailor_16";
		break;

		case "StartSailor_16":
			dialog.text = "Eso como mínimo. Y si nos atacan los piratas - puede que no lleguemos nunca. Las Antillas Menores son peligrosas, incluso sin carga valiosa a bordo.";
			link.l1 = "¡Excepto por los pasajeros!";
			link.l1.go = "StartSailor_17";
		break;

		case "StartSailor_17":
			dialog.text = "¡Ja-ja! No se preocupe. En el peor de los casos, lo esconderé personalmente en la bodega - ningún pirata buscaría a un noble gascón entre los barriles de ron. ¡No somos idiotas! Mezclar gascones vivos con ron... ¡Eso explotaría peor que la pólvora, ja-ja!";
			link.l1 = "¡Ja! Menos mal que el ron se acabó hace un mes.";
			link.l1.go = "StartSailor_18";
		break;

		case "StartSailor_18":
			dialog.text = "Ehm... sería mejor no decir esas cosas en voz alta. Podrían pensar que usted tiene la culpa de nuestra desgracia con el ron.";
			link.l1 = "Está bien, Alonso, no lo haré. De todos modos, jamás meteré esa porquería en la boca. Y sobre tu brillante plan de meterme en la bodega antes del combate - ni lo sueñes.";
			link.l1.go = "StartSailor_20";
		break;
		
		case "StartSailor_20":
			dialog.text = "¿Y eso por qué?";
			link.l1 = "Soy noble, sé manejar una espada con firmeza y no pienso esconderme en la bodega.";
			link.l1.go = "StartSailor_21_fencing";
			link.l2 = "Si llega el momento - defenderé el barco y lucharé con todos. ¿Cómo podría ser de otra forma?";
			link.l2.go = "StartSailor_21_leadership";
			link.l3 = "Puedo decidir por mí mismo - cuándo luchar y cuándo huir. Lo veré sobre la marcha.";
			link.l3.go = "StartSailor_21_fortune";
			locCameraFromToPos(-14.85, 4.73, 5.82, true, -10.30, 4.52, 6.14);
		break;

		case "StartSailor_21_fencing":
			dialog.text = "Ja. Puede que tenga algo dentro de sí. Pero cuidado - el Caribe le arranca la piel a quienes caminan con la nariz en alto. No sobrevivirá al primer encuentro con la avanzadilla pirata. Es más, el primer mendigo a las puertas de Saint-Pierre lo acuchillará.";
			link.l1 = "No sabes nada de mí.";
			link.l1.go = "StartSailor_22";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;

		case "StartSailor_21_leadership":
			dialog.text = "Ja. Puede que tenga algo dentro de sí. Pero cuidado - el Caribe le arranca la piel a quienes caminan con la nariz en alto. No sobrevivirá al primer encuentro con la avanzadilla pirata. Es más, el primer mendigo a las puertas de Saint-Pierre lo acuchillará.";
			link.l1 = "No sabes nada de mí.";
			link.l1.go = "StartSailor_22";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;

		case "StartSailor_21_fortune":
			dialog.text = "Ja. Puede que tenga algo dentro de sí. Pero cuidado - el Caribe le arranca la piel a quienes caminan con la nariz en alto. No sobrevivirá al primer encuentro con la avanzadilla pirata. Es más, el primer mendigo a las puertas de Saint-Pierre lo acuchillará.";
			link.l1 = "No sabes nada de mí.";
			link.l1.go = "StartSailor_22";
			AddCharacterSkillPoints(pchar, "Fortune", 1);
		break;

		case "StartSailor_22":
			dialog.text = "Pero yo sí conozco el Nuevo Mundo y a sus habitantes. Si no va a terminar secándose entre libros de contabilidad o sirviendo en la casa del gobernador - tendrá que aprenderlo todo desde cero.";
			link.l1 = "Menos mal que no planeo quedarme mucho tiempo.";
			link.l1.go = "StartSailor_23";
		break;
		
		case "StartSailor_23":
			dialog.text = "Eso cree usted. Rara vez llevamos pasajeros de regreso a Europa. Unos mueren - de fiebre, de la soga o de una bala. Otros se quedan - para siempre. He visto a aristócratas endebles convertirse en capitanes, y a bandidos despiadados en respetables plantadores. También he visto a brillantes oficiales terminar como mendigos.";
			link.l1 = "Muy tentador, maldita sea, pero regresaré a Francia. Me esperan allá.";
			link.l1.go = "StartSailor_24";
		break;

		case "StartSailor_24":
			dialog.text = "Ah, sí, claro. ¿El padre enfermo?";
			link.l1 = "Digamos que... hay una dama cuyo esposo no está precisamente feliz de verme en París. Pero en un par de meses, todo se calmará.";
			link.l1.go = "StartSailor_25";
		break;

		case "StartSailor_25":
			dialog.text = "¡Ja-ja-ja! Entonces realmente está en el lugar correcto. El Caribe es un paraíso para quienes huyen de esposos celosos. Y el tiempo aquí pasa volando. Deme tiempo - ¡y acabará siendo marinero!";
			link.l1 = "Capitán, más bien. No sirvo como simple marinero. No nací para trabajar con las manos.";
			link.l1.go = "StartSailor_26";
		break;

		case "StartSailor_26":
			dialog.text = "En Francia la gente gobierna por derecho de nacimiento, pero en un barco - el capitán es el rey, juez y Dios. Y nadie sabe lo que tuvo que pasar para ganarse su sombrero. Aquí cada quien recibe lo que merece. Como decimos en cubierta - a cada quien lo suyo.";
			link.l1 = "Qué disparate. Hablando de capitanes - tengo que hablar con el tuyo, sobre todo si me está buscando. Hasta luego, Alonso.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_StartKino_6");
		break;
		
		// <-- Шарль на носу корабля, матрос подходит с диалогом
		
		// --> С Алонсо можно в любой момент поговорить
		case "AlonsoWait":
			dialog.text = "¿Quería preguntarme algo?";
			if (PCharDublonsTotal() >= 60 && CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive") && !CheckAttribute(npchar, "SharlieTutorial_KaznacheyQuest_Alonso"))
			{
				link.l1 = "Vengo de parte del señor Pinchón.";
				link.l1.go = "AlonsoGold_2";
			}
			link.l2 = "Nada.";
			link.l2.go = "AlonsoWait_2";
		break;

		case "AlonsoGold_2":
			dialog.text = "¡Vaya! ¿Así que nuestro cuatroojos también lo reclutó a usted?";
			link.l1 = "¿Cuatroojos?";
			link.l1.go = "AlonsoGold_3";
		break;

		case "AlonsoGold_3":
			dialog.text = "¿Ha visto sus lentes? ¡Eso mismo! Pero no se equivoque: la tripulación respeta al señor Pinchón. Un buen médico siempre es apreciado en un barco. Y como tesorero tampoco es malo.";
			link.l1 = "¿Qué asuntos tiene usted con él?";
			link.l1.go = "AlonsoGold_4";
		break;

		case "AlonsoGold_4":
			dialog.text = "Eeeh... Perdón, pero eso es asunto nuestro. Pero no se preocupe, no estamos violando las leyes del barco.";
			link.l1 = "¿Y las leyes normales?";
			link.l1.go = "AlonsoGold_5";
		break;

		case "AlonsoGold_5":
			dialog.text = "Esas no nos interesan. ¿Y cuánto dijeron que debía pagar?";
			if (PCharDublonsTotal() >= 40)
			{
				link.l1 = "40 doblones.";
				link.l1.go = "AlonsoGold_DatDeneg_3_gold40";
			}
			if (PCharDublonsTotal() >= 50)
			{
				link.l2 = "50 doblones.";
				link.l2.go = "AlonsoGold_DatDeneg_3_gold50";
			}
			if (PCharDublonsTotal() >= 60)
			{
				link.l3 = "60 doblones.";
				link.l3.go = "AlonsoGold_DatDeneg_3_gold60";
			}
			// link.l4 = "Necesito revisar todo otra vez. Volveré luego.";
			// link.l4.go = "AlonsoWait_2";
		break;
		
		case "AlonsoGold_DatDeneg_3_gold40":
			dialog.text = "¡Ahí está el oro! ¡Prepárate, Saint-Pierre! ¡Ja-ja!";
			link.l1 = "...";
			link.l1.go = "AlonsoWait_2";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(40);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			npchar.SharlieTutorial_KaznacheyQuest_Alonso = true;
		break;

		case "AlonsoGold_DatDeneg_3_gold50":
			dialog.text = "¡Ahí está el oro! ¡Prepárate, Saint-Pierre! ¡Ja-ja!";
			link.l1 = "...";
			link.l1.go = "AlonsoWait_2";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(50);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			npchar.SharlieTutorial_KaznacheyQuest_Alonso = true;
		break;

		case "AlonsoGold_DatDeneg_3_gold60":
			dialog.text = "¡Ahí está el oro! ¡Prepárate, Saint-Pierre! ¡Ja-ja!";
			link.l1 = "...";
			link.l1.go = "AlonsoWait_2";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(60);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.SharlieTutorial_KaznacheyQuest_Alonso = true;
		break;
		
		case "AlonsoWait_2":
			DialogExit();
			NextDiag.CurrentNode = "AlonsoWait";
		break;
		
		// <-- С Алонсо можно в любой момент поговорить
		
		// --> капитан на корабле, который идёт из Европы
		case "Captain":
			dialog.text = "Ah, "+pchar.name+". No se ha dado mucha prisa. Cuando el capitán de un barco quiere hablar con usted, debe presentarse de inmediato. ¿Tiene problemas para obedecer órdenes?";
			link.l1 = "No estoy acostumbrado a recibir órdenes, capitán.";
			link.l1.go = "Captain_2_fencing";
			link.l2 = "Mis disculpas, capitán, algo me distrajo.";
			link.l2.go = "Captain_2_leadership";
			link.l3 = "Ya me han explicado claramente que su barco - sus reglas.";
			link.l3.go = "Captain_2_sailing";
			if (bBettaTestMode)
			{
				link.l9 = "BetaTest (saltar el tutorial y empezar el juego en Martinica)";
				link.l9.go = "BetaTest_StartGame";
			}
			//NextDiag.TempNode = "Captain";
			pchar.questTemp.SharlieTutorial_CaptainDialog = true;
		break;
		
		case "Captain_2_fencing":
			dialog.text = "No permitiré que se cuestione mi autoridad. No tiene idea de cuán a menudo les ocurren cosas malas a los pasajeros en alta mar. Tiene una suerte increíble de que esté interesado en llevarlo sano y salvo a Saint-Pierre.";
			link.l1 = "¿De qué está hablando?";
			link.l1.go = "Captain_3";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;

		case "Captain_2_leadership":
			dialog.text = "Disculpas aceptadas. Aproveche el momento. Difícilmente tendrá otra oportunidad de disfrutar un atardecer así pronto.";
			link.l1 = "¿De qué está hablando?";
			link.l1.go = "Captain_3";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;

		case "Captain_2_sailing":
			dialog.text = "Me alegra ver que ha aprendido algo durante esta travesía. El poder del capitán es absoluto, y a veces incluso se extiende a tierra firme, lejos del barco.";
			link.l1 = "¿De qué está hablando?";
			link.l1.go = "Captain_3";
			AddCharacterSkillPoints(pchar, "Sailing", 1);
		break;

		case "Captain_3":
			dialog.text = "Capitán. Le agradecería que se dirigiera a mí conforme al reglamento marítimo.";
			link.l1 = "¿De qué está hablando, capitán?";
			link.l1.go = "Captain_4";
		break;

		case "Captain_4":
			dialog.text = "Quería informarle que hemos bajado las velas y estamos a la deriva. Desafortunadamente, su llegada a Martinica se retrasará un par de días.";
			link.l1 = "¿Pero por qué, capitán?";
			link.l1.go = "Captain_5";
		break;

		case "Captain_5":
			dialog.text = "Porque así lo he decidido.";
			link.l1 = "¿Tiene algo que ver con nuestro encuentro de ayer con el convoy mercante rumbo a ese... cómo se llamaba...";
			link.l1.go = "Captain_6";
		break;
		
		case "Captain_6":
			dialog.text = "Cabsterreville. Mire, "+pchar.name+": necesito tener una conversación seria con usted. Lo invito a cenar en mi camarote. En cuanto suene la campana, podremos pasar un rato como gente civilizada — terminando la última botella de vino del barco.";
			link.l1 = "Gracias por la invitación. Será un honor, capitán.";
			link.l1.go = "Captain_7";
		break;

		case "Captain_7":
			if (!CheckAttribute(npchar, "SharlieTutorial_question_0"))
			{
				dialog.text = "Hágame saber cuando esté listo. Aún tenemos tiempo, así que es libre de caminar por el barco — siempre y cuando no distraiga a mi tripulación de sus tareas.";
				npchar.SharlieTutorial_question_0 = true;
				// теперь можно пострелять из пушки
				sld = &Locations[FindLocation("Quest_Ship_deck_Medium_trade")];
				SetLocatorEvent(sld.id, "event3", "SharlieTutorial_cannon_1");
			}
			else dialog.text = "¿Alguna otra pregunta?";
			link.l1 = "(Terminar asuntos) Estoy listo, capitán. ¡Con usted hasta bebería borgoña!";
			link.l1.go = "Captain_8";
			if (!CheckAttribute(npchar, "SharlieTutorial_question_1"))
			{
				link.l2 = "¿Qué observa con tanto interés por el catalejo... capitán?";
				link.l2.go = "Captain_7_question_1_1";
			}
			if (!CheckAttribute(npchar, "SharlieTutorial_question_2"))
			{
				link.l3 = "Capitán, tuve el placer de hablar con un tal Alonso. ¿Cuál es su puesto a bordo?";
				link.l3.go = "Captain_7_question_2_1";
			}
			if (!CheckAttribute(npchar, "SharlieTutorial_question_3"))
			{
				link.l4 = "Capitán, cuénteme sobre su barco. ¿Es un pinaza, verdad?";
				link.l4.go = "Captain_7_question_3_1";
			}
			link.l5 = "Hasta pronto, capitán.";
			link.l5.go = "Captain_7_exit";
		break;
		
		case "Captain_7_exit":
			DialogExit();
			NextDiag.CurrentNode = "Captain_7";
			if (!CheckAttribute(npchar, "SharlieTutorial_Zapis"))
			{
				npchar.SharlieTutorial_Zapis = true;
				AddQuestRecord("SharlieTutorial", "0.1");
			}
		break;
		
		case "Captain_7_question_1_1":
			dialog.text = "Nada en particular. Solo observo el horizonte. Al estar a la deriva, somos presa fácil.";
			link.l1 = "¿Está buscando piratas?";
			link.l1.go = "Captain_7_question_1_2";
		break;

		case "Captain_7_question_1_2":
			dialog.text = "O españoles. Navegamos bajo bandera francesa y sin escolta, y las Antillas Menores son un verdadero pasillo marítimo, dominio de Jacques Barbazón.";
			link.l1 = "¿Quién es ese? ¿Un gobernador?";
			link.l1.go = "Captain_7_question_1_3";
		break;

		case "Captain_7_question_1_3":
			dialog.text = "Peor — uno de los barones piratas. Esos ahorcados crearon algo parecido a una organización y se hacen llamar la Hermandad de la Costa. Dividieron el Caribe en seis zonas y pusieron a un barón en cada una para no pelear entre ellos.";
			link.l1 = "¿Y por qué las autoridades no hacen nada?";
			link.l1.go = "Captain_7_question_1_4";
		break;

		case "Captain_7_question_1_4":
			dialog.text = "Es muy ingenuo, "+pchar.name+". La piratería solo existe porque las autoridades locales les permiten reparar y abastecer sus barcos en ciertos puertos, a cambio de una buena parte del botín. Me desagrada admitirlo, pero los únicos que realmente hacen algo contra esta plaga negra son los españoles. De no ser por ellos, no solo habría que equipar el barco con costosos cañones, sino también contratar una escolta.";
			link.l1 = "...";
			link.l1.go = "Captain_7";
			npchar.SharlieTutorial_question_1 = true;
		break;

		case "Captain_7_question_2_1":
			dialog.text = "Contramaestre. No sé mucho de él, pero le aseguro: si cada persona tiene un esqueleto en el armario, Alonso tiene un cementerio entero.";
			link.l1 = "Lo dice como si no confiara en él.";
			link.l1.go = "Captain_7_question_2_2";
		break;

		case "Captain_7_question_2_2":
			dialog.text = "En absoluto. ¿Cree que es fácil encontrar gente con experiencia? Hace falta al menos un año y un buen contramaestre para que la chusma reclutada en las tabernas empiece a parecer una tripulación. Además, Alonso es la voz del equipo. El capitán no se molesta en tratar con la gente de abajo, pero sería una estupidez y un error mortal ignorar que los marineros también tienen sus intereses. Él los defiende cuando es necesario.";
			link.l1 = "¿Y qué pasa si la tripulación no está contenta?";
			link.l1.go = "Captain_7_question_2_3";
		break;

		case "Captain_7_question_2_3":
			dialog.text = "Me colgarán a mí y a usted simplemente lo acuchillarán. Pero no tiemble así. Mientras la tripulación reciba su salario, ron, provisiones y atención médica — el contrato entre capitán y marineros se respeta. Yo no arriesgo sus vidas en vano, no castigo por capricho, reparto el botín y a veces los consiento con alcohol gratis y otros placeres en tierra. Así se mantiene un frágil equilibrio y el barco siempre llega a destino.";
			link.l1 = "...";
			link.l1.go = "Captain_7";
			npchar.SharlieTutorial_question_2 = true;
		break;
		
		case "Captain_7_question_3_1":
			dialog.text = "¡Ha tocado una fibra sensible, "+pchar.name+"! Podría hablar de mi bella dama sin parar. Tercer classe, veinte cañones, excelente velocidad — ¡aunque parezca un 'mercante'!";
			link.l1 = "Entiendo lo de los cañones y la velocidad. ¿Pero 'classe'? ¿'Mercante'?";
			link.l1.go = "Captain_7_question_3_2";
		break;

		case "Captain_7_question_3_2":
			dialog.text = "Los rangos son una división condicional de los barcos según la cantidad de cañones. El séptimo classe no está muy lejos de un bote, y el primero — de una fortaleza. Pero no se le ocurra repetir eso en Europa, especialmente frente a oficiales navales.";
			link.l1 = "¿Por qué? ¿Es alguna broma marinera?";
			link.l1.go = "Captain_7_question_3_3";
		break;

		case "Captain_7_question_3_3":
			dialog.text = "Lo tomarán por un completo ignorante y se burlarán de usted. Francamente, en cualquier marina seria, los classes funcionan de forma muy distinta y se aplican solo a barcos militares. Pero aquí en el Caribe, como siempre, hacemos las cosas a nuestra manera.";
			link.l1 = "¿Y qué quiso decir al llamar a su barco 'mercante'?";
			link.l1.go = "Captain_7_question_3_4";
		break;

		case "Captain_7_question_3_4":
			dialog.text = "Otra convención. Los barcos militares — son más resistentes y disparan mejor; los corsarios — saquean y escapan. Los mercantes pueden llevar mucho cargamento útil, tripulación o cañones, pero hay que sacrificar algo para no perder velocidad. También existen los barcos multifunción, pero poco hay que decir de ellos, salvo que se adaptan a las necesidades de su dueño.";
			link.l1 = "Se ha animado, capitán.";
			link.l1.go = "Captain_7_question_3_5";
		break;

		case "Captain_7_question_3_5":
			dialog.text = "Amo mi barco, "+pchar.name+".";
			link.l1 = "...";
			link.l1.go = "Captain_7";
			npchar.SharlieTutorial_question_3 = true;
		break;

		case "Captain_8":
			if (IsEquipCharacterByItem(pchar, "hat3"))
			{
				dialog.text = "Entonces ha tenido suerte — sólo me queda un borgoña... ¡Un momento, "+pchar.name+"! ¿¡Cómo es que lleva mi viejo sombrero!?\nUn momento. ¡Eh, en los mástiles! ¿Qué sucede allí?";
				ChangeCharacterComplexReputation(pchar, "nobility", -1);
			}
			else dialog.text = "Entonces ha tenido suerte — sólo me queda un borgoña.\nUn momento. ¡Eh, en los mástiles! ¿Qué sucede allí?";
			link.l1 = "...";
			link.l1.go = "Captain_9";
		break;
		
		case "Captain_9":
			DialogExit();
			DelLandQuestMark(npchar);
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga");
		break;
		
		case "BetaTest_StartGame":	// досрочный выход на сушу
			DialogExit();
			AddDialogExitQuestFunction("SharlieTutorial_StartGameInMartinique");
		break;
		
		// <-- капитан на корабле, который идёт из Европы
		
		case "OhrannikCabin":
			dialog.text = "Lo siento, señor "+pchar.lastname+", pero no puede pasar.";
			link.l1 = "Tengo acceso a la cabina del capitán. Deberías recordarlo.";
			link.l1.go = "OhrannikCabin_1";
			link.l2 = "Qué pena que mi pérfido plan haya fracasado. Hasta luego, marinero.";
			link.l2.go = "exit";
			if (GetSummonSkillFromName(pchar, SKILL_Leadership) >= 15) NextDiag.TempNode = "OhrannikCabin";
			else NextDiag.TempNode = "OhrannikCabin_again";
			if (!CheckAttribute(npchar, "SharlieTutorial_OhrannikStay"))
			{
				LAi_SetStayType(npchar);
				npchar.SharlieTutorial_OhrannikStay = true;
				DeleteQuestCondition("SharlieTutorial_OhrannikStopaet");
			}
		break;

		case "OhrannikCabin_1":
			dialog.text = "Lo siento, señor, pero las circunstancias han cambiado.";
			link.l1 = "¿Y qué ha pasado exactamente?";
			link.l1.go = "OhrannikCabin_2";
		break;

		case "OhrannikCabin_2":
			dialog.text = "El viaje casi ha terminado y el capitán no quiere que alguien robe sus pertenencias y luego huya impunemente a los bandidos en Le François.";
			link.l1 = "Dudo que el capitán se refiriera a mí cuando dio esa orden.";
			link.l1.go = "OhrannikCabin_3";
		break;

		case "OhrannikCabin_3":
			if (GetSummonSkillFromName(pchar, SKILL_Leadership) >= 15)
			{
				if (!CheckAttribute(npchar, "SharlieTutorial_OhrannikFail"))
				{
					dialog.text = "Bueno... tiene razón. Y ya ha comido en la cabina del capitán más de una vez. Pase, señor "+pchar.lastname+".";
					link.l1 = "¡Así se habla!";
					link.l1.go = "OhrannikCabin_4";
					notification("Prueba superada", SKILL_Leadership);
				}
				else
				{
					dialog.text = "¿Insi... insi qué? ¡No quise insinuar nada, señor "+pchar.lastname+"!";
					link.l1 = "Entonces estás obligado a dejarme pasar.";
					link.l1.go = "OhrannikCabin_3_1";
				}
			}
			else
			{
				if (!CheckAttribute(npchar, "SharlieTutorial_OhrannikFail"))
				{
					dialog.text = "Señor, usted entiende que la cabina del capitán no es de libre acceso. Las órdenes se respetan aquí.";
					link.l1 = "Maldita sea, ojalá lleguemos pronto a tierra. ¡Es humillante!";
					npchar.SharlieTutorial_OhrannikFail = true;
				}
				else
				{
					dialog.text = "Señor, ya lo hemos discutido. No puedo dejarle pasar.";
					link.l1 = "Qué testarudo eres, marinero. Adiós.";
				}
				link.l1.go = "exit";
				NextDiag.TempNode = "OhrannikCabin_again";
				notification("Habilidad insuficiente (15)", SKILL_Leadership);
			}
		break;
		
		case "OhrannikCabin_3_1":
			dialog.text = "Ay... bueno, supongo que no pasará nada grave.";
			link.l1 = "¡Así se habla!";
			link.l1.go = "OhrannikCabin_4";
			notification("Prueba superada", SKILL_Leadership);
		break;

		case "OhrannikCabin_4":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			DelLandQuestMark(npchar);
			LocatorReloadEnterDisable("Quest_Ship_deck_Medium_trade", "reload_cabin", false);
		break;

		case "OhrannikCabin_again":
			dialog.text = "¿Algo más, señor? No puedo dejarle pasar — el capitán teme por sus pertenencias.";
			link.l1 = "¿Insinúas que soy un ladrón, marinero? Cuida tus palabras. ¡Esas insinuaciones son inaceptables!";
			if (CheckAttribute(npchar, "SharlieTutorial_OhrannikFail")) link.l1.go = "OhrannikCabin_3";
			else link.l1.go = "OhrannikCabin_1";
			link.l2 = "Nada, marinero.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OhrannikCabin_again";
		break;
		
		// <-- Диалог с охранником каюты
		
		// --> матрос ругается на ГГ, который активировал брашпиль
		case "SailorWithWindlass_1":
			dialog.text = "¡Eh, noble idiota! ¿¡Metiste al diablo en el cabrestante!?\n¡Con tu patita real soltaste el freno! ¿¡Nos quieres mandar a todos al fondo del mar!?\nHaznos un favor y no toques nada... ¡a menos que sea una nariz francesa!";
			link.l1 = "¿Y eso qué es, exactamente?";
			link.l1.go = "SailorWithWindlass_2";
		break;

		case "SailorWithWindlass_2":
			dialog.text = "Es un cabrestante, cabeza hueca. Sube el ancla. Si no se bloquea, puede destrozar el barco o enrollar a alguien con la cuerda como sardina en barril.";
			link.l1 = "Ja... ¿Y si se gira al otro lado baja el ancla, no?";
			link.l1.go = "SailorWithWindlass_3";
		break;

		case "SailorWithWindlass_3":
			dialog.text = "No, genio, en ese caso rebobina el tiempo. Pero tu mala suerte es que ya naciste.";
			link.l1 = "Bueno, nadie salió herido, ¿verdad? Los barcos son increíblemente complicados. Seré más cuidadoso.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_windlass_8");
			AddCharacterSkillPoints(pchar, "Sailing", 1);
		break;
		
		// <-- матрос ругается на ГГ, который активировал брашпиль
		
		// --> матрос ругается на ГГ, который активировал пушку
		case "SailorWithCannon_1":
			dialog.text = "Observas el largo cañón con la misma admiración con la que mirabas el atardecer hace un momento.";
			link.l1 = "Veo que te gusta observarme, Alonso. Mejor dime, ¿qué maravilla de la ingeniería es esta?";
			link.l1.go = "SailorWithCannon_2";
		break;

		case "SailorWithCannon_2":
			dialog.text = "Este es un cañón de dieciséis libras. Ni siquiera todos los barcos de guerra llevan uno así.";
			link.l1 = "¿Y es fácil acertar con esto?";
			link.l1.go = "SailorWithCannon_3";
		break;

		case "SailorWithCannon_3":
			dialog.text = "A corta distancia destrozamos a cualquiera. A cien yardas ya estamos en el juego. Más allá... sobre todo ruido y fuego, pero también sirve.";
			link.l1 = "A cien yardas, el enemigo también puede hacernos lo mismo.";
			link.l1.go = "SailorWithCannon_4";
		break;

		case "SailorWithCannon_4":
			dialog.text = "Cierto. Pero ahí entra en juego qué tripulación está mejor entrenada y qué artilleros son mejores. Lástima que nuestro artillero esté roncando ahora mismo — él sí que te enseñaría toda la ciencia... ¡y luego te cargaría en el cañón, ja ja!";
			link.l1 = "¿Un artillero es un oficial, verdad?";
			link.l1.go = "SailorWithCannon_5";
		break;

		case "SailorWithCannon_5":
			dialog.text = "Generalmente sí. Sin un artillero decente, mejor ni meterse en batalla — es más fácil lanzar los cañones por la borda y salir huyendo.\nLos capitanes de barcos mercantes rara vez llevan algo más potente que cañones de seis libras — confían en escoltas o en la fortuna.\nY tiene sentido: sin cañones pesados ni municiones, el barco navega mejor y cabe más mercancía en la bodega.\nSi nuestro capitán no se hubiera arruinado en estas bellezas, tal vez todavía tendríamos ron. ¡Ehh!";
			link.l1 = "¿El capitán no dirige personalmente el fuego?";
			link.l1.go = "SailorWithCannon_6";
		break;

		case "SailorWithCannon_6":
			dialog.text = "Con un buen artillero y una tripulación coordinada, no hace falta. Pero te digo algo: si el capitán apunta él mismo en lugar de solo gritar '¡Fuego!' desde el alcázar, los barcos enemigos terminan con más agujeros en sus costados.";
			link.l1 = "¿Puedo disparar?";
			link.l1.go = "SailorWithCannon_7";
			link.l2 = "Gracias por la clase magistral, Alonso. Eres un verdadero pozo de sabiduría marinera.";
			link.l2.go = "SailorWithCannon_7_exit";
		break;
		
		case "SailorWithCannon_7_exit":
			dialog.text = "¡Por supuesto! Pero mejor no toques el cañón ni pongas nerviosa a la tripulación.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_cannon_11");
		break;

		case "SailorWithCannon_7":
			dialog.text = "¿Disparar? Difícil. Para hacer un disparo hay que pedir permiso al capitán. ¡Ya voy a preguntarle!";
			link.l1 = "¡No hace falta!";
			link.l1.go = "SailorWithCannon_8";
		break;

		case "SailorWithCannon_8":
			dialog.text = "¡Caaaapitán!";
			link.l1 = "...";
			link.l1.go = "exit";
			locCameraSleep(true);
			AddDialogExitQuestFunction("SharlieTutorial_cannon_3");
		break;

		case "CaptainWithCannon_1":
			dialog.text = "¿Qué pasa aquí, Alonso?";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_2";
		break;

		case "CaptainWithCannon_2":
			StartInstantDialog("SharlieTutorial_Sailor_10", "CaptainWithCannon_3", "Quest\\Sharlie\\Tutorial.c");
		break;

		case "CaptainWithCannon_3":
			dialog.text = "El señor "+pchar.name+" propone disparar un cañón — puramente con fines educativos.";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_4";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Captain_clone"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Captain_clone"), npchar);
		break;

		case "CaptainWithCannon_4":
			StartInstantDialog("SharlieTutorial_Captain_clone", "CaptainWithCannon_5", "Quest\\Sharlie\\Tutorial.c");
		break;

		case "CaptainWithCannon_5":
			dialog.text = "Pensé que representabas los intereses de la tripulación, Alonso. ¿Y ahora propones despertar al siguiente turno y alarmar a todos los demás de la forma más salvaje posible?";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_6";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Sailor_10"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Sailor_10"), npchar);
		break;
		
		case "CaptainWithCannon_6":
			StartInstantDialog("SharlieTutorial_Sailor_10", "CaptainWithCannon_7", "Quest\Sharlie\Tutorial.c");
		break;
		
		case "CaptainWithCannon_7":
			dialog.text = "Creo que vale la pena activar la sangre de todos y estar listos. No me gusta que estemos a la deriva a la vista de todos. No vaya a ser que pase algo.";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_8";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Captain_clone"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Captain_clone"), npchar);
		break;

		case "CaptainWithCannon_8":
			StartInstantDialog("SharlieTutorial_Captain_clone", "CaptainWithCannon_9", "Quest\\Sharlie\\Tutorial.c");
		break;

		case "CaptainWithCannon_9":
			dialog.text = "¡No llames al mal tiempo! Está bien. Un solo disparo. Con pólvora de fogueo.";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_10";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Sailor_10"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Sailor_10"), npchar);
		break;

		case "CaptainWithCannon_10":
			dialog.text = "Diviértanse, "+pchar.name+". Pondremos en alerta a la tripulación... ¡a su costa, ja-ja!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_cannon_5");
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Sailor_10"), pchar);
		break;
		
		// <-- матрос ругается на ГГ, который активировал пушку
		
		// --> Диалог с матросом, который хочет рома
		case "SailorWantRum":
			dialog.text = "¿Tiene un minuto, señor?";
			link.l1 = "Habla, marinero.";
			link.l1.go = "SailorWantRum_1";
		break;

		case "SailorWantRum_1":
			dialog.text = "Encantado de conocerle, señor. Me llamo Henry. ¿Le gustaría ganar algo de dinero?";
			link.l1 = "¿Cuánto es 'algo'?";
			link.l1.go = "SailorWantRum_2";
		break;

		case "SailorWantRum_2":
			dialog.text = "Quinientos pesos.";
			link.l1 = "¿¡Cuánto!? ¿Y qué quieres que haga por ese dinero? Espero que no estés planeando un motín.";
			link.l1.go = "SailorWantRum_3";
		break;

		case "SailorWantRum_3":
			dialog.text = "¡Dios nos libre, señor! ¿Por qué gritar así?";
			link.l1 = "Es mucho dinero, marinero. Incluso en París se puede vivir bien con eso.";
			link.l1.go = "SailorWantRum_4";
		break;

		case "SailorWantRum_4":
			dialog.text = "Ah, no quiero aprovecharme de su ignorancia, así que seré honesto: en el Caribe, quinientos pesos no son gran cosa. Los capitanes y comerciantes traen tanta mercancía que los precios están por las nubes para todo lo útil. Es tan absurdo que a veces una espada rara cuesta lo mismo que un pequeño barco.";
			link.l1 = "Una locura.";
			link.l1.go = "SailorWantRum_5";
		break;

		case "SailorWantRum_5":
			dialog.text = "¿Qué se le va a hacer? Todos esperamos que pronto se estabilice y los precios bajen. Entonces, ¿le interesa ganar quinientos pesos?";
			link.l1 = "Primero quiero saber de qué se trata el trabajo.";
			link.l1.go = "SailorWantRum_6";
		break;

		case "SailorWantRum_6":
			dialog.text = "Seguro ya sabe sobre la triste situación con el ron en el barco. Pero yo creo que si se busca bien, aún deben quedar algunas botellas. El ron embotellado no es lo mismo que el de barril. Tiene mejor sabor, previene intoxicaciones, fortalece el cuerpo... en fin, es algo necesario. Más aún al final del viaje, cuando uno ya se vuelve loco viendo solo el horizonte.";
			link.l1 = "¿Y qué harás con él? ¿Y por qué no lo buscas tú mismo?";
			link.l1.go = "SailorWantRum_7";
		break;
		
		case "SailorWantRum_7":
			dialog.text = "¿Cuándo voy a tener tiempo? Estamos cortos de tripulación, así que trabajamos por tres. Y el ron... lo revenderé, seguro que encuentro a quién.";
			link.l1 = "Bueno, aprecio la franqueza en las personas.";
			link.l1.go = "SailorWantRum_8";
		break;

		case "SailorWantRum_8":
			dialog.text = "Entonces, ¿aceptas? Necesito tres botellas.";
			link.l1 = "Lo intentaré, pero no prometo nada.";
			link.l1.go = "SailorWantRum_9";
			link.l2 = "Prefiero rechazar. Ese tipo de trabajo no es para mí.";
			link.l2.go = "SailorWantRum_10";
		break;

		case "SailorWantRum_9":
			DialogExit();
			NextDiag.CurrentNode = "SailorWantRum_PrinestiRum";
			AddDialogExitQuestFunction("SharlieTutorial_PrinestiRum");
		break;

		case "SailorWantRum_10":
			dialog.text = "Es una lástima, pero no guardaré rencor. Que tenga una buena noche, señor.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SailorWantRum_PrinestiRum";
			npchar.SailorWantRum_Done = true;
			DelLandQuestMark(npchar);
		break;

		case "SailorWantRum_PrinestiRum": // esperando el ron
			dialog.text = "¿Sí, señor "+pchar.lastname+"?";
			if (GetCharacterItem(pchar, "potionrum") >= 3 && !CheckAttribute(npchar, "questTemp.SailorWantRum_Done"))
			{
				link.l1 = "Aquí tienes tus tres botellas de ron.";
				link.l1.go = "SailorWantRum_PrinestiRum_2";
			}
			if (PCharDublonsTotal() >= 42 && CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive") && !CheckAttribute(npchar, "SharlieTutorial_KaznacheyQuest_Anri"))
			{
				link.l2 = "Henry, tengo algo para ti de parte del señor Pinchon.";
				link.l2.go = "RumGold_2";
			}
			link.l3 = "Nada.";
			link.l3.go = "exit";
			NextDiag.TempNode = "SailorWantRum_PrinestiRum";
		break;
		
		case "RumGold_2":
			dialog.text = "¡Siempre es un placer serle útil! ¿Cuánto me toca esta vez?";
			if (PCharDublonsTotal() >= 28)
			{
				link.l1 = "28 doblones.";
				link.l1.go = "RumGold_DatDeneg_gold28";
			}
			if (PCharDublonsTotal() >= 35)
			{
				link.l2 = "35 doblones.";
				link.l2.go = "RumGold_DatDeneg_gold35";
			}
			if (PCharDublonsTotal() >= 42)
			{
				link.l3 = "42 doblones.";
				link.l3.go = "RumGold_DatDeneg_gold42";
			}
			// link.l4 = "Necesito revisar todo de nuevo. Volveré más tarde.";
			// link.l4.go = "RumGold_DatDeneg_3";
		break;

		case "RumGold_DatDeneg_gold28":
			dialog.text = "Gracias, señor "+pchar.lastname+". Envíele mis saludos al señor tesorero.";
			link.l1 = "...";
			link.l1.go = "RumGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(28);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			npchar.SharlieTutorial_KaznacheyQuest_Anri = true;
		break;

		case "RumGold_DatDeneg_gold35":
			dialog.text = "Gracias, señor "+pchar.lastname+". Envíele mis saludos al señor tesorero.";
			link.l1 = "...";
			link.l1.go = "RumGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(35);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			npchar.SharlieTutorial_KaznacheyQuest_Anri = true;
		break;
		
		case "RumGold_DatDeneg_gold42":
			dialog.text = "Gracias, señor "+pchar.lastname+". Envíele mis saludos al señor tesorero.";
			link.l1 = "...";
			link.l1.go = "RumGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(42);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.SharlieTutorial_KaznacheyQuest_Anri = true;
		break;
		
		case "RumGold_DatDeneg_3":
			DialogExit();
			NextDiag.CurrentNode = "SailorWantRum_PrinestiRum";
		break;
		
		case "SailorWantRum_PrinestiRum_2":
			dialog.text = "Gracias, señor "+pchar.lastname+". ¡Lo ha hecho usted con mucha destreza!";
			link.l1 = "Espero recibir mi dinero con la misma destreza.";
			link.l1.go = "SailorWantRum_PrinestiRum_3";
			RemoveItems(pchar, "potionrum", 3);
			npchar.SailorWantRum_Done = true;
		break;

		case "SailorWantRum_PrinestiRum_3":
			dialog.text = "¿Qué le parece si le pago de otra forma?";
			link.l1 = "Vaya, no eres tan honesto como parecía.";
			link.l1.go = "SailorWantRum_PrinestiRum_4";
		break;

		case "SailorWantRum_PrinestiRum_4":
			dialog.text = "¡No, no! Si prefiere el dinero, tendrá su dinero. Pero también puedo compartir conocimientos.";
			link.l1 = "¿Qué tipo de conocimientos?";
			link.l1.go = "SailorWantRum_PrinestiRum_5";
		break;

		case "SailorWantRum_PrinestiRum_5":
			dialog.text = "Puedo contarle muchas cosas útiles sobre la vida en el mar. Cosas que no encontrará en libros.";
			link.l1 = "Adelante, enséñame la lección más cara de mi vida.";
			link.l1.go = "SailorWantRum_PrinestiRum_6";
			link.l2 = "Quinientos consejos no valen quinientas monedas. Prefiero el dinero.";
			link.l2.go = "SailorWantRum_PrinestiRum_money";
		break;

		case "SailorWantRum_PrinestiRum_money":
			dialog.text = "Como guste, señor "+pchar.lastname+". ¡Y gracias otra vez!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_PrinestiRumFinal");
		break;

		case "SailorWantRum_PrinestiRum_6":
			dialog.text = "De verdad espero, señor "+pchar.name+", que esta lección le sea útil. ¿Sabe usted lo que es la navegación?";
			link.l1 = "Te sorprenderá, pero sí. Y también sé leer. Navegación es determinar la posición y calcular la ruta, por ejemplo, de un barco.";
			link.l1.go = "SailorWantRum_PrinestiRum_7";
		break;
		
		case "SailorWantRum_PrinestiRum_7":
			dialog.text = "Ah... habla usted de estrellas y mapas. No, eso no lo manejo. Para eso están el navegante o el capitán. Aquí llamamos navegación a la capacidad de manejar y comandar un barco.";
			link.l1 = "¿'Aquí' dónde exactamente?";
			link.l1.go = "SailorWantRum_PrinestiRum_8";
		break;

		case "SailorWantRum_PrinestiRum_8":
			dialog.text = "En el Caribe. Así se ha dado, no pregunte por qué. El punto es que cuanto mejor sea su navegación, más velocidad y maniobrabilidad podrá sacar de su barco. Y la tripulación manejará las velas con mayor rapidez. Pero eso no es lo más importante.";
			link.l1 = "Vaya, sabes mantener el suspenso.";
			link.l1.go = "SailorWantRum_PrinestiRum_9";
		break;

		case "SailorWantRum_PrinestiRum_9":
			dialog.text = "Cuanto mayor su habilidad de navegación, más grande será el barco que podrá comandar. Y si toma un barco para el que no tiene las habilidades necesarias, ¡puede perder concentración, fuerza e incluso salud por el esfuerzo!";
			link.l1 = "Suena peligroso. Extraño cómo he vivido sin saberlo.";
			link.l1.go = "SailorWantRum_PrinestiRum_10";
		break;

		case "SailorWantRum_PrinestiRum_10":
			dialog.text = "Por suerte, no hace falta saberlo todo. Siempre puede contratar a un buen navegante, y él se encargará de ese aspecto. Solo asegúrese de pagarle a tiempo y mantenerlo leal. Quedarse sin navegante en un barco que no puede manejar — no es nada agradable.";
			link.l1 = "Gracias por la lección, Henry. No estoy seguro de que me sirva, pero nunca sobran los conocimientos.";
			link.l1.go = "SailorWantRum_PrinestiRum_11";
			AddCharacterSkillPoints(pchar, "Sailing", 3);
		break;

		case "SailorWantRum_PrinestiRum_11":
			dialog.text = "De nada, señor "+pchar.lastname+". ¡Y gracias a usted una vez más!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_PrinestiRumFinal");
		break;
		
		// <-- Диалог с матросом, который хочет рома
		
		// --> Диалог со старым матросом в трюме
		case "OldSailor":
			dialog.text = "(cantando) C’est la mère Michel qui a perdu son chat... Qui crie par la fenêtre à qui le lui rendra...";
			link.l1 = "¿Qué haces aquí, marinero?";
			link.l1.go = "OldSailor_1";
			NextDiag.TempNode = "OldSailor";
		break;

		case "OldSailor_1":
			dialog.text = "Pues, como Madame Michel, estoy buscando a mi gato. Pero no grito, no le gusta que le griten.";
			link.l1 = "La vi esta mañana, otra vez arañó mis botas.";
			link.l1.go = "OldSailor_2";
		break;

		case "OldSailor_2":
			dialog.text = "Eso no es nada. Las botas del capitán no tuvieron tanta suerte. ¿Te gustan los gatos?";
			link.l1 = "Por supuesto que sí.";
			link.l1.go = "OldSailor_3";
			link.l2 = "No mucho.";
			link.l2.go = "OldSailor_4";
		break;

		case "OldSailor_3":
			dialog.text = "Tiene sentido. ¿Cómo más podríamos deshacernos de esas malditas ratas?";
			link.l1 = "¿Pero no puedes confiar siempre en los gatos? Son criaturas bastante caprichosas.";
			link.l1.go = "OldSailor_5";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "OldSailor_4":
			dialog.text = "Es una lástima. En los barcos, los gatos son amados y valorados. ¿Cómo más podríamos deshacernos de esas malditas ratas?";
			link.l1 = "¿Pero no puedes confiar siempre en los gatos? Son criaturas bastante caprichosas.";
			link.l1.go = "OldSailor_5";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;

		case "OldSailor_5":
			dialog.text = "Es cierto. Por eso tenemos que recurrir al arsénico. Pero intenta encontrarlo en el Caribe. Así que perdemos mercancía: las ratas contaminan el ron, estropean los bizcochos y roen todo lo demás.\nNuestro tesorero dice: 'Tómenlo con calma, es como un impuesto al comercio'.\nPero nosotros sabemos que es pereza. Si no fuera por nuestra querida Chantal, el capitán ya lo habría hecho vivir en la bodega y cazar ratas personalmente, ¡ja, ja!";
			link.l1 = "Buena suerte con el gato. Me tengo que ir.";
			link.l1.go = "OldSailor_6";
		break;
		
		case "OldSailor_6":
			dialog.text = "Espere, señor. Normalmente un simple marinero apenas ve a los pasajeros nobles en la cubierta, ¡y usted ha bajado hasta la bodega!";
			link.l1 = "La curiosidad mató al gato, ¡ja, ja!";
			link.l1.go = "OldSailor_7";
		break;

		case "OldSailor_7":
			dialog.text = "¿Le interesa la vida marítima?";
			link.l1 = "Parece que cada miembro de la tripulación se ha propuesto hacer de mí un verdadero marinero.";
			link.l1.go = "OldSailor_8";
		break;

		case "OldSailor_8":
			dialog.text = "No es de sorprender. Aunque para muchos de nosotros el mar trajo más penas que alegrías, amamos nuestro trabajo. Y a un marinero siempre le agrada ver a alguien nuevo mostrar interés genuino.";
			link.l1 = "...";
			link.l1.go = "OldSailor_9";
		break;

		case "OldSailor_9":
			dialog.text = "A ver, dígame: ¿cuál es la habilidad más importante para un capitán?";
			if (GetSummonSkillFromName(pchar, SKILL_Sailing) >= 6)
			{
				link.l1 = "La navegación. De ella depende el tamaño del barco que puede comandar.";
				link.l1.go = "OldSailor_10";
				notification("Prueba superada", SKILL_Sailing);
			}
			else
			{
				link.l1 = "No voy a mentir, no lo sé.";
				link.l1.go = "OldSailor_9_1";
				notification("Habilidad insuficiente (6)", SKILL_Sailing);
			}
		break;

		case "OldSailor_9_1":
			dialog.text = "No se preocupe, señor. Hable con la tripulación, explore el barco. Si encuentra la respuesta, le contaré algo muy curioso. Como a uno de los nuestros.";
			link.l1 = "Lo tendré en cuenta. ¡Hasta luego!";
			link.l1.go = "exit";
			NextDiag.TempNode = "OldSailor_again";
		break;

		case "OldSailor_10":
			dialog.text = "¡Correcto! Ahora otra pregunta con truco: ¿qué es mejor, velas cuadradas o de cuchillo?";
			link.l1 = "No me atrevo a juzgar, pero intuyo una trampa. Creo que cada una tiene su utilidad.";
			link.l1.go = "OldSailor_11";
		break;
		
		case "OldSailor_11":
			dialog.text = "¡Y otra vez, correcto! Las velas cuadradas son poderosas si el viento sopla por la popa. Pero una goleta puede ceñir y hasta adelantar con viento de través. Es un gusto ver que no ha perdido el tiempo, señor.";
			link.l1 = "No estoy seguro de que este conocimiento me sirva alguna vez... A menos que impresione a las damas de la alta sociedad haciéndome pasar por un verdadero marinero, ¡ja, ja!";
			link.l1.go = "OldSailor_12";
		break;

		case "OldSailor_12":
			dialog.text = "Oh, no sé, señor "+pchar.name+". Puede que sea usted un noble, pero trata con nosotros como un igual. Eso lo valoramos. Algo trama nuestro capitán. Una mala señal ha pasado entre ustedes.";
			link.l1 = "Qué tonterías. ¿De qué hablas, marinero?";
			link.l1.go = "OldSailor_13";
		break;

		case "OldSailor_13":
			dialog.text = "Dicen que no fue casual que enviara una carta a Capsterville con un barco de paso hace unos días\nY tampoco es casual que se pusiera a la deriva justo al final del viaje, cuando todos aúllan por pisar tierra firme.";
			link.l1 = "No me importan los rumores. ¿Para qué? Puedo preguntarle directamente. No le negará una respuesta honesta a un noble.";
			link.l1.go = "OldSailor_14";
		break;

		case "OldSailor_14":
			dialog.text = "No lo conoce, señor "+pchar.name+". Claro que lo negará. Y ahora está furioso — ha perdido la llave.";
			link.l1 = "¿La llave?";
			link.l1.go = "OldSailor_15";
		break;

		case "OldSailor_15":
			dialog.text = "La de su baúl en el camarote. Creo que no será difícil encontrarla. Debe de estar tirada por ahí.";
			link.l1 = "¿Buscar la llave? ¿Yo?";
			link.l1.go = "OldSailor_16";
		break;

		case "OldSailor_16":
			dialog.text = "Eso lo decide usted\nPor cierto, señor "+pchar.name+", ¿no le queda algo de ron? ¡No se lo habrá dado todo a Henry, ja, ja!";
			if (GetCharacterItem(pchar, "potionrum") >= 1)
			{
				link.l1 = "Sí. Tómalo.";
				link.l1.go = "OldSailor_17";
			}
			link.l2 = "Por desgracia, no. Fue un milagro que encontrara esas tres botellas.";
			link.l2.go = "OldSailor_16_1";
		break;
		
		case "OldSailor_16_1":
			dialog.text = "De verdad. Buena suerte, señor "+pchar.name+". Iré a seguir buscando a esa bribona a rayas.";
			link.l1 = "Suerte para ti también, marinero.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_OldSailorKey");
			PlaySound("ambient\Animals\Cat_01.wav");
		break;

		case "OldSailor_17":
			dialog.text = "¡Oh, qué ayuda! Se ha portado con honor con la tripulación, señor "+pchar.name+". Aquí tiene un pequeño regalo — ¡para la suerte!";
			link.l1 = "¿Una piedra con un agujero? Qué lindo.";
			link.l1.go = "OldSailor_18";
			GiveItem2Character(PChar, "talisman11");
			TakeItemFromCharacter(pchar, "potionrum");
		break;

		case "OldSailor_18":
			dialog.text = "Ríase, ríase. Pero yo le digo: en el mar, los talismanes no hacen daño.";
			link.l1 = "Son supersticiosos ustedes, los marinos. Suerte, marinero.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_OldSailorKey");
			PlaySound("ambient\Animals\Cat_01.wav");
		break;

		case "OldSailor_again":
			dialog.text = "¿Ya encontró la respuesta? ¿Cuál es la habilidad más importante para un capitán?";
			if (GetSummonSkillFromName(pchar, SKILL_Sailing) >= 6)
			{
				link.l1 = "Navegación. De ella depende el tamaño del barco que puede comandar.";
				link.l1.go = "OldSailor_10";
				notification("Prueba superada", SKILL_Sailing);
			}
			else
			{
				link.l1 = "Todavía no.";
				link.l1.go = "exit";
				NextDiag.TempNode = "OldSailor_again";
				notification("Habilidad insuficiente (6)", SKILL_Sailing);
			}
		break;
		
		// <-- Диалог со старым матросом в трюме
		
		// --> Диалог с матросом, которому нужен ящик с ядрами (Поль)
		case "SailorNeedBox":
			dialog.text = "¡Eh, muchacho!";
			link.l1 = "No te pareces a mi padre. Gracias a Dios.";
			link.l1.go = "SailorNeedBox_1";
		break;

		case "SailorNeedBox_1":
			dialog.text = "¡Ja! Estaría orgulloso de tener un hijo tan alto y noble. Pero solo puedo engendrar sal de la tierra como yo.";
			link.l1 = "Bueno, acepto el cumplido. ¿Qué sucede?";
			link.l1.go = "SailorNeedBox_2";
		break;

		case "SailorNeedBox_2":
			dialog.text = "Necesito una mano amiga, muchacho. Me ordenaron apilar balas junto a los cañones — por si nos metemos en problemas en estas aguas peligrosas. Pasé media guardia arrastrando estos bastardos de hierro desde la bodega, y mi espalda se rindió en la última caja.";
			link.l1 = "¿Por qué no simplemente pides ayuda a tus compañeros? Pensé que los marineros se ayudan entre sí.";
			link.l1.go = "SailorNeedBox_3";
		break;

		case "SailorNeedBox_3":
			dialog.text = "Una cosa que nuestra hermandad definitivamente odia es acarrear cargas pesadas sin buena razón. Hoy me tocó la paja más corta — arrastrar cajas de balas desde la bodega. Trabajo asqueroso, indigno de un marinero de mi calibre. ¿Pero qué se puede hacer?";
			link.l1 = "Deja de quejarte. Te ayudaré. Al menos veré esa bodega con la que me amenazan constantemente.";
			link.l1.go = "SailorNeedBox_4";
			if (IsCharacterPerkOn(pchar, "HT3"))
			{
				link.l2 = "(Atleta) ¿Ves esta espada ancha en mi cinturón? Pesa más que tú. Iré a buscar tus balas — no hay problema.";
				link.l2.go = "SailorNeedBox_4";
			}
			link.l3 = "No hago trabajo manual, marinero. Acarrea tus propias cajas.";
			link.l3.go = "SailorNeedBox_Net";
		break;

		case "SailorNeedBox_4":
			dialog.text = "Gracias, muchacho. ¡Solo no te vayas a romper la espalda!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SailorNeedBox_PrinestiBalls";
			AddDialogExitQuestFunction("SharlieTutorial_SailorNeedBoxOfBalls");
		break;
		
		case "SailorNeedBox_Net":
			DialogExit();
			
			LAi_CharacterDisableDialog(npchar);
			DelLandQuestMark(npchar);
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;
		
		case "SailorNeedBox_PrinestiBalls":	// espera las balas
			dialog.text = "¿Cómo va todo, muchacho?";
			if (CheckCharacterItem(PChar, "BoxOfBalls"))
			{
				link.l1 = "Aquí tienes tus balas. Pensé que serían más grandes.";
				link.l1.go = "SailorWantRum_PrinestiBalls_2";
			}
			if (PCharDublonsTotal() >= 30 && CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive") && !CheckAttribute(npchar, "SharlieTutorial_KaznacheyQuest_Poli"))
			{
				link.l2 = "¿Tu nombre es Paul, verdad?";
				link.l2.go = "BallsGold_2";
			}
			link.l3 = "Nos vemos.";
			link.l3.go = "exit";
			NextDiag.TempNode = "SailorNeedBox_PrinestiBalls";
		break;

		case "BallsGold_2":
			dialog.text = "Eh... s-sí.";
			link.l1 = "Tu nombre está en la lista que me dio monsieur Pinchon.";
			link.l1.go = "BallsGold_3";
		break;
		
		case "BallsGold_3":
			dialog.text = "Uf, ya pensé... Sí, Paul - ese soy yo entonces. ¿Cuánto tenéis ahí para mí?";
			if (PCharDublonsTotal() >= 20)
			{
				link.l1 = "20 doblones.";
				link.l1.go = "BallsGold_DatDeneg_gold20";
			}
			if (PCharDublonsTotal() >= 25)
			{
				link.l2 = "25 doblones.";
				link.l2.go = "BallsGold_DatDeneg_gold25";
			}
			if (PCharDublonsTotal() >= 30)
			{
				link.l3 = "30 doblones.";
				link.l3.go = "BallsGold_DatDeneg_gold30";
			}
			// link.l4 = "Necesito verificar todo. Volveré más tarde.";
			// link.l4.go = "BallsGold_DatDeneg_3";
		break;

		case "BallsGold_DatDeneg_gold20":
			dialog.text = "Gracias, muchacho.";
			link.l1 = "...";
			link.l1.go = "BallsGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(20);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			npchar.SharlieTutorial_KaznacheyQuest_Poli = true;
		break;
		
		case "BallsGold_DatDeneg_gold25":
			dialog.text = "Gracias, muchacho.";
			link.l1 = "...";
			link.l1.go = "BallsGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(25);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			npchar.SharlieTutorial_KaznacheyQuest_Poli = true;
		break;

		case "BallsGold_DatDeneg_gold30":
			dialog.text = "Gracias, muchacho.";
			link.l1 = "...";
			link.l1.go = "BallsGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(30);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.SharlieTutorial_KaznacheyQuest_Poli = true;
		break;
		
		case "BallsGold_DatDeneg_3":
			DialogExit();
			NextDiag.CurrentNode = "SailorNeedBox_PrinestiBalls";
		break;
		
		case "SailorWantRum_PrinestiBalls_2":
			dialog.text = "¡Y menos mal! Que llegue un regalito así al costado del barco, tal vez solo deje astillas. ¿Pero si atraviesa la popa y empieza a rebotar por toda la cubierta como una pelota?";
			link.l1 = "¿Te pasó algo así?";
			link.l1.go = "SailorWantRum_PrinestiBalls_3";
			TakeItemFromCharacter(pchar, "BoxOfBalls");
		break;

		case "SailorWantRum_PrinestiBalls_3":
			dialog.text = "Me pasó, muchacho. El hombre es bueno inventando instrumentos de muerte. Mira la metralla: no llega lejos, no atraviesa el casco, pero puede llevarse a una docena al otro mundo. O el cañón de bola doble — si acierta en las velas, las deja hechas jirones. ¡Y de las bombas ni hablo! Nunca vi una y que así siga. ¡Invento del diablo! Y encima caras.";
			link.l1 = "Ya me convencí del poder de las balas — a costa de tu pobre espalda.";
			link.l1.go = "SailorWantRum_PrinestiBalls_4";
		break;

		case "SailorWantRum_PrinestiBalls_4":
			dialog.text = "¡Sí que ayudaste! Y yo no me quedo atrás. Toma — una botella de ron de primera, casi llena, ¡ja ja!";
			link.l1 = "¿De dónde la sacaste? Solo escucho que el ron se acabó demasiado pronto a bordo. Con eso en las manos, podrías haber convencido a cualquier tripulante de cargar no solo una, sino todas las cajas del almacén.";
			link.l1.go = "SailorWantRum_PrinestiBalls_5";
			GiveItem2Character(PChar, "potionrum");
		break;

		case "SailorWantRum_PrinestiBalls_5":
			dialog.text = "Así son las cosas, muchacho. Gracias y hasta la próxima.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SailorNeedBox_PrinestiBalls";
			AddDialogExitQuestFunction("SharlieTutorial_SailorNeedBoxOfBallsFinal");
		break;
		
		// <-- Диалог с матросом, которому нужен ящик с ядрами
		
		// --> Диалог с офицером-торговцем, который торгует всяким
		case "OfficerTorgovets":
			dialog.text = "Ah, monsieur "+pchar.lastname+". Si planeaba dormir, no tuvo suerte. Nuestro artillero tomó su litera. Ya sabe, despertarlo no será posible.";
			link.l1 = "Cuando le conviene, ¡oye perfectamente!";
			link.l1.go = "OfficerTorgovets_1";
		break;

		case "OfficerTorgovets_1":
			dialog.text = "Eso no es nada. Oí que en la tripulación de Sharp había un artillero ciego. Dicen que apuntaba por el sonido del cañón.";
			link.l1 = "Hoy está usted sorprendentemente hablador, monsieur contramaestre.";
			link.l1.go = "OfficerTorgovets_2";
		break;

		case "OfficerTorgovets_2":
			dialog.text = "¡Y tengo razón para ello! Pronto tocaremos tierra, y eso significa — hora de convertir los productos restantes en brillantes pesos. ¡En el burdel de Saint-Pierre siempre los aprecian, ja ja!";
			link.l1 = "Sorprendente que sea usted, y no el tesorero, quien maneja el pequeño comercio a bordo.";
			link.l1.go = "OfficerTorgovets_3";
		break;

		case "OfficerTorgovets_3":
			dialog.text = "¡Él no sabe tratar con la gente! Para eso está el contramaestre — sabe hablar y actuar, ja ja. El tesorero también tiene su negocio, claro, pero yo no me meto en aguas turbias.";
			link.l1 = "¿Y qué está vendiendo hoy?";
			link.l1.go = "OfficerTorgovets_4";
		break;

		case "OfficerTorgovets_4":
			if (!CheckAttribute(npchar, "SharlieTutorial_question_0"))
			{
				dialog.text = "La última botella de ron en el barco, algunos amuletos útiles... ¡y voilà! Un mapa del tesoro completo.";
				link.l1 = "¡Debería ser comerciante, no contramaestre! Muéstrame lo que tienes.";
				npchar.SharlieTutorial_question_0 = true;
			}
			else
			{
				dialog.text = "¿Algo más?";
				link.l1 = "Muéstrame lo que tienes.";
			}
			link.l1.go = "OfficerTorgovets_5";
			if (!CheckAttribute(npchar, "SharlieTutorial_question_1"))
			{
				link.l2 = "¿Amuletos? ¿Como el que cuelga en su pecho?";
				link.l2.go = "OfficerTorgovets_6_question_1_1";
			}
			if (!CheckAttribute(npchar, "SharlieTutorial_question_2"))
			{
				link.l3 = "¿Perdón... un mapa del tesoro?";
				link.l3.go = "OfficerTorgovets_6_question_2_1";
			}
			link.l4 = "Quizás en otra ocasión.";
			link.l4.go = "exit";
			NextDiag.TempNode = "OfficerTorgovets_4";
		break;
		
		case "OfficerTorgovets_5":
			DialogExit();
			NextDiag.CurrentNode = "OfficerTorgovets_4";
			sld = ItemsFromID("map_full");
			sld.price = 4000;
			LaunchItemsTrade(NPChar, 0);
		break;
		
		case "OfficerTorgovets_6_question_1_1":
			dialog.text = "Ah, buen ojo, monsieur. Sí, la 'Cabeza de Coral' — cosa útil. Especialmente para mí. Si llegara el momento, Dios no lo quiera, de liderar un abordaje — con ella organizo a los hombres en un instante.";
			link.l1 = "¿De verdad cree en eso?";
			link.l1.go = "OfficerTorgovets_6_question_1_2";
		break;

		case "OfficerTorgovets_6_question_1_2":
			dialog.text = "No necesito creer. Así son las reglas del Caribe y de la vida marina. Los amuletos son cosas útiles. Así que si va a quedarse por aquí, le aconsejo llevar un par para distintas ocasiones.";
			link.l1 = "...";
			link.l1.go = "OfficerTorgovets_4";
			npchar.SharlieTutorial_question_1 = true;
		break;

		case "OfficerTorgovets_6_question_2_1":
			dialog.text = "Oh, sí. No son raras en el Caribe. Algunos tienen suerte — y hacen una gran fortuna. Luego hay dos caminos: pagar impuestos y vivir en paz mucho tiempo, o esconder el oro en una cueva — y de ellos solo queda una tumba, el tesoro... y un pedazo de papel.";
			link.l1 = "¿Así de simple?";
			link.l1.go = "OfficerTorgovets_6_question_2_2";
		break;

		case "OfficerTorgovets_6_question_2_2":
			dialog.text = "No del todo. Los mapas son caros, y atraen a otros cazadores como usted. Y a veces el botín apenas vale el esfuerzo. Incluso al gran Albert Blackwood no le fue fácil al principio. Haga del tesoro su profesión — y cuanto más encuentre, mayores serán las recompensas. ¡Y si compra un amuleto de suerte — aún mejor!";
			link.l1 = "...";
			link.l1.go = "OfficerTorgovets_4";
			npchar.SharlieTutorial_question_2 = true;
		break;
		// <-- Диалог с офицером-торговцем, который торгует всяким
		
		// --> Диалог с офицером-казначеем
		case "OfficerKaznachey":
			dialog.text = "¡Monsieur "+pchar.lastname+"! Un momento.";
			link.l1 = "¿Otra vez va a sermonearme, monsieur Pinchon? ¡No toqué su preciosa tinta!";
			link.l1.go = "OfficerKaznachey_2";
		break;

		case "OfficerKaznachey_2":
			dialog.text = "¿Y con qué escribe entonces a escondidas en su libretita? ¿Agua bendita? No había tinta en la lista de pertenencias de pasajeros. En fin, ahora tiene problemas más serios.";
			link.l1 = "...";
			link.l1.go = "OfficerKaznachey_3";
		break;

		case "OfficerKaznachey_3":
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass")) sStr = "Y además — doscientos por el cabrestante dañado. El cabo del ancla se rompió.";
			dialog.text = "Le recuerdo que aún debe treinta pesos al tesoro del barco — por dañar un barril de agua de lluvia. Su cómico intento de lavar la camisa pudo haber costado más si no hubiera vuelto a llover. "+sStr+"";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass"))
			{
				if (sti(pchar.Money) >= 230)
				{
					link.l1 = "Lo que me faltaba — deudas nada más llegar. Tome.";
					link.l1.go = "OfficerKaznachey_4";
				}
			}
			else
			{
				if (sti(pchar.Money) >= 30)
				{
					link.l1 = "Lo que me faltaba — deudas nada más llegar. Tome.";
					link.l1.go = "OfficerKaznachey_4";
				}
			}
			link.l2 = "¿Y eso es todo? No es una deuda de juego, desde luego. Estoy ocupado. Tendrá que esperar hasta llegar al puerto.";
			link.l2.go = "OfficerKaznachey_3_1";
		break;

		case "OfficerKaznachey_3_1":
			dialog.text = "Qué lástima. Entonces, directo al grano — tengo un trabajo para usted.";
			link.l1 = "¿No se le da muy bien tratar con la gente, verdad?";
			link.l1.go = "OfficerKaznachey_6";
		break;
		
		case "OfficerKaznachey_4":
			dialog.text = "Un momento, déjeme contar.";
			link.l1 = "Después de la cena no olvide contar también las migas de pan que dejé en la mesa.";
			link.l1.go = "OfficerKaznachey_5";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass")) AddMoneyToCharacter(pchar, -230);
			else AddMoneyToCharacter(pchar, -30);
		break;

		case "OfficerKaznachey_5":
			dialog.text = "Felicidades. Ahora el tesoro del barco no tiene más preguntas para usted. Por ahora\nVamos al grano — tengo un trabajo para usted.";
			link.l1 = "No se le da muy bien tratar con la gente, ¿verdad?";
			link.l1.go = "OfficerKaznachey_6";
		break;

		case "OfficerKaznachey_6":
			dialog.text = "Con la gente — no mucho. Pero sé contar bien\nY usted, monsieur "+pchar.lastname+", ¿sabe contar?";
			if (IsCharacterPerkOn(pchar, "HT2"))
			{
				link.l1 = "(Contable) Estoy familiarizado con libros de cuentas, letras de cambio, y hasta con el concepto de cero.";
				link.l1.go = "OfficerKaznachey_7";
			}
			else
			{
				link.l1 = "Lo suficiente para estirar la escasa pensión paterna hasta fin de temporada.";
				link.l1.go = "OfficerKaznachey_8";
			}
		break;

		case "OfficerKaznachey_7":
			dialog.text = "¡Ohhh! Lástima que no me lo dijera antes — este viaje habría sido mucho más interesante.";
			link.l1 = "¿Mencionó algo sobre trabajo?";
			link.l1.go = "OfficerKaznachey_9";
		break;

		case "OfficerKaznachey_8":
			dialog.text = "Por su propio bien — espero que nunca se convierta en propietario de un barco. Arruinará no solo a usted, sino también a todos los que estén a bordo.";
			link.l1 = "¿Mencionó algo sobre trabajo?";
			link.l1.go = "OfficerKaznachey_9";
		break;
		
		case "OfficerKaznachey_9":
			dialog.text = "Sí. No sé si lo sabe, pero el tesorero y el médico son los segundos después del capitán\n"+
			"Salir al mar sin estos dos es arriesgar el dinero, y sin dinero un barco es solo un pedazo de madera muy caro\n"+
			"Sin un tesorero, incluso una pequeña balandra puede arruinar a su capitán. Y el primer combate sin médico puede destruir a toda la tripulación, lo que inicia un tedioso y muy costoso proceso de reclutamiento y entrenamiento\n"+
			"Por suerte para ambos, yo desempeño ambos cargos. Por eso puedo hacer negocios privados y usar pequeños servicios de la tripulación\n"+
			"Por supuesto, estos servicios se pagan generosamente — y ahora es un buen momento para hacerlo\n"+
			"Quiero que tome esta lista, un cofre de doblones — y pague a los miembros de la tripulación según corresponda\n"+
			"¡Exactamente según la lista! Por eso le pregunté si sabe contar.";
			link.l1 = "¿Y por qué no lo hace usted mismo? Al fin y al cabo, si la gente espera el pago — que vengan ellos.";
			link.l1.go = "OfficerKaznachey_10";
		break;

		case "OfficerKaznachey_10":
			dialog.text = "Tengo demasiadas cosas que hacer. Faltan pocos días para el final del viaje, y pronto habrá una cola de cien personas exigiendo su salario.";
			link.l1 = "Mencionó doblones...";
			link.l1.go = "OfficerKaznachey_11";
		break;

		case "OfficerKaznachey_11":
			dialog.text = "Moneda de oro española. Moneda sólida y verdadero indicador de riqueza. Los servicios más raros, caros y necesarios — solo por ellos\n"+
			"Se guardan en cofres como este, por comodidad.";
			link.l1 = "¿Y qué recibiré a cambio?";
			link.l1.go = "OfficerKaznachey_12";
		break;

		case "OfficerKaznachey_12":
			if (IsCharacterPerkOn(pchar, "HT2"))
			{
				dialog.text = "(Contable) 150 pesos, y 5 doblones extra por ser casi colega. Y también podrá cambiar pesos por doblones a buen tipo de cambio.";
			}
			else
			{
				dialog.text = "150 pesos y la posibilidad de cambiar pesos por doblones. No es mucho, pero el trabajo es muy simple.";
			}
			link.l1 = "Bien. Deme la lista y el cofre.";
			link.l1.go = "OfficerKaznachey_11_agree";
			link.l2 = "Me temo que ese trabajo no es para mí. Adiós, monsieur Pinchon.";
			link.l2.go = "OfficerKaznachey_11_otkaz";
		break;
		
		case "OfficerKaznachey_11_otkaz":
			dialog.text = "Está en su derecho. En ese caso, no me distraiga, monsieur "+pchar.lastname+".";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			DelLandQuestMark(npchar);
		break;

		case "OfficerKaznachey_11_agree":
			if(GetItemsWeight(pchar) + sti(Items[GetItemIndex("Chest")].weight) > GetMaxItemsWeight(pchar))
			{
				dialog.text = "Adelante. Pero por el amor de Dios — no olvide sacar los doblones del cofre, siga estrictamente la lista, y no se le ocurra quedarse con nada. También espero que me devuelva el cofre vacío\n"+
				"Y no se esfuerce demasiado, monsieur. ¿Por qué carga con tantas cosas? Le recomiendo dejar parte en algún cofre.";
			}
			else
			{
				dialog.text = "Adelante. Pero por el amor de Dios — no olvide sacar los doblones del cofre, siga estrictamente la lista, y no se le ocurra quedarse con nada. También espero que me devuelva el cofre vacío.";
			}
			link.l1 = "Como usted diga. Hasta pronto, monsieur Pinchon.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_QuestRazdatZoloto");
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass")) AddQuestRecordInfo("SharlieTutorial_ListOfSailors", "1");
			else AddQuestRecordInfo("SharlieTutorial_ListOfSailors", "2");
			GiveItem2Character(PChar, "chest");
			if (!isMultiObjectKnown("gold_dublon"))
			{
				SetAlchemyRecipeKnown("gold_dublon");
				SetAlchemyRecipeKnown("Chest");
			}
		break;
		
		case "OfficerKaznachey_12_Wait":
			dialog.text = "¿Qué tal? ¿Distribuyó el pago? ¿Entregó todo? ¿Los doblones restantes, el cofre vacío?";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuest") && sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) == 3 && CheckCharacterItem(PChar, "chest_open") && GetCharacterItem(pchar, "gold_dublon") >= 18)
			{
				link.l1 = "Todo listo.";
				link.l1.go = "OfficerKaznachey_13";
			}
			link.l2 = "Aún no, monsieur Pinchon.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OfficerKaznachey_12_Wait";
		break;

		case "OfficerKaznachey_13":
			dialog.text = "Veamos...";
			link.l1 = "...";
			link.l1.go = "OfficerKaznachey_14";
		break;

		case "OfficerKaznachey_14":
			addGold = GetCharacterItem(pchar, "gold_dublon");
			if (addGold >= 18 && addGold <= 39)
			{
				dialog.text = "Y decían que sabía contar. Aquí hay menos de lo debido. Eso significa que mi contabilidad acaba de complicarse, y usted me trajo un nuevo problema en vez de resolver el actual\n"+
				"Por lo tanto, monsieur "+pchar.lastname+", no recibirá pago.";
				link.l1 = "¿Y aún así cambiará mis doblones?";
				link.l1.go = "OfficerKaznachey_15_gold_115";
			}
			if (addGold >= 41)
			{
				dialog.text = "Y decían que sabía contar. Aquí hay más de lo debido. Eso significa que mi contabilidad acaba de complicarse, y usted me trajo un nuevo problema en vez de resolver el actual\n"+
				"Por lo tanto, monsieur "+pchar.lastname+", no recibirá pago.";
				link.l1 = "¿Y qué hay del cambio?";
				link.l1.go = "OfficerKaznachey_15_gold_115";
			}
			if (addGold == 40)
			{
				if (IsCharacterPerkOn(pchar, "HT2"))
				{
					dialog.text = "Todo en orden. Es agradable ver que la nueva generación sabe manejar los números. Gracias, monsieur "+pchar.lastname+". Aquí tiene su pago — y una pequeña bonificación, como casi colega.";
					link.l1 = "¿Y sobre el cambio?";
					link.l1.go = "OfficerKaznachey_15_gold_100";
					AddItems(pchar, "gold_dublon", 5);
				}
				else
				{
					dialog.text = "Todo en orden. Es agradable ver que la nueva generación se toma en serio el dinero. Gracias, monsieur "+pchar.lastname+". Aquí tiene su pago.";
					link.l1 = "¿Todavía cambia doblones?";
					link.l1.go = "OfficerKaznachey_15_gold_105";
				}
				AddMoneyToCharacter(pchar, 300);
				AddCharacterSkillPoints(pchar, "Commerce", 1);
			}
			DelLandQuestMark(npchar);
			TakeItemFromCharacter(pchar, "chest_open");
			RemoveDublonsFromPCharTotal(addGold);
			AddItems(npchar, "gold_dublon", 100);
			pchar.questTemp.SharlieTutorial_KaznacheyQuestCompleted = true;
			DeleteAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive");
			npchar.Merchant.type = "SharlieTurorialK";
			pchar.SharlieTutorial.FullyCompleted = sti(pchar.SharlieTutorial.FullyCompleted) + 1;
		break;
		
		case "OfficerKaznachey_15_gold_115":
			dialog.text = "¿Por qué no? Ciento quince pesos por doblón. Acuda a mí si le interesa.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
			npchar.questTemp.GoldPrice = 115;
		break;

		case "OfficerKaznachey_15_gold_105":
			dialog.text = "Por supuesto. Ciento cinco pesos por doblón. Acuda a mí si le interesa\n"+
			"Y permítame un consejo: si, Dios no lo quiera, el destino lo pone al mando de un barco, contrate a un tesorero de inmediato. Incluso un especialista mediocre le ahorrará una fortuna.";
			link.l1 = "Gracias, monsieur Pinchon.";
			link.l1.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
			npchar.questTemp.GoldPrice = 105;
		break;

		case "OfficerKaznachey_15_gold_100":
			dialog.text = "¡Por supuesto! Cien pesos por doblón — un tipo de cambio justo. En los bancos del Caribe le habrían cobrado más\n"+
			"Y permítame un consejo: si, Dios no lo quiera, el destino lo pone al mando de un barco, contrate a un tesorero de inmediato. Incluso un especialista mediocre le ahorrará una fortuna.";
			link.l1 = "Gracias, monsieur Pinchon.";
			link.l1.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
			npchar.questTemp.GoldPrice = 100;
		break;

		case "OfficerKaznachey_16_Proval": // Если не выполнил задание, то отбирает дублоны
			dialog.text = "¿Descansando, monsieur "+pchar.lastname+"?";
			link.l1 = "¿También lo enviaron a la bodega?";
			link.l1.go = "OfficerKaznachey_16_Proval_2";
		break;

		case "OfficerKaznachey_16_Proval_2":
			dialog.text = "¡Soy el médico del barco, "+pchar.lastname+"! Pronto el comedor estará lleno de heridos, y veré más sangre que cualquier participante de la batalla. E incluso si no fuera médico, solo tesorero — en combate también me alinearía como todos. No, el único que fue enviado a descansar en la acogedora bodega es usted.";
			link.l1 = "Entonces, ¿qué hace usted aquí?";
			link.l1.go = "OfficerKaznachey_16_Proval_3";
		break;

		case "OfficerKaznachey_16_Proval_3":
			dialog.text = "La batalla no empezará hasta dentro de un par de horas, así que es el momento perfecto para cerrar las cuentas diarias. Tenéis mi cofre con doblones, de Maure. Tened la amabilidad de devolverlo.";
			if (GetCharacterItem(pchar, "gold_dublon") >= 1 || GetCharacterItem(pchar, "chest") >= 1 || GetCharacterItem(pchar, "chest_open") >= 1)
			{
				link.l1 = "Tomadlo. Y no mostréis más vuestra cara por aquí abajo.";
				link.l1.go = "OfficerKaznachey_16_Proval_4";
			}
			else
			{
				link.l1 = "Dejé vuestros trastos en otro lugar.";
				link.l1.go = "OfficerKaznachey_16_Proval_5";
			}
		break;
		
		case "OfficerKaznachey_16_Proval_4":
			addGold = GetCharacterItem(pchar, "gold_dublon");
			dialog.text = "No tenía intención de hacerlo. No soy una rata de tierra - mi lugar no está en la bodega. Adiós.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_TrumLoad_4");
			if (GetCharacterItem(pchar, "gold_dublon") >= 1 || GetCharacterItem(pchar, "chest") >= 1) ChangeCharacterComplexReputation(pchar, "nobility", -3);
			else ChangeCharacterComplexReputation(pchar, "nobility", -6);
			RemoveDublonsFromPCharTotal(addGold);
			AddItems(npchar, "gold_dublon", addGold);
			TakeItemFromCharacter(pchar, "chest");
			TakeItemFromCharacter(pchar, "chest_open");
		break;
		
		case "OfficerKaznachey_16_Proval_5":
			dialog.text = "En otro lugar... Lo discutiremos después de la batalla - en presencia del capitán. Hasta entonces.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_TrumLoad_4");
			ChangeCharacterComplexReputation(pchar, "nobility", -6);
		break;
		
		case "TreasurerTrade":
			dialog.text = "¿Interesado en doblones, monsieur "+pchar.lastname+"?";
			link.l1 = "Vamos a negociar.";
			link.l1.go = "TreasurerTrade_1";
			link.l2 = "Por ahora no.";
			link.l2.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
		break;

		
		case "TreasurerTrade_1":
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
			NextDiag.CurrentNode = "TreasurerTrade";
		break;
		// <-- Диалог с офицером-казначеем
		
		// --> Матрос сообщает о приближающихся кораблях
		case "Sailor_Trevoga":
			dialog.text = "¡Capitán, alerta! ¡Piratas en el horizonte!";
			link.l1 = "...";
			link.l1.go = "Sailor_Trevoga_2";
			SetCameraDialogMode(npchar);
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Captain"));
			PlaySound("Ship\rynda_alarm.wav");
		break;

		case "Sailor_Trevoga_2":
			StartInstantDialog("SharlieTutorial_Captain", "Sailor_Trevoga_3", "Quest\Sharlie\Tutorial.c");
		break;

		case "Sailor_Trevoga_3":
			dialog.text = "Alonso, acompaña cortésmente al monsieur "+pchar.lastname+" a la bodega. Y asegúrate de que monsieur Dreusac se despierte y prepare las piezas para el combate.";
			link.l1 = "¡Capitán, estoy listo para luchar! ¡Un noble no puede...";
			link.l1.go = "Sailor_Trevoga_4_fencing";
			link.l2 = "Si puedo ayudar en algo...";
			link.l2.go = "Sailor_Trevoga_4_leadership";
			link.l3 = "¿Entonces no habrá borgoña?";
			link.l3.go = "Sailor_Trevoga_4_fortune";
		break;

		case "Sailor_Trevoga_4_fencing":
			dialog.text = "Alonso, sácalo de aquí. ¡A trabajar, holgazanes! ¡Izad las velas!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga_7");
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;

		case "Sailor_Trevoga_4_leadership":
			dialog.text = "Alonso, sácalo de aquí. ¡A trabajar, holgazanes! ¡Izad las velas!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga_7");
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;
		
		case "Sailor_Trevoga_4_fortune":
			dialog.text = "Alonso, sácalo de aquí. ¡A trabajar, holgazanes! ¡Izad las velas!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga_7");
			AddCharacterSkillPoints(pchar, "Fortune", 1);
		break;
		// <-- Матрос сообщает о приближающихся кораблях
		
		// --> Диалог с пиратом в трюме
		case "EnemyPirate_1":
			dialog.text = "¡Demonios! ¡Qué testarudos!";
			link.l1 = "...";
			link.l1.go = "EnemyPirate_2";
			//PlaySound("VOICE\Russian\OliverTrast01.wav");
			PlaySound("VOICE\Spanish\OliverTrast01.wav"); //вставить для испанской версии
			PlaySound("interface\abordage.wav");
			PlaySound("interface\abordage.wav");
		break;

		case "EnemyPirate_2":
			dialog.text = "¿Y tú qué haces aquí? ¿Has abandonado a los tuyos y te escondes de la pelea, rata de bodega? ¡Te voy a sacar las tripas ahora mismo!";
			link.l1 = "Mal lugar elegiste para esconderse. ¡Te las sacaré yo a ti!";
			link.l1.go = "EnemyPirate_3_Fencing";
			link.l2 = "A duras penas te sostienes, y gran parte de esa sangre ni siquiera es tuya.";
			link.l2.go = "EnemyPirate_3_Leadership";
			if (IsCharacterPerkOn(pchar, "HT1"))
			{
				link.l3 = "(Duelista) Esto es justo lo que necesitaba.";
				link.l3.go = "EnemyPirate_3_Duelyant";
			}
		break;

		case "EnemyPirate_3_Fencing":
			dialog.text = "Je je. Vamos, intenta, mocoso.";
			link.l1 = "...";
			link.l1.go = "EnemyPirate_4";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;

		case "EnemyPirate_3_Leadership":
			dialog.text = "Je je. Entonces, no tengo nada que perder.";
			link.l1 = "...";
			link.l1.go = "EnemyPirate_4";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "EnemyPirate_3_Duelyant":
			dialog.text = "¿Qué dices?";
			link.l1 = "Dos meses. ¡Dos meses sin desenfundar mi espada! ¡A bailar!";
			link.l1.go = "EnemyPirate_4";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;
		
		case "EnemyPirate_4":
			DialogExit();
			AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_2");
		break;
		
		// <-- Диалог с пиратом в трюме
		
		// --> Диалог с выжившим матросом
		case "SailorAlive_1":
			dialog.text = "Al menos tú estás vivo... Yo ya no. Me han dado bien en el timón...";
			link.l1 = "¿Qué ha pasado?";
			link.l1.go = "SailorAlive_2";
			DelLandQuestMark(npchar);
		break;

		case "SailorAlive_2":
			dialog.text = "Un abordaje. ¡Arrggh! ¡Malditos testarudos!\nEscucha con atención: hemos defendido la cubierta de artillería, pero arriba la fiesta apenas empieza. Te aseguro que pronto volverán a bajar. ¡Toma la escopeta de metralla! ¡Diablos, cuidado! ¡Está cargada!";
			if (IsCharacterPerkOn(pchar, "HT4"))
			{
				link.l1 = "(Tirador) No te preocupes por mí. Al que se asome le hago un colador.";
			}
			else link.l1 = "...";
			link.l1.go = "SailorAlive_3";
		break;

		case "SailorAlive_3":
			dialog.text = "Es metralla. Si apuntas bien, puedes tumbar a dos o tres de un tiro.\nConfío en ti, "+pchar.name+". Cuando los detengas, revisa los cuerpos. Tal vez encuentres algo para mí... o no podré ayudarte más.";
			link.l1 = "Aguanta, Alonso. ¡Ya vienen!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_5");
			GiveItem2Character(PChar, "pistol3");
			EquipCharacterByItem(PChar, "pistol3");
			AddItems(pchar, "grapeshot", 5);
			AddItems(pchar, "GunPowder", 5);
			LAi_GunSetChargeQuant(pchar, GUN_ITEM_TYPE, 1);
		break;

		case "SailorAlive_11":
			dialog.text = "Bien... Buen trabajo, "+pchar.name+". ¿Encontraste algo para mí?";
			if (CheckCharacterItem(PChar, "quest_potion"))
			{
				link.l1 = "Creo que esto servirá. Aunque tiene pinta sospechosa.";
				link.l1.go = "SailorAlive_12";
			}
			link.l2 = "¡Sigo buscando!";
			link.l2.go = "exit";
			NextDiag.TempNode = "SailorAlive_11";
		break;

		case "SailorAlive_12":
			dialog.text = "¡Y sabe bastante bien, ja ja! Gracias, "+pchar.name+". Y esos tres los tumbaste con estilo. Si de verdad eres un noble, entonces toma el mando. Juntos mantendremos la cubierta, y si los de arriba aguantan — ¡el día será nuestro!";
			link.l1 = "...";
			//link.l1.go = "exit";
			link.l1.go = "SailorAlive_13";
			//AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_7");
			TakeItemFromCharacter(pchar, "quest_potion");
			PlaySound("Ambient\Tavern\glotok_001.wav");
			DelLandQuestMark(npchar);
		break;

		case "SailorAlive_13":
			/*if (CheckAttribute(npchar, "fighter"))
			{
				dialog.text = "Eso está mejor. ¿Ya cargaste la escopeta de metralla?";
				link.l1 = "Estoy en ello... ¿Y por qué de pronto se hizo tanto silencio?";
				link.l1.go = "SailorAlive_14";
				SetMusic("");
			}
			else
			{
				dialog.text = "Si de verdad eres un noble, entonces toma el mando.";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "SailorAlive_13";
			}*/
			dialog.text = "Eso está mejor. ¿Ya cargaste la escopeta de metralla?";
			link.l1 = "Estoy en ello... ¿Y por qué de pronto se hizo tanto silencio?";
			link.l1.go = "SailorAlive_14";
			SetMusic("");
			LAi_SetActorType(npchar);
			LAi_ActorSetGroundSitMode(npchar);
			LAi_ActorAnimation(npchar, "ground_standup", "1", -1);
		break;

		case "SailorAlive_14":
			dialog.text = "Para darle más dramatismo. Ya viene lo bueno.";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_8");
		break;
		// <-- Диалог с выжившим матросом
		
		// --> Диалог с Алонсо после боя
		case "AfterBattle_Alonso_1":
			dialog.text = "Y aquí terminamos donde empezamos. Gracias por salvarme el pellejo, "+pchar.name+".";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_Ranen"))
			{
				link.l1 = "Creo que estamos a mano. Ni siquiera recuerdo cómo me sacaste de ahí.";
			}
			else
			{
				link.l1 = "Creo que estamos a mano. Si no fuera por ti y los muchachos, me habría quedado allí.";
			}
			link.l1.go = "AfterBattle_Alonso_2";
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "tutorial_4", "", -1);
			CharacterTurnByLoc(pchar, "quest", "quest6");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "tutorial_5", "", -1);
			CharacterTurnByLoc(npchar, "quest", "quest7");
		break;

		case "AfterBattle_Alonso_2":
			dialog.text = "Podrías haberte quedado en la bodega, como se te ordenó. Lástima que el capitán no viviera para darte una buena reprimenda.";
			link.l1 = "Tuvimos que sacarlo de debajo de una montaña de cadáveres. ¿Cuántos bastardos logró abatir?";
			link.l1.go = "AfterBattle_Alonso_3";
		break;

		case "AfterBattle_Alonso_3":
			dialog.text = "Alguien dijo que mató a tres. Otros, que a una docena. Creo que sólo el diablo llevó la cuenta exacta.";
			link.l1 = "Aún no me explicaste cómo ocurrió todo esto.";
			link.l1.go = "AfterBattle_Alonso_4";
		break;

		case "AfterBattle_Alonso_4":
			dialog.text = "¿Qué hay que explicar? Ni nuestros cañones de dieciséis libras nos salvaron de un solo bergantín pirata. Eso es un barco hecho para el combate\n"+
			"Se nos echó encima en un suspiro y, mientras girábamos, nos acribilló con metralla y se lanzó al abordaje. Tendrías que haber visto la cubierta — no quedaba nada que llevarle al médico\n"+
			"Lo peor de pelear con piratas es que no hay ganancia. Unos miserables. Ni siquiera pudimos quedarnos con su bergantín.";
			link.l1 = "¿Y ahora qué pasará?";
			link.l1.go = "AfterBattle_Alonso_5";
		break;

		case "AfterBattle_Alonso_5":
			dialog.text = "El barco sigue a flote y tenemos suficientes hombres para llevarte a Saint-Pierre según lo previsto, donde yo buscaré nuevo capitán y tú hallarás a tu hermano y le contarás tus aventuras. Y lo que venga después... sólo Dios lo sabe.\n"+
			"Pero de algo estoy seguro — aquí te vas a quedar. Nada mal para una rata de tierra, "+pchar.name+".";
			link.l1 = "...";
			link.l1.go = "AfterBattle_Alonso_6";
		break;

		case "AfterBattle_Alonso_6":
			dialog.text = "¡Vaya! Ya te está dando vueltas el estómago. No te cortes. Es el miedo saliendo. ¡Bienvenido al Caribe!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_SeaNearMartinique");
		break;
		
		
		// <-- Диалог с Алонсо после боя
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}