void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
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

		case "Naemnik":
			dialog.text = "Eres buen"+GetSexPhrase("o","a")+"... endemoniadamente buen"+GetSexPhrase("o","a")+". Pero antes de que termines el trabajo, escúchame. Estoy seguro de que lo que tengo que decir te interesará.";
			link.l1 = "Está bien, puedes hablar antes de morir. Pero no te hagas ilusiones. No saldrás de esta cueva.";
			link.l1.go = "Naemnik_2";
		break;

		case "Naemnik_2":
			dialog.text = "El jefe del puerto, ¿verdad? ¿Él fue quien te envió por mi cabeza?";
			link.l1 = "Eres perspicaz.";
			link.l1.go = "Naemnik_3";
		break;

		case "Naemnik_3":
			dialog.text = "Te envió para matarme, ¿no es así? ¿No capturarme, no detenerme, sino matarme?";
			link.l1 = "Exacto. ¿Y qué con eso?";
			link.l1.go = "Naemnik_4";
		break;

		case "Naemnik_4":
			dialog.text = "Oh... eres un"+GetSexPhrase(" idiota","a tonta")+". ¿Alguna vez te detuviste a pensar por qué quiere que me maten en lugar de encerrarme? ¿No? No tienes ni idea de a quién estás intentando salvar. Esa araña del puerto ha tejido una red de mentiras por todo este lugar, y tú, "+GetSexPhrase("chico","chica")+", estás atrapad"+GetSexPhrase("o","a")+" en ella.\n¿Crees que es un administrador honesto? ¡Ja! La honestidad solo la sueña. Vende información a piratas y holandeses. Traiciona a quienes confían en él. ¡Un escoria como él solo merece estar bajo tierra!";
			link.l1 = "¿Y tú acaso no estás libre de pecado? Tampoco pareces un monje.";
			link.l1.go = "Naemnik_5";
		break;

		case "Naemnik_5":
			dialog.text = "No lo parezco, ni pretendo serlo. Mi espada nunca miente. Basta una mirada y el hombre entiende: la muerte ha venido por él. No sonrío a mis víctimas, no les doy la mano sabiendo que están condenadas. No. Mis intenciones son claras. Pero ese burócrata...\nTraiciona a todos los que confían en él, y lo hace con cara de estar ayudándoles. Es peor que cualquier bastardo que haya enviado al otro mundo.";
			link.l1 = "Supongamos que dices la verdad. ¿Quién te contrató?";
			link.l1.go = "Naemnik_6";
		break;

		case "Naemnik_6":
			dialog.text = "No te diré el nombre - ni siquiera lo sé. Pero fue alguien que sufrió por culpa de ese desgraciado. Una persona que busca justicia... o venganza. Llámalo como quieras, el resultado es el mismo. ¡Quinientos doblones por la cabeza de ese burócrata podrido! Ayúdame, y compartiremos la recompensa.";
			link.l1 = "¡Basta de cháchara! Dirías cualquier cosa para salvar tu pellejo. Ya te dejé hablar"+GetSexPhrase("","a")+", ahora es hora de morir.";
			link.l1.go = "Naemnik_7";
			link.l2 = "Bonita historia. Pero no voy a creerte solo por tu palabra. ¿Tienes algo más que cuentos? ¿Pruebas, testigos? ¿O esto es solo otro truco para evitar la muerte?";
			link.l2.go = "Naemnik_8";
		break;
		
		case "Naemnik_7":
			DialogExit();
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("GS_Naemnik");
			LAi_SetImmortal(sld, false);
			LAi_SetCurHPMax(sld);
			LAi_GetCharacterMaxEnergy(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheckFunction("EnemyFight", "GS_UbivaemNaemnika");
		break;
		
		case "Naemnik_8":
			dialog.text = "Estos documentos fueron encontrados en el camarote de un pirata que mi cliente venció en combate. Recibía información del jefe del puerto. Las notas detallan claramente las rutas de los barcos, las fechas de salida al mar y las cargas que transportaban. Las rutas coinciden con aquellas de los barcos que fueron saqueados, destruidos o desaparecieron sin dejar rastro.\nY lo más importante: la caligrafía coincide exactamente con la de los documentos de carga oficiales. Estas notas son la clave para desenmascararlo. Mi cliente quiere que terminen en el cadáver. Un juicio común no es suficiente.\nEse canalla es demasiado influyente y tiene muchos amigos corruptos. Si todo llegara a un tribunal, se escaparía. Gente como él no merece vivir. Una muerte deshonrosa es lo mínimo que se merece.";
			link.l1 = "¡Miserable traidor! La gente le confía sus vidas, ¡y él las vende a los piratas! Estoy dentro. No hay lugar en este mundo para alguien así.";
			link.l1.go = "Naemnik_9";
			GiveItem2Character(PChar, "GS_letters");
			AddQuestRecordInfo("GS_Letters", "1");
		break;

		case "Naemnik_9":
			dialog.text = "Tengo una llave de su casa — la conseguí a través de un carpintero que reparaba muebles en su mansión. Todo iba bien hasta que descubrí que no vivía solo. Cuando llegué para terminar el trabajo, su esposa estaba adentro.\nSu presencia me sorprendió. Nadie me pagaría por su cabeza, y las autoridades sin duda se esforzarían más por atrapar al asesino. Así que cambié el plan y lo esperé cerca del edificio de administración.";
			link.l1 = "Demonios. La ciudad entera está alerta, no podemos simplemente entrar y matarlo. ¿Qué propones?";
			link.l1.go = "Naemnik_10";
		break;

		case "Naemnik_10":
			dialog.text = "He estado vigilando la ciudad, esperando a que se calmen las aguas. Después de mi visita, ese cobarde mandó a su esposa lejos. La vi con mis propios ojos embarcarse y dejar el puerto.\nAhora está solo — es el momento perfecto para terminar lo que empezamos. Puedes entrar en su guarida por la noche y cerrar este capítulo. Luego deja los documentos a la vista, para que todos sepan qué clase de escoria era.\nPero yo no puedo volver al pueblo ahora. Tú sí puedes. Nadie te espera, puedes escabullirte fácilmente. Su casa está cerca de la prisión de la ciudad. ¡Quinientos doblones! La mitad es tuya si completas la tarea.";
			link.l1 = "De acuerdo. Yo mismo enviaré a ese bastardo al otro mundo. Esos documentos se quedarán en su casa — todos deben saber la verdad. Espérame aquí. Volveré cuando todo esté hecho.";
			link.l1.go = "Naemnik_11";
		break;
		
		case "Naemnik_11":
			DialogExit();
			chrDisableReloadToLocation = false;
			locations[FindLocation("Beliz_Cave")].DisableEncounters = false;
			AddQuestRecord("GS", "5");
			AddQuestUserData("GS", "sSex", GetSexPhrase("","а"));
			
			sld = CharacterFromID("GS_Naemnik");
			LAi_SetWarriorType(sld);
			LAi_SetCurHPMax(sld);
			LAi_GetCharacterMaxEnergy(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
			NextDiag.CurrentNode = "Naemnik_12";
			
			sld = &Locations[FindLocation("Beliz_town")];
			sld.reload.l11.open_for_night = 1;
			sld = &Locations[FindLocation("Beliz_houseS5_room2")];
			sld.locators_radius.item.button01 = 1.0;
			
			pchar.quest.GS_SoldatyDoma.win_condition.l1 = "Hour";
			pchar.quest.GS_SoldatyDoma.win_condition.l1.start.hour = 0.00;
			pchar.quest.GS_SoldatyDoma.win_condition.l1.finish.hour = 5.00;
			PChar.quest.GS_SoldatyDoma.win_condition.l2 = "location";
			PChar.quest.GS_SoldatyDoma.win_condition.l2.location = "Beliz_houseS5";
			PChar.quest.GS_SoldatyDoma.function = "GS_SoldatyDoma";
		break;
		
		case "Naemnik_12":
			dialog.text = "¿Por qué te quedas ahí como una estatua?";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Naemnik_12";
		break;

		case "Portman_1":
			dialog.text = "¿Usted? ¿Qué demonios? ¿Cómo ha llegado hasta aquí?";
			link.l1 = "Cómo llegué aquí no importa. Y creo que, en el fondo, usted ya sabe por qué he venido.";
			link.l1.go = "Portman_2";
			DelLandQuestMark(npchar);
		break;

		case "Portman_2":
			dialog.text = "¡No, no lo sé! Si ha venido por su recompensa, vuelva mañana a la oficina, se la entregaré toda.";
			link.l1 = "¡Basta de fingir inocencia! Lo sé todo. Usted vendía información a los piratas sobre los barcos de sus propios clientes. Un hombre tan vil no merece ocupar un puesto de responsabilidad. Más aún, no merece vivir entre gente honesta. Señor, su lugar está entre los suyos... en el infierno.";
			link.l1.go = "Portman_3";
		break;

		case "Portman_3":
			dialog.text = "¡Oh, no-no-no! ¡No! ¡Usted lo ha entendido todo mal! E-ellos me obligaron... Vinieron a mí y amenazaron con matar a mi familia si no colaboraba con ellos... ¡usted no lo entiende!";
			link.l1 = "¡Ya basta de excusas patéticas! Tengo en mis manos sus notas, donde exige su porcentaje por la información entregada. Su hipocresía es repugnante y no pienso tolerarla más. ¡Tome su arma y defiéndase si le queda algo de valor!";
			link.l1.go = "Portman_4";
		break;
		
		case "Portman_4":
			DialogExit();
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Beliz_portman_clone");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheckFunction("EnemyFight", "GS_PortmanDead");
		break;
		
		case "Naemnik_21":
			dialog.text = "Bueno, ¿cuáles son las noticias? ¿Está hecho el trabajo?";
			link.l1 = "¿Lo dudabas? Hizo todo lo posible por exprimir algún tipo de excusa, pero no le sirvió de nada. Dejé las notas en un lugar destacado, como acordamos.";
			link.l1.go = "Naemnik_22";
		break;

		case "Naemnik_22":
			dialog.text = "Babosas patéticas como él siempre piensan que pueden comprar su salida de la justicia con mentiras baratas y dinero.";
			link.l1 = "Bueno, ahora ya no está pensando en nada. Dame mi dinero y me iré.";
			link.l1.go = "Naemnik_23";
		break;

		case "Naemnik_23":
			dialog.text = "Aquí están tus doblones. Excelente trabajo, debo admitir. Pero sabes, si hubiera tenido algo más serio en mis manos entonces, todo podría haber sido diferente... para ti. Entre las estrechas paredes de la casa, no hay mucho espacio para maniobrar, así que tomé este patético mondadientes, planeando llevar a cabo el trabajo rápidamente\nSi hubiera sabido cómo resultarían las cosas, habría tomado una herramienta más sustancial.";
			link.l1 = "Ja-ja. ¡Y nuestro pobre hombre decía que estabas armado como el mismo Roldán antes del Paso de Roncesvalles!";
			link.l1.go = "Naemnik_24";
			AddItems(pchar, "gold_dublon", 250);
		break;

		case "Naemnik_24":
			dialog.text = "Je. Bueno, el miedo tiene ojos grandes. Tú mism"+GetSexPhrase("o","a")+" ves con qué tipo de tenedor casi toqué tu corazón.";
			link.l1 = "¿Estás diciendo que si hubieras tenido un hierro más pesado, habrías podido competir conmigo?";
			link.l1.go = "Naemnik_25";
		break;

		case "Naemnik_25":
			dialog.text = "En el manejo de armas de peso medio, soy un maestro, eso es un hecho. ¿No lo crees? Bueno, compartiré contigo un par de trucos que me han salvado más de una vez. Escucha con atención - no son solo palabras, sino algo que podría salvarte la piel algún día. Tales secretos no se cuentan a cualquiera.";
			link.l1 = "...";
			link.l1.go = "Naemnik_26";
		break;

		case "Naemnik_26":
			DialogExit();

			SetLaunchFrameFormParam("Ha pasado una hora...", "Run_Function", 0, 4.0);
			SetLaunchFrameRunFunctionParam("GS_Spravedlivost_2", 0.0);
			LaunchFrameForm();
		break;
		
		case "Naemnik_27":
			dialog.text = "...";
			link.l1 = "Veo que realmente sabes lo que haces. Gracias por la lección. Pero si eso es todo, tengo que irme.";
			link.l1.go = "Naemnik_28";
			AddComplexSelfExpToScill(0, 500, 0, 0);
		break;

		case "Naemnik_28":
			dialog.text = "Adiós, "+GetSexPhrase("capitán","guapa")+". Espero que no volvamos a encontrarnos en combate. Sería una pena tener que matarte. Ja-ja.";
			link.l1 = "No tendrás ni una sola oportunidad, incluso si estoy borrach"+GetSexPhrase("o","a")+" y sobre una sola pierna, je-je. Bueno, adiós, mercenario.";
			link.l1.go = "Naemnik_29";
		break;

		case "Naemnik_29":
			DialogExit();
			chrDisableReloadToLocation = false;
			locations[FindLocation("Beliz_Cave")].DisableEncounters = false;
			LAi_SetPlayerType(pchar);

			LAi_SetWarriorType(npchar);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PEACE);

			AddQuestRecord("GS", "7");
			CloseQuestHeader("GS");

			AddSimpleRumourCity("Dicen que encontraron al jefe del puerto muerto en su propia casa. Junto a él se hallaron notas que demuestran su implicación en las desapariciones de barcos. Qué vergüenza para nuestra ciudad...", "Beliz", 30, 1, "");
			AddSimpleRumourCity("¿Ya lo oíste? Alguien se metió en la casa del jefe del puerto, mató a la guardia y lo ejecutó. En el cadáver se encontraron notas con rutas de barcos desaparecidos — ¡escritas por él mismo! ¡Un servidor de la corona y en realidad, un traidor! ¡Recibió lo que merecía! ¿Y el gobernador? ¿Dónde ha estado todo este tiempo?", "Beliz", 30, 1, "");
			AddSimpleRumourCity("¡El jefe del puerto ha sido asesinado! ¡En su propia casa! La guardia fue aniquilada y entre sus pertenencias se encontraron notas con las rutas de los barcos desaparecidos. No cabe duda, fue obra suya. Al fin, la justicia lo alcanzó.", "Beliz", 30, 1, "");
		break;
	}
}