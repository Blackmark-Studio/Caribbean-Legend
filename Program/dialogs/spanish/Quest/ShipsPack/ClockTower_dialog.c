int iClockSP4PseudoGlobal = SOUND_INVALID_ID;

void ProcessDialogEvent()
{
	ref NPChar, sld, realShip;
	aref Link, NextDiag, arTmp;
	int i, n, NextMonth, idx;
	string sTemp, sStr, Month, NationName, shipType;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	if (HasSubStr(Dialog.CurrentNode, "chosenIdx/"))
	{
		Dialog.tmpIdx = FindStringAfterChar(Dialog.CurrentNode, "/");
		Dialog.CurrentNode = FindStringBeforeChar(Dialog.CurrentNode, "/");
	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Что вам надо?";
			link.l1 = "Ничего.";
			link.l1.go = "exit";
		break;
		
		// Диалог с Йоханом
		case "ClockTower_Johan_1":
			dialog.text = "Halte, "+GetTitle(NPChar, true)+". Passage interdit au-delà de ce point.";
			link.l1 = "Pourquoi donc?";
			link.l1.go = "ClockTower_Johan_2";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Johan_2":
			dialog.text = "Vous voyez cette tour? Bureau de la Compagnie des Indes occidentales. Département d'enregistrement des navires et archives. Entrée sur rendez-vous uniquement.";
			link.l1 = "Et comment obtient-on un rendez-vous?";
			link.l1.go = "ClockTower_Johan_3";
		break;

		case "ClockTower_Johan_3":
			dialog.text = "Ceux qui ont besoin de savoir le savent. Le mynheer directeur ne travaille pas avec n'importe qui.";
			link.l1 = "'Mynheer directeur'? Qui est-ce?";
			link.l1.go = "ClockTower_Johan_4";
		break;

		case "ClockTower_Johan_4":
			dialog.text = "L'intendant van Doorn. Ce n'est peut-être pas vraiment un directeur, mais tout le monde l'appelle comme ça. Il travaille ici depuis dix ans — il a mis de l'ordre partout. Maintenant, tous les navires des Caraïbes passent par son bureau.";
			link.l1 = "Tous les navires? Même les vaisseaux de guerre?";
			link.l1.go = "ClockTower_Johan_5";
		break;

		case "ClockTower_Johan_5":
			dialog.text = "Seulement les meilleurs navires et les capitaines les plus fortunés. Être client de notre bureau est un grand honneur!";
			link.l1 = "Quel genre de services offrez-vous?";
			link.l1.go = "ClockTower_Johan_6";
		break;

		case "ClockTower_Johan_6":
			dialog.text = "Je ne suis pas au courant des détails — je garde simplement l'entrée. Mais j'ai entendu dire que les gens repartent satisfaits.";
			link.l1 = "Impressionnant.";
			link.l1.go = "ClockTower_Johan_7";
		break;

		case "ClockTower_Johan_7":
			dialog.text = "Et je vais vous dire autre chose. Vous voyez cette horloge? Une merveille européenne — vous n'en trouverez pas de pareille dans notre coin perdu. Le mynheer directeur l'entretient personnellement.";
			link.l1 = "Peut-être pourrions-nous nous arranger?";
			link.l1.go = "ClockTower_Johan_8_1";
			link.l2 = "Il n'y a vraiment rien que je puisse faire pour entrer?";
			link.l2.go = "ClockTower_Johan_8_2";
		break;

		case "ClockTower_Johan_8_1":
			dialog.text = "Je ne prends pas de pots-de-vin!";
			link.l1 = "Excusez-moi. Vous êtes un bon homme. Comment vous appelez-vous?";
			link.l1.go = "ClockTower_Johan_9";
		break;

		case "ClockTower_Johan_9":
			dialog.text = ""+npchar.name+"... Écoutez... Je comprends que vous n'êtes pas d'ici. Mais ici, il y a de l'ordre. Le mynheer directeur dit toujours : montrez de la faiblesse une fois, et notre tour s'effondre. Vous voulez entrer? Aidez la ville — et on vous remarquera.";
			link.l1 = "Je vois. Au revoir, soldat.";
			link.l1.go = "ClockTower_Johan_11";
		break;

		case "ClockTower_Johan_8_2":
			dialog.text = "Eh bien, je ne sais pas. Le mynheer directeur récompense les amis de Willemstad. Aidez la ville — et on vous remarquera. Je comprends que vous n'êtes pas d'ici. Mais ici, il y a de l'ordre. Le mynheer directeur dit toujours : montrez de la faiblesse une fois, et notre tour s'effondre.";
			link.l1 = "Je vois. Et quel est votre nom?";
			link.l1.go = "ClockTower_Johan_10";
		break;

		case "ClockTower_Johan_10":
			dialog.text = ""+npchar.name+", "+GetTitle(NPChar, true)+".";
			link.l1 = "Quant à moi, je suis "+GetTitle(NPChar, false)+" "+GetFullName(pchar)+". Au revoir, soldat.";
			link.l1.go = "ClockTower_Johan_11";
		break;
		
		case "ClockTower_Johan_11":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_Quest_1");
		break;
		
		case "ClockTower_Johan_repeat":
			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) >= 51)
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+"!";
				link.l1 = "¿Ha ocurrido algo?";
				link.l1.go = "ClockTower_Johan_22";
				Notification_ReputationNation(true, 51, HOLLAND);
			}
			else 
			{
				dialog.text = ""+Greeting(true)+", "+GetTitle(NPChar, true)+". ¿Puedo ayudarlo en algo?";
				link.l1 = "No, "+npchar.name+". Continúa.";
				link.l1.go = "exit";
				NextDiag.TempNode = "ClockTower_Johan_repeat";
				Notification_ReputationNation(false, 51, HOLLAND);
			}
		break;
		
		case "ClockTower_Johan_21":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+"!";
			link.l1 = "¿Ha ocurrido algo?";
			link.l1.go = "ClockTower_Johan_22";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Johan_22":
			dialog.text = "Enhorabuena. Tienes una cita programada.";
			link.l1 = "¿Una cita? ¿Con quién?";
			link.l1.go = "ClockTower_Johan_23";
		break;

		case "ClockTower_Johan_23":
			dialog.text = "Con el adjunto del mynheer director. Se enteró de tu ayuda a la ciudad y me ordenó invitarte.";
			link.l1 = "¿Y el propio director?";
			link.l1.go = "ClockTower_Johan_24";
		break;

		case "ClockTower_Johan_24":
			dialog.text = "Eh... No estoy autorizado a decirte nada sobre eso. Buena suerte ahí dentro, mynheer capitán.";
			link.l1 = "Gracias.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_InvitationToTheTower");
		break;
		
		// Диалог с Маартеном Виссером, заместителем директора
		case "ClockTower_Visser_1":
			dialog.text = "Bienvenido al departamento de registro naval de la CNIOC. "+UpperFirst(GetTitle(NPChar, false))+"?..";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "ClockTower_Visser_2";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_2":
			dialog.text = ""+GetFullName(NPChar)+", subdirector.\n"+
						 "He oído que has ayudado bastante a Willemstad. Quizás nuestra oficina también pueda serte útil.";
			link.l1 = "Por eso estoy aquí.";
			link.l1.go = "ClockTower_Visser_3_1";
			link.l2 = "Me alegro de haber podido servir a la capital de Curazao.";
			link.l2.go = "ClockTower_Visser_3_2";
		break;

		case "ClockTower_Visser_3_1":
			dialog.text = "Cualquier capitán, francés, español, holandés, puede encargarnos una auditoría naval. Inspeccionamos el aparejo, los cañones, el cordaje. Encontramos puntos débiles, damos recomendaciones.";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_4";
		break;

		case "ClockTower_Visser_3_2":
			dialog.text = "Cualquier capitán, francés, español, holandés, puede encargarnos una auditoría naval. Inspeccionamos el aparejo, los cañones, el cordaje. Encontramos puntos débiles, damos recomendaciones.";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_4";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;

		case "ClockTower_Visser_4":
			dialog.text = "Y si una auditoría no es suficiente, también podemos conseguir nuevos documentos navales. En otras palabras, el trabajo de nuestra oficina mejorará tu barco, sin gastar caoba ni seda preciosas.";
			link.l1 = "¿Cómo es posible?";
			link.l1.go = "ClockTower_Visser_4_1";
		break;

		case "ClockTower_Visser_4_1":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+"? No tienes ni idea de lo poderoso que es el lugar al que has llegado, y cuánto puede lograr un simple trazo de pluma.";
			link.l1 = "Por doblones, supongo.";
			link.l1.go = "ClockTower_Visser_5";
		break;

		case "ClockTower_Visser_5":
			dialog.text = "Por supuesto. Nuestros servicios no son baratos y dependen del tamaño de tu barco. Pero siempre se recupera la inversión. Un capitán que ha pasado por nosotros rara vez fracasa\n"+
						 "Sin embargo, no solo tomamos tu oro — también te damos oportunidad de ganarlo. Los piratas se han multiplicado tanto que incluso en las Antillas Menores los capitanes deben armar escuadrones para ahuyentar a estas plagas. Trae pruebas de su eliminación y recibirás pago en esos mismos doblones.";
			link.l1 = "¿Qué tipo de pruebas?";
			link.l1.go = "ClockTower_Visser_6";
		break;

		case "ClockTower_Visser_6":
			dialog.text = "Diarios de a bordo. Incluso esa escoria debe llevar algún tipo de documentación, de lo contrario ni siquiera puedes comandar un lugre como es debido. Además de ser prueba irrefutable de sus fechorías, los diarios siempre tienen un lugar en nuestros archivos. Útiles en disputas de seguros\n"+
						 "Si te interesan nuestros servicios, se ha liberado un lugar en nuestra lista de clientes: uno de los capitanes concluyó recientemente su colaboración. Completa el trabajo y el lugar será tuyo.";
			link.l1 = "¿Por qué tantas complicaciones? ¿No bastan mis doblones?";
			link.l1.go = "ClockTower_Visser_7";
		break;

		case "ClockTower_Visser_7":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+", trabajamos con calidad, no con cantidad. Cada cliente de nuestra oficina recibe el mejor servicio y la atención personal del mismísimo mynheer director. Y esto último, créeme, cuesta un dinero considerable incluso para nuestra compañía, que dista mucho de ser pobre. Como solo hay treinta días en un mes, solo podemos permitirnos treinta clientes.";
			link.l1 = "¿Qué tengo que hacer?";
			link.l1.go = "ClockTower_Visser_8";
		break;

		case "ClockTower_Visser_8":
			dialog.text = "Trae cinco diarios de a bordo piratas: eso demostrará tu eficacia. La recompensa depende de lo peligrosos que fueran sus dueños.";
			link.l1 = "Muy bien. Lo haré.";
			link.l1.go = "ClockTower_Visser_9_1";
			link.l2 = "Necesito pensarlo.";
			link.l2.go = "ClockTower_Visser_9_2";
			link.l3 = "¿Y dónde está el propio director?";
			link.l3.go = "ClockTower_Visser_9_3";
		break;

		case "ClockTower_Visser_9_1":
			dialog.text = "Excelente. Espero resultados y confío en nuestra colaboración.";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "ClockTower_Visser_13_exit";
		break;

		case "ClockTower_Visser_9_2":
			dialog.text = "Como quieras. La oferta sigue en pie. Pero tu lugar podría ser ocupado más rápido de lo que piensas.";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "ClockTower_Visser_13_exit";
		break;

		case "ClockTower_Visser_9_3":
			dialog.text = "En el mar. El mynheer van Doorn combina la gestión de la oficina con el mando del buque insignia.";
			link.l1 = "¿Cómo lo consigue?";
			link.l1.go = "ClockTower_Visser_10";
		break;

		case "ClockTower_Visser_10":
			dialog.text = "Trabaja dieciocho horas al día. Duerme aquí, en la oficina de arriba. Dice que dormir es una pérdida de tiempo. Cuatro horas le bastan.";
			link.l1 = "¿Y el estruendo de esos enormes mecanismos de relojería? ¿Cómo se puede dormir aquí?";
			link.l1.go = "ClockTower_Visser_11";
		break;

		case "ClockTower_Visser_11":
			dialog.text = "Podrás preguntarle tú mismo y quizás aprender algo. Siempre está encantado de hablar con los clientes. ¿Nos entendemos?";
			link.l1 = "Perfectamente.";
			link.l1.go = "ClockTower_Visser_12";
			link.l2 = "No del todo...";
			link.l2.go = "ClockTower_Visser_12";
		break;

		case "ClockTower_Visser_12":
			dialog.text = "Buen día, "+GetTitle(NPChar, false)+".";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "ClockTower_Visser_13_exit";
		break;

		case "ClockTower_Visser_13_exit":
			 DialogExit();
			 AddDialogExitQuestFunction("ClockTower_Quest_2");
		break;
		
		// Йохан спрашивает про журналы
		case "ClockTower_Johan_31":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+"! ¿Tiene los diarios consigo?";
			link.l1 = "Veo que estás bien informado, Johan.";
			link.l1.go = "ClockTower_Johan_32";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Johan_32":
			if (!CheckAttribute(npchar, "questTemp.ClockTower_Johan_journal"))
			{
				dialog.text = "¡Ja! Esto no es el muelle ni las puertas de la ciudad, y yo no soy un simple guardia de servicio, sino un empleado de la compañía.";
				npchar.questTemp.ClockTower_Johan_journal = true;
			}
			else
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+"! ¿Tiene los diarios consigo?";
			}
			if (ClockTower_JournalsQty() >= 5 || bBettaTestMode)
			{
				link.l1 = "Traje los diarios. ¿Me dejarás pasar?";
				link.l1.go = "ClockTower_Johan_33";
			}
			link.l2 = "En otra ocasión.";
			link.l2.go = "ClockTower_Johan_34";
		break;

		case "ClockTower_Johan_33":
			dialog.text = "¡Me alegra que todo saliera bien! Adelante, lo están esperando.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_InvitationToTheTower_2");
		break;

		case "ClockTower_Johan_34":
			dialog.text = "Que tenga un buen día, mynheer capitán.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Johan_32";
		break;
		
		case "ClockTower_Visser_21":
			dialog.text = "¡Capitán! Has vuelto. ¿Trajiste los diarios?";
			if (ClockTower_JournalsQty() >= 5 || bBettaTestMode)
			{
				link.l1 = "Sí. Los cinco.";
				link.l1.go = "ClockTower_Visser_22";
				DelLandQuestMark(npchar);
			}
			else
			{
				link.l1 = "En otra ocasión.";
				link.l1.go = "exit";
				NextDiag.TempNode = "ClockTower_Visser_21";
			}
		break;

		case "ClockTower_Visser_22":
			dialog.text = "Excelente. Déjame verlos.\n"+
						"Sí, todo en orden. Son barcos piratas genuinos. Buen trabajo. Os corresponden #количество_дублонов doblones.\n"+
						"Por favor, tomadlos. Y firmad aquí también, por favor.";
			link.l1 = "¿Entonces estoy en la lista?";
			link.l1.go = "ClockTower_Visser_23";
			//RemoveItemsFromPCharTotal("ClockTower_PirateJournal", 5);   
		break;

		case "ClockTower_Visser_23":
			dialog.text = "Casi. Primero necesitamos completar los documentos. Esto llevará algunos minutos.\n"+
						"Nombre completo?";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "ClockTower_Visser_24";
		break;

		case "ClockTower_Visser_24":
			dialog.text = "Nacionalidad?";
			link.l1 = ""+NationNameNominative(sti(pchar.baseNation))+".";
			link.l1.go = "ClockTower_Visser_25";
		break;

		case "ClockTower_Visser_25":
			dialog.text = "Nombre de tu barco?";
			link.l1 = ""+PChar.Ship.Name+".";
			link.l1.go = "ClockTower_Visser_26";
		break;

		case "ClockTower_Visser_26":
			shipType = XI_ConvertString(GetShipTypeName(pchar));
			dialog.text = "Tipo de embarcación?";
			link.l1 = ""+shipType+".";
			link.l1.go = "ClockTower_Visser_27";
		break;

		case "ClockTower_Visser_27":
			dialog.text = "Cantidad de cañones?";
			link.l1 = ""+GetCannonQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_28";
		break;

		case "ClockTower_Visser_28":
			dialog.text = "Tamaño de la tripulación?";
			link.l1 = ""+GetMaxCrewQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_29";
		break;

		case "ClockTower_Visser_29":
			dialog.text = "Bien. Ahora firma aquí. Y aquí. Y aquí también.";
			link.l1 = "¿Eso es todo?";
			link.l1.go = "ClockTower_Visser_30";
		break;

		case "ClockTower_Visser_30":
			dialog.text = "Casi. Solo queda introducirte en el registro. Claro, el mynheer director debería conoceros personalmente primero... Pero eso es una formalidad — estoy autorizado para aceptar nuevos clientes.\n"+
					"...Pero me desvío. Permítanme familiarizarles nuevamente con nuestra lista de servicios.\n"+
					"Seguro. Caro, pero ninguna escuadra naval tocará los barcos asegurados por la compañía. Podéis mantener tantos barcos en almacenes portuarios como deseéis sin temor a perderlos durante un asedio colonial.\n"+
					"Auditoría naval — incrementa ligeramente todas las características sin consumir bienes estratégicos. Comprobaremos todo: aparejo, bodega, alojamiento de la tripulación. Darán recomendaciones. El precio dependerá del tamaño del barco.\n"+
					"Registro en nuestros archivos. Incrementa la seguridad del barco en la región del Caribe, de forma que los cazadores de recompensas, piratas y militares pensarán dos veces antes de atacaros.\n"+
					"Auditoría y registro pueden realizarse sólo una vez para un barco específico. Así que si ya habéis invertido, cuidad vuestro barco. No imagináis cuánta irritación causa a mi liderazgo cuando los capitanes tratan sus barcos negligentemente y los cambian como guantes!\n"+
					"Pero me desvío de nuevo. Ahora, respecto a los servicios repetibles...\n"+
					"Cambio de documentos. Sabéis que los barcos pueden tener diferentes especialidades. Pero ni siquiera sospecháis que eso depende principalmente de cómo está documentado el barco. Si no os gusta que vuestro barco de guerra esté documentado para el asedio de fortalezas, sabéis a quién dirigiros.\n"+
					"Bueno, de las recompensas por entregar diarios de a bordo piratas ya habéis oído... Cuánto más peligroso sea el pirata, más pagaremos por su diario.";
			link.l1 = "Impresionante. Debo decir, mynheer Visser, que su oficina realmente...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_AmsterdamInTheHarbor");
		break;

		case "ClockTower_Visser_31":
			dialog.text = "'"+GetShipName("Amsterdam")+"' en el puerto! ¡El mynheer director ha regresado!";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_31_add";
			CharacterTurnByChr(CharacterFromID("ClockTower_Johan_Clone"), CharacterFromID("ClockTower_Visser"));
			ClockTower_AmsterdamInTheHarbor_2();
		break;

		case "ClockTower_Visser_31_add":
			StartInstantDialogNoType("ClockTower_Visser", "ClockTower_Visser_32", "Quest\ShipsPack\ClockTower_dialog.c");
		break;

		case "ClockTower_Visser_32":
			dialog.text = "¿Qué?! ¿Ya?! ¡Pero no iba a regresar hasta dentro de tres días!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_32_add";
		break;

		case "ClockTower_Visser_32_add":
			StartInstantDialog("ClockTower_Johan_clone", "ClockTower_Visser_33", "Quest\ShipsPack\ClockTower_dialog.c");
		break;

		case "ClockTower_Visser_33":
			dialog.text = "¡El mynheer director ya ha desembarcado! ¡Viene directamente aquí!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_33_add";
			CharacterTurnByChr(CharacterFromID("ClockTower_Johan_Clone"), CharacterFromID("ClockTower_Visser"));
		break;

		case "ClockTower_Visser_33_add":
			StartInstantDialogNoType("ClockTower_Visser", "ClockTower_Visser_34", "Quest\ShipsPack\ClockTower_dialog.c");
		break;

		case "ClockTower_Visser_34":
			dialog.text = "¡Dios mío...! Si te ve...";
			link.l1 = "¿Cuál es el problema? Acabas de decir que tienes la autoridad para aceptar nuevos clientes.";
			link.l1.go = "ClockTower_Visser_35";
		break;

		case "ClockTower_Visser_35":
			dialog.text = "¡La tengo! Pero no le gusta cuando... Da igual. Capitán, espera fuera. Junto a la entrada. El mynheer director querrá hablar contigo.";
			link.l1 = "¿Conmigo?";
			link.l1.go = "ClockTower_Visser_36";
		break;

		case "ClockTower_Visser_36":
			dialog.text = "Examina personalmente a cada nuevo cliente. Siempre. Ve, rápido!";
			link.l1 = "¡No voy a devolver los doblones por los diarios!";
			link.l1.go = "ClockTower_Visser_36_1";
			link.l2 = "Lástima, me habría quedado a escuchar.";
			link.l2.go = "ClockTower_Visser_36_2";
		break;

		case "ClockTower_Visser_36_1":
			DialogExit();
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			AddDialogExitQuestFunction("ClockTower_AmsterdamInTheHarbor_Kino_1");
		break;

		case "ClockTower_Visser_36_2":
			DialogExit();
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddDialogExitQuestFunction("ClockTower_AmsterdamInTheHarbor_Kino_1");
		break;
		
		// диалог с Йоханом, после того как мы вышли из башни
		case "ClockTower_Johan_41":
			dialog.text = "...";
			link.l1 = "¿Qué fue eso, Johan?";
			link.l1.go = "ClockTower_Johan_42";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Johan_42":
			dialog.text = "El mynheer director ha regresado.";
			link.l1 = "¿Y qué tiene eso de terrible?";
			link.l1.go = "ClockTower_Johan_43";
		break;

		case "ClockTower_Johan_43":
			dialog.text = "¡Nada terrible! Es solo que... Al mynheer director no le gustan las sorpresas. Todo debe ir según el plan. Y aquí hay un cliente nuevo que aún no ha examinado.";
			link.l1 = "Maarten dijo que tenía autoridad para registrarme.";
			link.l1.go = "ClockTower_Johan_44";
		break;

		case "ClockTower_Johan_44":
			dialog.text = "No, no es eso. El mynheer director simplemente... bueno, quiere controlarlo todo él mismo. Cada pequeño detalle. Dice que de lo contrario todo se desmoronará. Ya verás, ahora empezará a preocuparse por su reloj otra vez.";
			link.l1 = "¿Qué?";
			link.l1.go = "ClockTower_Johan_45";
		break;

		case "ClockTower_Johan_45":
			dialog.text = "Mynheer van Doorn, cuando se irrita, detiene el reloj y empieza a toquetearlo. A veces la ciudad se queda sin hora durante medio día. Y eso pasa...";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_45_1";
		break;

		case "ClockTower_Johan_45_1":
			dialog.text = "Oh... ¿Oyes? Ha empezado.";
			link.l1 = "El jefe ha vuelto. Lo de siempre.";
			link.l1.go = "ClockTower_Johan_46_1";
			link.l2 = "Ya lo creo que lo oigo. Le están dando una buena a Maarten.";
			link.l2.go = "ClockTower_Johan_46_2";
			iClockSP4PseudoGlobal = ClockTower_PlaySound_rh2("Location/SP4_quest2");
		break;

		case "ClockTower_Johan_46_1":
			dialog.text = "Desgraciadamente, ahora es lo habitual.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_47";

			if (iClockSP4PseudoGlobal != SOUND_INVALID_ID)
				SendMessage(Sound, "lll", MSG_SOUND_EVENT_STOP, iClockSP4PseudoGlobal, 0);
			ClockTower_PlaySound_rh2("Location/SP4_quest3");
		break;

		case "ClockTower_Johan_46_2":
			dialog.text = "No deberías hablar así. No es justo, si me preguntas.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_47";	
			ChangeCharacterComplexReputation(pchar, "nobility", -2);

			if (iClockSP4PseudoGlobal != SOUND_INVALID_ID)
				SendMessage(Sound, "lll", MSG_SOUND_EVENT_STOP, iClockSP4PseudoGlobal, 0);
			ClockTower_PlaySound_rh2("Location/SP4_quest3");
		break;

		case "ClockTower_Johan_47":
			dialog.text = "Parece que se ha calmado. Pronto te invitarán a pasar.";
			link.l1 = "¿Voy a tener problemas?";
			link.l1.go = "ClockTower_Johan_48";
		break;

		case "ClockTower_Johan_48":
			dialog.text = "No te preocupes. No has hecho nada malo.";
			link.l1 = "Qué tranquilizador.";
			link.l1.go = "ClockTower_Johan_49";
		break;

		case "ClockTower_Johan_49":
			dialog.text = "¡Vamos! El mynheer director a veces puede ser demasiado estricto... Pero es generoso y cortés... ¡Oh, ya lo decía yo!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_50";
		break;

		case "ClockTower_Johan_50":
			dialog.text = "¡Oh, ya lo decía yo!";
			link.l1 = "...";
			link.l1.go = "exit";
			ClockTower_VisserComingTowardsUs();
		break;

		case "ClockTower_Visser_37":
			dialog.text = "El mynheer director te espera dentro.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_VisserComingTowardsUs_2");
			DelLandQuestMark(npchar);
		break;
		
		// Первое знакомство с ван Дорном
		case "ClockTower_VanDoorn_1":
			NationName = GetSexPhrase(""+NationNameMan(sti(pchar.baseNation))+"",""+NationNameWoman(sti(pchar.baseNation))+"");
			shipType = LowerFirst(XI_ConvertString(GetShipTypeName(pchar)));
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+" "+GetFullName(pchar)+", "+NationName+". Tu barco: '"+PChar.Ship.Name+"', "+shipType+". "+GetCannonQuantity(pchar)+" cañones y "+GetMaxCrewQuantity(pchar)+" tripulantes.";
			link.l1 = "Todo correcto.";
			link.l1.go = "ClockTower_VanDoorn_2";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_VanDoorn_2":
			shipType = XI_ConvertString(GetShipTypeName(npchar));
			dialog.text = "Es injusto que yo lo sepa todo sobre ti mientras tú no sabes nada de mí salvo los cotilleos de Johan. Hendrik van Doorn. Director del departamento de registro de la Compañía Neerlandesa de las Indias Occidentales en el Caribe. Comandante de la fragata Amsterdam. "+shipType+". "+GetCannonQuantity(npchar)+" cañones y "+GetMaxCrewQuantity(npchar)+" tripulantes.";
			link.l1 = "Encantado de conocerle.";
			link.l1.go = "ClockTower_VanDoorn_3";
		break;

		case "ClockTower_VanDoorn_3":
			dialog.text = "Conseguiste cinco diarios de a bordo piratas. Mi adjunto te valoró muy positivamente, te inscribió en el registro de clientes y te familiarizó con los servicios de mi oficina.\n"+
						"Pero la decisión final sobre la admisión siempre es mía. Personalmente. Tras una entrevista. Maarten podía proponer un candidato, nada más.";
			link.l1 = "Entonces, empecemos.";
			link.l1.go = "ClockTower_VanDoorn_4";
		break;

		case "ClockTower_VanDoorn_4":
			if (!CheckAttribute(npchar, "ClockTower_option"))
			{
				dialog.text = "Necesito capitanes que combatan eficazmente a los piratas y que al mismo tiempo sean lo bastante exitosos comercialmente como para permitirse nuestros servicios. ¿Cumples estos criterios?";
			}
			else dialog.text = "";
			if (!CheckAttribute(npchar, "ClockTower_option_1") && CheckAttribute(pchar, "questTemp.DiegoDeLanda_Memento"))
			{
				link.l1 = "Destruí a Mortimer Grimm. Capitán del bergantín Memento.";
				link.l1.go = "ClockTower_VanDoorn_option_1";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_2") && CheckAttribute(pchar, "questTemp.DiegoDeLanda_LadyBeth"))
			{
				link.l2 = "Creo que tu compañía valoró mucho mi victoria sobre Albert Blackwood. La nieve Lady Beth era un adversario formidable.";
				link.l2.go = "ClockTower_VanDoorn_option_2";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_3") && CheckAttribute(pchar, "questTemp.DiegoDeLanda_SantaMisericordia"))
			{
				link.l3 = "Fernando de Alamida no era un pirata, pero...";
				link.l3.go = "ClockTower_VanDoorn_option_3";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_4") && CheckAttribute(pchar, "questTemp.KhaelRoa"))
			{
				link.l4 = "Derroté al terror de todos los que navegan. Debes saberlo.";
				link.l4.go = "ClockTower_VanDoorn_option_4";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_5") && GetCharacterShipClass(PChar) <= 3)
			{
				link.l5 = "Acabas de registrar mi barco. ¿Crees que un capitán incompetente podría mantenerlo?";
				link.l5.go = "ClockTower_VanDoorn_option_5";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_6") && sti(pchar.Money) >= 1000000)
			{
				link.l6 = "Me las arreglo bien, y el dinero crece en los árboles en el Caribe.";
				link.l6.go = "ClockTower_VanDoorn_option_6";
			}
			link.l7 = "Mynheer Visser ya verificó mi competencia. ¿No es suficiente la evaluación de tu propio adjunto?";
			link.l7.go = "ClockTower_VanDoorn_5";
			npchar.ClockTower_option = true;
		break;

		case "ClockTower_VanDoorn_option_1":
			dialog.text = "¿Grimm? Nuestra organización nunca tuvo quejas sobre Grimm, todo lo contrario. Pero quien ocupó su lugar... Sé quién era y con qué propósito llegó originalmente al Caribe. Tales villanías no prescriben, y me alegro de que castigaras al criminal y verdadero enemigo de mi país.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_1 = true;
		break;

		case "ClockTower_VanDoorn_option_2":
			dialog.text = "Si recuerdo correctamente el informe sobre el incidente en Caimán, no tuviste oportunidad de comprobarlo. En mi opinión, la situación no es del todo clara, pero tu victoria fue sin duda competente.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_2 = true;
		break;

		case "ClockTower_VanDoorn_option_3":
			dialog.text = "Pero podría haberse convertido en algo mucho peor, sí. Un enemigo digno, aunque no perdió contra ti sino contra sus ingratos superiores. Soy holandés, así que sé de lo que hablo cuando se trata de la guerra con Castilla.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_3 = true;
		break;

		case "ClockTower_VanDoorn_option_4":
			dialog.text = "'"+GetShipName("Flying Heart")+"'. Todavía me sorprende que la gente honrada no salga corriendo al ver a esa monstruosidad entrar al puerto. Muchas cosas de esta historia me sorprenden, capitán. Pero algún día encontrará su lugar en nuestros libros y perderá todo su encanto. En cuanto a ti... te has inmortalizado.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_4 = true;
		break;

		case "ClockTower_VanDoorn_option_5":
			dialog.text = "Te sorprenderías. Pero en tu caso, no hay lugar a dudas, es cierto.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_5 = true;
		break;

		case "ClockTower_VanDoorn_option_6":
			dialog.text = "Y por eso no valen nada. A menos que sean doblones, claro.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_6 = true;
		break;

		case "ClockTower_VanDoorn_5":
			dialog.text = "\nEstás aprobado para los servicios de la oficina. Bienvenido al registro de clientes de la estimada Compañía Neerlandesa de las Indias Occidentales.";
			link.l1 = "Gracias.";
			link.l1.go = "ClockTower_VanDoorn_6";
		break;

		case "ClockTower_VanDoorn_6":
			dialog.text = "Es una cooperación mutuamente beneficiosa. Obtienes acceso a los mejores servicios del Caribe. Nosotros ganamos un socio confiable.";
			link.l1 = "Bien.";
			link.l1.go = "ClockTower_VanDoorn_7";
		break;

		case "ClockTower_VanDoorn_7":
			dialog.text = "¡Espera! ¿Oyes eso?";
			link.l1 = "No oigo nada.";
			link.l1.go = "ClockTower_VanDoorn_8";
			// sound stops
			i = FindSoundEventId("Location/clocks_mechanism_inside");
			SetSoundEventPauseState(i, true);
			DelEventHandler("NextHour", "Villemstad_BigClock_Above");
		break;

		case "ClockTower_VanDoorn_8":
			dialog.text = "¡Justo ese es el punto! Bastó con irme una semana...";
			link.l1 = "¿Algo anda mal?";
			link.l1.go = "ClockTower_VanDoorn_9";
		break;

		case "ClockTower_VanDoorn_9":
			dialog.text = "Con el reloj. Necesito revisar el mecanismo. Disculpa. Esto... es importante.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
		break;

		case "ClockTower_VanDoorn_10":
			if (!CheckAttribute(npchar, "ClockTower_question"))
			{
				dialog.text = "Parece que todo está bien. Mis disculpas nuevamente. ¿Tienes preguntas?";
				LAi_Fade("", "");
				// sound returns
				i = FindSoundEventId("Location/clocks_mechanism_inside");
				SetSoundEventPauseState(i, false);
				SetEventHandler("NextHour", "Villemstad_BigClock_Above", 0);
			}
			else dialog.text = "¿Más preguntas?";
			if (!CheckAttribute(npchar, "ClockTower_question_1"))
			{
				link.l1 = "Tu adjunto explicó los servicios de la oficina en detalle. ¿Cómo es posible todo esto?";
				link.l1.go = "ClockTower_VanDoorn_question_1";
			}
			if (!CheckAttribute(npchar, "ClockTower_question_2"))
			{
				link.l2 = "¿Cómo combinas dos puestos? ¿Capitán y director?";
				link.l2.go = "ClockTower_VanDoorn_question_2";
			}
			if (!CheckAttribute(npchar, "ClockTower_question_3"))
			{
				link.l3 = "¿Cómo trabajas en tales condiciones? El estruendo de los mecanismos del reloj, la oscuridad y las ventanas cubiertas con cortinas gruesas.";
				link.l3.go = "ClockTower_VanDoorn_question_3";
			}
			link.l4 = "No, gracias por tu tiempo. ¿Y qué hay de los servicios de la oficina?";
			link.l4.go = "ClockTower_VanDoorn_11";
			npchar.ClockTower_question = true;
		break;

		case "ClockTower_VanDoorn_question_1":
			dialog.text = "Aquí no hay ninguna brujería, "+GetTitle(NPChar, false)+". La pluma y la tinta gobiernan el mundo. La Iglesia registra el nacimiento, bautismo, matrimonio y muerte de una persona. Cambia aunque sea una línea y su destino cambia. Un barco es un poco más complejo, pero incluso en su caso un trazo de pluma cambia mucho. No voy a ocultarlo, estoy orgulloso de lo que he logrado. Y aun así sé que puede ser mejor. ¿Y si registráramos en los libros no solo barcos y personas, sino un mundo entero?";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
			npchar.ClockTower_question_1 = true;
		break;

		case "ClockTower_VanDoorn_question_2":
			dialog.text = "Porque alguien debe hacerlo. El anterior capitán del Amsterdam murió en combate contra un grupo de Antigua. La compañía no encontró un reemplazo digno. Me ofrecí yo. Me formé. Aprobé los exámenes. Obtuve la patente\n"+
			"Sí, soy un mal capitán. Mucho peor que tú, eso seguro. Pero un buen gestor puede dirigir cualquier cosa, no solo un barco. Es difícil aprender a comandar a tres personas. Una vez que lo aprendes, puedes comandar a tres mil. Una oficina, un barco, una ciudad o incluso una gran compañía: no hay límite, mientras encuentres personas talentosas y confíes en que te representen... Esto último es lo más difícil. Una verdadera maldición.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
			npchar.ClockTower_question_2 = true;
		break;

		case "ClockTower_VanDoorn_question_3":
			dialog.text = "Y además apenas hay aire para respirar. "+UpperFirst(GetTitle(NPChar, false))+", una persona moldea su propio entorno. Aquí nada ni nadie me distrae, todo está a mano y sometido solo a mí y al tiempo. Si pudiera, me comunicaría con el mundo exterior únicamente a través del papel. Desafortunadamente, eso es imposible. Y no te lo tomes como algo personal, "+GetTitle(NPChar, false)+". Mejor estar solo, pero no solitario. Si entiendes a qué me refiero.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
			npchar.ClockTower_question_3 = true;
		break;

		case "ClockTower_VanDoorn_11":
			// pchar.quest.ClockTower.date = rand(27)+1;
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			dialog.text = "Solo atendemos con cita previa. Tienes programado... "+pchar.quest.ClockTower.date+" "+month+". Si no vienes el día indicado, no pasa nada. Contacta con Johan y te informará de la próxima cita disponible.";
			link.l1 = "¿Por qué tantas complicaciones?";
			link.l1.go = "ClockTower_VanDoorn_12";
		break;

		case "ClockTower_VanDoorn_12":
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			dialog.text = "Nuestro trabajo es caro porque realizamos verdaderos milagros y aportamos gran beneficio a nuestros clientes. Los conflictos de intereses son imposibles, y por eso dedicamos un día laboral completo a las necesidades de una persona específica. Tu próximo día disponible: "+pchar.quest.ClockTower.date+" "+month+"\n"+
			"Si ves a Visser... Maarten actuó correctamente al proponer tu candidatura. Díselo. Es un buen adjunto. Que no lo dude.";
			link.l1 = "Bien.";
			link.l1.go = "ClockTower_VanDoorn_13";
		break;

		case "ClockTower_VanDoorn_13":
			dialog.text = "Buen día, "+GetTitle(NPChar, false)+".";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_VanDoornInCabinet_3");
		break;
		
		case "ClockTower_Visser_41":
			dialog.text = "¿Cómo fue todo?";
			link.l1 = "Fue un día largo, pero van Doorn confirmó tu decisión.";
			link.l1.go = "ClockTower_Visser_42";
		break;

		case "ClockTower_Visser_42":
			dialog.text = "Gracias a Dios. Entonces hice todo bien.";
			link.l1 = "Me pidió que te dijera que eres un buen adjunto.";
			link.l1.go = "ClockTower_Visser_43";
		break;

		case "ClockTower_Visser_43":
			dialog.text = "¿En serio? ¿Él... dijo eso?";
			link.l1 = "Sí. Lo dijo.";
			link.l1.go = "ClockTower_Visser_44";
		break;

		case "ClockTower_Visser_44":
			dialog.text = "Maldición. No debería haber dicho eso. Ahora me sentiré como un desgraciado desagradecido. ¿O quizás lo previó y lo calculó todo?";
			link.l1 = "Mynheer adjunto, de repente has dejado de ser tú mismo.";
			link.l1.go = "ClockTower_Visser_45";
		break;

		case "ClockTower_Visser_45":
			dialog.text = "Capitán, soy un hombre de negocios, y tú también, así que no voy a alargar esto.\n"+
						 "El mynheer director hace tiempo que no trabaja para nosotros.";
			link.l1 = "¿Cómo, perdón?!";
			link.l1.go = "ClockTower_Visser_46";
		break;

		case "ClockTower_Visser_46":
			dialog.text = "Vino aquí con un contrato y un único objetivo: organizar el trabajo del departamento de registro naval. Lo logró brillantemente, formó a su sucesor, me promocionó... y eso es todo.";
			link.l1 = "¿Cómo, eso es todo?";
			link.l1.go = "ClockTower_Visser_47";
		break;

		case "ClockTower_Visser_47":
			dialog.text = "Su contrato terminó hace mucho tiempo. No sabemos exactamente cuándo, pero estamos completamente seguros de que este hombre ya no tiene derecho a ocupar su puesto.";
			link.l1 = "Entiendo. Los peces gordos del ala central de este edificio se ponen nerviosos.";
			link.l1.go = "ClockTower_Visser_48_1";
			link.l2 = "Entiendo. Estás cansado de esperar a que libere su silla para ti.";
			link.l2.go = "ClockTower_Visser_48_2";
		break;

		case "ClockTower_Visser_48_1":
			dialog.text = "¡Exacto! ¡Y no pueden hacer nada al respecto!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_49";
		break;

		case "ClockTower_Visser_48_2":
			dialog.text = "No voy a mentir. Realmente estoy cansado. ¡Maldita sea, van Doorn me ascendió precisamente para que lo reemplazara cuando terminara el contrato!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_49";
		break;

		case "ClockTower_Visser_49":
			dialog.text = "Sin embargo, jamás sacudiría este maldito sillón bajo él sólo porque me siento engañado. ¡Dios sabe que estoy agradecido y admiro a este hombre!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_50";
		break;

		case "ClockTower_Visser_50":
			dialog.text = "No, mynheer. Van Doorn quiere deshacerse de nuestros superiores comunes. ¡Precisamente aquellos que están detrás del muro de la torre, en el ala central de este edificio! Sin embargo, ni siquiera ellos pueden controlarlo.";
			link.l1 = "¿Qué tiene eso de difícil? Van Doorn difícilmente es más importante que Stuyvesant.";
			link.l1.go = "ClockTower_Visser_51";
		break;

		case "ClockTower_Visser_51":
			dialog.text = "Esto no es un barco ni una corte real, capitán. Nuestra compañía es un tipo de organización completamente nuevo. No puedes simplemente señalar con el dedo y despedir a una persona tan valiosa.\n"+
						 "Primero, nadie sabe dónde está el original del contrato de van Doorn. Ergo, no hay motivos para el despido. Intentáramos hacerlo, y él enviaría una horda de abogados, y terminaríamos debiéndole dinero.\n"+
						 "Segundo, la dirección cometió un error al darle a van Doorn la patente del Amsterdam. Aunque sea un capitán mediocre, reunió una tripulación — la mejor de toda la región. Da una orden, y los soldados de élite de la Compañía ocuparían este edificio sin pestañear.\n"+
						 "Tercero, su esposa lo adora. No importa que no la haya visto en varios años. La propia hija de De Witt es capaz de mucho por su amado esposo. Y el Consejo de los Diecisiete se ve obligado a aceptarlo.\n"+
						 "En otras palabras, el directorio pagará muy generosamente por tu ayuda. Y preservará tus privilegios en la oficina de registro naval.";
			link.l1 = "Impresionante. Realmente eres un hombre de negocios, Maarten. Me vendes traición con el mismo profesionalismo con el que hace poco vendías los servicios de tu oficina.";
			link.l1.go = "ClockTower_Visser_57";
		break;

		case "ClockTower_Visser_57":
			dialog.text = "No es difícil cuando el propio van Doorn te enseñó el arte de la negociación y crees sinceramente en lo que dices.";
			link.l1 = "Entonces, ¿qué quieres de mí?";
			link.l1.go = "ClockTower_Visser_58";
		break;

		case "ClockTower_Visser_58":
			dialog.text = "Algo que solo un forastero puede hacer. Entra en la oficina por la noche y encuentra el contrato original de van Doorn. Me aseguraré de que las puertas estén abiertas.";
			link.l1 = "¿Por qué no lo haces tú mismo? ¿Y qué me impide ir ahora mismo y contárselo todo a tu superior?";
			link.l1.go = "ClockTower_Visser_59";
		break;

		case "ClockTower_Visser_59":
			dialog.text = "Porque van Doorn tiene la costumbre de recibir a cualquiera por la noche, excepto a empleados de la compañía. Nadie se sorprenderá al verte salir de esta torre a una hora inusual.";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_60";
		break;

		case "ClockTower_Visser_60":
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			dialog.text = "Respecto a tu amenaza... No llegarás al director ahora, ya que tienes programado otro día. "+pchar.quest.ClockTower.date+" "+month+", ¿verdad? Para entonces la urgencia de la noticia habrá disminuido un poco. Además, el director nunca recompensa a los delatores. Y siempre protege a sus empleados.";
			link.l1 = "Conveniente para ti.";
			link.l1.go = "ClockTower_Visser_61";
		break;

		case "ClockTower_Visser_61":
			dialog.text = "Esto no es traición, capitán. Simplemente queremos cumplir el contrato y proteger a la compañía. También Willemstad, al que tanto has ayudado, por cierto.";
			link.l1 = "Lo pensaré. Pero no prometo nada.";
			link.l1.go = "ClockTower_Visser_62";
		break;

		case "ClockTower_Visser_62":
			dialog.text = "No te pido más, capitán. Ante todo, eres nuestro cliente. Como quiera que resulten las cosas, estoy muy orgulloso de haber sido yo quien te encontró e inscribió en el registro de la oficina.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_63";
		break;

		case "ClockTower_Visser_63":
			dialog.text = "Siempre podrás encontrarme en el ala central. Buen día.";
			link.l1 = "Hasta luego.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_Quest_3");
		break;
		
		case "ClockTower_Visser_64":
			dialog.text = "Hola, "+GetTitle(NPChar, false)+". ¿Alguna novedad?";
			link.l1 = "Nada todavía.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Visser_64";
		break;
		
		case "ClockTower_Johan_51":
			if (GetHour() >= 6 && GetHour() < 24)
			{
				if (pchar.quest.ClockTower.date <= GetDataDay())
				{
					NextMonth = GetDataMonth() + 1;
					if (NextMonth == 13) NextMonth = 1;
				}
				else NextMonth = GetDataMonth();
				Month = XI_ConvertString("MonthGen_" + NextMonth);
				if (pchar.quest.ClockTower.date == GetDataDay() && CheckAttribute(pchar, "questTemp.ClockTower_NoToday"))
				{
					if (!CheckAttribute(npchar, "ClockTower_repeat"))
					{
						dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+", hoy es su día. Por favor, adelante.";
						npchar.ClockTower_repeat = true;
						SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
						
						ClockTower_RightDay();
					}
					else
					{
						dialog.text = "¡Buen día, "+GetTitle(NPChar, false)+"!";
					}
				}
				else
				{
					if (!CheckAttribute(npchar, "ClockTower_repeat"))
					{
						dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+", lo esperan otro día. Nos alegraremos de verlo: "+pchar.quest.ClockTower.date+" "+month+".";
						npchar.ClockTower_repeat = true;
						SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
					}
					else
					{
						dialog.text = "¡Buen día, "+GetTitle(NPChar, false)+"!";
					}
				}
				link.l1 = "Gracias, Johan.";
				link.l1.go = "exit";
				NextDiag.TempNode = "ClockTower_Johan_51";
			}
			else
			{
				if (!CheckAttribute(npchar, "ClockTower_repeatnight"))
				{	// первая ночная встреча с Йоханом
					dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+", llegas algo tarde. La oficina está cerrada.";
					link.l1 = "Hola, "+npchar.name+". Escuché que opera incluso de noche.";
					link.l1.go = "ClockTower_Johan_52";
					npchar.ClockTower_repeatnight = true;
					SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
				}
				else
				{
					dialog.text = ""+TimeGreeting()+", "+GetTitle(NPChar, false)+"!";
					link.l1 = "";
					link.l1.go = "ClockTower_Johan_53";
				}
			}
		break;
		
		case "ClockTower_Johan_52":
			dialog.text = "Es cierto. Viene todo tipo de gente. Hasta sacerdotes aparecen a veces, je-je. Pero todos deben pasar primero por mí. Y no he recibido instrucciones sobre ti.";
			link.l1 = "Espera, ¿montas guardia aquí las veinticuatro horas? ¿Cómo es eso posible?";
			link.l1.go = "ClockTower_Johan_53";
		break;

		case "ClockTower_Johan_53":
			if (!CheckAttribute(npchar, "ClockTower_repeatnight_2"))
			{
				dialog.text = "Sí. El mynheer director acaba de ordenarlo. Cómo lo logra, no lo sé, pero igual me alcanza el tiempo para descansar y para el servicio. Y me subieron el sueldo, ¡no puedo quejarme!";
				npchar.ClockTower_repeatnight_2 = true;
			}
			else
			{
				dialog.text = "¿Algo más?";
			}
			if (!CheckAttribute(pchar, "questTemp.ClockTower_NightFree"))
			{
				link.l1 = "Deberías dejarme pasar. Trabajo para la alta dirección de la compañía.";
				link.l1.go = "ClockTower_Johan_54";
				link.l2 = "(Matarlo)";
				link.l2.go = "ClockTower_Johan_KillHim";
			}
			link.l3 = "Sigue así, soldado.";
			link.l3.go = "ClockTower_Johan_NightExit";
		break;

		case "ClockTower_Johan_KillHim":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_KillToJohan");
		break;

		case "ClockTower_Johan_NightExit":
			DialogExit();
			NextDiag.CurrentNode = "ClockTower_Johan_51";
		break;

		case "ClockTower_Johan_54":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 80)
			{
				dialog.text = "Eh. ¿Qué quiere de mí, mynheer capitán? Solo soy un soldado raso, no sé nada.";
				link.l1 = "Lo sabes todo, Johan. No seas tan modesto. Los señores en las oficinas importantes quizás no te rinden cuentas, pero seguro has oído del gato negro entre ellos.";
				link.l1.go = "ClockTower_Johan_55";
				Notification_Skill(true, 80, SKILL_LEADERSHIP);
			}
			else
			{
				dialog.text = "Soy un hombre humilde, pero no voy a pasar por encima de mi superior directo. Disculpe, mynheer capitán.";
				link.l1 = "Volveremos a esta conversación.";
				link.l1.go = "ClockTower_Johan_NightExit";
				Notification_Skill(false, 80, SKILL_LEADERSHIP);
			}
		break;

		case "ClockTower_Johan_55":
			Achievment_Set("ach_CL_197");
			dialog.text = "Es verdad, mynheer capitán. El mynheer director se ha quedado demasiado tiempo. Se avecina tormenta.";
			link.l1 = "¿Qué has oído?";
			link.l1.go = "ClockTower_Johan_56";
		break;

		case "ClockTower_Johan_56":
			dialog.text = "Todos temen que, si no es hoy, mañana tomará el poder. Es un hombre demasiado importante para nuestro rincón olvidado. Está asfixiando a todos con sus inspecciones, hace pasar cada firma por él.\nSe lo digo con sinceridad, y usted mismo lo ha visto: cada vez que el Amsterdam entra al puerto, enseguida se levanta una tensión desagradable.";
			link.l1 = "Puedo resolver esto, pero para eso debes dejarme pasar.";
			link.l1.go = "ClockTower_Johan_57";
		break;

		case "ClockTower_Johan_57":
			dialog.text = "Adelante, mynheer capitán. Solo le ruego que no me arruine: si el mynheer director se entera, perderé la cabeza, y tengo una familia que alimentar.";
			link.l1 = "Haré lo que pueda.";
			link.l1.go = "ClockTower_Johan_58_hint";
		break;

		case "ClockTower_Johan_58_hint":
			ClockTower_AddBook();
			dialog.text = "Es usted un buen hombre, mynheer capitán. Quizás pueda ayudarle: sé que en uno de los libros el mynheer director guarda una llave. Para qué es, no lo sé, pero quizás le sea útil.";
			link.l1 = "Gracias, Johan.";
			link.l1.go = "ClockTower_Johan_NightSuccess";
		break;
		
		case "ClockTower_Johan_NightSuccess":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_NightFree");
			NextDiag.CurrentNode = "ClockTower_Johan_51";
			// if (sti(pchar.reputation.nobility) < 71) Notification_Reputation(false, 71, "low");
		break;
		
		case "ClockTower_Peter_50":
			dialog.text = "Alto. Está en propiedad de la Compañía Neerlandesa de las Indias Occidentales. Departamento de registro naval y archivo. Entrada solo con cita previa.";
			link.l1 = "Soy el "+GetTitle(NPChar, false)+" "+pchar.name+".";
			link.l1.go = "ClockTower_Peter_51";
			DelLandQuestMark(npchar);
		break;
		
		case "ClockTower_Peter_51":
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			if (pchar.quest.ClockTower.date == GetDataDay() && CheckAttribute(pchar, "questTemp.ClockTower_NoToday"))
			{
				if (!CheckAttribute(npchar, "ClockTower_repeat"))
				{
					dialog.text = "¿Tiene cita? Adelante.";
					npchar.ClockTower_repeat = true;
					SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
					
					ClockTower_RightDay();
				}
				else
				{
					dialog.text = "...";
				}
			}
			else
			{
				if (!CheckAttribute(npchar, "ClockTower_repeat"))
				{
					dialog.text = "Su cita está programada para otro día: "+pchar.quest.ClockTower.date+" "+month+".";
					npchar.ClockTower_repeat = true;
					SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
				}
				else
				{
					dialog.text = "...";
				}
			}
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Peter_51";
		break;
		
		case "ClockTower_Visser_71":
			dialog.text = "Hola, "+GetTitle(NPChar, false)+". ¿Alguna novedad?";
			link.l1 = "Sí. Aquí está el contrato.";
			link.l1.go = "ClockTower_Visser_72";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_72":
			dialog.text = "Increíble... Expiró hace siete años!";
			link.l1 = "¿Entonces esto es lo que necesitabas?";
			link.l1.go = "ClockTower_Visser_73";
		break;

		case "ClockTower_Visser_73":
			dialog.text = "¡Exacto! Con este documento la compañía puede revocarlo legalmente. Sin escapatorias. Sin excusas. Se acabó el tiempo, punto.";
			link.l1 = "¿Qué sigue?";
			link.l1.go = "ClockTower_Visser_74";
		break;

		case "ClockTower_Visser_74":
			dialog.text = "Enviaré el contrato a Ámsterdam. El Consejo de los Diecisiete tomará una decisión. A Doorn le ordenarán regresar. No podrá negarse.";
			link.l1 = "¿Y si se niega?";
			link.l1.go = "ClockTower_Visser_75";
		break;

		case "ClockTower_Visser_75":
			dialog.text = "No puede. Aunque su esposa sea hija de un accionista, el Gran Pensionario, ni siquiera su padre irá contra el Consejo. Y la propia Catharina... Lleva diez años esperando. Si descubre que puede volver pero se niega, la matará.";
			link.l1 = "Cruel.";
			link.l1.go = "ClockTower_Visser_76";
		break;

		case "ClockTower_Visser_76":
			dialog.text = "Sí. Pero es la única manera. Gracias, capitán. Has hecho un trabajo importante.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_77";
		break;

		case "ClockTower_Visser_77":
			if (CharacterIsAlive("ClockTower_Johan"))
			{
				dialog.text = "Tu recompensa: quinientos doblones. Y te doy mi palabra: en dos o tres meses, cuando ocupe la silla del director, tendrás acceso ilimitado a los servicios de la oficina. Sin colas. Sin citas. En cualquier momento.";
				AddItems(pchar, "gold_dublon", 500);
			}
			else
			{
				dialog.text = "Y mataste a Johan. Ya he traicionado a un hombre al que admiro y al que le debo todo. Ahora esto también.\n"+
							 "Quizás en tu barco la gente sea como astillas, pero la compañía valora a sus empleados. Y me repugna ser cómplice de un asesinato.\n"+
							 "Tus doblones irán a la familia de Johan, pero cumpliré la segunda parte del trato.\n"+
							 "Te doy mi palabra: en dos o tres meses, cuando ocupe la silla del director, tendrás acceso ilimitado a los servicios de la oficina.";
			}
			link.l1 = "Cuento con tu palabra. Buen día.";
			link.l1.go = "ClockTower_Visser_78";
		break;

		case "ClockTower_Visser_78":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_WaitFewMonths");
		break;

		case "ClockTower_Visser_79":
			dialog.text = "Hola, "+GetTitle(NPChar, false)+". Todavía no hay noticias. No te preocupes, recuerdo nuestro acuerdo.";
			link.l1 = "Espero.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Visser_79";
		break;

		case "ClockTower_Visser_81":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+"! Adelante, adelante. Me alegra verte.";
			link.l1 = "Felicitaciones por tu nombramiento.";
			link.l1.go = "ClockTower_Visser_82";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_82":
			dialog.text = "Gracias. El Consejo de los Diecisiete tomó su decisión más rápido de lo que esperaba. El contrato resultó ser prueba suficiente. Mynheer van Doorn fue destituido de la dirección de la oficina.";
			link.l1 = "¿Cómo se lo tomó?";
			link.l1.go = "ClockTower_Visser_83";
		break;

		case "ClockTower_Visser_83":
			dialog.text = "Sabe perder. Simplemente recogió sus pertenencias personales del despacho y se fue. Aunque, ¿realmente perdió?\n"+
						 "Le mantuvieron el mando del Amsterdam. En ese aspecto, la compañía ciertamente cometió un error. No deberían haberle dado ese barco en aquel entonces.\n"+
						 "Lo subestimamos. Espero que al final las cosas no empeoren.";
			link.l1 = "¿Cómo podría ser peor?";
			link.l1.go = "ClockTower_Visser_84";
		break;

		case "ClockTower_Visser_84":
			dialog.text = "Mynheer van Doorn sabe quién sacó el contrato de su oficina.";
			link.l1 = "¿¡Cómo!?";
			link.l1.go = "ClockTower_Visser_85";
		break;

		case "ClockTower_Visser_85":
			dialog.text = "¡No me mires así! No le dije nada. Él lo descubrió solo.";
			link.l1 = "¿Y ahora qué?";
			link.l1.go = "ClockTower_Visser_86";
		break;

		case "ClockTower_Visser_86":
			dialog.text = "Ahora te considera un enemigo. Pero mientras no representes una amenaza para la República de las Siete Provincias Unidas, no te tocará.\n"+
						 "Van Doorn siempre supo separar lo personal de lo profesional. La pregunta es, ¿puedes tú?";
			link.l1 = "¿Y si no puedo?";
			link.l1.go = "ClockTower_Visser_87";
		break;

		case "ClockTower_Visser_87":
			dialog.text = "Entonces te encontrará. Y hará su trabajo. No le des un motivo.";
			link.l1 = "Lo intentaré.";
			link.l1.go = "ClockTower_Visser_88";
		break;

		case "ClockTower_Visser_88":
			dialog.text = "Buen día, "+GetTitle(NPChar, false)+". No dudes en usar los servicios de nuestra... mi oficina en cualquier momento.";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_VillemstadStreet");
		break;
		
		case "ClockTower_Johan_61":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+", lo esperan. Mynheer Visser ordenó que se permita entrar libremente a todos los clientes. Dice que las viejas normas eran demasiado estrictas.";
			link.l1 = "Gracias, Johan.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_FreeAccess_2");
			DelLandQuestMark(npchar);
		break;
		
		case "ClockTower_Peter_61":
			dialog.text = "Adelante en cualquier horario de oficina. Las citas han sido abolidas.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_FreeAccess_2");
			DelLandQuestMark(npchar);
		break;
		
		case "ClockTower_Helena_1":
			dialog.text = "¿Tienes un minuto?";
			link.l1 = "Para ti, siempre.";
			link.l1.go = "ClockTower_Helena_2";
		break;

		case "ClockTower_Helena_2":
			dialog.text = "Ah, ojalá fuera cierto, mi capitán. Tienes otras pasiones en la vida. Ahora mismo, por ejemplo, tu linda cabeza está ocupada por alguien que no soy yo, ¿verdad?";
			link.l1 = "...";
			link.l1.go = "ClockTower_Helena_3";
		break;

		case "ClockTower_Helena_3":
			dialog.text = "Lo sabía. Conozco bien a mi hombre. Y la pasión de un marinero, eso lo conozco aún mejor. Así que dime directamente, cariño...\n"+
						 "¿Qué nos costará capturar el buque insignia de la estimada Compañía Comercial Neerlandesa de las Indias Occidentales?";
			link.l1 = "Para que van Doorn venga por nosotros él mismo, tendré que convertirme en enemigo de Willemstad.";
			link.l1.go = "ClockTower_Helena_4";
		break;

		case "ClockTower_Helena_4":
			dialog.text = "Oh, mi capitán... Así que así será. No es la primera vez, ¿verdad?";
			link.l1 = "Como si no lo aprobaras.";
			link.l1.go = "ClockTower_Helena_5";
		break;

		case "ClockTower_Helena_5":
			dialog.text = "Me enamoré de ti tal como eres. Y siempre estaré de tu lado. Solo recuerda la carga de responsabilidad que nosotros... es decir, que tú llevas ante tu gente.";
			link.l1 = "Aunque para eso tenemos a nuestro Alonso. Él te lo recordará.";
			link.l1.go = "ClockTower_Helena_6";
		break;

		case "ClockTower_Helena_6":
			dialog.text = "En cuanto zarpemos, mi capitán.";
			link.l1 = "Entonces no lo retrasemos, cariño.";
			link.l1.go = "ClockTower_Girl_End";
		break;
		
		case "ClockTower_Mary_1":
			dialog.text = "¿Charles? Quiero preguntarte algo.";
			link.l1 = "Por supuesto, Mary. ¿Qué pasó?";
			link.l1.go = "ClockTower_Mary_2";
		break;

		case "ClockTower_Mary_2":
			dialog.text = "Yo... estoy preocupada por ti, ¿sabes? Conozco esa mirada. Estás pensando en algo malo.";
			link.l1 = "Tonterías. Ni siquiera recuerdo en qué estaba pensando. ¿Cómo lo sabrías tú?";
			link.l1.go = "ClockTower_Mary_3";
		break;

		case "ClockTower_Mary_3":
			dialog.text = "¡Simplemente lo sé! Vi ese Amsterdam, ¿sabes? Un barco hermoso. Muy hermoso. Pero...\n"+
						 "Ya lo has decidido todo... Como antes, ¿verdad?";
			link.l1 = "Van Doorn vendrá por nosotros él mismo, pero para eso tendré que convertirme en enemigo de Willemstad.";
			link.l1.go = "ClockTower_Mary_4";
		break;

		case "ClockTower_Mary_4":
			dialog.text = "¿Vale la pena, Charles?";
			link.l1 = "No lo sé, Mary.";
			link.l1.go = "ClockTower_Mary_5";
		break;

		case "ClockTower_Mary_5":
			dialog.text = "Quiero que seas feliz, ¿sabes? Pero aun así le pediré a Alonso que trate de convencerte de que lo dejes, ¿de acuerdo?";
			link.l1 = "Eso sería típico de él. Vamos, cariño.";
			link.l1.go = "ClockTower_Girl_End";
		break;
		
		case "ClockTower_Girl_End":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_Girl_DlgExit");
		break;
		
		case "ClockTower_Alonso_1":
			dialog.text = "Cap, tenemos que hablar.";
			link.l1 = "Te escucho.";
			link.l1.go = "ClockTower_Alonso_2";
			link.l2 = "Ahora no, Alonso.";
			link.l2.go = "ClockTower_Alonso_2";
		break;

		case "ClockTower_Alonso_2":
			dialog.text = "Es así, cap, pero tendrás que escucharme. Es, eh, cómo se dice...\n"+
						 "¡Un asunto urgente, eso es!\n"+
						 "Bueno, un pajarito me contó que usted personalmente echó a uno de los directores de la compañía de su cómodo puesto, y ese guarda rencor y ahora nos está cazando en su hermosa fragata.";
			link.l1 = "Eso es una gran exageración.";
			link.l1.go = "ClockTower_Alonso_3";
		break;

		case "ClockTower_Alonso_3":
			dialog.text = "Ya sabe cómo le gusta a la gente mover la lengua, cap. Deje que un rumor fermente una semana, y oirá que van Doorn fue seducido por la hija de un plantador, que el Amsterdam tiene una tripulación de muertos vivientes, y en la bodega están los tesoros del mismísimo Cortés.\n"+
						 "Pero a mí me interesa más la situación real. Entonces, cap, ¿habrá pelea o no?";
			link.l1 = "...";
			if (CheckPassengerInCharacter(pchar, "Irons")) // Tommy
			{
				link.l1.go = "ClockTower_Alonso_4_1";
			}
			else
			{
				link.l1.go = "ClockTower_Alonso_4_5";
			}
		break;

		case "ClockTower_Alonso_4_1":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_TommyInCabin");
		break;

		case "ClockTower_Alonso_4_2":
			dialog.text = "Lo cual, por cierto, ¡sería jodidamente divertido, no discuto! ¡El buque insignia holandés! ¡Ja! Me imagino las caras de esos comeques cuando nosotros...";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_4_3";
		break;

		case "ClockTower_Alonso_4_3":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_TommyInCabin_2");
		break;

		case "ClockTower_Alonso_4_4":
			dialog.text = "Tommy, cállate.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_4_5";
		break;

		case "ClockTower_Alonso_4_5":
			dialog.text = "...";
			link.l1 = "Si hay pelea, no será pronto. Van Doorn no buscará venganza, no es ese tipo de hombre. Primero tendremos que enfurecer seriamente a los holandeses.";
			link.l1.go = "ClockTower_Alonso_4_6";
			CharacterTurnByChr(npchar, pchar);
		break;

		case "ClockTower_Alonso_4_6":
			dialog.text = "Gracias, cap, eso tranquilizará a la tripulación.";
			link.l1 = "¿Y a ti?";
			link.l1.go = "ClockTower_Alonso_5";
		break;

		case "ClockTower_Alonso_5":
			dialog.text = "Mi preocupación es proteger a la tripulación. De sí mismos y... de usted, si puedo. De todos modos hará lo que planeó.";
			if (CheckPassengerInCharacter(pchar, "Irons")) // Tommy
			{
				link.l1 = "...";
				link.l1.go = "ClockTower_Alonso_5_add";
			}
			else
			{
				link.l1 = "Sigue así, Alonso.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("ClockTower_CuracaoInCabin_4_DlgExit");
			}
		break;

		case "ClockTower_Alonso_5_add":
			StartInstantDialogTurnToNPC("Irons", "ClockTower_Alonso_6", "Quest\ShipsPack\ClockTower_dialog.c", "ClockTower_Alonso");
		break;

		case "ClockTower_Alonso_6":
			dialog.text = "¡Terco como una mula española!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_6_add";
		break;

		case "ClockTower_Alonso_6_add":
			StartInstantDialogTurnToNPC("ClockTower_Alonso", "ClockTower_Alonso_7", "Quest\ShipsPack\ClockTower_dialog.c", "Irons");
		break;

		case "ClockTower_Alonso_7":
			dialog.text = "Señor, por qué yo.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_7_add";
		break;

		case "ClockTower_Alonso_7_add":
			StartInstantDialogTurnToNPC("Irons", "ClockTower_Alonso_8", "Quest\ShipsPack\ClockTower_dialog.c", "ClockTower_Alonso");
		break;

		case "ClockTower_Alonso_8":
			dialog.text = "¡Complicando todo! El cap quiere un buen barco — le daremos un buen barco! Somos una tripulación!";
			link.l1 = "Sigue así, Alonso. Tommy, fuera.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_CuracaoInCabin_4_DlgExit");
		break;
		
		// Абордаж Амстердама, перед боем с Ван Дормом
		case "ClockTower_VanDoorn_21":
			NationName = GetSexPhrase(""+NationNameMan(sti(pchar.baseNation))+"",""+NationNameWoman(sti(pchar.baseNation))+"");
			shipType = LowerFirst(XI_ConvertString(GetShipTypeName(pchar)));
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+" "+GetFullName(pchar)+", "+NationName+". Tu barco: '"+PChar.Ship.Name+"', "+shipType+". "+GetCannonQuantity(pchar)+" cañones y "+GetMaxCrewQuantity(pchar)+" tripulantes.";
			link.l1 = "Es usted tan preciso como siempre, mynheer director.";
			link.l1.go = "ClockTower_VanDoorn_22";
		break;

		case "ClockTower_VanDoorn_22":
			dialog.text = "Ese título ya no me pertenece, gracias a sus esfuerzos. Pero ni se le ocurra pensar que lo ataqué por un sentimiento mezquino de venganza. Estaba cumpliendo con mi trabajo.\n"+
						 "Y obviamente fracasé. Tampoco podría haberlo logrado: ya le dije una vez que usted es un capitán mucho mejor que yo.";
			link.l1 = "¡Usted mismo asumió esta carga! Su contrato expiró hace siete años. ¿Qué le impidió simplemente volver a casa?";
			link.l1.go = "ClockTower_VanDoorn_23";
		break;

		case "ClockTower_VanDoorn_23":
			dialog.text = "¿Qué le impide hacer lo mismo? Conoce la respuesta, capitán. Tiene un sueño. No tiene otra vida. Y si suelta el control, todo se derrumba.\n"+
						 "Podría haber traído orden a esta región. Detener el ciclo interminable de violencia. Si no hubiera aflojado el control. Si hubiera aplastado mi miedo e hecho lo que debí hacer hace tiempo.\n"+
						 "Pero basta de patetismo. Soy tan mal luchador como capitán, pero sé elegir a mi gente. Usted mismo se convirtió en mi última tarea, capitán. ¡Hoy en el registro de la oficina habrá dos capitanes menos!";
			if (CheckCharacterItem(PChar, "CatharinaLetter"))
			{
				link.l1 = "Estaba diciendo algo sobre el miedo. Así que lea esta carta.";
				link.l1.go = "ClockTower_VanDoorn_24";
			}
			link.l2 = "Solo uno. ¡Al combate!";
			link.l2.go = "ClockTower_cabinFight";
		break;

		case "ClockTower_VanDoorn_24":
			dialog.text = "¿¡De Catharina!? ¡¿Cómo se atreve a mezclar lo personal con el trabajo?!";
			link.l1 = "Como puede ver, la carta aún está sellada. Estoy esperando.";
			link.l1.go = "ClockTower_VanDoorn_25";
			TakeItemFromCharacter(pchar, "CatharinaLetter");
			pchar.questTemp.ClockTower_GaveCatharinaLetter = true;
		break;

		case "ClockTower_VanDoorn_25":
			dialog.text = "...ya no puede esperar más... se irá con otro... ¡¿si no regreso?!";
			link.l1 = "Ya perdió la oficina. Su tripulación está muriendo ahora mismo. ¿Está dispuesto a perder también a su familia?";
			link.l1.go = "ClockTower_VanDoorn_26";
		break;

		case "ClockTower_VanDoorn_26":
			dialog.text = "No así. Capitán, ¿acepta mi rendición?";
			link.l1 = "Sí. Lárguese de mi barco.";
			link.l1.go = "ClockTower_VanDoorn_27";
			link.l2 = "No. Esa fue la última cortesía para el condenado. ¡Al combate!";
			link.l2.go = "ClockTower_cabinFight";
		break;

		case "ClockTower_VanDoorn_27":
			dialog.text = "Entonces felicitaciones por su victoria, capitán "+GetFullName(pchar)+". Hoy el registro tendrá solo un capitán menos. Adiós.";
			link.l1 = "...";
			link.l1.go = "ClockTower_cabinPeace";
			GiveItem2Character(PChar, "pistol15");
			RemoveCharacterEquip(npchar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(npchar, GUN_ITEM_TYPE);
			TakeItemFromCharacter(npchar, "pistol15");
		break;
		
		// Финальный диалог с Маартеном
		case "ClockTower_Visser_101":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+" "+GetFullName(pchar)+". No esperaba que se atreviera a venir aquí.";
			link.l1 = "¿Por qué no? Todavía soy su cliente, y necesito los servicios de la oficina.";
			link.l1.go = "ClockTower_Visser_102";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_102":
			dialog.text = "Servicios? ¡SERVICIOS?! ¿Después de lo que hizo? ¡Es usted enemigo de la estimada Compañía Neerlandesa de las Indias Occidentales! ¡Otro capitán ocupará su lugar de cliente!";
			link.l1 = "Lo dudo. Mire lo que encontré en los papeles de van Doorn.";
			link.l1.go = "ClockTower_Visser_103";
		break;

		case "ClockTower_Visser_103":
			dialog.text = "...";
			link.l1 = "Su predecesor consideró que estaba por debajo de su dignidad usar este documento, incluso cuando su silla empezó a tambalearse.";
			link.l1.go = "ClockTower_Visser_104";
			TakeItemFromCharacter(pchar, "Visser_Key");
		break;

		case "ClockTower_Visser_104":
			dialog.text = "...";
			link.l1 = "Tuvo suerte de tener tal superior. Por tales artimañas le esperaría un juicio, en el mejor de los casos.";
			link.l1.go = "ClockTower_Visser_105";
		break;

		case "ClockTower_Visser_105":
			dialog.text = "...";
			link.l1 = "Es usted un hombre de negocios. Sabe adónde voy con esto.";
			link.l1.go = "ClockTower_Visser_106";
		break;

		case "ClockTower_Visser_106":
			dialog.text = "Usted... Su lugar en el registro está restaurado.";
			link.l1 = "Ah, Maarten. Quería ocupar el lugar del director, aunque él le dio todo. Lo salvó del juicio y ni siquiera consideró necesario informarle.";
			link.l1.go = "ClockTower_Visser_107";
		break;

		case "ClockTower_Visser_107":
			dialog.text = "...";
			link.l1 = "Este pecadillo nunca le permitirá ascender más alto y lo dejará viviendo en constante miedo.";
			link.l1.go = "ClockTower_Visser_108";
		break;

		case "ClockTower_Visser_108":
			dialog.text = "...";
			link.l1 = "Ahora es su turno de estar encadenado a este lugar. Pero ciertamente no tendrá un adjunto como el que tenía van Doorn.";
			link.l1.go = "ClockTower_Visser_109";
		break;

		case "ClockTower_Visser_109":
			dialog.text = "¡Basta! ¿Quiere acabar conmigo completamente?!";
			link.l1 = "No del todo. Quiero que registre mi nuevo barco en el registro. No quiero malentendidos.";
			link.l1.go = "ClockTower_Visser_110";
		break;

		case "ClockTower_Visser_110":
			dialog.text = "Su barco es el Amsterdam. Buque insignia de la CNIOC. No se puede simplemente... volver a registrar.";
			link.l1 = "¿Por qué no? El papel lo aguanta todo. ¿No es así como funciona su sistema?";
			link.l1.go = "ClockTower_Visser_111";
		break;

		case "ClockTower_Visser_111":
			dialog.text = "¡Dios mío, pero todo tiene límites!";
			link.l1 = "Creo en el poder de este lugar. Usted también debería.";
			link.l1.go = "ClockTower_Visser_112";
		break;

		case "ClockTower_Visser_112":
			dialog.text = "...";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_113";
		break;

		case "ClockTower_Visser_113":
			dialog.text = "Nombre completo?";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "ClockTower_Visser_114";
		break;

		case "ClockTower_Visser_114":
			dialog.text = "Nacionalidad?";
			link.l1 = ""+NationNameNominative(sti(pchar.baseNation))+".";
			link.l1.go = "ClockTower_Visser_115";
		break;

		case "ClockTower_Visser_115":
			dialog.text = "Nombre de su barco?";
			link.l1 = ""+PChar.Ship.Name+".";
			link.l1.go = "ClockTower_Visser_116";
		break;

		case "ClockTower_Visser_116":
			shipType = XI_ConvertString(GetShipTypeName(pchar));
			dialog.text = "Tipo de embarcación?";
			link.l1 = ""+shipType+".";
			link.l1.go = "ClockTower_Visser_117";
		break;

		case "ClockTower_Visser_117":
			dialog.text = "Número de cañones?";
			link.l1 = ""+GetCannonQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_118";
		break;

		case "ClockTower_Visser_118":
			dialog.text = "Tamaño de la tripulación?";
			link.l1 = ""+GetMaxCrewQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_119";
		break;

		case "ClockTower_Visser_119":
			dialog.text = "Bien. Ahora firme aquí. Y aquí. Y aquí también.";
			link.l1 = "¿Eso es todo?";
			link.l1.go = "ClockTower_Visser_120";
		break;

		case "ClockTower_Visser_120":
			dialog.text = "Eso es todo.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_Visser_pausa_1");
		break;

		case "ClockTower_Visser_121":
			dialog.text = "...";
			link.l1 = "Olvidó decir algo.";
			link.l1.go = "ClockTower_Visser_122";
		break;

		case "ClockTower_Visser_122":
			dialog.text = "\nBienvenido al registro de clientes de la estimada Compañía Neerlandesa de las Indias Occidentales.";
			link.l1 = "Hasta luego, mynheer director.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_FINAL");
		break;
		

		//------------------Услуги конторы------------------//
		case "ClockTower_OfficeServices":
			if (npchar.id == "ClockTower_VanDoorn")
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+" "+pchar.name+". ¿En qué puedo ayudarlo hoy yo y mi oficina?";
			}
			if (npchar.id == "ClockTower_Visser")
			{
				if (CharacterIsAlive("ClockTower_VanDoorn"))
				{
					dialog.text = "¡Me alegra verlo, "+GetTitle(NPChar, false)+"! Siempre a su servicio. ¿Qué le interesa hoy?";
				}
				else
				{
					dialog.text = "¿Bien? ¿Qué le interesa hoy?";
				}
			}
			link.l1 = "¿Realizará una auditoría de mi embarcación? Quiero mejorar sus características.";
			link.l1.go = "ClockTower_OfficeServices_audit"; // Аудит
			link.l2 = "No estoy satisfecho con la especialización de mi barco. ¿Conseguirá nuevos documentos?";
			link.l2.go = "ClockTower_OfficeServices_changeTrait"; // Смена документов
			link.l3 = "¿Registrará mi barco en el registro de la compañía? Que los piratas y cazadores lo piensen dos veces.";
			link.l3.go = "ClockTower_OfficeServices_buffSpec"; // Занесение в реестр
			if (!CheckAttribute(pchar, "questTemp.ShipInsurance"))
			{
				link.l4 = "Quiero asegurar mis barcos en los almacenes portuarios. Barcos actuales y futuros.";
				link.l4.go = "ClockTower_OfficeServices_Insurance"; // Страховка (пропадает после оплаты)
			}
			if(!CheckAttributeEqualTo(npchar, "last_logbook_date", LastSpeakDate()) && ClockTower_JournalsQty() > 0)
			{
				link.l5 = "¿Acepta los diarios de los capitanes piratas?";
				link.l5.go = "ClockTower_OfficeServices_logbook"; // Награда за пиратов (раз в сутки)
			}
			link.l6 = "Quizás no hoy. Buen día.";
			link.l6.go = "ClockTower_OfficeServices_exit"; // Отказ
		break;

		// Аудит
		case "ClockTower_OfficeServices_audit":
			if (!IsShipInPort(npchar.city))
			{
				ClockTower_NoShipInPort(link);
				break;
			}
			n = 0;
			dialog.text = "El costo depende del tamaño del barco. ¿De qué barco se trata?";
			for (i = 0; i < COMPANION_MAX; i++)
			{
				idx = GetCompanionIndex(pchar, i);
				if (idx < 0) continue;

				sld = GetCharacter(idx);
				realShip = GetRealShip(GetCharacterShipType(sld));
				if (CheckAttribute(realShip, "tuning.Audit")) continue;
				if (!IsFellowOurCrew(sld)) continue;

				n++;
				sTemp = "l"+n;
				link.(sTemp) = XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName) + " '" + sld.Ship.Name + "'.";
				link.(sTemp).go = Dialog.currentNode + "_chosenIdx/" + idx;
			}

			if (n == 0)
			{
				dialog.text = "Lamentablemente, la auditoría es un servicio único para cada barco individual. ¿Algo más?";
				link.l1 = "Entonces en otra ocasión.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_audit_chosenIdx":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			sTemp = "";
			if (CanUpgradeShip(sld, &sTemp, "Audit"))
			{
				n = GetAuditShipCost(sld);
				dialog.text = "Veamos... Esto costará " + n + " doblones.";
				if (PCharDublonsTotal() > n)
				{
					link.l1 = "Proceda.";
					link.l1.go = "ClockTower_OfficeServices_audit_upgradeShip";
				}
				link.l2 = "Aunque... hagámoslo en otra ocasión.";
				link.l2.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "Kaleuche")
			{
				dialog.text = "Me veo obligado a rechazar su solicitud. Según el registro, su barco fue a parar al diablo del mar hace muchos años, y un fantasma así del pasado no puede borrarse con un simple trazo de pluma. Antes de que podamos cooperar, deberá restaurarlo. Dicen que en Isla Tesoro hay un maestro dispuesto a encargarse de ese trabajo.";
				link.l1 = "Claro, gracias.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "alreadyUpgraded")
			{
				dialog.text = "$El barco ya ha sido mejorado.";
				link.l1 = "Claro, gracias.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_audit_upgradeShip":
			Achievment_Set("ach_CL_199");
			sld = GetCharacter(sti(Dialog.tmpIdx));
			RemoveDublonsFromPCharTotal(GetAuditShipCost(sld));
			UpgradeShipAudit(sld);
			dialog.text = "Listo.";
			link.l1 = "Gracias.";
			link.l1.go = "ClockTower_OfficeServices_exit";
		break;

		// Улучшение специализации
		case "ClockTower_OfficeServices_buffSpec":
			if (!IsShipInPort(npchar.city))
			{
				ClockTower_NoShipInPort(link);
				break;
			}
			n = 0;
			dialog.text = "El costo depende del tamaño del barco. ¿De qué barco se trata?";
			for (i = 0; i < COMPANION_MAX; i++)
			{
				idx = GetCompanionIndex(pchar, i);
				if (idx < 0) continue;

				sld = GetCharacter(idx);
				realShip = GetRealShip(GetCharacterShipType(sld));
				if (CheckAttribute(realShip, "tuning.SpecialityUpgrade")) continue;
				if (!IsFellowOurCrew(sld)) continue;

				n++;
				sTemp = "l"+n;
				link.(sTemp) = XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName) + " '" + sld.Ship.Name + "'.";
				link.(sTemp).go = Dialog.currentNode + "_chosenIdx/" + idx;
			}

			if (n == 0)
			{
				dialog.text = "Lamentablemente, la inscripción en el registro es un servicio único para cada barco individual. ¿Algo más?";
				link.l1 = "Entonces en otra ocasión.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_buffSpec_chosenIdx":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			sTemp = "";
			if (CanUpgradeShip(sld, &sTemp, "SpecialityUpgrade"))
			{
				n = GetSpecialityUpgradeShipCost(sld);
				dialog.text = "Veamos... Esto costará " + n + " doblones.";
				if (PCharDublonsTotal() > n)
				{
					link.l1 = "Proceda.";
					link.l1.go = "ClockTower_OfficeServices_buffSpec_upgradeShip";
				}
				link.l2 = "Aunque... hagámoslo en otra ocasión.";
				link.l2.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "Kaleuche")
			{
				dialog.text = "Me veo obligado a rechazar su solicitud. Según el registro, su barco fue a parar al diablo del mar hace muchos años, y un fantasma así del pasado no puede borrarse con un simple trazo de pluma. Antes de que podamos cooperar, deberá restaurarlo. Dicen que en Isla Tesoro hay un maestro dispuesto a encargarse de ese trabajo.";
				link.l1 = "Claro, gracias.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "alreadyUpgraded")
			{
				dialog.text = "$El barco ya ha sido mejorado.";
				link.l1 = "Claro, gracias.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_buffSpec_upgradeShip":
			Achievment_Set("ach_CL_199");
			sld = GetCharacter(sti(Dialog.tmpIdx));
			RemoveDublonsFromPCharTotal(GetSpecialityUpgradeShipCost(sld));
			UpgradeShipSpeciality(sld);
			dialog.text = "Listo.";
			link.l1 = "Gracias.";
			link.l1.go = "ClockTower_OfficeServices_exit";
		break;

		// Смена трейта корабля
		case "ClockTower_OfficeServices_changeTrait":
			if (!IsShipInPort(npchar.city))
			{
				ClockTower_NoShipInPort(link);
				break;
			}
			n = 0;
			dialog.text = "El costo depende del tamaño del barco. ¿De qué barco se trata?";
			for (i = 0; i < COMPANION_MAX; i++)
			{
				idx = GetCompanionIndex(pchar, i);
				if (idx < 0) continue;

				sld = GetCharacter(idx);
				realShip = GetRealShip(GetCharacterShipType(sld));
				sTemp = "";
				ShipTraitCanBeChanged(sld, &sTemp);
				if (sTemp == "EmptyShip" || sTemp == "QuestCompanion") continue;

				n++;
				sTemp = "l"+n;
				link.(sTemp) = XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName) + " '" + sld.Ship.Name + "'.";
				link.(sTemp).go = Dialog.currentNode + "_chosenIdx/" + idx;
			}

			if (n == 0)
			{
				dialog.text = "Hmmm. No veo ninguno de sus barcos en el puerto.";
				link.l1 = "Entonces en otra ocasión.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_changeTrait_chosenIdx":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			sTemp = "";

			if (ShipTraitCanBeChanged(sld, &sTemp))
			{
				n = GetChangeShipTraitCost(sld);
				dialog.text = "Veamos... Esto costará " + n + " doblones.";
				if (PCharDublonsTotal() > n)
				{
					link.l1 = "Proceda.";
					link.l1.go = "ClockTower_OfficeServices_changeTrait_upgradeShip";
				}
				link.l2 = "Aunque... hagámoslo en otra ocasión.";
				link.l2.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "QuestSP")
			{
				dialog.text = "Lamento decirle que eso no es posible. Su barco es un ejemplar único, rodeado de leyendas. Un rasgo de pluma no cambiará eso.";
				link.l1 = "Claro, gracias.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
			else
			{
				dialog.text = "¿De qué especialización está hablando? Su barco es universal, sin características destacadas.";
				link.l1 = "Bueno saberlo, gracias.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_changeTrait_upgradeShip":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			NextDiag.CurrentNode = "ClockTower_OfficeServices";
			DialogExit();
			LaunchChangeShipTraitScreen(sld);
		break;

		// Страховка
		case "ClockTower_OfficeServices_Insurance":
			n = GetInsuranceCost();
			dialog.text = "Veamos... Esto costará " + n + " doblones.";
			if (PCharDublonsTotal() > n)
			{
				link.l1 = "Proceda.";
				link.l1.go = "ClockTower_OfficeServices_Insurance_done";
			}
			link.l2 = "Aunque... hagámoslo en otra ocasión.";
			link.l2.go = "ClockTower_OfficeServices_exit";
		break;

		case "ClockTower_OfficeServices_Insurance_done":
			pchar.questTemp.ShipInsurance = true;
			RemoveDublonsFromPCharTotal(GetInsuranceCost());
			dialog.text = "Listo.";
			link.l1 = "Gracias.";
			link.l1.go = "ClockTower_OfficeServices_exit";
			Achievment_Set("ach_CL_199");
		break;

		// Награда за пиратов
		case "ClockTower_OfficeServices_logbook":
			dialog.text = "Correcto. La recompensa depende del número de diarios y de la peligrosidad relativa de sus dueños.\n" +
						  "¿Cuántos diarios ha traído?";
			link.l1 = "" + ClockTower_JournalsQty();
			link.l1.go = "ClockTower_OfficeServices_logbook_1";
		break;

		case "ClockTower_OfficeServices_logbook_1":
			dialog.text = "La compañía le agradece su trabajo. Se le deben " + JournalsCost() + " doblones. Por favor, recíbalos y firme aquí.";
			link.l1 = "Gracias.";
			link.l1.go = "ClockTower_OfficeServices_exit";
			npchar.last_logbook_date = LastSpeakDate();
			Achievment_Set("ach_CL_199");
		break;

		case "ClockTower_OfficeServices_exit":
			DialogExit();
			NextDiag.CurrentNode = "ClockTower_OfficeServices";
		break;

		case "ClockTower_cabinFight":
			QuestAboardCabinDialogExitWithBattle("");
			DialogExit();
			ClockTower_CabinFight2();
		break;
		
		case "ClockTower_cabinPeace":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_cabinPeace");
		break;
	}
}

void ClockTower_NoShipInPort(ref link)
{
	dialog.text = "No veo su barco en el puerto.";
	link.l1 = "Entonces en otra ocasión.";
	link.l1.go = "ClockTower_OfficeServices_exit";
}

int ClockTower_PlaySound_rh2(string name)
{
    float x = stf(loadedLocation.locators.reload.houseO2.x);
    float y = stf(loadedLocation.locators.reload.houseO2.y);
    float z = stf(loadedLocation.locators.reload.houseO2.z);
    return SendMessage(Sound, "lslfff", MSG_SOUND_EVENT_PLAY, name, 0, x, y, z);
}
