void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arTmp;
	int i, n;
	string sTemp, sStr;
	
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
			dialog.text = "¿Qué necesitas?";
			link.l1 = "Nada.";
			link.l1.go = "exit";
		break;
		
		// Квест "Путеводная звезда"
		// Этап 0, ПРОЛОГ
		case "PZ_Alonso_1":
			dialog.text = "Me disculpo por irrumpir en sus aposentos, Señor Capitán, pero esto es muy importante.";
			link.l1 = "Espero que así sea, Alonso. Si cada uno de ustedes empieza a irrumpir aquí como si fuera su propio espacio, tendremos un problema. Así que, ¿qué está pasando?";
			link.l1.go = "PZ_Alonso_2";
		break;
		
		case "PZ_Alonso_2":
			dialog.text = "Encontramos que tu casillero había sido saqueado.";
			link.l1 = "¿Qué?! Espera... ¿Cómo lo averiguaste? ¿Y qué estaban haciendo todos en mi camarote?";
			link.l1.go = "PZ_Alonso_3";
		break;
		
		case "PZ_Alonso_3":
			dialog.text = "Limpíamos tus camarotes de vez en cuando cuando estás fuera, ya sea en la ciudad o descansando en las literas. ¿Nunca te diste cuenta? ¿O simplemente lo olvidaste?";
			link.l1 = "Oh, eso es correcto. Bueno, puedes irte ahora.";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_Tichingitu_1":
			dialog.text = "Capitán Charles, ¡mire! Alguien estuvo hurgando en su gran cajón.";
			link.l1 = "¿Qué? ¿Cuándo te diste cuenta de esto? ¿Sabes quién fue?";
			link.l1.go = "PZ_Tichingitu_2";
		break;
		
		case "PZ_Tichingitu_2":
			dialog.text = "No hace mucho, cuando venía a verte. Los espíritus guardan silencio sobre quién podría ser.";
			link.l1 = "Es un buen detalle, Tichingitu. Ahora, si me disculpas, necesito verificar si falta algo.";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_Duran_1":
			dialog.text = "Hola, Capitán, ¿qué estás mirando? Alguien ha estado hurgando en tus cosas. Incluso yo me di cuenta.";
			link.l1 = "¿No fuiste tú? Después de todo, no te pago tan generosamente como Francois.";
			link.l1.go = "PZ_Duran_2";
		break;
		
		case "PZ_Duran_2":
			dialog.text = "Je, si yo fuera el ladrón, no te lo diría, ¿verdad? Me llevaría los objetos de valor y limpiaría después. Este desorden no es mi estilo.";
			link.l1 = "Odio admitirlo, pero tienes razón. Bueno, Claude, guarda tus pullas para después. Tengo que verificar qué se llevó el ladrón.";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_Folke_1":
			dialog.text = "Capitán, hoy noté que alguien había hurgado en tu casillero. ¿No te diste cuenta?";
			link.l1 = "¿Qué? No estoy revisando constantemente el armario, Folke, y ni siquiera estoy en la cabina todo el tiempo. Dime honestamente, ¿fuiste tú? ¿Te equivocaste de nuevo y sacaste más préstamos bancarios la última vez que estuvimos en tierra?";
			link.l1.go = "PZ_Folke_2";
		break;
		
		case "PZ_Folke_2":
			dialog.text = "Para nada, Capitán. No tengo nada suyo en mis bolsillos ni en mi baúl. Y nunca lo tendré.";
			link.l1 = "Espero que no. Puedes irte, yo revisaré qué falta.";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_OsmatrivaemKautu":
			DialogExit();
			
			if (npchar.id == "Tichingitu")
			{
				LAi_SetOfficerType(npchar);
				npchar.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
				npchar.Dialog.CurrentNode = "Tichingitu_officer";
			}
			if (npchar.id == "FMQT_mercen" || npchar.id == "Folke")
			{
				LAi_SetOfficerType(npchar);
				npchar.Dialog.Filename = "Enc_Officer_dialog.c";
				npchar.Dialog.CurrentNode = "hired";
			}
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "rld", "loc2", "PZ_OsmatrivaemSunduk", -1);
		break;
		
		case "PZ_LigaInJungle_1":
			dialog.text = "Charles de Maure, ¿verdad?";
			link.l1 = "Por la expresión en tu rostro, diría que ya conoces la respuesta. Entonces, ¿qué deseas?";
			link.l1.go = "PZ_LigaInJungle_2";
		break;
		
		case "PZ_LigaInJungle_2":
			dialog.text = "Tu cabeza.";
			link.l1 = "¡Fascinante! Debo decir que me gusta cómo empieza esta conversación. Pero antes de continuar, ¿podrías al menos decirme a quién he agraviado? Tal vez podamos negociar.";
			link.l1.go = "PZ_LigaInJungle_3";
		break;
		
		case "PZ_LigaInJungle_3":
			dialog.text = "No somos aficionados, Monsieur de Maure. Incluso si te lo dijéramos, no te serviría de nada - nuestro empleador ya ha abandonado el Archipiélago. No puedes hacerles daño ni ofrecer una disculpa. Nos han pagado, y ahora es el momento de cumplir con nuestra parte del trato.";
			link.l1 = "Si ya te han pagado, ¿por qué derramar más sangre?";
			link.l1.go = "PZ_LigaInJungle_4";
		break;
		
		case "PZ_LigaInJungle_4":
			dialog.text = "No somos aficionados. Valoramos nuestra reputación.";
			link.l1 = "Me temo que esta vez no podrás estar a la altura.";
			link.l1.go = "PZ_LigaInJungle_5";
		break;
		
		case "PZ_LigaInJungle_5":
			dialog.text = "Ya veremos. ¡Registra su cadáver cuando terminemos! ¡Quema todo lo que encuentres!";
			link.l1 = "¿Quemar qué?..";
			link.l1.go = "PZ_LigaInJungle_6";
		break;
		
		case "PZ_LigaInJungle_6":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("LigaInJungle_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_LigaInJunglePosleBitvy");
			
			if (CharacterIsHere("Longway"))
			{
				sld = characterFromId("Longway");
				LAi_SetCheckMinHP(sld, 1, true, "");
			}
		break;
		
		case "PZ_Longway_1":
			dialog.text = "Lo que dijo el hombre enmascarado... ¿Podría ser...?";
			link.l1 = "¿Qué sucede, Longway? No es la primera vez que los cazarrecompensas vienen tras de mí, pero pareces inusualmente preocupado.";
			link.l1.go = "PZ_Longway_2";
		break;
		
		case "PZ_Longway_2":
			dialog.text = "Longway cree que sabe quién envió a estos hombres tras de ti, Mi Señor Capitán.";
			link.l1 = "¿Algo de lo que deba estar al tanto?";
			link.l1.go = "PZ_Longway_3";
		break;
		
		case "PZ_Longway_3":
			dialog.text = "Esta es la manera del Lord Rodenburg: eliminar a aquellos que le han ayudado pero saben demasiado.";
			link.l1 = "¿En serio... Ese hombre enmascarado dijo que su empleador recientemente dejó el Archipiélago. ¡Eso es exactamente lo que Lucas estaba planeando! ¿Crees que deberíamos esperar más ataques?";
			link.l1.go = "PZ_Longway_4";
		break;
		
		case "PZ_Longway_4":
			dialog.text = "Es prudente estar preparado para cualquier cosa, Mi Señor Capitán.";
			link.l1 = "Palabras sabias. Así lo haremos. Pero, ¿qué buscaba Lucas? ¿Qué pensaba que tenía yo? ¿Alguna idea, Longway?";
			link.l1.go = "PZ_Longway_5";
		break;
		
		case "PZ_Longway_5":
			dialog.text = "Mm-mm, no, Longway no tiene idea de qué podría ser.";
			link.l1 = "Eso es una pena. Pero bueno, vámonos de aquí.";
			link.l1.go = "PZ_Longway_6";
		break;
		
		case "PZ_Longway_6":
			DialogExit();
			
			Return_LongwayOfficer();
			
			chrDisableReloadToLocation = false;
			pchar.questTemp.PZ_RazgovorGerrits = true;
			pchar.questTemp.PZ_PodozrenieLucas = true;
		break;
		
		// Этап 1, ВЕРНЫЙ КЛЯТВЕ
		case "PZ_Longway_11":
			dialog.text = "Mi Señor Capitán, Longway desea hablar con usted. Es de gran importancia.";
			if (CheckAttribute(pchar, "questTemp.PZ_PodozrenieLucas"))
			{
				link.l1 = "¿Qué ocurre, Longway? ¿Te preocupa la forma en que Lucas se despidió, o has descubierto algo nuevo?";
				link.l1.go = "PZ_Longway_12";
				AddCharacterExpToSkill(pchar, "Sneak", 100);
			}
			else
			{
				link.l1 = "¡Por supuesto! ¿Qué tienes en mente?";
				link.l1.go = "PZ_Longway_13";
			}
		break;
		
		case "PZ_Longway_12":
			dialog.text = "Desafortunadamente, no.";
			link.l1 = "Entonces, ¿qué es, Longway?";
			link.l1.go = "PZ_Longway_13";
		break;
		
		case "PZ_Longway_13":
			dialog.text = "Longway no puede decir. Pero... desea pedir permiso para irse.";
			link.l1 = "¿Irte? ¿Para siempre? ¿Por qué, Longway? Como tu capitán, tengo derecho a saber la razón.";
			link.l1.go = "PZ_Longway_14";
		break;
		
		case "PZ_Longway_14":
			dialog.text = "Eso es cierto, Mi Señor Capitán. Pero Longway no es ni un trabajador ni un sirviente. Vino a ayudar por su propia voluntad, y puede irse de la misma manera. No será para siempre - hay un asunto importante que atender. Longway espera regresar una vez que esté resuelto.";
			link.l1 = "¿Qué asunto es este? Dime, si no como tu capitán, al menos como alguien que ha pasado por mucho contigo.";
			link.l1.go = "PZ_Longway_15";
		break;
		
		case "PZ_Longway_15":
			dialog.text = "Todo lo que Longway puede decir es que hizo un juramento - hace mucho tiempo. Ha llegado el momento de cumplirlo. De lo contrario... no hay sentido en la vida de Longway.";
			link.l1 = "Tienes razón, Longway: no eres un prisionero, y yo no soy un carcelero. Eres libre de irte. ¡Que Dios te acompañe!";
			link.l1.go = "PZ_Longway_Otpustit_1";
			link.l2 = "Puedes irte, pero al menos dime adónde te diriges. Podría ayudar sin hacer demasiadas preguntas.";
			link.l2.go = "PZ_Longway_Pomoch_1";
			link.l3 = "Tengo una tarea importante también: salvar a mi hermano. Para eso, necesito a cada hombre, incluido tú, Longway. No podemos hacerlo sin ti.";
			link.l3.go = "PZ_Longway_NeOtpuskaem_1";
		break;
		
		case "PZ_Longway_NeOtpuskaem_1":
			dialog.text = "No intentes jugar con mi compasión o sentido del deber. Lo entiendo perfectamente. ¿Has hecho alguna vez un juramento, Mi Señor Capitán?";
			link.l1 = "Por supuesto que sí. Así que cuéntame todo tal como es, y mis hombres y yo sin duda te ayudaremos.";
			link.l1.go = "PZ_Longway_NeOtpuskaem_2";
		break;
		
		case "PZ_Longway_NeOtpuskaem_2":
			dialog.text = "Longway no puede. Simplemente... no puede. Es un gran misterio, y ni siquiera es mío para compartir.";
			link.l1 = "Es una lástima. Pensé que había confianza entre nosotros. No vas a dejar el barco, ahora tengo a todos los oficiales de mi lado.";
			link.l1.go = "PZ_Longway_NeOtpuskaem_3";
			link.l2 = "Tienes razón, Longway, no eres un prisionero y yo no soy un carcelero. Eres libre de irte. Que Dios te acompañe.";
			link.l2.go = "PZ_Longway_Otpustit_1";
		break;
		
		case "PZ_Longway_NeOtpuskaem_3":
			dialog.text = "¡No puedes hacer eso!";
			link.l1 = "Lamentablemente, puedo, Longway. Ahora vuelve a tus deberes.";
			link.l1.go = "PZ_Longway_NeOtpuskaem_4";
		break;
		
		case "PZ_Longway_NeOtpuskaem_4":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			npchar.Dialog.CurrentNode = "Longway_officer";
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			PChar.quest.PZ_LongwayUhoditOtNasNavsegda.win_condition.l1 = "MapEnter";
			PChar.quest.PZ_LongwayUhoditOtNasNavsegda.win_condition = "PZ_LongwayUhoditOtNasNavsegda";
		break;
		
		case "PZ_Longway_Otpustit_1":
			dialog.text = "No pensé que me dejarías ir tan fácilmente. Gracias, Mi Señor Capitán.";
			link.l1 = "Ah, no es nada. Pero dime, ¿dónde puedo encontrarte una vez que termines tus asuntos?";
			link.l1.go = "PZ_Longway_GdeIskat_1";
		break;
		
		case "PZ_Longway_Pomoch_1":
			dialog.text = "Longway realmente no puede decir, por más que desee poder hacerlo. Pero aprecia la disposición del Señor Capitán para ayudar.";
			link.l1 = "Que así sea. ¿Dónde debería buscarte una vez que hayas cumplido tu promesa?";
			link.l1.go = "PZ_Longway_GdeIskat_1";
			pchar.questTemp.PZ_LongwayGood = true;
		break;
		
		case "PZ_Longway_GdeIskat_1":
			dialog.text = "Espero terminar mi negocio en un mes. Después de eso, Longway te esperará una semana más en la taberna en Basse-Terre.";
			link.l1 = "Bueno, lo que digas, amigo mío. No es un adiós. Nos vemos en Basse-Terre.";
			link.l1.go = "PZ_Longway_GdeIskat_2";
		break;
		
		case "PZ_Longway_GdeIskat_2":
			DialogExit();
			
			RemovePassenger(pchar, npchar);
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			LAi_SetImmortal(npchar, true);
			npchar.location = "None";
			
			SetQuestHeader("PZ");
			AddQuestRecord("PZ", "1");
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			SetTimerCondition("PZ_IshemLongway", 0, 0, 30, false);	// ВЕРНУТЬ 30 дней
		break;
		
		case "PZ_SharliePlennik_BadFinal_1":
			dialog.text = "Bueno, hola, Capitán.";
			link.l1 = "No me gusta tu sonrisa, señor.";
			link.l1.go = "PZ_SharliePlennik_BadFinal_2";
		break;
		
		case "PZ_SharliePlennik_BadFinal_2":
			dialog.text = "Estoy devastado. Vine a decirte que finalmente eres libre. Pero si quieres quedarte más tiempo en esta lujosa cabina, eres bienvenido a hacerlo.";
			link.l1 = "En absoluto. Entonces, ¿han encontrado a Longway? ¿Dónde está? ¿En una de las celdas?";
			link.l1.go = "PZ_SharliePlennik_BadFinal_3";
		break;
		
		case "PZ_SharliePlennik_BadFinal_3":
			dialog.text = "En otro mundo más parecido - no hablaría con ninguno de nosotros y se iría directamente a la batalla.";
			link.l1 = "¡Maldita sea! Podrías haberlo capturado.";
			link.l1.go = "PZ_SharliePlennik_BadFinal_4";
		break;
		
		case "PZ_SharliePlennik_BadFinal_4":
			dialog.text = "Algunas personas son mucho más fáciles de matar que de capturar, ¿no lo sabías? Deberías estar agradecido de que no tengamos nada contra ti: tu chino causó otra masacre, y necesitamos varias unidades más con tiradores para lidiar con él.";
			link.l1 = "Sí, en efecto. Gracias por eso.";
			link.l1.go = "PZ_SharliePlennik_BadFinal_5";
		break;
		
		case "PZ_SharliePlennik_BadFinal_5":
			dialog.text = "Hablando de eso, como era tu amigo, encontramos algunos papeles en él. No entendimos qué eran, tú probablemente lo sabrías mejor. Había algunos garabatos escritos en las partes que no estaban cubiertas de sangre.";
			link.l1 = "Eso es... Mierda. Gracias por devolverlos. Adiós, oficial.";
			link.l1.go = "PZ_SharliePlennik_BadFinal_6";
		break;
		
		case "PZ_SharliePlennik_BadFinal_6":
			DialogExit();
			
			LAi_ActorGoToLocator(npchar, "goto", "goto22", "", -1);
			DoQuestCheckDelay("PZ_SharliePlennik_BadFinal_2", 3.0);
		break;
		
		case "PZ_BasTerStop":
			dialog.text = "Ven con nosotros, el Comandante desea hablar contigo.";
			link.l1 = "Supongo que esto tiene que ver con mi búsqueda del chino?";
			link.l1.go = "PZ_BasTerStop_2";
		break;
		
		case "PZ_BasTerStop_2":
			dialog.text = "Lo verás por ti mismo, monsieur.";
			link.l1 = "¿Se me acusa de algo?";
			link.l1.go = "PZ_BasTerStop_3";
		break;
		
		case "PZ_BasTerStop_3":
			dialog.text = "En absoluto. Nadie intenta arrestarte o detenerte. Por ahora. Cuando dije que el Comandante desea hablar contigo, quise decir exactamente eso.";
			link.l1 = "Ah, bueno...";
			link.l1.go = "PZ_BasTerStop_4";
		break;
		
		case "PZ_BasTerStop_4":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("BasTer_town")], false);
			DoQuestReloadToLocation("BasTer_prison", "goto", "goto17", "PZ_BasTer_TurmaPriveli");
		break;
		
		case "PZ_BasTer_OtryadPeshera_1":
			dialog.text = "¿Tienes alguna idea? Este hombre de piel amarilla es mortalmente peligroso. No somos el primer escuadrón enviado aquí. Las órdenes son las órdenes, pero no quiero morir estúpidamente al entrar sin un plan sólido.";
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				link.l1 = "Está solo ahí dentro, y yo estoy contigo. Me encargaré de él - ustedes concéntrense en cubrirme. Lo lograremos.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_2";
				if (pchar.location.from_sea != "BasTer_Town")
				{
					link.l2 = "Tengo uno. Todos vais a morir - justo aquí.";
					link.l2.go = "PZ_BasTer_OtryadPeshera_Kill_1";
				}
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				link.l1 = "No te preocupes, solo vamos a hablar con él.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_2";
				if (pchar.location.from_sea != "BasTer_Town")
				{
					link.l2 = "Lo siento, pero todos van a morir hoy. Y no será a manos de un chino.";
					link.l2.go = "PZ_BasTer_OtryadPeshera_Kill_1";
				}
			}
		break;
		
		case "PZ_BasTer_OtryadPeshera_Kill_1":
			pchar.questTemp.PZ_Podelnik = true;
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "Entonces no eres un cazador de recompensas... ¡Pero incluso si lo eres, eres amigo de ese maldito chino!";
				link.l1 = "Así es. Tendría que deshacerme de ti de todos modos, no tiene sentido retrasar lo inevitable.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_Kill_2";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "¿Qué quieres decir?! ¡Prometiste ayudar!";
				link.l1 = "Creo que de todos modos no nos habrías dado una salida pacífica. No es nada personal.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_Kill_2";
			}
		break;
		
		case "PZ_BasTer_OtryadPeshera_Kill_2":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			chrDisableReloadToLocation = true;
			
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			sld = CharacterFromID("PZ_BasTer_OtryadPesheraOff");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_BasTer_OtryadPeshera_Kill_3");
		break;
		
		case "PZ_BasTer_OtryadPeshera_2":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "Me gustaría creer eso.";
				link.l1 = "Me he enfrentado a peores. Un chino no será nuestro fin. ¡Vamos, muchachos!";
				link.l1.go = "PZ_BasTer_OtryadPeshera_3";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "¿Y si la conversación no sale como planeamos?";
				link.l1 = "Odiaría eso, pero entonces tendré que defenderme. Vamos.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_3";
			}
		break;
		
		case "PZ_BasTer_OtryadPeshera_3":
			DialogExit();
			
			DoQuestReloadToLocation("Guadeloupe_CaveEntrance", "reload", "reload2", "PZ_IshemLongway_OtryadUPeshery");
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway":
			dialog.text = "¿¡Señor Capitán!? ¡Longway no puede creer que estés con ellos!";
			link.l1 = "¡No, Longway, solo estoy aquí para hablar! ¡No es lo que piensas!";
			link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_2";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_2":
			dialog.text = "¡Entonces habrías venido solo! ¡Estás tratando de bajar mi guardia para atacarme con la ayuda de estos soldados!";
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayGood"))
			{
				link.l1 = "Si pudiera, lo haría. Soy la única razón por la que aún no te han atacado. Cálmate y hablemos, sí, ¿eh?";
				link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_3";
			}
			else
			{
				link.l1 = "¡Deja de tonterías! Si quisiera, ya te habría matado. Depón las armas, y hablaremos. Eso es una orden de tu capitán.";
				link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_Bad_1";
			}
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_3":
			dialog.text = "Aye. Longway confía en usted, Mi Señor Capitán.";
			link.l1 = "Ahí, eso es mejor. Ahora, dime...";
			link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_4";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_4":
			StartInstantDialog("PZ_BasTer_OtryadPesheraOff", "PZ_BasTer_SOtryadom_DialogLongway_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_5":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "Monsieur, ¿qué está pasando? ¿Qué es esta... conmovedora reunión? Se suponía que debías ayudarnos a eliminar a ese salvaje chino, ¿no es así?";
				link.l1 = "Lo soy. Me lo llevo conmigo, y toda esta matanza se detendrá. Dirás al comandante que lo matamos juntos. ¿Trato?";
				link.l1.go = "PZ_BasTer_SOtryadomOhotnik_1";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "¡Bien hecho, Capitán! Ha depuesto sus armas. Es bueno tenerte con nosotros. Ahora llevémoslo al comandante.";
				link.l1 = "¿Por qué haría eso? Pagué una multa en oro por las acciones de Longway, una generosa. Tus compañeros oficiales fueron testigos, lo confirmarán. El comandante me autorizó a llevar a mi hombre conmigo al barco.";
				link.l1.go = "PZ_BasTer_SOtryadomDrug_1";
			}
		break;
		
		case "PZ_BasTer_SOtryadomDrug_1":
			dialog.text = "El comandante podría tener suficiente de este oro sangriento, pero yo no. Algunos de los hombres que mató en esa cueva sangrienta eran mis amigos. Además, dudo que le importe si matamos al chino de todos modos.";
			link.l1 = "¿Estás seguro de que quieres averiguarlo? Y sobre tus amigos que fueron asesinados... ¿alguna vez oíste hablar de esa descarada banda de bandidos? Debieron ser ellos.";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_2";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_2":
			StartInstantDialog("Longway", "PZ_BasTer_SOtryadomDrug_3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_BasTer_SOtryadomDrug_3":
			dialog.text = "";
			link.l1 = "Longway, no mataste a tantos soldados como dicen, ¿verdad?";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_4";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_4":
			dialog.text = "Así es, Mi Señor Capitán. Longway vio a esa banda. Se escondieron más adentro de la cueva para que no lo notaran. Y Longway escuchó sonidos de conversación, maldiciones y peleas entre los bandidos y los soldados.";
			link.l1 = "";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_5";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_5":
			StartInstantDialog("PZ_BasTer_OtryadPesheraOff", "PZ_BasTer_SOtryadomDrug_6", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_BasTer_SOtryadomDrug_6":
			dialog.text = "";
			link.l1 = "¿Ves? Todo encaja. Longway puede tener mal genio, pero es un hombre honesto. Nos vamos. Si nos tocan, deshonrarán su uniforme. Adiós, caballeros.";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_7";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_7":
			DialogExit();
			
			AddQuestRecord("PZ", "13");
			LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_CaveEntrance")], false);
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "PZ_BasTer_OtryadRazveli", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				LAi_CharacterDisableDialog(sld);
			}
			sld = CharacterFromID("PZ_BasTer_OtryadPesheraOff");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "PZ_BasTer_OtryadRazveli", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_CharacterDisableDialog(sld);
			
			sld = CharacterFromID("Longway");
			AddPassenger(pchar, sld, false);
			LAi_SetImmortal(sld, false);
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.Dialog.CurrentNode = "Longway_officer";
			
			DeleteQuestCondition("PZ_LongwayNelzyaUmeret");
			
			//Продолжение второго этапа
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition = "PZ_LongwayRazgovorVKaute";
		break;
		
		case "PZ_BasTer_SOtryadomOhotnik_1":
			dialog.text = "¡De ninguna manera, monsieur! Mató a un montón de nuestros hombres, ¿y ahora dices que se saldrá con la suya? ¡O nos ayudas a matar al bastardo, o al menos mantente malditamente fuera de nuestro camino!";
			link.l1 = "Tengo miedo de que tenga que intervenir. Lo siento, de verdad.";
			link.l1.go = "PZ_BasTer_SOtryadomOhotnik_2";
		break;
		
		case "PZ_BasTer_SOtryadomOhotnik_2":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Longway");
			LAi_SetImmortal(sld, false);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_CharacterDisableDialog(sld);
			}
			sld = CharacterFromID("PZ_BasTer_OtryadPesheraOff");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_CharacterDisableDialog(sld);
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_IshemLongway_Zastupaemsya");
			
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1 = "NPC_Death";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1.character = "Longway";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition = "PZ_LongwayNelzyaUmeret";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_Bad_1":
			dialog.text = "Si solo quisieras hablar, no me pedirías que me desarmara. Pero un tigre sigue siendo un tigre, incluso con las garras retraídas. Debes haber decidido traicionar a Longway hace mucho tiempo, no hay necesidad de mentir. ¡Defiéndete, Capitán!";
			link.l1 = "¡Maldición!";
			link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_Bad_2";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_Bad_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_CaveEntrance")], false);
			LAi_SetFightMode(pchar, true);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				LAi_CharacterDisableDialog(sld);
			}
			
			sld = CharacterFromID("Longway");
			LAi_SetImmortal(sld, false);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_BasTer_MyUbilLongway_BadFinal");
		break;
		
		case "PZ_BasTer_SOtryadom_UbiliLongway":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "¡No puedo creer que lo hayamos superado con él! Pero dime, ¿por qué te llamó Capitán?";
				link.l1 = "Es más complicado de lo que parece, amigo. Necesitaba tranquilizar a tu comandante. Lo importante es el resultado, ¿verdad? Y el resultado es que Longway está muerto, y te ayudé con eso.";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_2";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "Aún tu presencia no ayudó - aún así nos atacó. Maldito salvaje...";
				link.l1 = "No deberías hablar de él así. Nos atacó porque estaba molesto y pensó que yo estaba contigo.";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_2";
			}
		break;
		
		case "PZ_BasTer_SOtryadom_UbiliLongway_2":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "Tal vez. En ese caso, adiós, monsieur. Le diremos nosotros mismos al comandante que el chino finalmente está muerto.";
				link.l1 = "Muy bien, gracias. Adiós, muchachos.";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_3";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "Bueno, molesto o no, salvaje o no, eso no cambia nada - mató a muchos de los nuestros antes, derramó sangre primero.";
				link.l1 = "Algo debió haberlo llevado a ese estado. Pero no nos detengamos en eso. Me voy, y tú puedes regresar al comandante cuando lo consideres oportuno. Hasta luego.";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_3";
			}
		break;
		
		case "PZ_BasTer_SOtryadom_UbiliLongway_3":
			DialogExit();
			
			LAi_SetWarriorType(npchar);
			LAi_CharacterDisableDialog(npchar);
			ChangeCharacterNationReputation(pchar, FRANCE, 12);
			AddQuestRecord("PZ", "11");
			CloseQuestHeader("PZ");
			
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog":
			dialog.text = "¿Señor Capitán?";
			link.l1 = "¡Ay! He estado buscándote por todos lados, Longway. Has causado bastante revuelo en el pueblo. Tenemos mucho de qué hablar, así que volvamos al barco de inmediato.";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_2";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_2":
			dialog.text = "¡Allí!";
			link.l1 = "Veo que tenemos compañía. Parece que vamos a llegar un poco tarde.";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_3";
			locCameraFromToPos(-12.27, 1.29, -8.89, true, -3.23, -1.20, -4.77);
			DoQuestCheckDelay("PZ_IshemLongway_SorraKomendant_Dialog_Povernutsya", 1.3);
			
			for (i=1; i<=5; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_BasTer_OtryadPeshera"+i, "sold_fra_"+(rand(7)+1), "man", "man", sti(pchar.rank), FRANCE, 0, true, "soldier"));
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
				LAi_SetHP(sld, 60.0, 60.0);
			}
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_3":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_CaveEntrance")], false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Longway");
			LAi_SetImmortal(sld, false);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_IshemLongway_SorraKomendant_Pobeda1");
			
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1 = "NPC_Death";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1.character = "Longway";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition = "PZ_LongwayNelzyaUmeret";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_4":
			dialog.text = "¡Vienen más!";
			link.l1 = "Malditos testarudos, eso debo admitir. Estamos demasiado expuestos aquí. Vamos a la cueva, será más fácil defendernos.";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_5";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_5":
			DialogExit();
			pchar.questTemp.PZ_IshemLongway_SorraKomendant = true;
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			
			sld = CharacterFromID("Longway");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
			
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocation(pchar, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_6":
			dialog.text = "No podemos quedarnos aquí para siempre.";
			link.l1 = "¿Y eso es lo primero que quieres decir después de todo lo que ha pasado, Longway? ¿No crees que es hora de que expliques qué está sucediendo?";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_7";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_7":
			dialog.text = "Señor Capitán, Longway...";
			link.l1 = "Pero tienes razón - no podemos quedarnos. Movámonos antes de que aparezca otro escuadrón. Hablaremos en el barco una vez que hayamos zarpado.";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_8";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_8":
			DoQuestReloadToLocation("Guadeloupe_CaveEntrance", "reload", "reload1", "PZ_IshemLongway_VyhodIsPeshery");
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_1":
			dialog.text = "El engaño y la malicia del hombre blanco no tienen límites.";
			link.l1 = "¡Oye, yo también soy un hombre blanco! Además, mataste a sus amigos y compañeros soldados, tienen derecho a estar enojados.";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_2";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_2":
			dialog.text = "¿Los absuelves, Mi Señor Capitán?";
			link.l1 = "Te absuelvo, Longway. Y te insto a no juzgar a las personas por el color de su piel. Tú, más que nadie, deberías entender eso. Nos interrumpieron, ¿dónde estábamos...?";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_3";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_3":
			dialog.text = "¡Capitán! ¡Detrás de ti!";
			link.l1 = "Oh, no nos van a dejar tener una conversación adecuada hoy...";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_4";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_4":
			DialogExit();
			LAi_SetCurHPMax(pchar);
			LAi_GetCharacterMaxEnergy(pchar);
			LAi_SetCurHPMax(sld);
			LAi_GetCharacterMaxEnergy(sld);
			
			sld = CharacterFromID("Longway");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			for (i=6; i<=10; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_BasTer_OtryadPeshera"+i, "sold_fra_"+(rand(7)+1), "man", "man", sti(pchar.rank), FRANCE, 0, true, "soldier"));
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_SetHP(sld, 60.0, 60.0);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_IshemLongway_Zastupaemsya_5");
			
			AddDialogExitQuest("MainHeroFightModeOn"); // Rebbebion, fix
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_6":
			dialog.text = "Claro, Mi Señor Capitán.";
			link.l1 = "Eso está bien, pero no nos demoremos aquí. Tú y yo tenemos mucho de qué hablar. Sígueme - vamos de vuelta al barco.";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_7";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_7":
			DialogExit();
			
			sld = CharacterFromID("Longway");
			AddPassenger(pchar, sld, false);
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0;
			sld.Health.maxHP    = 60.0;
			SetCharacterPerk(sld, "ShipEscape");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.Dialog.CurrentNode = "Longway_officer";
			
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			AddQuestRecord("PZ", "14");
			DeleteQuestCondition("PZ_LongwayNelzyaUmeret");
			DeleteQuestCondition("PZ_KorablBuhta_BadFinal");
			
			//Продолжение второго этапа
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition = "PZ_LongwayRazgovorVKaute";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_1":
			dialog.text = "¿Mi Señor Capitán, realmente eres tú...?";
			link.l1 = "Sí, Longway. ¿Estás bien?";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_2";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_2":
			dialog.text = "Longway está bien. Gracias. ¡Pero, Capitán! ¡Mire!";
			link.l1 = "¡Corre a la cueva, date prisa! ¡Es una buena posición defensiva!";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_3";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_3":
			DialogExit();
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			
			sld = CharacterFromID("Longway");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
			
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocation(pchar, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
		break;
		
		case "PZ_IshemLongway_SrazuNashli_4":
			dialog.text = "Longway comprobará si los soldados todavía vienen.";
			link.l1 = "Iremos juntos - no podemos mantener nuestra defensa contra toda la guarnición.";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_5";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_5":
			dialog.text = "Sí, Mi Señor Capitán?";
			link.l1 = "Tenemos mucho de qué hablar. Ahora sígueme, necesitamos levar anclas de inmediato.";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_6";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_6":
			DoQuestReloadToLocation("Guadeloupe_CaveEntrance", "reload", "reload1", "PZ_IshemLongway_VyhodIsPeshery");
		break;
		
		// Этап 2, СТРАНИЦЫ ИСТОРИИ
		case "PZ_LongwayRazgovorOProshlom":
			dialog.text = "Gracias de nuevo por echarme una mano, Mi Señor Capitán. Estoy seguro de que tienes muchas preguntas.";
			link.l1 = "Eso es decir poco. ¿Por qué mataste a esos soldados? No matas por placer, lo sé.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_LongwayRazgovorOProshlom_2":
			dialog.text = "No, Longway no lo hace. Los soldados intentaron detener a Longway, y la prisión no era una opción. No escucharían a un chino, solo un hombre blanco recibe esa cortesía.";
			link.l1 = "No siempre escuchan a otros blancos tampoco, pero entiendo tu punto. Aun así, ¿masacrarlos como ganado en la ciudad? ¿Qué estabas haciendo en Basse-Terre?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_3";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_3":
			dialog.text = "Los blancos no sólo no suelen escucharme, sino que a veces ni siquiera hablan. Y cuando lo hacen, es para llamar a los guardias. Longway no eligió su piel ni sus ojos, pero está orgulloso de ser quien es. Cuando los soldados se burlan y amenazan, Longway se cansa... y se enfada.";
			link.l1 = "De ahora en adelante, trabajemos juntos. La gente me habla en lugar de llamar a los guardias... normalmente. Pero en serio, cuéntame sobre tu misión. Déjame ayudarte.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_4";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_4":
			dialog.text = "Por favor, Mi Señor Capitán, comprenda a Longway. Él hizo un juramento de hacer esto solo. No lo presione. Le debe eso a Longway.";
			link.l1 = "Estoy verdaderamente agradecida, pero podría haberme encargado de van Merden yo misma en ese momento. Sin embargo, estábamos a mano desde el principio: dijiste que salvé tu reputación, y tú salvaste mi vida. Ahora te he salvado de nuevo.";
			if (CheckAttribute(pchar, "questTemp.PZ_NashliArhiv")) link.l1.go = "PZ_LongwayRazgovorOProshlom_5";
			else link.l1.go = "PZ_LongwayRazgovorOProshlom_Grubim_1";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_5":
			dialog.text = "Hmm... tienes razón, Mi Señor Capitán. Longway cree que eres su verdadero amigo entre los hombres blancos. Una vez, pensó así antes, pero estaba amargamente equivocado. ¿Recuerdas a John Murdock? ¿Johan van Merden?";
			link.l1 = "Qué extraño que menciones a van Merden. Recientemente, alguien arrancó unas páginas de su archivo justo bajo mis narices. ¿Estaba relacionado con tu caso? ¿Encontraste al ladrón?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_6";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_6":
			dialog.text = "Lo hice. El ladrón era... Longway. Él lo siente mucho, Mi Señor Capitán. En ese entonces, no sabía si podía confiar completamente en usted.";
			if (sti(pchar.reputation.nobility) <= 60)
			{
				link.l1 = "¿Hablas de amistad, pero me robas a mis espaldas? Esta es la primera y última vez, Longway. ¿Entiendes?";
				link.l1.go = "PZ_LongwayRazgovorOProshlom_Grubim_1";
				notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(61))+")", "None");
			}
			else
			{
				link.l1 = "¿Y cómo lograste hacerlo, Longway?";
				link.l1.go = "PZ_LongwayRazgovorOProshlom_Proshaem_1";
				notification("Reputation Check Passed", "None");
			}
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Grubim_1":
			dialog.text = "Longway entiende. Él lo dice en serio.";
			link.l1 = "Eso espero. Ahora dime cómo llegaste a esta vida, qué promesa hiciste, cuándo y a quién.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_Grubim_2";
			if (CheckAttribute(pchar, "questTemp.PZ_NashliArhiv")) AddComplexSelfExpToScill(100, 100, 100, 100);
			notification("Longway disapproves", "Longway");
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Grubim_2":
			dialog.text = "Sí, Mi Señor Capitán\nLongway busca a la persona viva más importante que le queda: Chang Xing.";
			link.l1 = "Chang Xing, ¿es tu mejor amigo?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_7";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Proshaem_1":
			dialog.text = "Gracias a tu amabilidad, el resto de la tripulación pronto se acostumbró a mí y comenzó a confiar en mí.";
			link.l1 = "Bueno, lo entiendo. No eres de los que alaban, pero buen trabajo, Longway... si limpiaste el desastre que dejó tu intrusión.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_Proshaem_2";
			AddComplexLandExpToScill(200, 200, 0);
			pchar.questTemp.PZ_FlagArhiv = true;
			notification("Longway approves", "Longway");
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Proshaem_2":
			dialog.text = "Correcto. Pero no hay tiempo para eso.";
			link.l1 = "Supongo que no. Pero intenta no hacerlo de nuevo, ¿sí, eh? Si necesitas algo, solo pregunta. Puedes confiar en mí. Ahora, cuéntame sobre tu juramento.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_Proshaem_3";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Proshaem_3":
			dialog.text = "Por supuesto, Longway está feliz de compartir su carga contigo, Mi Señor Capitán.\nLongway busca a la persona viva más importante que le queda: Chang Xing.";
			link.l1 = "¿Chang Xing-es tu mejor amigo?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_7";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_7":
			dialog.text = "Chang Xing es mi familia, mi hermana. Desapareció hace años. Para encontrarla, Longway busca a aquellos que puedan saber dónde está.";
			link.l1 = "¿Qué tiene que ver esto con el archivo de van Merden? ¿Está relacionado con la desaparición de tu hermana?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_8";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_8":
			dialog.text = "Así es. Todo está conectado. Longway y Johan se conocieron hace muchos años, en la tierra que llamáis Formosa, mucho antes de que yo llegara al Archipiélago.";
			link.l1 = "¿Se conocen desde hace tantos años? ¿Y van Merden estuvo involucrado? ¡Qué historia! ¿Cuál fue su conexión con la desaparición de tu hermana?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_9";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_9":
			dialog.text = "Me ayudó en mi búsqueda de personas muy malas, incluso para los estándares de los hombres blancos. Oliveiro Fermentelos, Antoon van Diemen, y Joep van der Vink.";
			link.l1 = "Por sus nombres, uno es portugués y los otros dos son holandeses.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_10";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_10":
			dialog.text = "Sí, eso es correcto. Pero la búsqueda no tuvo éxito. Longway esperó pacientemente la guía del Cielo. Así que cuando obtuviste el archivo de van Merden, decidí estudiarlo. Cuando encontré las primeras páginas mencionando a Oliveiro, las arranqué y huí de la cabina.";
			link.l1 = "Todo finalmente encaja en la historia.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_11";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_11":
			dialog.text = "Pero la historia en sí acaba de comenzar. Mi Señor Capitán, ¿le gustaría saber sobre la búsqueda de Longway desde el principio? ¿Está listo para sentarse y escuchar?";
			link.l1 = "Por eso mismo te llamé a la cabina. Adelante.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_12";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_12":
			DialogExit();
			
			SetCurrentTime(12, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			SetMainCharacterIndex(GetCharacterIndex("Longway"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			DoQuestReloadToLocation("Formosa", "patrol", "patrol1", "PZ_Formosa_Start");
		break;
		
		case "PZ_Formosa_Tavern_1":
			dialog.text = "Chinos no son permitidos aquí. Este es un establecimiento respetable, para gente respetable, no para tipos como tú.";
			link.l1 = "Solo tengo una pregunta. Déjame hacerla, y me iré.";
			link.l1.go = "PZ_Formosa_Tavern_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Formosa_Tavern_2":
			dialog.text = "¡Aprende a hablar correctamente primero! Te dije que los de tu clase no son bienvenidos aquí.";
			link.l1 = "¿Dónde puedo encontrar a Oliveiro Fermentelos? Dime, y me pondré en camino.";
			link.l1.go = "PZ_Formosa_Tavern_3";
		break;
		
		case "PZ_Formosa_Tavern_3":
			dialog.text = "¿También eres sordo? No pongas a prueba mi paciencia, o pronto toda esta sala apestará a tripas amarillas.";
			link.l1 = "Mi gente ha vivido aquí durante miles de años. Esta es nuestra isla, ¿y ni siquiera podemos entrar a una simple taberna?";
			link.l1.go = "PZ_Formosa_Tavern_4";
		break;
		
		case "PZ_Formosa_Tavern_4":
			dialog.text = "¡Oh, hablas en grande, ¿eh?! Podrías ser ahorcado por eso. ¡Fuera!";
			link.l1 = "...";
			link.l1.go = "PZ_Formosa_Tavern_5";
		break;
		
		case "PZ_Formosa_Tavern_5":
			DialogExit();
			locCameraSleep(true);
			LAi_CharacterDisableDialog(npchar);
			
			sld = CharacterFromID("PZ_Formosa_smuggler");
			LAi_CharacterEnableDialog(sld);
			//AddLandQuestMark(sld, "questmarkmain");
			LAi_Fade("PZ_Formosa1_9", "");
		break;
		
		case "PZ_Formosa_smuggler_1":
			dialog.text = "He oído sobre tu gran problema, mi pequeño amigo. No deberías haber sido tan ruidoso, nombre equivocado, lugar equivocado.";
			link.l1 = "¿Sabes algo sobre este hombre? ¡Dímelo!";
			link.l1.go = "PZ_Formosa_smuggler_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Formosa_smuggler_2":
			dialog.text = "Tranquilo, compañero.";
			link.l1 = "Mis disculpas.";
			link.l1.go = "PZ_Formosa_smuggler_3";
		break;
		
		case "PZ_Formosa_smuggler_3":
			dialog.text = "No quiero tu disculpa, pero sí quiero tu dinero. Tal vez entonces te ayude. Soy Marcelo Schulte. ¿Y tú? Tienes dinero, ¿verdad?";
			link.l1 = "Mi nombre es Chang Tu. Tengo dinero. ¿Es suficiente?";
			link.l1.go = "PZ_Formosa_smuggler_4";
		break;
		
		case "PZ_Formosa_smuggler_4":
			dialog.text = "(silbidos) Escudos, pesos, florines, doblones... y hasta algunas de esas monedas raras que tienen ustedes. Esto servirá. Sí, ¿eh? Chung Chung, veré qué puedo averiguar sobre el hombre. No te preocupes, estoy aquí casi todos los días, así que tu dinero está seguro. Vuelve a diario y definitivamente nos cruzaremos.";
			link.l1 = "Espero. No me queda más dinero...";
			link.l1.go = "PZ_Formosa_smuggler_5";
		break;
		
		case "PZ_Formosa_smuggler_5":
			DialogExit();
			LAi_SetStayType(pchar);
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("A few days have passed,"+ NewStr() +"April 4, 1645.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Formosa_tavern", "goto", "goto1", "PZ_Formosa_Spustya4Dnya");
			LaunchFrameForm();
		break;
		
		case "PZ_Formosa_smuggler_11":
			dialog.text = "¡Ah, Chang-Chang! Ya estás aquí.";
			link.l1 = "Es Chang Tu.";
			link.l1.go = "PZ_Formosa_smuggler_12";
		break;
		
		case "PZ_Formosa_smuggler_12":
			dialog.text = "No importa, camarada.";
			link.l1 = "¿Descubriste dónde está Oliveiro?";
			link.l1.go = "PZ_Formosa_smuggler_13";
		break;
		
		case "PZ_Formosa_smuggler_13":
			dialog.text = "Nope, ni la más mínima idea.";
			link.l1 = "¡Mi dinero!";
			link.l1.go = "PZ_Formosa_smuggler_14";
		break;
		
		case "PZ_Formosa_smuggler_14":
			dialog.text = "¡No te pongas tan nervioso! ¿Me habría atrevido a acercarme a ti de nuevo si no hubiera averiguado nada? Voy a presentarte a alguien que sabe. Y qué suerte tienes, le encanta la gente asiática. Incluso tiene sirvientes a juego, diablos, hasta criadas. Aprendiendo tu sucio idioma también. Se llama Johan van Merden. Te estará esperando en una casa de dos pisos cerca de la residencia.";
			link.l1 = "Mi agradecimiento.";
			link.l1.go = "PZ_Formosa_smuggler_15";
		break;
		
		case "PZ_Formosa_smuggler_15":
			DialogExit();
			
			locCameraSleep(true);
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload1_back", "PZ_Formosa1_11", -1);
			LAi_ActorGoToLocation(npchar, "goto", "goto3", "", "", "", "", -1);
			npchar.location = "None";
			LocatorReloadEnterDisable("Formosa", "houseSp1", false);
		break;
		
		case "PZ_Formosa_JohanVanMerden_1":
			dialog.text = "Eres Chang Chang, ¿verdad? Adelante, no seas tímido.";
			link.l1 = "Es Chang Tu.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_2";
			DelLandQuestMark(npchar);
			locCameraFromToPos(-1.91, 2.06, -1.75, true, 2.23, -0.85, 0.85);
		break;
		
		case "PZ_Formosa_JohanVanMerden_2":
			dialog.text = "¿Es así? Mis disculpas. Ese Marcelo y su desfile de chistes... Lástima que tan pocos se interesen por tu cultura. Y todo esto solo por un idioma diferente y el corte de tus ojos. Pero eres inteligente. A diferencia de los negros, jejeje.";
			link.l1 = "(en mandarín) Entonces el contrabandista no mentía, realmente eres un hombre de cultura. ¿Y realmente hablas nuestro idioma?";
			link.l1.go = "PZ_Formosa_JohanVanMerden_2a";
			link.l2 = "Mi agradecimiento por las cálidas palabras sobre mi cultura. ¿Debes ser Johan van Merden?";
			link.l2.go = "PZ_Formosa_JohanVanMerden_3";
		break;
		
		case "PZ_Formosa_JohanVanMerden_2a":
			dialog.text = "Oh... Entendí solo unas pocas palabras. Todavía estoy aprendiendo, ¿sabes? ¿Podrías continuar en holandés?";
			link.l1 = "Como desees. ¿Eres Johan van Merden?";
			link.l1.go = "PZ_Formosa_JohanVanMerden_3";
		break;
		
		case "PZ_Formosa_JohanVanMerden_3":
			dialog.text = "Sí, Chung Tu, soy yo. He oído que buscas a Oliveiro Fermentelos. Sé dónde encontrarlo, pero primero dime, ¿por qué lo buscas? Tu respuesta determinará la mía.";
			link.l1 = "Él... secuestró a mi última y más querida miembro de la familia: mi hermana, Chang Xing.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_4";
		break;
		
		case "PZ_Formosa_JohanVanMerden_4":
			dialog.text = "Entonces debo decepcionarte, Chang Tu. Probablemente ya no hay esperanza para ella. Es probable que haya sido vendida como esclava a un rico hacendado o a un burdel. De cualquier manera, no podrás salvarla.";
			link.l1 = "Creo que Chang Xing todavía está viva. Oliveiro puso sus ojos en ella. Ella lo rechazó con orgullo. La secuestró cuando yo no estaba en casa. Y... mató a nuestros padres.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_5";
		break;
		
		case "PZ_Formosa_JohanVanMerden_5":
			dialog.text = "Yo... lo siento mucho. Si ese es el caso, Chang Xing, ¿verdad?, podría seguir vivo. Esto es lo que haremos: dame algo de tiempo para averiguar exactamente dónde está Oliveiro ahora mismo. Digamos una semana. Nos veremos de nuevo entonces. Encuéntrame fuera de las puertas de la ciudad, quién sabe qué ojos te siguen aquí. No quiero involucrarme más de lo que estoy acostumbrado, espero que lo entiendas.";
			link.l1 = "Estoy... estoy profundamente agradecido contigo, Mynheer van Merden. Espero con ansias nuestro próximo encuentro.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_6";
		break;
		
		case "PZ_Formosa_JohanVanMerden_6":
			DialogExit();
			LAi_SetStayType(pchar);
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("A week has passed,"+ NewStr() +"April 11, 1645.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Formosa_ExitTown", "goto", "goto3", "PZ_Formosa_Spustya7Dney");
			LaunchFrameForm();
		break;
		
		case "PZ_Formosa_JohanVanMerden_11":
			dialog.text = "Hola, Chung Tu. Veo el fuego en tus ojos. Tengo noticias, pero no son buenas.";
			link.l1 = "Cualquier noticia es de suma importancia para mí. Por favor, dígame, Mynheer van Merden.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_12";
		break;
		
		case "PZ_Formosa_JohanVanMerden_12":
			dialog.text = "Aye... Fermentelos se fue a Batavia hace aproximadamente un mes. Esa es la única pista que tengo sobre él. La buena noticia es que planea quedarse allí por un tiempo, así que si vas ahora, lo atraparás. ¿La mala noticia? Es amigo cercano del Gobernador General Anthony van Diemen. No te podrás acercar a él.";
			link.l1 = "Esta noticia es suficiente. Mis humildes agradecimientos a usted, Mynheer van Merden. Me marcharé de inmediato.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_13";
		break;
		
		case "PZ_Formosa_JohanVanMerden_13":
			dialog.text = "Algo me dijo que dirías eso, así que decidí ayudar a equilibrar las probabilidades para ti y Chang Xing. Escribí una carta a un viejo amigo mío, Oliver Trust. Tiene una tienda en Batavia. Me debe un favor, así que te ayudará.";
			link.l1 = "Yo... no sé qué decir...";
			link.l1.go = "PZ_Formosa_JohanVanMerden_14";
			//Log_Info("Вы получили письмо");
			PlaySound("interface\important_item.wav");
		break;
		
		case "PZ_Formosa_JohanVanMerden_14":
			dialog.text = "Un simple “gracias” bastará. Si no puedes encontrar a Oliveiro en la ciudad, busca la Estrella de la Mañana. Siempre puedes rastrearlo a través de su barco. Buena suerte, mi amigo; tú y tu hermana la necesitaréis.";
			link.l1 = "Gracias desde el fondo de mi corazón, Mynheer van Merden.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_15";
		break;
		
		case "PZ_Formosa_JohanVanMerden_15":
			DialogExit();
			LAi_SetStayType(pchar);
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("Batavia,"+ NewStr() +"May 29, 1645.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Batavia", "merchant", "mrcActive5", "PZ_Batavia_Puteshestvie");
			LaunchFrameForm();
		break;
		
		case "PZ_OliverTrust_1": //
			dialog.text = "¿Quién eres tú y qué haces aquí? No comercío con los de tu clase.";
			link.l1 = "Tengo una carta para usted.";
			link.l1.go = "PZ_OliverTrust_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_OliverTrust_2":
			dialog.text = "¡Ah, el mensajero! Aunque no esperaba cartas hoy. ¡Quédate aquí! Echaré un vistazo.";
			link.l1 = "¿Eres Oliver Trust? Van Merden me envió a ti.";
			link.l1.go = "PZ_OliverTrust_3";
			//Log_Info("Вы отдали письмо");
			PlaySound("interface\important_item.wav");
		break;
		
		case "PZ_OliverTrust_3":
			dialog.text = "Yo sé leer, ¿sabes? Normalmente, te mandaría lejos, pero gente como van Merden no acepta un no por respuesta. Finalmente, es hora de ajustar cuentas con van Diemen.";
			link.l1 = "Mi objetivo es Fermentelos. ¿Y qué hay de van Diemen?";
			link.l1.go = "PZ_OliverTrust_4";
		break;
		
		case "PZ_OliverTrust_4":
			dialog.text = "Eso no es asunto tuyo. Deberías estar agradecido de que te esté ayudando en absoluto. Ahora escucha con atención, antes de que decida que esto es una mala idea. Conozco a Fermentelos. Ha estado aquí por un tiempo, pero ya no está. La Estrella de la Mañana se fue hace unas semanas. Dios sabe cuándo volverá. Así que tu objetivo ha cambiado, y es un amigo de Fermentelos...";
			link.l1 = "... van Diemen.";
			link.l1.go = "PZ_OliverTrust_5";
		break;
		
		case "PZ_OliverTrust_5":
			dialog.text = "Sí. ¿También sabes sobre eso? ¿Supongo que Johan te lo contó? Oh, van Merden... eres un bastardo atrevido. Pero ya que sabes sobre van Diemen, sabes de su alta posición, ¿no? ¿Cuál es tu plan maestro para llegar al Gobernador General? ¡No será asaltando su residencia, estoy seguro!";
			link.l1 = "Chang Tu es un guerrero hábil.";
			link.l1.go = "PZ_OliverTrust_6";
		break;
		
		case "PZ_OliverTrust_6":
			dialog.text = "¿Un guerrero habilidoso, eh? ¿Te das cuenta de que ahora estamos todos enredados? ¿Y qué me pasará a mí si te capturan? Tendré que ayudarte por tu propia seguridad y la mía. Además de residir en su residencia, Van Diemen realiza visitas regulares a la plantación fuera de la ciudad y a su amante Vette.";
			link.l1 = "Mencionaste ayudarme.";
			link.l1.go = "PZ_OliverTrust_12";
		break;
		
		case "PZ_OliverTrust_12":
			dialog.text = "Creo que todos deberían tener una pasión, un pasatiempo. En cuanto a mí, colecciono armas raras y costosas. A veces tienen historia, a veces no, pero siempre son mortales. Mi colección puede ser útil para tu cruzada. Así que, dime, ¿dónde planeas emboscar a van Diemen?";
			link.l1 = "(Residencia) Ya que tienes tantas buenas armas, tomaré la mejor espada. Con ella, Chang Tu será inigualable entre los hombres blancos.";
			link.l1.go = "PZ_OliverTrust_resedinsia_1";
			link.l2 = "(Plantación) Los emboscaré en el camino de la plantación - no tendrán a dónde correr.";
			link.l2.go = "PZ_OliverTrust_Plantation1";
			link.l3 = "La señora - no habrá mucha gente allí, así que los guardias no reaccionarán a tiempo.";
			link.l3.go = "PZ_OliverTrust_lubovnitsa_1";
			SetCharacterPerk(pchar, "Gunman");
			SetCharacterPerk(pchar, "GunProfessional");
			InterfaceStates.Buttons.Save.enable = false;
		break;
		
		// Rebbebion, ну, с Богом...
		case "PZ_OliverTrust_Plantation1":
			pchar.questTemp.PZ_Batavia_plantation_Go = true;
			
			dialog.text = "¡Buena elección! Estoy impresionado. Para sacarle el máximo provecho, necesitarás una buena arma de fuego. Dime, ¿hasta dónde puedes apuntar, Chang Tu?";
			link.l1 = "Para ser honesto... no muy lejos, debo asegurarme de no fallar."link.l1.go ="PZ_OliverTrust_Plantation_MediumDistance1";
			link.l2 = "Atacaré desde lejos - mi enemigo ni siquiera se dará cuenta de dónde lo golpeé.";
			link.l2.go = "PZ_OliverTrust_Plantation_FarDistance1";
			notification("Jager Unlocked", "Longway");
			SetCharacterPerk(pchar, "Jager");
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance1":
			// делаем Лонгвэя мушкетёром с одновременной выдачей мушкета
			/* pchar.model = "Longway_mush";
			pchar.model.animation = "mushketer"; */
			pchar.model = "Longway";
			pchar.model.animation = "Longway";
			Characters_RefreshModel(pchar);
			GiveItem2Character(pchar, "mushket6"); 
			EquipCharacterByItem(pchar, "mushket6");
			//Log_Info("Вы получили башенный мушкетон");
			PlaySound("interface\important_item.wav");
			
			AddItems(pchar, "grapeshot", 50);
			AddItems(pchar, "gunpowder", 50);
			LAi_SetCharacterUseBullet(pchar, GUN_ITEM_TYPE, "grapeshot");
			
			dialog.text = "Ya veo. ¡En ese caso, toma esto! Un trabuco portugués antiguo, dispara un cartucho de gran calibre. Ya no hacen estos, ni siquiera en el Viejo Mundo.";
			link.l1 = "Vi uno cuando era niño...";
			link.l1.go = "PZ_OliverTrust_Plantation_MediumDistance2";
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance2":
			dialog.text = "Entonces, ¿sabes cómo usarlo?";
			link.l1 = "No...";
			link.l1.go = "PZ_OliverTrust_Plantation_MediumDistance3";
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance3":
			dialog.text = "Ten en cuenta que el mecanismo intercambiable se ha oxidado con el tiempo. Ningún aceite lo arreglará - está roto para siempre. Cargarlo es difícil, así que hagámoslo ahora. Observa con atención - usa un poco de fuerza, así. Pero no muy fuerte, o lo romperás.";
			link.l1 = "¿Así?";
			link.l1.go = "PZ_OliverTrust_Plantation_MediumDistance4";
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance4":
			dialog.text = "Exactamente.";
			link.l1 = "Entendido. ¡Muchas gracias!";
			link.l1.go = "PZ_OliverTrust_13";
		break;
		
		case "PZ_OliverTrust_Plantation_FarDistance1":
			// делаем Лонгвэя мушкетёром с одновременной выдачей мушкета
			/* pchar.model = "Longway_mush";
			pchar.model.animation = "mushketer"; */
			pchar.model = "Longway";
			pchar.model.animation = "Longway";
			Characters_RefreshModel(pchar);
			GiveItem2Character(pchar, "mushket2x2"); 
			EquipCharacterByItem(pchar, "mushket2x2");
			//Log_Info("Вы получили двуствольный штуцер");
			PlaySound("interface\important_item.wav");
			
			AddItems(pchar, "cartridge", 50);
			AddItems(pchar, "gunpowder", 50);
			LAi_SetCharacterUseBullet(pchar, GUN_ITEM_TYPE, "cartridge");
			
			dialog.text = "¡Un verdadero cazador! Ten cuidado, fue un regalo. Es uno de esos raros casos donde un arma es tanto decorativa como mortal. ¡Un rifle de caza de dos cañones! Pesado de sostener, fácil de usar. ¿Ya has descubierto cómo dispararlo?";
			link.l1 = "Entendido. ¡Muchas gracias!";
			link.l1.go = "PZ_OliverTrust_13";
		break;
		
		case "PZ_OliverTrust_lubovnitsa_1":
			dialog.text = "Tienes razón sobre los guardias, pero no subestimes el peligro. Van Diemen nunca va a ningún lugar de la ciudad sin su mano derecha, Joep van der Vink.";
			link.l1 = "Entonces, ¿están juntos con Vette...?";
			link.l1.go = "PZ_OliverTrust_lubovnitsa_2";
			pchar.questTemp.PZ_Batavia_lubovnitsa_Go = true;
			AddCharacterSkillDontClearExp(pchar, "Sailing", 10);
			AddCharacterSkillDontClearExp(pchar, "Commerce", 10);
			AddCharacterSkillDontClearExp(pchar, "Repair", 10);
			notification("Naval Skills +", "Longway");
			notification("Rat Wolf Unlocked", "Longway");
			SetCharacterPerk(pchar, "RatsWolf");
		break;
		
		case "PZ_OliverTrust_lubovnitsa_2":
			dialog.text = "¿Qué? ¡Ja! ¡Tienes una imaginación increíble, chino! Antoon es un cobarde, y van der Vink está allí para protegerlo en caso de que alguien interrumpa su “tiempo privado.”/nJoep siempre lleva una pesada armadura de trinchera - impenetrable para la mayoría de las armas blancas. Por eso tú también necesitarás algo especial. Toma este estoque. Es largo, más fuerte que la mayoría de las otras espadas, y pesa como una buena hoja.";
			link.l1 = "¿Un estoque para luchar contra enemigos con armadura...?";
			link.l1.go = "PZ_OliverTrust_lubovnitsa_3";
			//Log_Info("Вы получили асоледу");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "blade_26");
			EquipCharacterByItem(Pchar, "blade_26");
		break;
		
		case "PZ_OliverTrust_lubovnitsa_3":
			dialog.text = "No apuntes a la armadura en sí - no es un estoque. Golpea en las rendijas y puntos vulnerables, como la ingle, las axilas y la garganta. Desgástale, dicta los términos. Joep también empuña un hacha pesada, así que no intentes desviar sus golpes - mejor esquiva./nPor si acaso no encuentras una abertura, toma esta trabuco. Normalmente está cargado con perdigones, pero he preparado un juego de flechas de acero para ti.";
			link.l1 = "¿Flechas para un mosquete...?";
			link.l1.go = "PZ_OliverTrust_lubovnitsa_4";
			//Log_Info("Вы получили бландербуз");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "pistol8");
			EquipCharacterByItem(Pchar, "pistol8");
			AddItems(Pchar, "harpoon", 30);
			AddItems(Pchar, "gunpowder", 30);
			LAi_SetCharacterUseBullet(Pchar, GUN_ITEM_TYPE, "harpoon");
		break;
		
		case "PZ_OliverTrust_lubovnitsa_4":
			dialog.text = "¿Inusual, verdad? Una mezcla de lo viejo y lo nuevo. Está diseñado para ser disparado con una mano, pero si es demasiado pesado, usa ambas. Muchos lo hacen. Y aquí, prueba esta armadura de mimbre. Es más ligera que la coraza de Joep pero aún ofrece una protección decente. No dejes que su hacha te golpee directamente, ni siquiera una armadura milanesa resistiría un arma así. ¿Entiendes?";
			link.l1 = "Sí, entiendo. ¡Gracias, Sr. Confianza!";
			link.l1.go = "PZ_OliverTrust_13";
			//Log_Info("Вы получили кожаный корсет");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "cirass5");
			EquipCharacterByItem(Pchar, "cirass5");
		break;
		
		case "PZ_OliverTrust_resedinsia_1":
			dialog.text = "¿Demasiado confiado, verdad? Tal vez te hablé de mi colección demasiado pronto. Pero... ya estás comprometido. Atacar una residencia a plena luz del día es un movimiento audaz, inesperado. Esta hoja debería satisfacer tus necesidades. No es la mejor del mundo, pero es perfecta para apuñalar, cortar y tajar.";
			link.l1 = "¡Clewang! Reconozco esta hoja. La gente de las islas vecinas a menudo usa una.";
			link.l1.go = "PZ_OliverTrust_resedinsia_2";
			pchar.questTemp.PZ_Batavia_resedinsia_Go = true;
			notification("Duelist Unlocked", "Longway");
			SetCharacterPerk(pchar, "FencingMaster");
			SetCharacterPerk(pchar, "HT1");
		break;
		
		case "PZ_OliverTrust_resedinsia_2":
			dialog.text = "¿Has usado uno antes? Bien. Tendrás poco tiempo y muchos enemigos que enfrentar. Toma, coge esto también, es una pistola con tres cañones, bellamente incrustados. Cárgala delante de mí; no tendrás tiempo para eso más tarde. Y ponte este chaleco de duelo. Es ligero, te dará la velocidad que necesitarás, y algo de protección.";
			link.l1 = "¡Gracias, Señor Trust!";
			link.l1.go = "PZ_OliverTrust_13";
			//Log_Info("Вы получили клеванг");
			//Log_Info("Вы получили трёхствольный дробовик");
			//Log_Info("Вы получили жилет бретера");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "blade_30");
			EquipCharacterByItem(Pchar, "blade_30");
			GiveItem2Character(PChar, "pistol2");
			EquipCharacterByItem(Pchar, "pistol2");
			GiveItem2Character(PChar, "cirass6");
			EquipCharacterByItem(Pchar, "cirass6");
			AddItems(Pchar, "grapeshot", 50);
			AddItems(Pchar, "gunpowder", 50);
			LAi_SetCharacterUseBullet(Pchar, GUN_ITEM_TYPE, "grapeshot");
		break;
		
		case "PZ_OliverTrust_13":
			dialog.text = "Espera, no hemos terminado. Es de nuestro interés mutuo que sobrevivas. Toma esta medicina para curar tus heridas después de la batalla. \nY este elixir también. Sabe y huele horrible, pero elimina cualquier veneno en tu cuerpo. Joep van der Vink, el guardaespaldas de Van Diemen, unta sus armas con esa porquería. Maldito arrogante, así que tendrás ventaja.";
			link.l1 = "No sé si alguna vez podré agradecerte lo suficiente, Mynheer Trust...";
			link.l1.go = "PZ_OliverTrust_14";
			//Log_Info("Вы получили 10 лечебных зелий");
			//Log_Info("Вы получили противоядие");
			PlaySound("interface\important_item.wav");
			AddItems(Pchar, "potion1", 10);
			AddItems(Pchar, "potion3", 1);
		break;
		
		case "PZ_OliverTrust_14":
			dialog.text = "Tu mejor agradecimiento sería no delatarme si te atrapan. Aunque, lo más probable, es que simplemente te maten en el acto. Pero si sobrevives a esto, dile a Van Diemen que me debe su muerte a mí. ¿Puedes hacer eso?";
			link.l1 = "¡No hay problema. Gracias de nuevo, Mynheer Trust. ¡Adiós!";
			link.l1.go = "PZ_Batavia_NaOhotu";
		break;
		
		case "PZ_Batavia_NaOhotu":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_resedinsia_Go"))
			{
				DoQuestReloadToLocation("Batavia", "reload", "reload1", "PZ_Batavia_BitvaSoStrazhnikami");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_lubovnitsa_Go"))
			{
				DoQuestReloadToLocation("Batavia_HouseF3", "reload", "reload1", "PZ_Batavia_BitvaLubovnitsa");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_Plantation_Go"))
			{
				/*EndQuestMovie();
				sld = &Locations[FindLocation("Batavia_plantation")];
				sld.locators_radius.quest.detector4 = 3.0;
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1 = "locator";
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1.location = "Batavia_plantation";
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1.locator_group = "quest";
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1.locator = "detector4";
				PChar.quest.PZ_Batavia_plantation1.win_condition = "PZ_Batavia_plantation_selfdialog";*/
				DoQuestReloadToLocation("Batavia_plantation", "quest", "detector2", "PZ_Batavia_plantation_setguards");
			}
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_1":
			dialog.text = "¡Alto! ¿A dónde vas, chino?";
			link.l1 = "A la residencia.";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_2";
			locCameraFromToPos(-0.44, 7.45, 24.65, true, -1.90, 5.10, 18.50);
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_2":
			dialog.text = "Eso fue una pregunta retórica, genio. ¿Qué te hace pensar que alguien dejaría entrar a alguien como tú allí?";
			link.l1 = "Tengo asuntos con Mynheer Van Diemen. Déjame pasar, por favor.";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_3";
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_3":
			dialog.text = "¿Sabes el nombre del gobernador general? Bueno... dime cuál es tu asunto. Se lo transmitiré y te daré una respuesta.";
			link.l1 = "Mi conversación es solo con Mynheer Van Diemen. Me está esperando. Apártate, o lo lamentarás.";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_4";
			locCameraSleep(true);
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_4":
			dialog.text = "Vaya, vaya, no te pavonees, ojitos rasgados. Es mi camino o ningún camino.";
			link.l1 = "Mi camino entonces.";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_5";
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_5":
			DialogExit();
			LAi_SetActorType(pchar);
			CharacterTurnByChr(pchar, CharacterFromID("PZ_SoldResid_1"));
			LAi_group_MoveCharacter(pchar, LAI_GROUP_PLAYER);
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			
			sld = CharacterFromID("PZ_SoldResid_1");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
				
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			
			DoQuestCheckDelay("PZ_Batavia_resedinsia_1", 0.9);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_1":
			dialog.text = "¡Maldito campesino! ¿Quién te contrató? ¡Te pagaré más que eso!";
			link.l1 = "Ustedes los blancos solo se preocupan por el oro. Que los dragones maldigan a su clase. Vine por información, pero tu gente no me deja entrar.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_2";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_2":
			dialog.text = "¿Qué quieres?!";
			link.l1 = "Fermentelos. ¿Dónde está ahora?";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_3";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_3":
			dialog.text = "¿Oliveiro? ¡¿Pero por qué demonios lo quieres?! ¡No te diré nada!";
			link.l1 = "Él mató a mi familia y secuestró a mi hermana. Mi consejo para ti es que empieces a hablar. Por tu propio bien.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_4";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_4":
			dialog.text = "¿Qué vas a hacerme? Toda la guarnición estará aquí pronto.";
			link.l1 = "¿Has oído hablar de Lynchy? Es un castigo en mi cultura. Significa 'Muerte por Mil Cortes.'";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_5";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_5":
			dialog.text = "¡No tendrás tiempo para infligirme tantos cortes, imbécil!";
			link.l1 = "Es una figura retórica. El verdugo inflige cortes, uno por uno. O corta pedazos del cuerpo. Hacemos tanto como el tiempo nos lo permita, a menos que empieces a hablar.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_6";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_6":
			DialogExit();
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Sepp", "mercen_26", "man", "man", sti(pchar.rank), HOLLAND, -1, false, "quest"));
			sld.name = "Joep";
			sld.lastname = "van der Vink";
			GiveItem2Character(sld, "topor_04");
			EquipCharacterByItem(sld, "topor_04");
			GiveItem2Character(sld, "pistol3");
			EquipCharacterByItem(sld, "pistol3");
			sld.CantLoot = true;
			LAi_SetHP(sld, 300.0, 300.0);
			ChangeCharacterAddressGroup(sld, "Batavia_townhallRoom", "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			
			LAi_SetStayType(pchar);
			locCameraFromToPos(-3.06, 1.64, -0.43, true, 1.87, -1.20, 2.39);
			DoQuestCheckDelay("PZ_Batavia_BitvaResidensia_7", 2.5);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_7":
			dialog.text = "¡A-A-A!!! ¡Detente! Detente, bruto asqueroso. Te lo diré, te lo diré todo. Solo detente. ¡Joep! ¡Finalmente! ¿Dónde demonios has estado todo este tiempo?!";
			link.l1 = "Qué mal momento...";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_8";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_8":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Sepp");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_9";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_9":
			dialog.text = "¿Antoon? Necesitas ver a un médico de inmediato. Te ayudaré a llegar allí tan pronto como termine aquí. ¡Tú! ¿Qué diablos estás haciendo, carnicero cobarde?!";
			link.l1 = "¿Carnicero Amarillo? Me gusta cómo suena. Solo hay una pregunta que necesito que respondan, pero nadie parece dispuesto a hacerlo...";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_10";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_10":
			dialog.text = "¿Qué pregunta?!";
			link.l1 = "¿Dónde está Oliveiro Fermentelos? ¿No puedes decirme solo eso?";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_11";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_11":
			dialog.text = "¡Me importa un comino Fermentelos! ¿Quién te dio el dinero y la información?!";
			link.l1 = "Oliver Trust. Por cierto, quería que te dijera que le debes tu muerte.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_12";
			
			sld = CharacterFromID("PZ_AntoniOneDimen");
			LAi_ActorSetGroundSitMode(sld);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_12":
			dialog.text = "¿Confianza?! ¡Ja-ja-ja-ja-ja-ja! ¿Ese avaro pensando que podría vengarse solo porque tomamos su plantación? Pronto tomaremos su tienda y su vida, una vez que termine contigo.";
			link.l1 = "Estás desperdiciando mi tiempo.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_13";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_13":
			DialogExit();
			LAi_SetFightMode(pchar, true);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			
			PChar.quest.PZ_Batavia_BitvaResidensia_8.win_condition.l1 = "NPC_Death";
			PChar.quest.PZ_Batavia_BitvaResidensia_8.win_condition.l1.character = "PZ_Sepp";
			PChar.quest.PZ_Batavia_BitvaResidensia_8.win_condition = "PZ_Batavia_BitvaResidensia_8";
		break;
		
		case "PZ_Batavia_PlantationSelfDialog":
			dialog.text = " (en mandarín) Así que busquemos un buen lugar para emboscada.";
			if (CheckCharacterItem(pchar, "mushket6"))
			{
				link.l1 = "(en mandarín) Con esta cosa oxidada, necesitaré acercarme. Ráfaga rápida: aguda y despiadada. El miedo y el pánico harán el resto.";
				link.l1.go = "Exit";
			}
			else
			{
				link.l1 = "(en mandarín) Justo aquí. Ni siquiera me verán al principio. Las mejores batallas son las que no empiezan... o las que terminan rápidamente con poco derramamiento de sangre.";
				link.l1.go = "Exit";
			}
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_Batavia_PlantationFight");
		break;
		
		case "PZ_Batavia_PlantationDimen1":
			if (!CharacterIsAlive("PZ_SoldPlantation_1") && !CharacterIsAlive("PZ_SoldPlantation_2") &&  !CharacterIsAlive("PZ_SoldPlantation_3") && !CharacterIsAlive("PZ_SoldPlantation_4") && !CharacterIsAlive("PZ_SoldPlantation_5") && !CharacterIsAlive("PZ_SoldPlantation_6"))
			{
				dialog.text = "Bruto asqueroso... ¿Esclavo fugitivo, verdad? ¿Cómo conseguiste tal arma? ¿Alguien te contrató...?";
				link.l1 = "¡No hay tiempo! Dime dónde está Oliveiro Fermentelos - ¡ahora!";
				link.l1.go = "PZ_Batavia_PlantationDimen2";
			}
			else
			{
				dialog.text = RandSwear()+"";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_PlantationDimenSit");
			}
		break;
		
		case "PZ_Batavia_PlantationDimen2":
			dialog.text = "Hehehe, divertido... No hay tiempo - la sangre se derrama de mi vientre. Quémate en el infierno, pagano...";
			link.l1 = "¡No!!!";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_Batavia_PlantationDimenDead1");
		break;
		
		case "PZ_Batavia_Plantation_DimenDeadSelfDialog":
			dialog.text = "(en mandarín) ¿Por qué, por qué, por qué?! ¿Cómo se supone que voy a encontrar a Fermentelos ahora?!";
			link.l1 = "Pero primero, necesito esconderme - alguien ya debe haber informado de esta carnicería...";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_1":
			dialog.text = "¡Hic! ¡Un chino! No esperaba que alguien como tú fuera invitado aquí. ¿Te gusta mirar, eh? Jaja.";
			link.l1 = "¿Por qué hay tanta gente aquí...? ¿Y quién eres tú?";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_2";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_2":
			dialog.text = "¿No me reconoces por mi ropa? ¡Y cuida tu tono al hablar con el Gobernador General! ¡Hic!";
			link.l1 = "Entonces, usted debe ser Mynheer Van Diemen. Le pido disculpas por mi ignorancia. ¿Es este un carnaval que se celebra aquí?";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_3";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_3":
			dialog.text = "¡Así es, buen hombre, y de ninguna otra manera! ¡Un carnaval de travestis! ¡Ja-ja-ja! ¡No está tan mal, campesino! Estoy seguro de que a Luthers le encantaría llevar el vestido de Vette, ¡ja ja ja!";
			link.l1 = "Luthers?..";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_4";
			locCameraFromToPos(-4.45, 2.11, 1.53, true, 0.47, -0.30, 2.74);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_4":
			dialog.text = "E-e-ese pobre intento de esposo, que le encanta espiar desde el armario mientras a su querida esposa la están acostando. ¡A ella no le importa!";
			link.l1 = "Lo siento, не могу помочь с вашим запросом.";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_4_1";
			sld = CharacterFromID("PZ_Rubbe");
			CharacterTurnByChr(npchar, sld);
			CharacterTurnByChr(pchar, sld);
			CharacterTurnByChr(CharacterFromID("PZ_Brigitta"), sld);
			DoQuestCheckDelay("PZ_Batavia_BitvaLubovnitsa_4", 2.5);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_4_1":
			Event("QuestDelayExit","sl", "", 0);
			dialog.text = "¿Verdad, Vette, querida? Je-je.";
			link.l1 = "(en mandarín) ¿Qué diablos está pasando aquí...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_5";
			sld = CharacterFromID("PZ_Rubbe");
			CharacterTurnByChr(npchar, CharacterFromID("PZ_Brigitta"));
			CharacterTurnByChr(pchar, npchar);
			CharacterTurnByChr(CharacterFromID("PZ_Brigitta"), npchar);
			locCameraFromToPos(-2.21, 1.90, 2.26, true, -0.81, -0.40, 4.36);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_5":
			dialog.text = "¡Hic! No sé qué acabas de decir, pero por la mirada en tus ojos y tu tono, ¡estás de acuerdo conmigo! Van Haan es un maldito pervertido. Entonces, ¿qué eres tú, de todos modos? ¿Un trabajador? ¿Te invitó Vette?";
			link.l1 = "Yo...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_6";
			CharacterTurnByChr(pchar, npchar);
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(CharacterFromID("PZ_Brigitta"), pchar);
			locCameraFromToPos(-4.45, 2.11, 1.53, true, 0.47, -0.30, 2.74);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_6":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Sepp");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_7":
			dialog.text = "Invitar a un trabajador aquí es demasiado, incluso para Vette. Obviamente está perdido y en el lugar equivocado. Oye, tú. Sal de aquí y olvida todo lo que has visto. ¿Quién es tu amo? Lo contactaremos, y ambos serán pagados por su silencio. Incluso podrías volver con tu familia en el continente. Respóndeme y vete.";
			link.l1 = "En realidad, estoy aquí por negocios.";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_8";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_8":
			dialog.text = "Je, negocios. Solo Mynheer van Diemen hace “negocios” aquí. Mi trabajo es mantenerlo a salvo de personas como tú. Y Luthers... está siendo Luthers. O... ¿Vette realmente te invitó aquí?";
			link.l1 = " No, estoy aquí para...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_9";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_9":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Rubbe");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_10";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_10":
			dialog.text = "¿Acaso mi queridísima Vette invitaría aquí a un cobarde de mierda?! ¡¡¡Fuera de aquí!!!";
			link.l1 = "El miserable cornudo...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_11";
			link.l2 = "Nadie te está hablando. Cierra la boca. No pretendas tener cojones o dignidad.";
			link.l2.go = "PZ_Batavia_BitvaLubovnitsa_12";
			GiveItem2Character(npchar, "blade_06");
			EquipCharacterByItem(npchar, "blade_06");
			LAi_SetActorType(npchar);
			npchar.model.animation = "man";
			Characters_RefreshModel(npchar);
			SetCameraDialogMode(npchar);
			locCameraToPos(-1.88, 1.72, 0.27, false);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_11":
			dialog.text = "¿Co-co-cornudo? ¡No, la amo más que a mí mismo! Ja, un tonto chino como tú no entendería eso.";
			link.l1 = " (en mandarín) Maldito enfermo.";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_13";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_12":
			dialog.text = "¿Ga-gallo?! ¡Está perfecto! ¡Sí! Solo sé que otros hombres le dan más placer a mi querida Vette, ¡eso es todo!";
			link.l1 = "Como decimos en mi tierra, un hombre sigue siendo hombre hasta que solo le queda un dedo. Si fueras un hombre, lo entenderías.";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_13";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_13":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Brigitta");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_14";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_14":
			dialog.text = "No lo invité, por supuesto, pero, ya sabes, es bastante agradable. Podría quedarse cuando todos ustedes se vayan. Ya lo he intentado con nuestro perro, pero nunca lo he hecho con...";
			link.l1 = "¡Cállate, cuando los hombres hablan, ramera! Eres el único animal aquí. Estoy aquí por negocios. Busco a Oliveiro Fermentelos. Deben ser sus amigos. ¿Podrían por favor decirme dónde podría estar, Mynheer Van Diemen?";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_15";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_15":
			dialog.text = "¡Antoon, me insultó! ¡Me insultó! No vas a dejarlo pasar, ¿verdad?!";
			link.l1 = "...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_16";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_16":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_AntoniOneDimen");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_17":
			dialog.text = "Hehe, lo siento, amigo, pero la dama está enfadada. Voy a tener que darte una lección de modales. Lección uno.";
			link.l1 = "¿Pero puedes ayudarme en mi búsqueda de Oliveiro?";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_18";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_18":
			dialog.text = "No ayudará a un trabajador muerto.";
			link.l1 = "(en mandarín) Malditos sean todos...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_19";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_19":
			DialogExit();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			PlaySound("Voice\Russian\hambit\Longway-02.wav");
			
			sld = CharacterFromID("PZ_AntoniOneDimen");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld = CharacterFromID("PZ_Sepp");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld = CharacterFromID("PZ_Rubbe");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_Batavia_BitvaLubovnitsa_3");
			
			sld = CharacterFromID("PZ_Brigitta");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			PlaySound("People Fight\Peace_woman_death_05.wav");
			DoQuestCheckDelay("PZ_Batavia_BitvaLubovnitsa_5", 3.0);	//Нужно ещё раз, а то не бежит
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_21":
			dialog.text = "¡Maldita sea! ¡No aprendí nada!";
			link.l1 = "(en mandarín) Nunca olvidaré este día... Tengo que salir de aquí antes de que lleguen los guardias. No es que les importe el ruido que viene de este manicomio...";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_14":
			dialog.text = "¡(en mandarín) Los dioses han maldecido este día! ¡Van Diemen se desangró mientras lidiaba con su lacayo...!";
			link.l1 = " (en mandarín) Los guardias vienen. Tendré que abrirme paso luchando para salir de aquí.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final":
			DialogExit();
			RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(PChar, MUSKET_ITEM_TYPE);
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_resedinsia_Go"))
			{
				TakeItemFromCharacter(pchar, "blade_30");
				TakeItemFromCharacter(pchar, "pistol2");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_lubovnitsa_Go"))
			{
				TakeItemFromCharacter(pchar, "blade_26");
				TakeItemFromCharacter(pchar, "pistol8");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_Plantation_Go"))
			{
				TakeItemFromCharacter(pchar, "mushket6");
				TakeItemFromCharacter(pchar, "mushket2x2");
			}
			EquipCharacterByItem(Pchar, "blade_11");
			pchar.model = "Longway";
			pchar.model.animation = "Longway";
			pchar.model.animation = "man";
			Characters_RefreshModel(pchar);
			
			
			SetCurrentTime(2, 30);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("Formosa,"+ NewStr() +"26 July 1645.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Formosa", "goto", "goto7", "PZ_Formosa2_Start");
			LaunchFrameForm();
		break;
		
		case "PZ_Formosa_smuggler_21":
			dialog.text = "¡Oh, es Chang Chang! ¿Con qué necesitas ayuda esta vez, mi pequeño amigo?";
			link.l1 = "Es Chang Tu... ¿qué quieres decir?";
			link.l1.go = "PZ_Formosa_smuggler_22";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Formosa_smuggler_22":
			dialog.text = "Destilas desprecio por mí, ¿verdad? No vendrías aquí a menos que necesitaras algo.";
			link.l1 = "¿Sabes dónde está van Merden? ¿Está en la ciudad? No está en casa. Necesito hablar con él.";
			link.l1.go = "PZ_Formosa_smuggler_23";
		break;
		
		case "PZ_Formosa_smuggler_23":
			dialog.text = "Un hombre no puede esperar estar en casa todo el día, esperando que aparezca un solo hombre de piel amarilla. Tiene negocios en la isla. Regresará al pueblo esta noche, así que no te preocupes, ¡Chang Chang!";
			link.l1 = "Gracias. Adiós.";
			link.l1.go = "PZ_Formosa_smuggler_24";
		break;
		
		case "PZ_Formosa_smuggler_24":
			SetCurrentTime(1, 30);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			DoQuestReloadToLocation("Formosa", "goto", "goto7", "PZ_Formosa2_IshemMerden_3");
		break;
		
		case "PZ_Formosa_bandit_1":
			dialog.text = "¡Oye, ojos rasgados! ¿A qué viene tanta prisa a estas horas? Toda la gente decente ya está dormida.";
			link.l1 = "¿Entonces qué hay de ti?";
			link.l1.go = "PZ_Formosa_bandit_2";
		break;
		
		case "PZ_Formosa_bandit_2":
			dialog.text = "¡Bien dicho! ¡Estamos de patrulla! Dicen que hay un pequeño hombre amarillo husmeando por el pueblo, molestando a la gente temerosa de Dios.";
			link.l1 = "¿Quién podría ser, dime por favor?";
			link.l1.go = "PZ_Formosa_bandit_3";
		break;
		
		case "PZ_Formosa_bandit_3":
			dialog.text = "Basta de hablar - se está haciendo tarde y empiezo a tener sueño.";
			link.l1 = "Pronto tu sueño será eterno.";
			link.l1.go = "PZ_Formosa_bandit_4";
		break;
		
		case "PZ_Formosa_bandit_4":
			DialogExit();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("PZ_JohanVanMerden");
			ChangeCharacterAddressGroup(sld, PChar.location, "patrol", "patrol7");
			GiveItem2Character(sld, "blade_31");
			EquipCharacterByItem(sld, "blade_31");
			LAi_SetActorType(sld);
			
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("PZ_FormosaBandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_Formosa2_IshemMerden_7");
			
			DoQuestCheckDelay("PZ_Formosa2_IshemMerden_6", 10.0);
		break;
		
		case "PZ_Formosa_JohanVanMerden_21":
			dialog.text = "Chang Tu, ¿estás bien?";
			link.l1 = "¡Mynheer van Merden! Estoy bien, gracias a tu intervención. ¿Estás bien tú? Esa es la pregunta más importante.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_22";
		break;
		
		case "PZ_Formosa_JohanVanMerden_22":
			dialog.text = "Siempre pensando en los demás, ¿verdad? Compartimos ese rasgo. No podía quedarme de brazos cruzados cuando los vi atacándote, aunque sabía que podrías manejarlos. Para responder a tu pregunta, estoy bien, solo un poco cansada. Mis piernas están un poco temblorosas. Vamos adentro, si no te importa. Podemos hablar allí.";
			link.l1 = "Por supuesto, Mynheer van Merden, después de todo es tu casa.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_23";
		break;
		
		case "PZ_Formosa_JohanVanMerden_23":
			DoQuestReloadToLocation("Formosa_houseSp1", "goto", "goto1", "PZ_Formosa2_IshemMerden_8");
		break;
		
		case "PZ_Formosa_JohanVanMerden_24":
			dialog.text = "Ahora podemos hablar sin prisa, en paz y tranquilidad. Dime, ¿qué te trae a mí, Chang Tu?";
			link.l1 = "Tienes razón, Mynheer van Merden. Acabo de regresar de Batavia, y...";
			link.l1.go = "PZ_Formosa_JohanVanMerden_25";
		break;
		
		case "PZ_Formosa_JohanVanMerden_25":
			dialog.text = "Espera. ¿Es el pobre Chang Xing...?";
			link.l1 = "¡No, en absoluto! Espero que no. El cielo aún guarda su destino en secreto para mí. Y en cuanto a Fermentelos... no está en Batavia. Van Diemen no fue de ayuda.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_26";
		break;
		
		case "PZ_Formosa_JohanVanMerden_26":
			dialog.text = "No lo sería, porque él y Oliveiro son viejos amigos. Como dicen los ingleses, amigos y cómplices en el crimen. Me sorprendería si te diera algo útil.";
			link.l1 = "Sí, gracias tanto a ti como a Trust, adquirí poderosas armas. Ataqué a Van Diemen para interrogarlo y averiguar dónde estaba Fermentelos. Pero murió antes de que pudiera aprender algo...";
			link.l1.go = "PZ_Formosa_JohanVanMerden_28";
		break;
		
		case "PZ_Formosa_JohanVanMerden_28":
			dialog.text = "Impresionante. Te has dado cuenta de que la gente no siempre quiere compartir lo que sabe. Así que hay otros... métodos de persuasión, digamos. Pensé que podrías haber aprendido sobre la muerte de tu hermana, y por eso te enfureciste. Pero, ¿qué te trae a mí ahora? Te dije que no sabía a dónde va Fermentelos, aparte de sus visitas ocasionales a Batavia. Con Van Diemen fuera, esa última pista se pierde.";
			link.l1 = "Pero sabes muchas cosas y conoces a mucha gente. Pensé que podrías ayudarme de nuevo, tal vez preguntar sobre Fermentelos, como antes. Fuiste el primer hombre blanco en tratarme bien. El primer... amigo blanco.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_29";
		break;
		
		case "PZ_Formosa_JohanVanMerden_29":
			dialog.text = "Eso es... conmovedor.";
			link.l1 = "Mynheer van Merden, ¿por qué sonríes...?";
			link.l1.go = "PZ_Formosa_JohanVanMerden_30";
		break;
		
		case "PZ_Formosa_JohanVanMerden_30":
			dialog.text = "¿Eh? Oh, lo siento, Chang Tu. Me estoy volviendo viejo, sentimental y melancólico con la edad. Es una sonrisa sincera - no podría ocultarla. Me alegra que me consideres un amigo. Ya que somos amigos, también espero que me ayudes de vez en cuando. A cambio, definitivamente te ayudaré con Fermentelos. No te preocupes - no estás caminando hacia una trampa.";
			link.l1 = "Mm, ¿ayudarte cómo?";
			link.l1.go = "PZ_Formosa_JohanVanMerden_31";
		break;
		
		case "PZ_Formosa_JohanVanMerden_31":
			dialog.text = "Desde que nos vimos por última vez, he profundizado en el estudio de tu idioma y cultura, especialmente en medicina. Me gustaría que de vez en cuando me encontraras ciertas placas relicarias. Te pagaré generosamente por ellas, como por cualquier otro trabajo. Y espero que podamos practicar nuestras conversaciones en chino de vez en cuando. Me da vergüenza pedírselo a mis sirvientes, pero un amigo...";
			link.l1 = "Chang Tu hará lo mejor que pueda, Lord van Merden.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_32";
		break;
		
		case "PZ_Formosa_JohanVanMerden_32":
			dialog.text = "Bien. Tú y yo tenemos un largo camino por delante, mi amigo. Un largo camino. ¡Ja! Creo que sería un buen nombre de cobertura para ti. Una práctica útil de mi oficio. En holandés, es “Lange Afstand.” Los ingleses dicen “Long Way.” ¿Cuál prefieres?";
			link.l1 = "Me gusta más la versión en inglés. Largo. Camino. Longway. Suena bastante adecuado en mi idioma. Gracias por escuchar, Lord van Merden. Longway aguardará su palabra y estará listo para asistirle y cumplir sus solicitudes.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_33";
		break;
		
		case "PZ_Formosa_JohanVanMerden_33":
			DialogExit();
			
			SetCurrentTime(15, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			DeleteAttribute(pchar, "questTemp.lockedMusic");
			
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			
			bQuestDisableMapEnter = true;
			pchar.GenQuest.CabinLock = true;
			QuestToSeaLogin_Launch();
			QuestToSeaLogin_PrepareLoc("Guadeloupe", "Quest_Ships", "Quest_ship_8", false);
			DoQuestCheckDelay("PZ_SegodnyaVremya_2", 5.0);
		break;
		
		// Этап 3, СЛЕД ЗВЕЗДЫ
		case "PZ_Longway_PosleRasskaza":
			dialog.text = "Hablando del archivo, Mi Señor Capitán, ¿lo tienes contigo? Es todo lo que necesito - sé el cifrado de memoria.";
			if (CheckCharacterItem(pchar, "MerdokArchive"))
			{
				notification("All Skills +", "Longway");
				AddCharacterExpToSkill(npchar, "Leadership", 50);
				AddCharacterExpToSkill(npchar, "FencingLight", 50);
				AddCharacterExpToSkill(npchar, "Fencing", 50);
				AddCharacterExpToSkill(npchar, "FencingHeavy", 50);
				AddCharacterExpToSkill(npchar, "Pistol", 50);
				AddCharacterExpToSkill(npchar, "Fortune", 50);
				AddCharacterExpToSkill(npchar, "Sneak", 50);
				AddCharacterExpToSkill(npchar, "Sailing", 50);
				AddCharacterExpToSkill(npchar, "Accuracy", 50);
				AddCharacterExpToSkill(npchar, "Cannons", 50);
				AddCharacterExpToSkill(npchar, "Grappling", 50);
				AddCharacterExpToSkill(npchar, "Defence", 50);
				AddCharacterExpToSkill(npchar, "Repair", 50);
				AddCharacterExpToSkill(npchar, "Commerce", 50);	
				
				link.l1 = "Sí, lo guardé, pensando que podría ser útil algún día.";
				link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_1";
			}
			else
			{
				link.l1 = "Desafortunadamente, no. ¿Era tu última esperanza para encontrar a hermana?";
				link.l1.go = "PZ_Longway_PosleRasskaza_2";
			}
		break;
		
		case "PZ_Longway_PosleRasskaza_2":
			dialog.text = "Longway está muy complacido de que al Señor Capitán le preocupe. Por ahora, aún hay esperanza. He encontrado una nueva pista en Guadalupe.";
			link.l1 = "Está bien, entonces. Cuéntame qué te pasó allí.";
			link.l1.go = "PZ_Longway_PosleRasskaza_3";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_1":
			dialog.text = "Esa fue una decisión sabia. Tal vez encontremos algo ahí que pueda ayudarnos en nuestra búsqueda de Chang Xing.";
			link.l1 = "Eso sería ideal. Estudiémoslo ahora mismo.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_2";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_2":
			dialog.text = "Sí, estudiémoslo juntos. El año es... 1637. Antoon van Diemen vendió... vendió...";
			link.l1 = "¿Esclavos, verdad?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_3";
			AddQuestRecordInfo("PZ_ArchiveOneMerden", "1");
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_3":
			dialog.text = "Mujeres de mi pueblo, vendidas a ricos hombres blancos.";
			link.l1 = "Eso es terrible.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_4";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_4":
			dialog.text = "Señor Capitán, no parece sorprendido. ¿No le inquieta en absoluto el destino de esas mujeres?";
			link.l1 = "Longway, por supuesto que me preocupa sinceramente. He visto esta inmundicia desde dentro. Pero siempre he sido un defensor de las mujeres... y un poco mujeriego, para ser honesto. Es bueno que hayas matado a van Diemen; se lo merecía. ¿Hay algo más?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_5";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_5":
			dialog.text = "Van Diemen solo trabajaba con aquellos en quienes confiaba completamente: Joep van der Vink, su mano derecha, y ese maldito Oliveiro Fermentelos. Y... y...";
			link.l1 = "¿Qué sucede? Te has puesto pálido, Longway.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_6";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_6":
			dialog.text = "Johan van Merden...";
			link.l1 = "Lamento mucho. Es horrible, pero ¿por qué estás tan sorprendido? Antes dijiste que arrancaste todas las páginas que mencionaban a Fermentelos. ¿No encontraste mención de van Merden entonces?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_7";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_7":
			dialog.text = "Longway tenía prisa y debió haber pasado por alto esta pieza importante.";
			link.l1 = "Ya veo. Cuando estés listo, sigamos buscando y encontremos algo que podamos usar ahora mismo.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_8";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_8":
			dialog.text = "Está escrito que Fermentelos enviaría a su gente a capturar mujeres, sustituirlas y destruir los registros. Merden luego las enviaría a Batavia, donde van der Vink y van Diemen vendían a nuestras mujeres a hombres blancos. Si tan solo lo hubiera sabido antes...";
			link.l1 = "Entonces, al final, todos trabajaron juntos. No te culpes, Longway. No podías saberlo. El archivo solo llegó a tus manos recientemente. ¿Hay algo más?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_9";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_9":
			dialog.text = "Sí. Llevan casi diez años en eso. Tantas mujeres perdieron a sus familias, su honor, su esperanza... Pero entonces Fermentelos dejó de trabajar con van Merden. Esa es la única razón por la que me ayudó: todo lo que siempre quiso fue deshacerse de su antiguo socio.";
			link.l1 = "¿Qué otros detalles de sus sucias fechorías están registrados aquí?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_10";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_10":
			dialog.text = "Más de los oscuros pensamientos de van Merden. Descubrió que van Diemen lo estaba engañando con el dinero. Así que me envió a Batavia, esperando que muriera allí, pero también esperando que me llevara a van Diemen conmigo.";
			link.l1 = "Frío. Pero también increíblemente astuto.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_11";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_11":
			dialog.text = "Podría haber sido aún peor. Fue van Merden quien envió a esos matones a su casa para matarme. Intervino para ayudar solo cuando se dio cuenta de que podría derrotarlos por mi cuenta.";
			link.l1 = "Lo tenía todo pensado, sin duda.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_12";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_12":
			dialog.text = "Después de que regresé con vida, debió pensar que había descubierto su verdadera agenda y venía por venganza. Cuando hablamos, tenía su pistola apuntando bajo la mesa. Pero luego lo llamé mi primer amigo blanco... casi estalla de risa...";
			link.l1 = "Eso es horrible, Longway. Es amargo darse cuenta de que aquellos que considerábamos amigos se reían de nosotros a nuestras espaldas todo el tiempo.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_13";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_13":
			dialog.text = "Longway aprendió algo hace mucho tiempo, poco antes de llegar a este archipiélago. Fui capturado por los portugueses y querían colgarme. El Señor Rodenburg me salvó la vida.";
			link.l1 = "¿Es así como entraste a su servicio? ¿Lucas también estaba en Formosa?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_14";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_14":
			dialog.text = "Sí, así es. Y no solo él, también Van Berg. Van Merden me dijo que fue él quien aconsejó a Rodenburg que me perdonara. Pero algún tiempo después, Longway supo de una fuente turbia que en realidad fue Johan quien envió a los portugueses tras de mí. No lo creí entonces... pero ahora me doy cuenta de que podría ser cierto...";
			link.l1 = "Asqueroso.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_15";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_15":
			dialog.text = "Aún así, las dudas se asentaron en mi corazón ese día. Así que cuando supe que Mi Señor Capitán y van Merden se habían enfrentado, Longway recordó tu amabilidad y tomó tu lado.";
			link.l1 = "Fue la decisión correcta, Longway. Je, resulta que todo este tiempo, tu primer amigo blanco de verdad fui yo.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_16";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_16":
			dialog.text = "Resulta así, Mi Señor Capitán. Ahora entiendo. Van Merden me dijo que yo era su amigo. Pero en realidad, Longway no era más que otro trabajador para él, solo más útil que la mayoría. Eso es todo. Las otras páginas tratan de contabilidad, así como detalles comerciales entre Van Berg y Rodenburg.";
			link.l1 = "Ya veo. Y ahora es el momento de que me cuentes lo que hiciste en Guadalupe.";
			link.l1.go = "PZ_Longway_PosleRasskaza_3";
		break;
		
		case "PZ_Longway_PosleRasskaza_3":
			dialog.text = "Estaba buscando la Estrella de la Mañana. Una de las páginas arrancadas del archivo decía que fue vista por última vez cerca de San Cristóbal.";
			link.l1 = "¿Por qué allí? Acordamos encontrarnos en Guadalupe, y te encontré allí.";
			link.l1.go = "PZ_Longway_PosleRasskaza_4";
		break;
		
		case "PZ_Longway_PosleRasskaza_4":
			dialog.text = "Porque San Cristóbal es el hogar de Georges Gravel, uno de los informantes de van Merden. Georges cree que todavía trabajo para Johan. Además, Gravel una vez cometió una grave ofensa contra van Merden. Y Longway ayudó a encubrirlo.";
			link.l1 = "¿Y cuál fue esa ofensa?";
			link.l1.go = "PZ_Longway_PosleRasskaza_5";
		break;
		
		case "PZ_Longway_PosleRasskaza_5":
			dialog.text = "Eso no es importante. Lo importante es que Georges le debía una deuda a Longway. Así que fui a la iglesia donde Gravel trabaja como asistente de sacerdote. ¿Está el Señor Capitán listo para escuchar más? Pareces un poco distraído.";
			link.l1 = "Perdón, me distraje. Sí, claro, adelante, Longway.";
			link.l1.go = "PZ_Longway_PosleRasskaza_6";
		break;
		
		case "PZ_Longway_PosleRasskaza_6":
			DialogExit();
			SetCurrentTime(9, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			SetMainCharacterIndex(GetCharacterIndex("Longway"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("Capsterville,"+ NewStr() +"St. Christopher Island.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Kapstervil", "patrol", "patrol12", "PZ_Kapstervil_Start");
			LaunchFrameForm();
		break;
		
		case "PZ_Zhorzh_1":
			dialog.text = "Bien, no llegaste demasiado tarde. ¡No querría estar aquí más tiempo del necesario, ya sabes! ¿Qué necesitas esta vez, Longway?";
			link.l1 = "Cambia tu tono, Gravel. La organización requiere tus servicios.";
			link.l1.go = "PZ_Zhorzh_2";
		break;
		
		case "PZ_Zhorzh_2":
			dialog.text = "Debo confesar que no he sabido de ellos en mucho tiempo. ¿Se habrán olvidado de mí?";
			link.l1 = " Puedo recordárselos. Tal vez contando al Lord van Merden lo que hiciste.";
			link.l1.go = "PZ_Zhorzh_3";
		break;
		
		case "PZ_Zhorzh_3":
			dialog.text = "¡Está bien, está bien, no necesitas enfadarte tanto! ¿Qué puedo hacer por ti?";
			link.l1 = "Necesito información sobre la Estrella de la Mañana. Cualquier cosa que puedas encontrar. Cuanto más, mejor.";
			link.l1.go = "PZ_Zhorzh_4";
		break;
		
		case "PZ_Zhorzh_4":
			dialog.text = "¡Claro, pero tomará tiempo! ¡Dos días! Como mínimo.";
			link.l1 = "¿Por qué tanto tiempo?";
			link.l1.go = "PZ_Zhorzh_5";
		break;
		
		case "PZ_Zhorzh_5":
			dialog.text = "Normalmente, tomaré dinero de la caja de ofrendas para aflojar las lenguas de mis informantes. ¡Pero nos robaron recientemente! El Padre anunciará una nueva colecta de dinero de donaciones, por supuesto, pero aún necesitamos reparar nuestro techo - ¡está goteando! Va a tomar muchas donaciones para arreglarlo.";
			link.l1 = "Dos días. No puedo quedarme aquí para siempre. No tengo tanto tiempo. Longway no es conocido por su paciencia. Lord van Merden aún menos. ¿O debo recordártelo, Gravel?";
			link.l1.go = "PZ_Zhorzh_6";
		break;
		
		case "PZ_Zhorzh_6":
			dialog.text = "¡No puedo controlar lo que está fuera de mi alcance! Haré lo que pueda. Aunque, lo averiguaría mucho más rápido si encontrases a esos bandidos y trajeras de vuelta nuestras donaciones!";
			link.l1 = "Lo pensaré. Empieza a buscar. Dos días. No más. Nos vemos a la misma hora y en el mismo lugar.";
			link.l1.go = "PZ_Zhorzh_7";
		break;
		
		case "PZ_Zhorzh_7":
			DialogExit(); 
			SetCurrentTime(12, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("Un día después..."+ NewStr() +"En busca de los ladrones de iglesias.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Kapstervil_Jungle", "goto", "goto1", "PZ_Kapstervil_Jungle");
			LaunchFrameForm();
		break;
		
		case "PZ_VorugaChurch_1":
			dialog.text = "¡Vaya, mira eso! ¡Un hombre de ojos rasgados en nuestra isla! ¿Huyendo de tus amos, eh? ¿De quién te escondes, si no te importa que pregunte?";
			link.l1 = "Soy un hombre libre.";
			link.l1.go = "PZ_VorugaChurch_2";
		break;
		
		case "PZ_VorugaChurch_2":
			dialog.text = "¡Ja! Claro que sí. Pero pareces fuerte e inteligente, aunque tus ojos estén un poco rasgados. ¿Quieres unirte a nuestra banda? De todas formas, no creo que tengas otro lugar adonde ir.";
			link.l1 = "Longway piensa que estás más interesado en robarle que en reclutarle.";
			link.l1.go = "PZ_VorugaChurch_3";
		break;
		
		case "PZ_VorugaChurch_3":
			dialog.text = "Heh, considérate afortunado. Recientemente robamos una iglesia en la ciudad, ¿puedes creerlo? ¿Por qué? Porque robar a ladrones no es realmente robar.";
			link.l1 = "No planeaba perseguirte, pero me alegra haberte encontrado.";
			link.l1.go = "PZ_VorugaChurch_4";
		break;
		
		case "PZ_VorugaChurch_4":
			dialog.text = "¿Cazarnos? Ah, entonces eres un mercenario, no un trabajador fugitivo. Malo para ti entonces.";
			link.l1 = "Exactamente.";
			link.l1.go = "PZ_VorugaChurch_5";
		break;
		
		case "PZ_VorugaChurch_5":
			DialogExit();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			LAi_SetCheckMinHP(npchar, 1, true, "PZ_VorugaChurch_win");
			for (i=11; i<=14; i++)
			{
				sld = CharacterFromID("PZ_KapstervilBandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		break;
		
		case "PZ_VorugaChurch_6":
			if (!CharacterIsAlive("PZ_KapstervilBandit_11") && !CharacterIsAlive("PZ_KapstervilBandit_12") && !CharacterIsAlive("PZ_KapstervilBandit_13"))
			{
				dialog.text = "Maldita sea... ¿Por qué no me mataste de inmediato? ¿Qué quieres de mí? ¿Vas a arrastrarme a la prisión?";
				link.l1 = "No tengo interés en eso. Solo dime dónde escondiste el oro.";
				link.l1.go = "PZ_VorugaChurch_7";
			}
			else
			{
				dialog.text = RandSwear()+"¿Hola?";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_VorugaChurch_win");	
			}
		break;
		
		case "PZ_VorugaChurch_7":
			dialog.text = "Je... Maldito bastardo de piel amarilla...";
			link.l1 = "La paciencia de Longway se está agotando. Lo descubriré de todos modos. La única pregunta es cuánto tiempo sufrirás.";
			link.l1.go = "PZ_VorugaChurch_8";
			LAi_group_Delete("EnemyFight");
		break;
		
		case "PZ_VorugaChurch_8":
			dialog.text = "Está bien, sí, ¿eh?... Está en una cueva. Todo está allí. El dinero es tuyo. Solo... solo no me mates, ¿de acuerdo?";
			link.l1 = "No dije que no habría sufrimiento en absoluto...";
			link.l1.go = "PZ_VorugaChurch_9";
		break;
		
		case "PZ_VorugaChurch_9":
			DialogExit();
			
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Shot", "1", 1.5);
			DoQuestCheckDelay("PZ_VorugaChurch_win_2", 0.9);
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_0":
			StartQuestMovie(true, false, true);
			locCameraFromToPos(2.48, 0.87, 9.26, true, 6.72, -0.85, 6.05);
			dialog.text = " (en mandarín) Aquí está el escondite de los bandidos.";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_0_1";
			CharacterTurnToLoc(pchar, "box", "box1");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_0_1":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto2", "PZ_Kapstervil_Grot_1", -1);
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_1":
			dialog.text = "¡Es mucho!";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_1_1";
			CharacterTurnToLoc(pchar, "box", "box1");
			locCameraFromToPos(6.83, 2.65, 6.62, true, 2.83, -1.00, 7.67);
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_1_1":
			dialog.text = "（在普通话中）我听到脚步声...";
			link.l1 = "(en Mandarín) Hay alguien más aquí...";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_2";
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_2":
			DialogExit();
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Kapstervil_GrotSoldier_1", "sold_fra_7", "man", "man", 5, FRANCE, -1, true, "soldier"));
			LAi_SetActorType(sld);
			sld.CantLoot = true;
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
			TeleportCharacterToPosAy(sld, 4.17, 0.65, -1.42, 0.00);
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Kapstervil_GrotSoldier_2", "sold_fra_5", "man", "man", 5, FRANCE, -1, true, "soldier"));
			LAi_SetActorType(sld);
			sld.CantLoot = true;
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
			TeleportCharacterToPosAy(sld, 4.10, 0.65, 0.30, 3.00);
			
			LAi_SetStayType(pchar);
			LAi_Fade("PZ_Kapstervil_Grot_2", "");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_3":
			dialog.text = "¿Qué diablos hacemos aquí? No queda nadie - nos aseguramos de que todos los ladrones se fueran.";
			link.l1 = "";
			link.l1.go = "exit";
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_Kapstervil_GrotSoldier_2"));
			AddDialogExitQuest("PZ_Kapstervil_Grot_4");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_5":
			dialog.text = "¡Ese es el punto, idiota! Volverán, y les daremos una cálida bienvenida.";
			link.l1 = " ";
			link.l1.go = "exit";
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_Kapstervil_GrotSoldier_1"));
			AddDialogExitQuest("PZ_Kapstervil_Grot_5");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_7":
			dialog.text = "Voy a echar un vistazo, asegurarme de que nadie esté escondido. De todos modos, estoy aburrido...";
			link.l1 = "Lo siento, не могу помочь с этой просьбой.";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_8";
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_Kapstervil_GrotSoldier_2"));
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_8":
			DialogExit();
			LAi_Fade("PZ_Kapstervil_Grot_5_1", "");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_9":
			dialog.text = "(en mandarín) ¡Soldados! Qué desgracia... ¿Qué se supone que debo hacer ahora?";
			link.l1 = "(en mandarín) ¡Necesito este dinero más que los soldados blancos! ¡No me iré sin él!";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_10";
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_10":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("PZ_Kapstervil_GrotSoldier_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyWithRadius");
				LAi_group_SetRelation("EnemyWithRadius", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_SetLookRadius("EnemyWithRadius", 6.0);
				LAi_group_SetHearRadius("EnemyWithRadius", 2.0);
				LAi_group_SetSayRadius("EnemyWithRadius", 12.0);
				LAi_group_SetCheck("EnemyWithRadius", "PZ_Kapstervil_Grot_6");
			}
		break;
		
		case "PZ_Zhorzh_11":
			dialog.text = "¡Ah, monsieur Longway, has regresado!";
			link.l1 = "Por supuesto. ¿Había alguna duda? ¿Descubriste algo sobre la Estrella Matutina, Georges?";
			link.l1.go = "PZ_Zhorzh_12";
		break;
		
		case "PZ_Zhorzh_12":
			dialog.text = "Sí, monsieur. Es un galeón pesado, capitaneado por un español, o eso dicen...";
			link.l1 = "Es portugués. Ustedes, los blancos, ni siquiera pueden distinguirse entre sí.";
			link.l1.go = "PZ_Zhorzh_13";
		break;
		
		case "PZ_Zhorzh_13":
			dialog.text = "Oh, cierto. Mi error. De todos modos, descubrí que él ha modificado el galeón considerablemente para intentar hacerlo pasar por un barco mercante, con cañones de pequeño calibre y una tripulación más reducida. Pero amplió la bodega, llenándola hasta el tope - está tan pesado que apenas puede navegar.";
			link.l1 = "Así que ha decidido empezar una nueva vida. Bien. Ahora, ¿dónde puedo encontrarlo?";
			link.l1.go = "PZ_Zhorzh_14";
		break;
		
		case "PZ_Zhorzh_14":
			dialog.text = "Eso es más complicado. Se mueve constantemente entre nuestras colonias y las inglesas, pero solo entre las Islas de Barlovento. Sin embargo, he sabido que en este momento está de camino a Basse-Terre con un gran cargamento de vino.";
			link.l1 = "Necesito averiguar cómo llegar allí rápidamente.";
			link.l1.go = "PZ_Zhorzh_15";
		break;
		
		case "PZ_Zhorzh_15":
			dialog.text = "Eso es asunto tuyo, monsieur Longway. Tengo suficientes problemas propios... como arreglar ese maldito techo.";
			link.l1 = "Hablando de preocupaciones, encontré a esos ladrones de iglesias. Aquí está de vuelta su dinero de donación. Arregle el techo - no es bueno que su Dios esté sin uno.";
			link.l1.go = "PZ_Zhorzh_16";
		break;
		
		case "PZ_Zhorzh_16":
			dialog.text = "¡Muchísimas gracias, señor Longway! Nunca pensé que serías tú quien hiciera eso.";
			link.l1 = "No lo pensé tampoco. Pero tenía que hacer algo con esos dos días.";
			link.l1.go = "PZ_Zhorzh_17";
		break;
		
		case "PZ_Zhorzh_17":
			dialog.text = "Entonces, ¿necesitas llegar a Guadalupe? Te encontraré un barco que vaya para allá. ¡Espera noticias mías pronto!";
			link.l1 = "Eso sería útil. Gracias, Georges.";
			link.l1.go = "PZ_Zhorzh_18";
		break;
		
		case "PZ_Zhorzh_18":
			DialogExit();
			SetCurrentTime(9, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("A la mañana siguiente..."+ NewStr() +"Capsterville", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Kapstervil", "goto", "goto19", "PZ_Kapstervil_PoiskZvezda");
			LaunchFrameForm();
		break;
		
		case "PZ_Kapstervil_Kurier_1":
			dialog.text = "¿Debes ser un conocido de Georges? Me pidió que te entregara esto.";
			link.l1 = "¿Una nota? Mi gratitud. ¿Cómo supiste que era para mí?";
			link.l1.go = "PZ_Kapstervil_Kurier_2";
		break;
		
		case "PZ_Kapstervil_Kurier_2":
			dialog.text = "¿En serio?";
			link.l1 = "Ah, claro.";
			link.l1.go = "PZ_Kapstervil_Kurier_3";
		break;
		
		case "PZ_Kapstervil_Kurier_3":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("PZ_Kapstervil_ChitaemPismo", 1.5);
		break;
		
		case "PZ_Kapstervil_ChitaemPismo_Dialog":
			dialog.text = "(Lee la carta) Monsieur Longway, el pinnace 'Provence' parte hacia Basse-Terre mañana por la mañana. El capitán, Mathieu Terugny, se encuentra en la taberna. Da mis saludos a monsieur van Merden. - Georges Gravel.";
			link.l1 = "¿Lo harás? ¡Prométemelo, sí, ¿eh? ¡Jura que no me traicionarás!";
			link.l1.go = "PZ_Kapstervil_ChitaemPismo_Dialog_2";
		break;
		
		case "PZ_Kapstervil_ChitaemPismo_Dialog_2":
			DialogExit();
			LAi_RemoveCheckMinHP(pchar);
			chrDisableReloadToLocation = false;
			LAi_SetPlayerType(pchar);
			sld = characterFromId("PZ_Kapstervil_tavernkeeper");
			sld.dialog.currentnode = "PZ_TerunyiTavern1";
			LAi_SetBarmanType(sld);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "PZ_TerunyiTavern1":
			dialog.text = "No servimos bebidas a tu tipo aquí. Y a menos que quiera escuchar quejas sobre pulgas, tampoco te alquilaré una habitación.";
			link.l1 = "No necesito un trago ni una habitación. Y... Longway no tiene pulgas.";
			link.l1.go = "PZ_TerunyiTavern2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_TerunyiTavern2":
			dialog.text = "¿Cómo demonios se supone que debo saberlo? Está bien, escúpelo. ¿Qué quieres? Entonces lárgate.";
			link.l1 = "Lo haré. Estoy buscando al Capitán Mathieu Terugny. No puedo encontrarlo. ¿Sabes dónde está?";
			link.l1.go = "PZ_TerunyiTavern3";
		break;
		
		case "PZ_TerunyiTavern3":
			dialog.text = "Está ocupado preparando su barco para zarpar en la tienda local. Eso es mucho más importante que charlar con un chino como tú, pero claramente no entiendes eso.";
			link.l1 = "En realidad, solía ser... No importa. No es importante ahora mismo.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_CreateTerunyi");
		break;
		
		case "PZ_Terunyi1":
			dialog.text = "¿Qué quieres, chino? ¿No ves que estoy ocupado? Necesito preparar mi barco.";
			link.l1 = "¿Capitán Mathieu Terugny?";
			link.l1.go = "PZ_Terunyi2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Terunyi2":
			dialog.text = "Bueno, esto dejó de ser divertido. ¿Cómo alguien como tú sabe quién soy? ¿Te envió alguien?";
			link.l1 = "No hay necesidad de preocuparse. Escuché que navegas a Basse-Terre. ¿Puedes llevarme como pasajero? Te pagaré.";
			link.l1.go = "PZ_Terunyi3";
		break;
		
		case "PZ_Terunyi3":
			dialog.text = "Esto sigue mejorando. Me dirijo a St. Pierre, no a Basse-Terre, pero es un pequeño desvío. Eso es bueno, porque no tendré que mantenerte en el barco más de lo necesario. Cinco mil pesos. Partimos en tres horas. Paga en el muelle. Aunque soy un comerciante, no hay regateo. ¿Entendido?";
			link.l1 = "Sí. Gracias. Nos vemos en el muelle, Capitán Terugny.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TeleportToPier");
		break;
		
		case "PZ_Terunyi4":
			dialog.text = "Al final apareciste, chinito. Pensé que no lo lograrías, nadie le da dinero de verdad a los de tu clase voluntariamente.";
			link.l1 = "Cinco mil pesos, tal como pediste. ¿Estás listo para zarpar?";
			link.l1.go = "PZ_Terunyi5";
		break;
		
		case "PZ_Terunyi5":
			AddMoneyToCharacter(pchar, -5000);
			
			dialog.text = "¡No, no! Yo debería ser quien te pregunte eso. Pero supongo que estás listo. Vamos. Tú remarás el bote. ¡Y no esperes un camarote decente! Eres la única razón por la que hacemos este desvío.";
			link.l1 = "No necesito consuelo. Solo llévame allí.";
			link.l1.go = "PZ_Terunyi6";
		break;
		
		case "PZ_Terunyi6":
			DialogExit();
			
			SetCurrentTime(2, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			InterfaceStates.Buttons.Save.enable = true;
			
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			
			QuestToSeaLogin_Launch();
			QuestToSeaLogin_PrepareLoc("Guadeloupe", "Quest_Ships", "Quest_ship_8", false);
			DoQuestCheckDelay("PZ_Flashback_Final_1", 3.5);
		break;
		
		case "PZ_Longway_PosleRasskaza21":
			dialog.text = "...así que Longway no pudo averiguar exactamente hacia dónde se dirige la Estrella Matutina.";
			link.l1 = "Sí, puedo ver cómo terminaste en todo ese lío.";
			link.l1.go = "PZ_Longway_PosleRasskaza22";
		break;
		
		case "PZ_Longway_PosleRasskaza22":
			if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena")) sStr = "Helena";
			else sStr = "Alonso";
			dialog.text = "Vi un bergantín en las aguas de Guadalupe. Quizás era el Banten. Intentaré averiguarlo. Bueno, puedes irte ahora, Longway. Tráeme "+sStr+".";
			link.l1.go = "PZ_Longway_PosleRasskaza23";
		break;
		
		case "PZ_Longway_PosleRasskaza23":
			DialogExit();
			LAi_SetStayType(pchar);
			LAi_FadeLong("PZ_LongwayUhoditIzKauty", "PZ_HelenaOrAlonso");
		break;
		
		case "PZ_Helena_1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "Mi capitán, ¿todo está bien? Vine tan pronto como Longway dijo que me necesitabas.";
				link.l1 = "Solo estoy tratando de juntar las piezas. ¿Recuerdas el nombre de ese bergantín que vimos frente a la isla?";
				link.l1.go = "PZ_Helena_3";
			}
			else
			{
				dialog.text = "¿Querías verme?";
				link.l1 = "Sí. ¿Recuerdas la fragata que vimos recientemente? Averigua su ubicación y nombre.";
				link.l1.go = "PZ_Helena_2";
			}
		break;
		
		case "PZ_Helena_2":
			dialog.text = "Recuerdo, pero ¿por qué el repentino interés en un bergantín? Averiguarlo podría llevar algún tiempo.";
			link.l1 = "Helen, solo hazlo, por favor. Y sí, sé que podría llevar un tiempo. Estaré esperando.";
			link.l1.go = "PZ_PoiskBanten";
		break;
		
		case "PZ_Helena_3":
			dialog.text = "No, no comprobé. ¿Por qué? ¿Es importante?";
			link.l1 = "Ajá. ¿Puedes averiguar más? Necesito saber dónde están anclados ahora, si no han salido ya de las aguas de Guadalupe.";
			link.l1.go = "PZ_Helena_4";
		break;
		
		case "PZ_Helena_4":
			dialog.text = "Por supuesto. Solo una advertencia, podría tardar un poco. Llevaré un bote y un par de chicos para ayudar, sí, ¿eh, Charles?";
			link.l1 = "Por supuesto, Helen, gracias. Estaré esperando.";
			link.l1.go = "PZ_PoiskBanten";
		break;
		
		case "PZ_Alonso_11":
			dialog.text = "Señor Capitán, ¿me llamaste?";
			link.l1 = "Sí, Alonso. Pasamos una goleta en las aguas frente a la isla cuando regresamos por Longway. ¿Por casualidad captaste su nombre?";
			link.l1.go = "PZ_Alonso_12";
		break;
		
		case "PZ_Alonso_12":
			dialog.text = "No, mi trabajo es vigilar a los nuevos reclutas y participar en la vanguardia de abordaje. Además, no tengo un catalejo, y no estábamos tan cerca.";
			link.l1 = "Es cierto. Pero necesito saberlo de todos modos. Hazlo.";
			link.l1.go = "PZ_Alonso_13";
		break;
		
		case "PZ_Alonso_13":
			dialog.text = "Sí, Capitán. Creo que puedo hacerlo en medio día.";
			link.l1 = "Apresúrate. Estaré esperando.";
			link.l1.go = "PZ_PoiskBanten";
		break;
		
		case "PZ_PoiskBanten":
			DialogExit();
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			LAi_SetStayType(pchar);
			SetLaunchFrameFormParam("Five hours later...", "PZ_PoiskBanten_2", 0, 4.0);
			LaunchFrameForm();
			locCameraSleep(true);
		break;
		
		case "PZ_Helena_5":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "Lo he aprendido todo. ¿Todo estuvo bien mientras estuve fuera, mi capitán?";
				link.l1 = "Sí, estoy bien, gracias, Helen. Dime.";
				link.l1.go = "PZ_Helena_7";
			}
			else
			{
				dialog.text = "¡Uf, ya estoy de vuelta. Encontré tu bergantín!";
				link.l1 = "Bienvenido de nuevo. ¿Cuál es su ubicación y nombre?";
				link.l1.go = "PZ_Helena_6";
			}
		break;
		
		case "PZ_Helena_6":
			dialog.text = "El Banten. Ese nombre significa algo para ti, ¿verdad? Ahora está en el faro, y algunos de sus tripulantes han desembarcado. ¿Vamos a atacar ese barco?";
			link.l1 = "No, necesitamos averiguar exactamente quién desembarcó. Iremos al faro por tierra. Teniendo en cuenta que ya hemos sido retrasados, es hora de salir del puerto. Deberíamos anclar en algún lugar remoto. La Playa Capster sería buena. Apresurémonos, Helen.";
			link.l1.go = "PZ_BasTerMayak";
		break;
		
		case "PZ_Helena_7":
			dialog.text = "Bueno, el bergantín se llama el Banten, y está anclado en el faro. Algunos de la tripulación han desembarcado allí. ¿Qué vas a hacer?";
			link.l1 = "Para averiguarlo, tendremos que llegar al faro sin ser vistos, y solo podemos hacerlo a pie. Nuestro barco necesita anclar en un lugar seguro. ¿Qué tal la Playa de Capster?";
			link.l1.go = "PZ_Helena_8";
		break;
		
		case "PZ_Helena_8":
			dialog.text = "Buena idea. Charles, ¿quieres que vaya contigo al faro?";
			link.l1 = "Lo pensaré mientras movemos el barco - ya estás lo suficientemente cansado.";
			link.l1.go = "PZ_BasTerMayak";
		break;
		
		case "PZ_Alonso_15":
			dialog.text = "Regresé tan pronto como terminé, Mi Señor Capitán.";
			link.l1 = "Muy bien. Informe, Alonso.";
			link.l1.go = "PZ_Alonso_16";
		break;
		
		case "PZ_Alonso_16":
			dialog.text = "La balandra aún está frente a la isla, en el faro, para ser precisos. El nombre en la popa es Banten. Algunos de su tripulación han desembarcado.";
			link.l1 = "Buen trabajo, Alonso. Prepara a la tripulación para levar anclas de inmediato.";
			link.l1.go = "PZ_Alonso_17";
		break;
		
		case "PZ_Alonso_17":
			dialog.text = "¿Prepararnos para abordar también?";
			link.l1 = "Aún no. Si su capitán se dirige al faro, podría esconderse en la ciudad si atacamos en el mar. Nos dirigiremos a la Playa Capster para asegurar nuestro barco, luego nos acercaremos al faro a pie.";
			link.l1.go = "PZ_BasTerMayak";
		break;
		
		case "PZ_BasTerMayak":
			DialogExit();
			locCameraSleep(false);
			LAi_SetPlayerType(pchar);
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			chrDisableReloadToLocation = false;
			bDisableCharacterMenu = false;
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			Island_SetReloadEnableGlobal("Guadeloupe", true);
			
			AddQuestRecord("PZ", "15");
			PChar.quest.PZ_Banten_PlyazhKapster.win_condition.l1 = "location";
			PChar.quest.PZ_Banten_PlyazhKapster.win_condition.l1.location = "Shore29";
			PChar.quest.PZ_Banten_PlyazhKapster.win_condition = "PZ_Banten_PlyazhKapster";
			
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1 = "Timer";
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.hour = sti(GetTime() + 7);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition = "PZ_Banten_PlyazhKapster_Proval";
			
			if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena"))
			{
				LAi_SetActorType(npchar);
				LAi_ActorFollow(npchar, pchar, "", -1);
				LAi_SetOfficerType(npchar);
				npchar.Dialog.Filename = "Quest\Saga\Helena.c";
				npchar.Dialog.CurrentNode = "Helena_officer";
			}
		break;
		
		case "PZ_Longway_21":
			dialog.text = "¡Mi Señor Capitán, mire! Hay alguien dentro del faro.";
			link.l1 = "¡Bien, estamos a tiempo! Vamos rápido a por ellos. Alonso tendrá mucho trabajo hoy.";
			link.l1.go = "PZ_Longway_22";
		break;
		
		case "PZ_Longway_22":
			dialog.text = "¿Pero qué pasa si mueren en el proceso?";
			link.l1 = "¿Qué sugieres?";
			link.l1.go = "PZ_Longway_23";
		break;
		
		case "PZ_Longway_23":
			dialog.text = "Ingresamos sigilosamente y escuchamos su conversación primero.";
			link.l1 = "Dudo que podamos hacerlo sin que nos vean desde la ventana. Pero intentémoslo.";
			link.l1.go = "PZ_Longway_24";
		break;
		
		case "PZ_Longway_24":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			npchar.Dialog.CurrentNode = "Longway_officer";
			LAi_SetCheckMinHP(npchar, 1, true, "SkritoeBessmertie");
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1 = "locator";
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1.location = "Mayak4";
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1.locator_group = "goto";
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1.locator = "goto31";
			PChar.quest.PZ_MayakPodslushivanie.win_condition = "PZ_MayakPodslushivanie";
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_1":
			dialog.text = "Piensa en lo que te dije. Piensa bien. El dinero no es un problema, dentro de ciertos límites, por supuesto. Pero incluso ese límite te parecerá una montaña de oro: ¡el chino debe morir! He enviado hombres tras él antes, pero sin éxito. Sin embargo, esta vez, si se unen con tus hombres...";
			link.l1 = "";
			link.l1.go = "PZ_MayakPodslushivanie_Dialog_1_1";
			CharacterTurnByChr(npchar, CharacterFromID("PZ_BasTerJailOff_Clone"));
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_1_1":
			StartInstantDialog("PZ_BasTerJailOff_Clone", "PZ_MayakPodslushivanie_Dialog_2", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_2":
			dialog.text = "¡Mira, nos están vigilando! ¡Es él! ¡Él y su maldito capitán!";
			link.l1 = "";
			link.l1.go = "PZ_MayakPodslushivanie_Dialog_3";
			CharacterTurnToLoc(npchar, "item", "flower5");
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_3":
			DialogExit();
			EndQuestMovie();
			locCameraSleep(false);
			locCameraToPos(1.52, 18.87, -9.55, true);
			DoQuestCheckDelay("CameraReset", 1.0);
			DeleteAttribute(pchar, "questTemp.NoFast");
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("PZ_Neznakomets");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			
			sld = CharacterFromID("PZ_BasTerJailOff_Clone");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetCheckMinHP(sld, 1, true, "PZ_MayakPodslushivanie_win");
			
			for (i=1; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_Neznakomets_Bandit_"+i, "citiz_" + (rand(9) + 41), "man", "man", sti(pchar.rank), PIRATE, -1, true, "pirate"));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		break;
		
		case "PZ_Mayak_KomendantSidit_1":
			if (!CharacterIsAlive("PZ_Neznakomets_Bandit_1") && !CharacterIsAlive("PZ_Neznakomets_Bandit_2") && !CharacterIsAlive("PZ_Neznakomets_Bandit_3")&& !CharacterIsAlive("PZ_Neznakomets_Bandit_4"))
			{
				dialog.text = "Maldito seas, sucio asiático... Tuve que soportar tanto por tu culpa. Y ahora, por todo eso, estoy a punto de morir...";
				link.l1 = "Te llevaremos con nuestro médico, Señor Comandante. Solo dinos con quién hablabas, es muy importante.";
				link.l1.go = "PZ_Mayak_KomendantSidit_2";
				LAi_group_Delete("EnemyFight");
			}
			else
			{
				dialog.text = RandSwear()+"";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_MayakPodslushivanie_win");	
			}
		break;
		
		case "PZ_Mayak_KomendantSidit_2":
			dialog.text = "Su nombre... es Joep van der Vink, él... kha...";
			link.l1 = "...";
			link.l1.go = "PZ_Mayak_KomendantSidit_3";
		break;
		
		case "PZ_Mayak_KomendantSidit_3":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_KillCharacter(npchar);
			DoQuestCheckDelay("PZ_Mayak_Longway", 1.5);
		break;
		
		case "PZ_Longway_25":
			dialog.text = "";
			link.l1 = "Está muerto... Bueno, al menos sabemos el nombre. ¿Longway...?";
			link.l1.go = "PZ_Longway_26";
		break;
		
		case "PZ_Longway_26":
			dialog.text = "Eso absolutamente no puede ser...";
			link.l1 = "Te ves un poco pálido, Longway.";
			link.l1.go = "PZ_Longway_27";
		break;
		
		case "PZ_Longway_27":
			dialog.text = "Longway estaba bastante seguro de haber matado a van der Vink hace diez años\n¡Se están escapando! ¡Su barco es rápido!";
			link.l1 = "Sí, un bergantín maravilloso... desafortunadamente para nosotros. Incluso si llegamos a nuestro barco a tiempo, ya se habrán ido para cuando izemos las velas y atrapemos el viento.";
			link.l1.go = "PZ_Longway_28";
		break;
		
		case "PZ_Longway_28":
			dialog.text = "Esto podría ser el fin...";
			link.l1 = "No, Longway. Escúchame. Si planean quedarse en el Archipiélago, tarde o temprano nos encontraremos con ellos; el mundo es pequeño, y el Caribe especialmente. Tan pronto como volvamos a seguir su rastro, dejaré todo y los perseguiré. Te lo prometo. ¿Me escuchas?";
			link.l1.go = "PZ_Longway_29";
		break;
		
		case "PZ_Longway_29":
			dialog.text = "Sí, Mi Señor Capitán. Gracias.";
			link.l1 = "Mantén la cabeza en alto, Longway. Necesitamos apresurarnos de regreso al barco - la muerte del Comandante será una gran noticia muy pronto.";
			link.l1.go = "PZ_Longway_30";
		break;
		
		case "PZ_Longway_30":
			DialogExit();
			
			Return_LongwayOfficer();
			LAi_RemoveCheckMinHP(npchar);
			AddQuestRecord("PZ", "17");
			sld = &Locations[FindLocation("Mayak4")];
			sld.locators_radius.goto.goto31 = 0.5;
			
			chrDisableReloadToLocation = false;
			QuestOpenSeaExit();
			
			pchar.questTemp.PZ_Etap4_Start = true;
		break;
		
		// Этап 4, Обманчивая Звезда
		case "PZ_PoterpKrushenie_1":
			dialog.text = "¡Monsieur! ¡Un momento! ¿Eres capitán?";
			link.l1 = "Tal vez. ¿Cómo lo adivinaste? ¿Y qué quieres?";
			link.l1.go = "PZ_PoterpKrushenie_2";
		break;
		
		case "PZ_PoterpKrushenie_2":
			dialog.text = "Bueno, aquí solo hay montañas y una densa jungla, sin caminos a la ciudad. Sin embargo, aquí estás. No estás solo de turismo, ¿verdad?";
			link.l1 = "Buena observación. Pero aún no me has dicho qué quieres.";
			link.l1.go = "PZ_PoterpKrushenie_3";
		break;
		
		case "PZ_PoterpKrushenie_3":
			dialog.text = "¡Ah, cierto! Capitán, nuestro barco chocó contra las rocas justo frente a esta cala. Somos los únicos que lo logramos...";
			link.l1 = "Lo siento. Quieres que te lleve a algún lugar, ¿no?";
			link.l1.go = "PZ_PoterpKrushenie_4";
		break;
		
		case "PZ_PoterpKrushenie_4":
			dialog.text = "Sí... No causaremos ningún problema, lo juro. Sólo déjanos en Belice, y nos las arreglaremos desde allí.";
			link.l1 = "No está lejos, ¿verdad? En ese caso, bienvenido a bordo.";
			link.l1.go = "PZ_PoterpKrushenie_5";
			link.l2 = "Lo siento, pero voy en la dirección contraria.";
			link.l2.go = "PZ_PoterpKrushenie_7";
		break;
		
		case "PZ_PoterpKrushenie_5":
			dialog.text = "¡Gracias, Capitán! Quién sabe cuánto tiempo habríamos estado atrapados sin ti.";
			link.l1 = "En efecto. ¡No perdamos tiempo!";
			link.l1.go = "PZ_PoterpKrushenie_6";
		break;
		
		case "PZ_PoterpKrushenie_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			DeleteAttribute(&locations[FindLocation("Shore9")], "DisableEncounters");
			
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("PZ_PoterpKrushenie_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "sea", "", "", "", "", -1);
				sld.location = "None";
			}
			
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1 = "location";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1.location = "Beliz_town";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition = "PZ_Beliz_PoterpKrushenie";
			AddMapQuestMarkCity("Beliz", false);
			
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			
			SetTimerCondition("PZ_BelizFail", 0, 0, 30, false);
		break;
		
		case "PZ_PoterpKrushenie_7":
			dialog.text = "¡Pero Belice está tan cerca! No tardaría mucho, ¿verdad?";
			link.l1 = "Tengo prisa. No puedo permitirme ningún desvío.";
			link.l1.go = "PZ_PoterpKrushenie_8";
		break;
		
		case "PZ_PoterpKrushenie_8":
			dialog.text = "¿Ni siquiera un viaje corto? ¿Solo hasta Belice? Por favor, Capitán, ¡no nos deje varados!";
			link.l1 = "Está bien, espero no lamentar esto. ¡Todos a bordo!";
			link.l1.go = "PZ_PoterpKrushenie_6";
			link.l2 = "Así es la vida. Que tengan un buen día, mis amigos.";
			link.l2.go = "PZ_PoterpKrushenie_9";
		break;
		
		case "PZ_PoterpKrushenie_9":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			DeleteAttribute(&locations[FindLocation("Shore9")], "DisableEncounters");
			
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("PZ_PoterpKrushenie_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "", "", "", "", 10);
				sld.location = "None";
			}
			
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1 = "location";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1.location = "Beliz_town";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition = "PZ_Beliz_QuestCitizenDialog";
			
			AddMapQuestMarkCity("Beliz", false);
			
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddCharacterExpToSkill(pchar, "FencingL", 20);
			AddCharacterExpToSkill(pchar, "FencingS", 20);
			AddCharacterExpToSkill(pchar, "FencingH", 20);
			AddCharacterExpToSkill(pchar, "Pistol", 20);
			
			pchar.questTemp.PZ.Shipwreckers.Decline = true;
			
			SetTimerCondition("PZ_BelizFail", 0, 0, 30, false);
		break;
		
		case "PZ_PoterpKrushenie_11":
			dialog.text = "¡Gracias de nuevo, Capitán! Somos solo simples marineros, así que no tenemos mucho que ofrecerle.";
			link.l1 = "Bueno, al menos no tuvimos que desviarnos demasiado.";
			link.l1.go = "PZ_PoterpKrushenie_12";
		break;
		
		case "PZ_PoterpKrushenie_12":
			dialog.text = "Levantaremos una copa por tu salud y encenderemos una vela por ti en la iglesia.";
			link.l1 = "Eso es mejor que nada. ¡Salud, muchachos!";
			link.l1.go = "PZ_PoterpKrushenie_13";
		break;
		
		case "PZ_PoterpKrushenie_13":
			DialogExit();
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("PZ_PoterpKrushenie_"+i);
				LAi_SetCitizenType(sld);
				LAi_CharacterDisableDialog(sld);
				sld.lifeday = 0;
				sld.location = "None";
			}
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_BelizZhitelNovosti", "citiz_4", "man", "man", 1, ENGLAND, 0, false, "quest"));
			ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto5");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_BelizZhitelNovosti_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "PZ_BelizZhitelNovosti_1":
			dialog.text = "¿Escuchaste? ¡Finalmente lo atraparon! ¡Nuestras aguas están seguras al fin!";
			link.l1 = "¿Son... buenas noticias? Pero, ¿a quién atraparon?";
			link.l1.go = "PZ_BelizZhitelNovosti_2";
			DeleteQuestCondition("PZ_BelizFail");
		break;
		
		case "PZ_BelizZhitelNovosti_2":
			dialog.text = "¡Matthew Lutter, el Charlatán en persona!";
			link.l1 = "No estoy familiarizado, ¿qué hizo?";
			link.l1.go = "PZ_BelizZhitelNovosti_3";
		break;
		
		case "PZ_BelizZhitelNovosti_3":
			dialog.text = "¿No lo sabes? ¡Vaya, claramente no eres inglés, puedo darme cuenta! Es un pirata que nos ha estado saqueando a nosotros y a los españoles durante años en su barco, la Gaviota.";
			link.l1 = "Saqueando tanto a los ingleses como a los españoles? Eso es inusual.";
			link.l1.go = "PZ_BelizZhitelNovosti_4";
		break;
		
		case "PZ_BelizZhitelNovosti_4":
			dialog.text = "En efecto. La guardia costera nunca pudo atraparlo, pero al final mordió más de lo que podía masticar - perdió contra un extraño barco mercante, si puedes creerlo.";
			link.l1 = "Eso es divertido. ¿Qué tenía de extraño el mercader?";
			link.l1.go = "PZ_BelizZhitelNovosti_5";
		break;
		
		case "PZ_BelizZhitelNovosti_5":
			dialog.text = "¡Pues era solo un enorme y torpe galeón sin escolta! Pero gracias a su capitán loco, Lutter cantará su última canción hoy - está a punto de ser ahorcado. ¡Deberías venir a verlo!";
			link.l1 = "Podría, pero por ahora, tengo otros asuntos que atender.";
			link.l1.go = "PZ_BelizZhitelNovosti_6";
		break;
		
		case "PZ_BelizZhitelNovosti_6":
			DialogExit();
			
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			
			sld = CharacterFromID("Longway");
			if (!CharacterIsHere("Longway"))
			{
				ChangeCharacterAddressGroup(sld, PChar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"));
			}
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Longway_31";
		break;
		
		case "PZ_Longway_31":
			dialog.text = "¡Señor Capitán!";
			link.l1 = "Un comerciante español derrotando a un pirata audaz... Estás pensando lo mismo que Longway, ¿verdad?";
			link.l1.go = "PZ_Longway_32";
		break;
		
		case "PZ_Longway_32":
			dialog.text = "La Estrella de la Mañana...";
			link.l1 = "Lo más probable es que no haya otro capitán mercante como él en todo el archipiélago.";
			link.l1.go = "PZ_Longway_33";
		break;
		
		case "PZ_Longway_33":
			dialog.text = "¡Debemos encontrarlo inmediatamente!";
			link.l1 = "Correcto. Pero no veo ningún galeón pesado en el puerto. Intentemos hablar con el Charlatán antes de que lo cuelguen. Veamos si se ha ganado ese apodo.";
			link.l1.go = "PZ_Longway_34";
		break;
		
		case "PZ_Longway_34":
			DialogExit();
			Return_LongwayOfficer();
			if (!CheckAttribute(pchar, "questTemp.PZ.Shipwreckers.Decline")) AddQuestRecord("PZ", "18");
			else AddQuestRecord("PZ", "18_1");
			pchar.questTemp.PZ_Beliz_Komendant = true;
			AddLandQuestMarkToPhantom("beliz_prison", "belizJailOff");
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
		break;
		
		case "PZ_Beliz_Komendant_8":
			dialog.text = "¿Sigue vivo? ¿Podemos hablar con él?";
			link.l1 = "";
			link.l1.go = "PZ_Beliz_Komendant_9";
			CharacterTurnByChr(npchar, CharacterFromID("BelizJailOff"));
		break;
		
		case "PZ_Beliz_Komendant_9":
			StartInstantDialogNoType("BelizJailOff", "PZ_Beliz_Komendant_10", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Beliz_Komendant_10":
			dialog.text = "¿Qué? Oh, sí. Está vivo... la ejecución aún no ha ocurrido. Puedes ir a hablar con él, está más hablador que nunca. Pero últimamente ha estado diciendo tonterías, mayormente hablando consigo mismo. El Charlatán se ha vuelto loco... No puedo esperar para colgarlo, antes de que todos nos volvamos locos con su charla interminable.";
			link.l1 = "";
			link.l1.go = "PZ_Beliz_Komendant_11";
		break;
		
		case "PZ_Beliz_Komendant_11":
			StartInstantDialog("Longway", "PZ_Beliz_Komendant_12", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Beliz_Komendant_12":
			dialog.text = "Gracias.";
			link.l1 = "";
			link.l1.go = "PZ_Beliz_Komendant_13";
			CharacterTurnByChr(npchar, CharacterFromID("BelizJailOff"));
		break;
		
		case "PZ_Beliz_Komendant_13":
			DialogExit();
			pchar.questTemp.jailCanMove = true;
			
			Return_LongwayOfficer();
			
			sld = CharacterFromID("BelizJailOff");
			LAi_SetHuberType(sld);
			sld.Dialog.Filename = "Common_Prison.c";
			sld.Dialog.CurrentNode = "First_officer";
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_MatthewLutter", "mercen_15", "man", "man", 1, ENGLAND, -1, false, "quest"));
			sld.name = "Matthew";
			sld.lastname = "Lutter";
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_MatthewLutter1";
			ChangeCharacterAddressGroup(sld, "Beliz_prison", "goto", "goto9");
			LAi_SetStayType(sld);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "PZ_MatthewLutter1":
			dialog.text = "¡Él robó mi tesoro!";
			link.l1 = "¿Matthew Lutter?";
			link.l1.go = "PZ_MatthewLutter2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_MatthewLutter2":
			dialog.text = "Mi tesoro está ligado a él ahora, ¿sabes?, ¡A ÉL! ¡No podemos hacer nada! ¿Qué quieres?! ¿Quieres quitarnos algo más? ¡No queda nada! ¡Ella va a morir! ¡O peor!";
			link.l1 = "¿Quién va a morir? ¿Qué tesoro? No importa, es tu culpa - atacaste ese galeón, no al revés.";
			link.l1.go = "PZ_MatthewLutter3";
		break;
		
		case "PZ_MatthewLutter3":
			dialog.text = "¡No! ¡Fue al revés! ¡Maldito hidalgo! ¡Él es la razón por la que estamos en este lío! ¡Vino directo hacia nosotros y disparó a quemarropa! ¡Luego se la llevó de nosotros!";
			link.l1 = "¿De verdad? Eso no me sorprende. ¿Qué más puedes contarnos sobre él? Y... ¿qué se llevó? ¿Quién es 'ella'?";
			link.l1.go = "PZ_MatthewLutter5";
		break;
		
		case "PZ_MatthewLutter5":
			dialog.text = "¡Ah-ah-ah!!! ¡A-A-A-A!!!";
			link.l1 = "Veo que estoy perdiendo el tiempo...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_BelizPrisonSoldierDialog");
		break;
		
		case "PZ_BelizPrisonQuestSoldier1":
			dialog.text = "Capitán, con su permiso... ¡Lutter! ¡Fuera! Fin de la línea, amigo.";
			link.l1 = "";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_BelizPrisonLongway_UvodyatNaKazn");
		break;
		
		case "PZ_Longway_35":
			dialog.text = "Capitán, necesitamos averiguar más sobre Sotta y Lutter. Vamos a preguntar por ahí.";
			link.l1 = "Buena idea, Longway. De todos modos, no conseguimos mucho del hombre que gritaba.";
			link.l1.go = "PZ_Longway_36";
		break;
		
		case "PZ_Longway_36":
			dialog.text = "Pero es mejor empezar con Sotta.";
			link.l1 = "Correcto, él es a quien buscamos. Vamos.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_BelizPrisonLongwayBack");
		break;
		
		case "PZ_Longway_37":
			dialog.text = "¡No saben nada!";
			link.l1 = "Obviamente. Pero tenemos suficiente para empezar a pensar por nosotros mismos. Por lo que he oído, Sotta probablemente intentará vender esos bienes estratégicos con los que fue recompensado, y pronto.";
			link.l1.go = "PZ_Longway_38";
		break;
		
		case "PZ_Longway_38":
			dialog.text = "¡Exactamente!";
			link.l1 = "Deberíamos interceptarlo en su camino hacia Port Royal o Capsterville. La única pregunta es hacia dónde se dirige y dónde deberíamos enfrentarlo. O tal vez lo atrapemos en mar abierto.";
			link.l1.go = "PZ_Longway_39";
		break;
		
		case "PZ_Longway_39":
			dialog.text = "¡No! Longway quiso decir... Fermentelos es un capitán experimentado. Una pelea en mar abierto podría ir en cualquier dirección. Tendríamos mejores oportunidades emboscándolo en el puerto.";
			link.l1 = "Tienes razón, supongo. No importa lo que realmente haya pasado entre Matt y él, Sotta es peligroso y no se puede subestimar.";
			link.l1.go = "PZ_Longway_40";
		break;
		
		case "PZ_Longway_40":
			dialog.text = "¡Nosotros tampoco podemos esperar!";
			link.l1 = "Correcto de nuevo, Longway. Así que levantemos el ancla de inmediato, y luego planearemos nuestro próximo movimiento.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LongwayBelizDialogBack");
			DelMapQuestMarkCity("Beliz");
		break;
		
		case "PZ_Longway_41":
			dialog.text = "Mi Señor Capitán, ¡el Lucero del Alba está en el puerto!";
			link.l1 = "Sí, ya lo he notado.";
			link.l1.go = "PZ_Longway_42";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Longway_42":
			dialog.text = "¿Cuál es tu plan?";
			link.l1 = "Aún no lo he decidido. Intentar abordarlos bajo los cañones del fuerte sería un suicidio. Y aunque capturáramos su galeón pesado, no podríamos escapar en él. ¿Tienes alguna idea, Longway?";
			link.l1.go = "PZ_Longway_43";
		break;
		
		case "PZ_Longway_43":
			dialog.text = "Sí. Podríamos anclar en una cala segura y acercarnos al galeón en bote bajo el amparo de la noche.";
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Kapstervil"))
			{
				link.l1 = "¿Qué tal Bahía Media Luna, Longway?";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Yamaika"))
			{
				link.l1 = "Creo que Portland Cove sería una buena opción, lo suficientemente cerca y relativamente seguro. ¿Qué piensas?";
			}
			link.l1.go = "PZ_Longway_44";
		break;
		
		case "PZ_Longway_44":
			dialog.text = "Buena elección.";
			link.l1 = "Genial, eso está resuelto. ¿Nos perdimos algo?";
			link.l1.go = "PZ_Longway_45";
		break;
		
		case "PZ_Longway_45":
			dialog.text = "No lo creo, Mi Señor Capitán. Solo necesitamos estar bien preparados.";
			link.l1 = "Absolutamente.";
			link.l1.go = "PZ_Longway_46";
		break;
		
		case "PZ_Longway_46":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.CabinLock");
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			bQuestDisableMapEnter = false;
			AddQuestRecord("PZ", "21");
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Kapstervil"))
			{
				AddQuestUserData("PZ", "sText", "Half Moon Bay");
				Island_SetReloadEnableGlobal("Nevis", true);
				
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1 = "location";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1.location = "Shore43";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition = "PZ_GotovimShlupki_Buhta";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Yamaika"))
			{
				AddQuestUserData("PZ", "sText", "Portland Cove");
				Island_SetReloadEnableGlobal("Jamaica", true);
				
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1 = "location";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1.location = "Shore36";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition = "PZ_GotovimShlupki_Buhta";
			}
			PChar.quest.PZ_ZvezdaUhodimNaGlobalkru_Proval.win_condition.l1 = "MapEnter";
			PChar.quest.PZ_ZvezdaUhodimNaGlobalkru_Proval.win_condition = "PZ_ZvezdaUhodimNaGlobalkru_Proval";
			
			sld = CharacterFromID("Longway");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.Dialog.CurrentNode = "Longway_officer";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan":
			dialog.text = "¿Quién demonios eres, qué está pasando? ¡Señor Holmes!";
			link.l1 = "El señor Holmes ya no trabaja aquí. Y hemos sellado todas las escotillas firmemente. Así que no seremos molestados por un tiempo, Mynheer Fermentelos.";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_2";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_2":
			dialog.text = "¿Qué? ¿Fermentelos? ¡Mi nombre es Edgardo Sotta!";
			link.l1 = "Ajá, he oído eso antes. Sabemos que ese no es tu verdadero nombre, Oliveiro.";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_3";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_3":
			dialog.text = "¡Fermentelos está muerto!";
			link.l1 = "Pensándolo bien, sí que pareces demasiado joven. Obviamente, no podrías haber sido el capitán del Morning Star hace diez años. Entonces, ¿qué le pasó a Oliveiro?";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_4";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_4":
			dialog.text = "Nos deshicimos de él. Era solo otro problema que teníamos que resolver, igual que el que está de pie junto a ti.";
			link.l1 = "Bueno, ya que no eres Fermentelos, tal vez aún puedas responder a nuestras preguntas. Estamos buscando a alguien que se llevó de mi amigo.";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_5";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_5":
			dialog.text = "¡No voy a decirte nada! Nunca me perdonará por esto.";
			link.l1 = "Ahora mismo, será mejor que te preocupes por si te perdonamos...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_SottaFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PZ_AnabelleLutter1":
			dialog.text = "Finalmente está muerto...";
			link.l1 = "Eso mismo. ¿Y quién es usted, señora? ¿La retuvo contra su voluntad? Te compadezco; debes haber pasado por un terrible calvario...";
			link.l1.go = "PZ_AnabelleLutter2";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_AnabelleLutter2":
			dialog.text = "Soy Annabel Lutter. Y gracias a Dios, no tuve que soportar mucho, pero aprecio tu preocupación, señor...?";
			link.l1 = "Capitán Charles de Maure. Lutter, dices...";
			link.l1.go = "PZ_AnabelleLutter3";
		break;
		
		case "PZ_AnabelleLutter3":
			dialog.text = "Ah, ¿has oído hablar de Matt? Pobre tonto... Yo era su... consorte.";
			link.l1 = "Lo siento por su pérdida, señora Lutter. Ahora es viuda. ¿Cuál era su apellido de soltera, si no es un secreto?";
			link.l1.go = "PZ_AnabelleLutter4";
		break;
		
		case "PZ_AnabelleLutter4":
			dialog.text = "No tenía uno. Mírame más de cerca. Mi pobre madre era una esclava de piel oscura de los piratas. Nadie sabe quién fue mi padre, así que no se molestaron en darme un nombre apropiado.";
			link.l1 = "¿Por qué entonces nadie te tocó? No me malinterpretes - me alegra que no haya pasado. Pero aún así, es... inusual.";
			link.l1.go = "PZ_AnabelleLutter5";
		break;
		
		case "PZ_AnabelleLutter5":
			dialog.text = "Tienes razón. Pero llamemos a las cosas por su nombre. No soy una noble mimada; soy la hija de un esclavo. No me desmayaré por una conversación pesada.";
			link.l1 = "Ahem, yo tampoco soy de esos que miman. Pero continúa, por favor. ¿Por qué la tripulación no tocó a la hija de la esclava? Tú no conoces a tu padre, y él no parecía importarle.";
			link.l1.go = "PZ_AnabelleLutter6";
		break;
		
		case "PZ_AnabelleLutter6":
			dialog.text = "Supongo que no. Ya que sabes sobre Matt, ¿sabes que trabajó para Levasseur por un tiempo?";
			link.l1 = "Sí, lo escuché mientras buscaba la Estrella Matutina. Pero, ¿qué tiene que ver eso con esto? Cuéntamelo todo, por favor.";
			link.l1.go = "PZ_AnabelleLutter7";
		break;
		
		case "PZ_AnabelleLutter7":
			dialog.text = "¿Todavía no entiendes, verdad? Al parecer, no has oído hablar de las... preferencias de Levasseur?";
			link.l1 = "No lo he hecho, pero de nuevo, ¿qué tiene eso que ver con...?";
			link.l1.go = "PZ_AnabelleLutter8";
		break;
		
		case "PZ_AnabelleLutter8":
			dialog.text = " Oh, supongo que tendré que contártelo todo. Si eres demasiado impresionable, siéntate, señor. La cosa es que duerme con muchas mujeres, y...";
			if (pchar.questTemp.FMQT == "end")
			{
				link.l1 = "Su esposa no está lejos de él, y se acuesta con casi cualquiera.";
				link.l1.go = "PZ_AnabelleLutterKnow1";
			}
			else
			{
				link.l1 = "Oh no.";
				link.l1.go = "PZ_AnabelleLutterDontKnow1";
			}
		break;
		
		case "PZ_AnabelleLutterKnow1":
			dialog.text = " Bueno, ya sabes lo que dicen... tal para cual. Pero no, estoy seguro de que él fue mucho más allá.";
			link.l1 = "¿Y qué tan lejos?";
			link.l1.go = "PZ_AnabelleLutter9";
		break;
		
		case "PZ_AnabelleLutterDontKnow1":
			dialog.text = "Su sarcasmo está fuera de lugar aquí, señor. No tiene idea de lo que estamos hablando.";
			link.l1 = "Está bien, está bien, lo siento. Continúa, por favor.";
			link.l1.go = "PZ_AnabelleLutter9";
		break;
		
		case "PZ_AnabelleLutter9":
			dialog.text = "No es solo engañar a su cónyuge. Está tomando mujeres contra su voluntad. Y no es solo un abuso ocasional. Secuestra a chicas y las mantiene en una de las bodegas que posee.";
			link.l1 = "¿Así que él recibe chicas esclavas con regularidad? ¿Y tú ibas a ser una de ellas?";
			link.l1.go = "PZ_AnabelleLutter10";
		break;
		
		case "PZ_AnabelleLutter10":
			dialog.text = "Tienes razón sobre lo último. Pero, ay, no sobre lo primero. No necesita esclavos. Levasseur está loco, a su manera, no como mi Matt. François quiere poseer a una mujer completamente, cuerpo y alma. Y no se trataba de amor, por supuesto. Necesitaba mujeres libres para quebrantar su voluntad. Disfrutaba viendo cómo cambiaban con el tiempo su apariencia, comportamiento y manera de hablar...";
			link.l1 = "Asqueroso...";
			link.l1.go = "PZ_AnabelleLutter11";
		break;
		
		case "PZ_AnabelleLutter11":
			dialog.text = "Ya te estás sintiendo un poco enfermo. Ahora imagina cómo fue para esas mujeres. Escuché sobre todo esto, y no solo de Matt. Levasseur una vez tuvo a una noble portuguesa...";
			link.l1 = "Miraste hacia otro lado y guardaste silencio. Cuéntanos todo. He visto todo tipo de cosas en el Viejo Mundo y durante mi tiempo en el Archipiélago también. Nada me sorprende ahora.";
			link.l1.go = "PZ_AnabelleLutterWant1";
			link.l2 = "Detente, no quiero saber qué le pasó a ella. Espero que esas mujeres no hayan sufrido demasiado en sus manos.";
			link.l2.go = "PZ_AnabelleLutter12";
		break;
		
		case "PZ_AnabelleLutterWant1":
			dialog.text = "Pero nunca has oído nada como esto. Y espero que nunca lo veas. La llevaron a él aún orgullosa e intacta, aunque, como me contó Matt, los hombres de Levasseur la violaron todo el camino a Tortuga después de tomar la plantación de su esposo cerca de Campeche - él murió de una hemorragia después de que esos monstruos le dispararan en ambas rodillas...";
			link.l1 = "Una mujer fuerte... Pero dijiste que Levasseur generalmente no tocaba a las mujeres que quería para sí mismo.";
			link.l1.go = "PZ_AnabelleLutterWant2";
		break;
		
		case "PZ_AnabelleLutterWant2":
			dialog.text = "Las que él específicamente solicitó fueron dejadas en paz. Pero la señora Leontina fue un regalo. Uno inesperado y placentero para todos ellos. Así que se entregaron a sí mismos...";
			link.l1 = "Veo...";
			link.l1.go = "PZ_AnabelleLutterWant3";
		break;
		
		case "PZ_AnabelleLutterWant3":
			dialog.text = "Supongo... Matt se había convertido en uno de los favoritos de Francois. Fue invitado a una de las soirées secretas de Levasseur... Durante el festín, uno de los piratas se quejó de que no había suficientes mujeres. Levasseur se rió y luego...";
			link.l1 = "¿Y luego? ¿Qué pasó?";
			link.l1.go = "PZ_AnabelleLutterWant4";
		break;
		
		case "PZ_AnabelleLutterWant4":
			dialog.text = "...luego la sacaron. ¡Con una correa! Golpeada, con la espalda arañada, con los ojos vendados y amordazada. Cuando le quitaron la mordaza, todo lo que dijo fue...";
			link.l1 = "Algo horrible, me imagino. ¿Lo maldijo con todo lo que tenía?";
			link.l1.go = "PZ_AnabelleLutterWant5";
		break;
		
		case "PZ_AnabelleLutterWant5":
			dialog.text = "Si tan solo... Doña Leontina simplemente susurró: '¿Qué desea mi amo?'";
			link.l1 = "Creo que voy a vomitar. ¿Matt te contó lo que le pasó después?";
			link.l1.go = "PZ_AnabelleLutterWant6";
		break;
		
		case "PZ_AnabelleLutterWant6":
			dialog.text = "Asesinada, por supuesto. Pero no a manos de Levasseur. La desechó como a un perro callejero. Uno de sus capitanes le disparó. Antes de morir, pronunció solo una palabra...";
			link.l1 = "¿Una maldición? ¿Una plegaria?";
			link.l1.go = "PZ_AnabelleLutterWant7";
		break;
		
		case "PZ_AnabelleLutterWant7":
			dialog.text = "No. 'Gracias...'";
			link.l1 = "Agradecer a la muerte tras tal tormento... Lo que debe haber soportado... y otros como ella en la guarida de ese monstruo...";
			link.l1.go = "PZ_AnabelleLutter12";
		break;
		
		case "PZ_AnabelleLutter12":
			dialog.text = "Levasseur despreciaba particularmente a los esclavos y a las mujeres de piel oscura - decía que no había nada que romper en ellas. No duraban mucho con él, y tampoco los indígenas - salvo algunos especialmente tercos. Pero la salvajez y la rebelión tampoco eran la respuesta - mataba a aquellos que intentaban complacerlo demasiado pronto y a aquellos que permanecían desafiantes por demasiado tiempo.";
			link.l1 = "Eso es horrendo... Dime, ¿alguna vez Levasseur tuvo mujeres asiáticas?";
			link.l1.go = "PZ_AnabelleLutter13";
		break;
		
		case "PZ_AnabelleLutter13":
			dialog.text = "No, al menos no que yo haya oído. En cuanto a mí... ya te he dicho que no le gustaban las mujeres de piel oscura. Así que cuando Matt trabajaba para Francois, caminaba conmigo abiertamente por las calles de Tortuga. Incluso me llevó a la residencia una vez.";
			link.l1 = "Pero Levasseur quería hacerte uno de sus esclavos de todos modos...";
			link.l1.go = "PZ_AnabelleLutter14";
		break;
		
		case "PZ_AnabelleLutter14":
			dialog.text = "Exactamente... No sé por qué le gusté tanto... Cuando Matt se enteró, huyó de la isla tan pronto como se lo dijeron. Nunca regresó a Tortuga. Podría haber estado un poco loco, pero me amaba. Me llamaba su tesoro...";
			link.l1 = "¡Así que eso es lo que quiso decir cuando dijo que Sotta le quitó su tesoro!";
			link.l1.go = "PZ_AnabelleLutter15";
		break;
		
		case "PZ_AnabelleLutter15":
			dialog.text = "Je, ¿él dijo eso? Oh, Matt... Pero parece que nunca estuvimos destinados a envejecer juntos. Si Levasseur ponía sus ojos en una mujer, haría cualquier cosa para conseguirla, sin importar su origen o el costo. Sotta era uno de sus capitanes, e hizo lo que se le ordenó.";
			link.l1 = "Ya veo. ¿Y qué piensas hacer ahora, Annabel?";
			link.l1.go = "PZ_AnabelleLutter16";
		break;
		
		case "PZ_AnabelleLutter16":
			dialog.text = "Corre. A algún lugar donde los hombres de Levasseur no puedan alcanzarme. Cambiar mi nombre. Disfrazarme...";
			link.l1 = "Espero que tengas éxito. Te deseo todo lo mejor, Annabel.";
			link.l1.go = "PZ_AnabelleLutter17";
			if (sti(pchar.Money) >= 10000)
			{
				link.l2 = "Necesitarás dinero para arreglar el pasaje. Toma esto. Aquí hay diez mil pesos.";
				link.l2.go = "PZ_AnabelleLutter17_Peso";
			}
			if (PCharDublonsTotal() >= 100)
			{
				link.l3 = "Necesitarás más que un poco de dinero. No todos están dispuestos a ayudar a una chica de piel oscura, incluso a una mestiza. Aquí, toma cien doblones, encuentra un barco y escóndete.";
				link.l3.go = "PZ_AnabelleLutter17_Dublon";
			}
		break;
		
		case "PZ_AnabelleLutter17":
			dialog.text = "¡Tú también! Adiós, Capitán.";
			link.l1 = "Adiós.";
			link.l1.go = "Exit";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddDialogExitQuest("PZ_AnabelleGo");
		break;
		
		case "PZ_AnabelleLutter17_Peso":
			dialog.text = "Yo... yo no sé qué decir. Nadie salvo Matt me ha mostrado tal bondad.";
			link.l1 = "Tal vez sea una señal. Que después de todo envejecerás felizmente en algún lugar. Adiós.";
			link.l1.go = "Exit";
			AddMoneyToCharacter(pchar, -10000);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddDialogExitQuest("PZ_AnabelleGo");
		break;
		
		case "PZ_AnabelleLutter17_Dublon":
			dialog.text = "Tienes razón. Muchas gracias por esto. Te recordaré en mis oraciones por el resto de mi vida.";
			link.l1 = "Gracias. Buena suerte.";
			link.l1.go = "Exit";
			RemoveDublonsFromPCharTotal(100);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			AddDialogExitQuest("PZ_AnabelleGo");
		break;
		
		case "PZ_Longway_47":
			dialog.text = "Ese hombre... No, ya no es un hombre. Es una bestia. Un monstruo. Torturando a mujeres de esa manera...";
			link.l1 = "  Sé lo que estás pensando, Longway. Pero oíste: nunca ha tenido una mujer de piel amarilla.";
			link.l1.go = "PZ_Longway_48";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Longway_48":
			dialog.text = "¡Pero conocía a todo el grupo! Van der Vink, Fermentelos, Sotta... Lo acabamos de leer en su diario. ¿Y si esa 'ella' en particular es... ella?";
			link.l1 = "Quién sabe... Una mujer empeñada en vengarse de Fermentelos - es fácil ver por qué pensarías eso. Pero podría haber sido cualquier mujer cuya vida fue destrozada por Oliveiro. No tiene que ser tu hermana. Ni siquiera tiene que ser una mujer de piel amarilla.";
			link.l1.go = "PZ_Longway_49";
		break;
		
		case "PZ_Longway_49":
			dialog.text = "¿Está... negándose a intentarlo, Mi Señor Capitán? ¿En el último momento...?";
			link.l1 = "No, Longway. Pero, ¿cómo te lo imaginas? Es poco probable que Levasseur responda a alguna de nuestras preguntas. Y husmear en Tortuga de esta manera es demasiado peligroso.";
			link.l1.go = "PZ_Longway_50";
		break;
		
		case "PZ_Longway_50":
			dialog.text = "¿Entonces qué sugieres?";
			link.l1 = "Esperemos. Sabemos que a Levasseur no le gustan las mujeres como tu hermana. Así que podemos conservar nuestros recursos por ahora. Paciencia y fuerza. François es un hueso duro de roer, no solo por su 'tortuga'. Pero con la ayuda de Svenson, podemos hablar con él en nuestros términos. Te prometí que te ayudaría a encontrar a tu hermana y pienso cumplirlo. ¿Me crees, Longway?";
			link.l1.go = "PZ_Longway_51";
		break;
		
		case "PZ_Longway_51":
			dialog.text = "Mm... Sí, sí, Mi Señor Capitán. Pero Longway tiene una petición más para usted.";
			link.l1 = "¿Qué pasa? No estarás planeando irte por tu cuenta otra vez, ¿verdad? La última vez no terminó tan bien.";
			link.l1.go = "PZ_Longway_52";
		break;
		
		case "PZ_Longway_52":
			dialog.text = "En absoluto, Mi Señor Capitán. Ahora me doy cuenta de que, desafortunadamente, un hombre como yo no puede hacer nada por sí solo en un mundo gobernado por hombres blancos. Longway le pide que atraque en Capsterville y entregue una nota a Georges Gravel, pidiéndole que averigüe algo mientras se prepara.";
			link.l1 = "Una idea sensata, Longway. Lo haremos.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TeleportToShore");
		break;
		
		case "PZ_Longway_53":
			dialog.text = "Señor Capitán, hay algo que Longway necesita preguntar...";
			link.l1 = "¿Olvidaste escribir la carta? Puedes simplemente hablar con Gravel.";
			link.l1.go = "PZ_Longway_54";
		break;
		
		case "PZ_Longway_54":
			dialog.text = "No, la carta está lista. Pero Longway pensó que era mejor no deambular solo por la ciudad. Mi Señor Capitán... ¿podrías entregar la carta a Georges por mí? Por favor?";
			link.l1 = "¿Acaso parezco un mensajero para ti? ¿O eres tú el capitán aquí?";
			link.l1.go = "PZ_Longway_55";
		break;
		
		case "PZ_Longway_55":
			dialog.text = "Mi Señor Capitán...";
			link.l1 = "Ja ja ja, ¡solo estoy bromeando, Longway! Recuérdame dónde puedo encontrar a ese Grava tuyo.";
			link.l1.go = "PZ_Longway_56";
		break;
		
		case "PZ_Longway_56":
			dialog.text = "Trabaja en la iglesia.";
			link.l1 = "Está bien, me encargaré de ello.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_ToCapstervilleChurch");
			AddLandQuestMark(characterFromId("Charles_Priest"), "questmarkmain");
		break;
		
		// Этап 5
		case "PZ_Mary_Sharptown1":
			dialog.text = "Charles, mi querido Charles, ¿algo va mal? Pareces preocupado y... cansado, sí, ¿eh?";
			link.l1 = "Oh, no, no, Mary, estoy bien. Es solo... esta misión en Tortuga mía. Parece estar en un callejón sin salida... otra vez. Y ese testamento de Sharp definitivamente me ha cobrado factura, por el amor de Dios. Pero no importa.";
			link.l1.go = "PZ_Mary_Sharptown2";
		break;
		
		case "PZ_Mary_Sharptown2":
			dialog.text = "¿Qué? ¿Qué misión? ¿Y qué tiene que ver eso con Sharp? ¡No entiendo nada!";
			link.l1 = "Demasiadas preguntas, Mary. Este no es lugar para hablar de eso. ¿Lo discutimos en la sala de la taberna? Tal como te gusta, fuera de la vista y de la mente. Te pondré al día sobre lo que he estado haciendo el último año.";
			link.l1.go = "PZ_Mary_Sharptown3";
		break;
		
		case "PZ_Mary_Sharptown3":
			dialog.text = "¡De acuerdo! Pero ten cuidado: si estás ocultando algo...";
			link.l1 = "¡Absolutamente no! Vamos, tenemos tiempo de sobra para matar...";
			link.l1.go = "PZ_HelenaMary_Exit";
		break;
		
		case "PZ_Helena_Sharptown1":
			dialog.text = "Qué extraño, ¿verdad, Charles? Se supone que soy el dueño de esta misma isla, pero no siento que me pertenezca en absoluto.";
			link.l1 = "¿Tú crees?";
			link.l1.go = "PZ_Helena_Sharptown2";
		break;
		
		case "PZ_Helena_Sharptown2":
			dialog.text = "¡Oh, esa sonrisa tuya... Sabes cómo tratar a una chica. Pero, ¿qué te pasa? ¡Tu cara está toda mal!";
			link.l1 = "¿Por qué? Es mi cara habitual, muy guapo también.";
			link.l1.go = "PZ_Helena_Sharptown3";
		break;
		
		case "PZ_Helena_Sharptown3":
			dialog.text = "Charles, puedo oírlo en tu voz, has estado decaído últimamente.";
			link.l1 = "Tengo mucho en mi plato, especialmente con Longway. Estoy simplemente agotada. Pero es demasiado tarde para rendirme, especialmente desde que le hice una promesa a él y a mi padre.";
			link.l1.go = "PZ_Helena_Sharptown4";
		break;
		
		case "PZ_Helena_Sharptown4":
			dialog.text = "No entiendo... ¿Qué tiene que ver Longway con esto? ¿Y qué promesas hiciste?";
			link.l1 = "Si vamos a discutirlo, hagámoslo en la taberna, alquila una habitación. Lejos de otras personas.";
			link.l1.go = "PZ_Helena_Sharptown5";
		break;
		
		case "PZ_Helena_Sharptown5":
			dialog.text = "Está bien, vamos. No hay nada más que hacer de todos modos, así que al menos podemos pasar un rato juntos.";
			link.l1 = "¡Guía el camino, cariño!";
			link.l1.go = "PZ_HelenaMary_Exit";
		break;
		
		case "PZ_HelenaMary_Exit":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) Return_MaryOfficer();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) Return_HelenaOfficer();
			WaitDate("", 0, 0, 0, 2, 0);
			LAi_SetImmortal(npchar, true);
			ChangeCharacterAddressGroup(npchar, "Pirates_tavern_upstairs", "goto", "goto1");
			DoQuestReloadToLocation("Pirates_tavern_upstairs", "goto", "goto2", "PZ_Etap5_NaverhuTavernBandits");
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "¡Mira qué dulcemente duermen en los brazos del otro! ¡Encantador!";
				link.l1 = "¿Celoso?";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "¡Arriba y a brillar! ¿Cómo durmieron, tortolitos?";
				link.l1 = "Bien, gracias por preguntar. ¿Y cómo han dormido ustedes, muchachos?";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_2";
			locCameraFromToPos(2.34, 1.92, 1.66, true, -1.66, -0.69, -0.02);
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Esa es una pregunta tonta, ¿no crees?";
				link.l1 = "Lo es. Y es una estupidez de tu parte. ¿Quieres saber por qué?";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Dicen que tienes la lengua afilada, Charles de Maure.";
				link.l1 = "Y no solo mi lengua. ¿Quieres descubrirlo? Pero dime, ¿por qué no atacaste mientras dormíamos?";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_3";
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "¿Y por qué es eso?";
				link.l1 = "No deberías enfadar a Mary por la mañana. Pronto descubrirás por qué.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "¡Simple! Es oscuro, ¿sabes?, así que no podíamos decir quién de ustedes era la chica.";
				link.l1 = "Bastardo.";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_4";
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "A diferencia de ti, no le tengo miedo a las mujeres. Hablando de eso, muchachos, llévenla sana y salva, o el hugonote nos convertirá a nosotros en mujeres en su lugar.";
				link.l1 = "¿Qu... quién?";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Al menos parezco un hombre. Muchachos, tomen a la rubia viva - el hugonote la está esperando.";
				link.l1 = "¿Qu... quién?";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_5";
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_5":
			DialogExit();
			LAi_SetFightMode(pchar, true);
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("PZ_NaverhuTavernBandits_"+i);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				
				LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
				LAi_group_SetCheck("EnemyFight", "PZ_Etap5_NaverhuTavernBandits_Win");
			}
		break;
		
		case "PZ_MaryHelena_BitvaNaverhu_1":
			DelLandQuestMark(npchar);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "¿Quién era ese, Charles? ¿Quién demonios es ese hugonote? ¿Es realmente...?";
				link.l1 = "Solo hay uno, Mary. Y será mejor que...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Charles... ¿qué fue eso? ¿Un hugonote? ¿Es este el hombre que creo que es?";
				link.l1 = "Me temo que sí, Helen. Necesitamos...";
			}
			link.l1.go = "PZ_MaryHelena_BitvaNaverhu_2";
		break;
		
		case "PZ_MaryHelena_BitvaNaverhu_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "¿Oyes eso? Alguien se acerca, sí, ¿eh? Probablemente amigos de estos hombres muertos.";
				link.l1 = "Entonces los veremos unirse a ellos. Prepárate...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "¿Lo oyes? Pasos.";
				link.l1 = "De hecho, lo haré. Quédate detrás de mí.";
			}
			link.l1.go = "PZ_MaryHelena_BitvaNaverhu_3";
		break;
		
		case "PZ_MaryHelena_BitvaNaverhu_3":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) Return_MaryOfficer();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) Return_HelenaOfficer();
			sld = CharacterFromID("Longway");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Longway_61";
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			RemovePassenger(pchar, sld);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "PZ_Longway_61":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Mi Señor Capitán, señora "+sStr+".";
			link.l1 = "¿Longway?! ¿Crees que puedes entrar en nuestra habitación así como así? ¿Y si estuviéramos...?";
			link.l1.go = "PZ_Longway_62";
			
			//заранее создаём заглушку для корабля
			sld = GetCharacter(NPC_GenerateCharacter("PZ_ShipStasis", "citiz_46", "man", "man", sti(pchar.rank), PIRATE, -1, false, "quest"));
			SetSPECIAL(sld, 1, 1, 1, 1, 1, 1, 1);
		break;
		
		case "PZ_Longway_62":
			dialog.text = "Eh, perdone, Mi Señor Capitán. Pensé que habría cerrado la puerta si estuviera ocupado así. Pero Longway la encontró abierta.";
			link.l1 = "Roto, no abierto. Pero dime, amigo mío, ¿por qué estás tan malditamente tranquilo? Hay cadáveres en el suelo, estamos armados, y tú...";
			link.l1.go = "PZ_Longway_63";
		break;
		
		case "PZ_Longway_63":
			dialog.text = "Bueno, estoy acostumbrada a ello.";
			link.l1 = "¿Y no puedes discutir con eso, verdad? Pero en serio, ¿no escuchaste los sonidos de la pelea en tu camino aquí? ¿No viste a esos brutos entrar en la taberna y subir las escaleras justo frente a ti?";
			link.l1.go = "PZ_Longway_64";
		break;
		
		case "PZ_Longway_64":
			dialog.text = "No, Mi Señor Capitán. No vi a ningún extraño en el salón mientras subía aquí.";
			link.l1 = "Esa es una coincidencia ridícula. Entonces, ¿qué quieres, Longway?";
			link.l1.go = "PZ_Longway_65";
		break;
		
		case "PZ_Longway_65":
			dialog.text = "Necesito urgentemente un barco y una tripulación, Mi Señor Capitán.";
			link.l1 = "¿Qué? ¿Por qué? ¿Finalmente has encontrado el rastro de Chang Xing? En ese caso, vayamos por ella ahora mismo, juntos.";
			link.l1.go = "PZ_Longway_66";
		break;
		
		case "PZ_Longway_66":
			dialog.text = "No Chang Xing, ay. Es... Joep van der Vink. Georges Gravel envió un mensaje y lo recibí mientras paseaba por el pueblo, mientras tú... descansabas con la dama.";
			link.l1 = "¡Aye, he tenido un gran descanso, te lo puedo asegurar! Pero, ¿por qué deberíamos separarnos ahora, Longway? Tenemos una lista maldita de tareas importantes que completar y gente peligrosa que matar.";
			link.l1.go = "PZ_Longway_67";
		break;
		
		case "PZ_Longway_67":
			dialog.text = "Van der Vink no es tan peligroso como Levasseur. Además, ya lo derroté una vez. Y lo derrotaré de nuevo. Esta vez, para asegurarme de que esté muerto de verdad. No quiero que todos nosotros desperdiciemos tiempo valioso en él. Deberías ir a Tortuga y preguntar a las personas importantes sobre lo que necesitamos. Capturaré a van der Vink yo mismo. Mi Señor Capitán, esto no vale la pena para que desperdicies tu tiempo y yo también fui un Capitán una vez. Me las arreglaré.";
			link.l1 = "Hmm, tienes razón, Longway. Van der Vink puede que no sea tan peligroso, pero el 'Banten' es uno de los barcos más rápidos del Archipiélago. No cualquier barco servirá para atraparlo. ¿Y qué hay de la tripulación? ¿Cómo planeas reunir hombres tan rápido y por tu cuenta?";
			link.l1.go = "PZ_Longway_68";
		break;
		
		case "PZ_Longway_68":
			dialog.text = "Conozco el lugar adecuado y tengo el respaldo de la Compañía allí. O al menos puedo fingir eso, como hice con Georges. La Compañía... Mynheer Rodenburg utilizó sus servicios cuando necesitó urgentemente hombres de combate, tripulaciones profesionales, que no hacen preguntas.";
			link.l1 = "Una tripulación de barco para contratar, entonces... Tiene sentido que exista algo así. ¿Y cuánto costará?";
			link.l1.go = "PZ_Longway_69";
		break;
		
		case "PZ_Longway_69":
			dialog.text = "Dos mil quinientos. Ahora mismo y al instante.";
			link.l1 = "¿Eso es todo? Se necesita más que eso para contratar a toda una tripulación de marineros regulares en una taberna, especialmente para un gran barco. Aparentemente, Rodenburg y sus agentes tienen precios especiales en lugares especiales.";
			link.l1.go = "PZ_Longway_70";
		break;
		
		case "PZ_Longway_70":
			dialog.text = "Me refería a los doblones, Mi Señor Capitán.";
			link.l1 = "¿¡QUÉ!? ";
			link.l1.go = "PZ_Longway_70_4";
		break;
		
		case "PZ_Longway_70_4":
			dialog.text = "Me ha escuchado bien, Mi Señor Capitán. Es importante. No pediría tal cantidad por una nimiedad.";
			link.l1 = "Sí, te escuché, pero aún no puedo creerlo. Precios especiales, de verdad. ¿Aceptan pesos?";
			link.l1.go = "PZ_Longway_70_5";
		break;
		
		case "PZ_Longway_70_5":
			dialog.text = "Sí... de los blancos. Longway puede tener problemas con eso, pero... creo que podré convencerlos si insisto lo suficiente. Siempre hay una manera.";
			link.l1 = "Bueno, eso es algo. Y eso es solo para la tripulación... Y también tienes un barco al que llegar. ¿Probablemente también en algún 'lugar especial'? Me temo preguntar cuánto nos costará...";
			link.l1.go = "PZ_Longway_70_6";
		break;
		
		case "PZ_Longway_70_6":
			dialog.text = "No exactamente, Mi Señor Capitán. La tripulación viene con su propio barco.";
			link.l1 = "¿Pero?";
			link.l1.go = "PZ_Longway_70_7";
		break;
		
		case "PZ_Longway_70_7":
			dialog.text = "La 'Meifeng'. Puede convertirse en un factor decisivo - ningún barco en el Archipiélago es más rápido que ella. Y ella es... era mía, así que la conozco. ¿Me la prestarás, Mi Señor Capitán?";
			if (PCharDublonsTotal() >= 2500)
			{
				link.l1 = "Aquí. Dos mil quinientos doblones. Siempre y cuando me traigas la cabeza de van der Vink en una bandeja de oro macizo, ¡ja ja ja ja!";
				link.l1.go = "PZ_Longway_Dublons_1";
			}
			if (sti(pchar.Money) >= 300000)
			{
				link.l2 = "No llevo tantos doblones, Longway. Y dudo que tenga tantos en el barco, estás hablando de una pila de oro. Pero pesos, seguro. Trescientos mil es justo lo que necesitas.";
				link.l2.go = "PZ_Longway_Peso_1";
			}
			link.l3 = "¿Sabes qué, Longway...? ¿De verdad estás sugiriendo que pague lo suficiente como para armar una flota de asedio solo para que puedas luchar contra un matón común?!";
			link.l3.go = "PZ_Longway_Otkaz";
		break;
				
		case "PZ_Longway_Dublons_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) AddQuestUserData("PZ", "sText", "Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) AddQuestUserData("PZ", "sText", "Helen");
			
			dialog.text = "¡Oh... Longway le agradece de todo corazón, Mi Señor Capitán! Pero aún así, ¿qué hay de la 'Meifeng'?";
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				link.l1 = "¿Qué hay de ella? Amigo mío, ¿te golpeaste la cabeza en el camino aquí? ¡Ella está en nuestra flota ahora mismo!";
				link.l1.go = "PZ_Longway_Mayfang1";
			}
			else
			{
				link.l1 = "Necesito pensarlo, Longway. ¿Cuánto tiempo tenemos para atrapar a van der Vink?";
				link.l1.go = "PZ_Longway_NoMayfang1";
			}
			RemoveDublonsFromPCharTotal(2500);
			pchar.questTemp.PZ_FlagShipDublons = true;
			notification("Longway approves", "Longway");
		break;
		
		case "PZ_Longway_Peso_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) AddQuestUserData("PZ", "sText", "Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) AddQuestUserData("PZ", "sText", "Helen");
			
			dialog.text = "Mi Señor Capitán, cometiste un pequeño error. Serían doscientos cincuenta mil pesos.";
			link.l1 = "No lo hice; es el tipo de interés especial de Charles de Maure cuando sus amigos necesitan ayuda, ja, ja. Te doy de más para que tengas para todo.";
			link.l1.go = "PZ_Longway_Peso_2";
			AddMoneyToCharacter(pchar, -300000);
		break;
		
		case "PZ_Longway_Peso_2":
			dialog.text = "Muchas gracias, mi Señor Capitán... Pero, ¿qué pasa con el 'Meifeng'?";
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				link.l1 = "¿Qué pasa con ella? Amigo mío, ¿te golpeaste la cabeza de camino aquí? ¡Ella está en nuestra flota ahora mismo!";
				link.l1.go = "PZ_Longway_Mayfang1";
			}
			else
			{
				link.l1 = "Tengo que pensarlo, Longway. ¿Cuánto tiempo tenemos para atrapar a van der Vink?";
				link.l1.go = "PZ_Longway_NoMayfang1";
			}
		break;
		
		case "PZ_Longway_Otkaz":
			dialog.text = "No hay otro camino, Mi Señor Capitán, por favor cálmese...";
			link.l1 = "Oh, aún no he empezado. Aquí está el trato. Cincuenta mil pesos. Eso es justo lo suficiente para comprar una balandra en el astillero, prepararla para la batalla e incluso contratar una tripulación.";
			link.l1.go = "PZ_Longway_Otkaz_2";
			AddMoneyToCharacter(pchar, -50000);
			
			pchar.questTemp.PZ.LongwayBrig = true; // Лонгвэй будет на бриге
			notification("Longway disapproves", "Longway");
		break;
		
		case "PZ_Longway_Otkaz_2":
			dialog.text = "Pero, Mi Señor Capitán. ¡Puede ser suficiente para un capitán blanco! ¡No todos estarán de acuerdo en tratar con Longway. Harán un trato difícil antes de venderme algo!";
			link.l1 = "¡Así que, sé persuasivo! Eres bastante hábil en el regateo, a juzgar por tu propuesta inicial... ¿Todavía estás aquí? Toma este dinero y vete, ya que es tan urgente como dices.";
			link.l1.go = "PZ_Longway_Otkaz_3";
		break;
		
		case "PZ_Longway_Otkaz_3":
			dialog.text = "Sí, sí, Mi Señor Capitán...";
			link.l1 = "Y no me mires así. Nos veremos más tarde en Tortuga. Buena suerte.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			AddQuestRecord("PZ", "58");
		break;
		
		case "PZ_Longway_Mayfang1":
			dialog.text = "Eh, no, Mi Señor Capitán. Por supuesto, lo recuerdo. Longway solo estaba preguntando si estás listo para compartirla conmigo.";
			link.l1 = "Lo soy. Después de todo, van der Vink está tan involucrado en las desgracias de tu hermana como las otras personas de nuestra lista. Así que atraparlo es realmente importante. Te doy el mando del Meifeng.";
			link.l1.go = "PZ_Longway_Mayfang2";
		break;
		
		case "PZ_Longway_Mayfang2":
			// если "Мейфенг" у ГГ
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							//pchar.questTemp.PZ.Mayfang.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Mayfang.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayMayfang = true;
			pchar.questTemp.PZ_FlagShip = true;
			
			dialog.text = "No puedo creerlo... ¡Gracias, Mi Señor Capitán!";
			link.l1 = "Ah, no es nada. Solía ser tu barco, siempre lo recordaré. Bueno, adelante. Mata al hijo de puta. Me voy a Tortuga.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			AddQuestRecord("PZ", "59");
			notification("Longway approves", "Longway");
		break;
		
		
		case "PZ_Longway_NoMayfang1":
			dialog.text = "“El tiempo es corto, Mi Señor Capitán. No deberíamos desperdiciarlo - Chang Xing podría necesitar nuestra ayuda...”";
			link.l1 = "Lo sé, Longway. Aun así, ¿cuánto tiempo tenemos exactamente para atrapar a van der Vink?";
			link.l1.go = "PZ_Longway_NoMayfang2";
		break;
		
		case "PZ_Longway_NoMayfang2":
			dialog.text = "Un par de meses - sigue su ruta regular durante ese tiempo antes de desaparecer por un tiempo. Así es su manera, como me informó Gravel en su carta.";
			link.l1 = "Está bien. Vamos al barco, entonces...";
			link.l1.go = "PZ_Longway_NoMayfang3";
		break;
		
		case "PZ_Longway_NoMayfang3":
			dialog.text = "Me temo que mis preparativos deben comenzar de inmediato, Mi Señor Capitán. Así podremos empezar de inmediato cuando tenga el Meifeng. Necesito negociar con los hombres de antemano.";
			link.l1 = "¿Dónde nos encontramos?";
			link.l1.go = "PZ_Longway_NoMayfang4";
		break;
		
		case "PZ_Longway_NoMayfang4":
			AddQuestRecord("PZ", "60");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) AddQuestUserData("PZ", "sText", "Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) AddQuestUserData("PZ", "sText", "Helen");
			
			i = FindColony("Pirates");
			if (colonies[i].nation != ENGLAND)
			{
				dialog.text = "Justo aquí. Pero podemos encontrarnos en el astillero para tu conveniencia.";
				link.l1 = "¿Y por qué soy la única que no sabía que aquí puedes contratar a toda una tripulación de hombres de pelea por el precio adecuado?";
				link.l1.go = "PZ_Longway_NoMayfangIslaTesoro1";
			}
			else
			{
				dialog.text = "Aquellos mercenarios solían tener un lugar en Isla Tesoro, pero se vieron obligados a mudarse aquí.";
				link.l1 = "Ya veo por qué. Entonces, ¿dónde te busco en La Vega?";
				link.l1.go = "PZ_Longway_NoMayfangLaVega1";
			}
		break;
		
		case "PZ_Longway_NoMayfangIslaTesoro1":
			dialog.text = "Porque muy pocos lo conocen. Y aún menos pueden permitírselo. Mynheer Rodenburg fue su único cliente durante mucho tiempo.";
			link.l1 = "Entiendo. Está bien, Longway. Nos vemos allí.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LongwayToPiratesShipyard");
		break;
		
		case "PZ_Longway_NoMayfangLaVega1":
			dialog.text = "La taberna, Mi Señor Capitán. ¿Dónde más estaría?";
			link.l1 = "Así es. ¡Hasta luego entonces, Longway! Cuídate.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LongwayToLaVegaTavern");
		break;
		
		case "PZ_Longway_WaitForShip1":
			dialog.text = "Mi Señor Capitán, debo informarle que la tripulación está lista. Hay un último asunto que tratar. ¿Qué pasa con el 'Meifeng'?";
			link.l1 = "Por ahora, no he encontrado un barco que sea digno de ti, Longway.";
			link.l1.go = "PZ_Longway_WaitForShip2";
			if ((FindCompanionShips(SHIP_SCHOONER_W)) || (FindCompanionShips(SHIP_BRIG)) || (FindCompanionShips(SHIP_CORVETTE)) || (FindCompanionShips(SHIP_POLACRE)) || (FindCompanionShips(SHIP_XebekVML)) || (FindCompanionShips(SHIP_BRIGANTINE)))
			{
				if (FindCompanionShips(SHIP_SCHOONER_W)) sStr = "War schooner";
				if (FindCompanionShips(SHIP_BRIG)) sStr = "Brig";
				if (FindCompanionShips(SHIP_CORVETTE)) sStr = "Corvette";
				if (FindCompanionShips(SHIP_POLACRE)) sStr = "Polacre";
				if (FindCompanionShips(SHIP_XebekVML)) sStr = "Xebek";
				if (FindCompanionShips(SHIP_BRIGANTINE)) sStr = "Brigantine";
				link.l2 = "'"+sStr+"es tuyo.";
				link.l2.go = "PZ_Longway_NoQuestShip1";
			}
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				link.l3 = "¿Qué pasa con el 'Meifeng'? ¿Crees que la dejé desperdiciarse?";
				link.l3.go = "PZ_Longway_Mayfang3";
			}
			if (FindCompanionShips(SHIP_CURSED_FDM))
			{
				link.l4 = "Tengo un... barco especial para ti, Longway. Uno rápido. E incluso más letal que Meifeng. Es un galeón de guerra, el 'Corazón Volador'.";
				link.l4.go = "PZ_Longway_Caleuche1";
			}
			if (FindCompanionShips(SHIP_POLACRE_QUEST))
			{
				link.l5 = "Te gustan los jabeques, Longway. ¿Qué opinas de las polacras? Especialmente de esta, la 'Torero'. No está hecha para regatas, por supuesto, pero es bastante poderosa.";
				link.l5.go = "PZ_Longway_Torero1";
			}
			if (FindCompanionShips(SHIP_ELCASADOR))
			{
				link.l6 = "Debo confesar que no pensé que un día habría un uso digno para esto. ¿Qué opinas de este galeón? ¡El poderoso 'El Casador'!";
				link.l6.go = "PZ_Longway_ElCasador1";
			}
		break;
		
		case "PZ_Longway_NoQuestShip1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			
			// а теперь хором, дети: ненавижу костыли, ненавижу костыли, ненавижу костыли, нена... помогите!!!
			if ((FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_SCHOONER_W)
						{
							//pchar.questTemp.PZ.SchoonerW.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.SchoonerW.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwaySchoonerW = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_BRIG)
						{
							//pchar.questTemp.PZ.Brig.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Brig.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayBrig = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_CORVETTE)
						{
							//pchar.questTemp.PZ.Corvette.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Corvette.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayCorvette = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_POLACRE)
						{
							//pchar.questTemp.PZ.Polacre.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.Polacre.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayPolacre = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_XebekVML)
						{
							//pchar.questTemp.PZ.Xebek.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Xebek.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayXebek = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_BRIGANTINE)
						{
							//pchar.questTemp.PZ.Brigantine.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Brigantine.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayBrigantine = true;
			}
			
			dialog.text = "¡No es el 'Meifeng', Mi Señor Capitán! ¿Qué ha pasado con el Meifeng?";
			link.l1 = "¡Longway! "+sStr+"¡ está en peligro! ¡Y tu hermana también! ¿Y estás de mal humor por no tener un barco como este? ¡Cualquiera estaría feliz con un barco así! Ponla bajo tu mando y muestra a van der Vink de lo que eres capaz.";
			link.l1.go = "PZ_Longway_NoQuestShip2";
		break;
		
		case "PZ_Longway_NoQuestShip2":
			dialog.text = "Bien... Espero que el Cielo me envíe buena fortuna. Así como espero lo mismo para ti en Tortuga. Adiós, Mi Señor Capitán.";
			link.l1 = "Estoy seguro de ello. Adiós, Longway.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			pchar.questTemp.PZ_NoQuestShip = true;
		break;
		
		case "PZ_Longway_Mayfang3":
			// если "Мейфенг" у ГГ
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							//pchar.questTemp.PZ.Mayfang.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Mayfang.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayMayfang = true;
			pchar.questTemp.PZ_FlagShip = true;
			
			dialog.text = "Eh, no, Mi Señor Capitán. Por supuesto, recuerdo. Longway solo estaba preguntando si estás listo para compartirla conmigo.";
			link.l1 = "Lo soy. Después de todo, Van der Vink está tan involucrado en las desgracias de tu hermana como las otras personas de nuestra lista. Así que atraparlo es realmente importante. Te doy el mando del 'Meifeng'.";
			link.l1.go = "PZ_Longway_Mayfang4";
		break;
		
		case "PZ_Longway_Mayfang4":
			dialog.text = "No puedo creerlo... ¡Gracias, Mi Señor Capitán!";
			link.l1 = "Ah, no es nada. Solía ser tu barco, siempre lo recordaré. Bueno, sigue adelante. Mata al hijo de puta. Me voy a Tortuga.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			notification("Longway approves", "Longway");
		break;
		
		case "PZ_Longway_Caleuche1":
			dialog.text = "Yo... yo no puedo comandar ESTO, Mi Señor Capitán. Longway todavía se preocupa por su vida, alma y cordura.";
			link.l1 = "Ja ja ja, ¡Longway! Vamos, no sabía que eras tan supersticioso. Pero de todas formas, la maldición ha sido levantada, así que no tienes nada que temer.";
			link.l1.go = "PZ_Longway_Caleuche2";
		break;
		
		case "PZ_Longway_Caleuche2":
			dialog.text = "Ah... pero ¿lo sabe van der Vink? Correrá como un conejo asustado en cuanto vea ese barco.";
			link.l1 = "Tienes razón en eso. Bien, encontraremos algo más para ti.";
			link.l1.go = "PZ_Longway_WaitForShip2";
		break;
		
		case "PZ_Longway_Torero1":
			// если "Тореро" у ГГ
			if (FindCompanionShips(SHIP_POLACRE_QUEST))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_POLACRE_QUEST)
						{
							//pchar.questTemp.PZ.Torero.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Torero.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayTorero = true;
			if (CheckAttribute(pchar, "questTemp.PZ_FlagShipDublons"))
			{
				pchar.questTemp.PZ_FlagShip = true;
				notification("Longway approves", "Longway");
			}
			
			dialog.text = "Jamás navegué una polacra cuando capitaneaba yo mismo. Es interesante, pero la velocidad es lo más importante ahora, no el poder.";
			link.l1 = "Eso es cierto, pero al fin y al cabo es una polacra. Puede que no sea tan rápida como el 'Banten', pero puedes atrapar el viento en ángulos que ellos no pueden. Incluso más de lo que la 'Meifeng' misma jamás pudo. Así que aprovecha eso.";
			link.l1.go = "PZ_Longway_Torero2";
		break;
		
		case "PZ_Longway_Torero2":
			dialog.text = "Aún así... el 'Meifeng' era mejor... Lástima que la dejaste perderse, Mi Señor Capitán. Buena suerte en Tortuga.";
			link.l1 = "Lo mismo para ti, Longway. Gracias.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
		break;
		
		case "PZ_Longway_ElCasador1":
			// если "Эль Касадор" у ГГ
			if (FindCompanionShips(SHIP_ELCASADOR))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_ELCASADOR)
						{
							//pchar.questTemp.PZ.ElCasador.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.ElCasador.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayElCasador = true;
			if (CheckAttribute(pchar, "questTemp.PZ_FlagShipDublons"))
			{
				pchar.questTemp.PZ_FlagShip = true;
				notification("Longway approves", "Longway");
			}
			
			dialog.text = "Que pueda ser el galeón más inusual del Archipiélago, Mi Señor Capitán. Puedo manejarlo, pero es más lento que el 'Banten'...";
			link.l1 = "Bueno, no estarás compitiendo con Joep en una regata, ¿verdad?";
			link.l1.go = "PZ_Longway_ElCasador2";
		break;
		
		case "PZ_Longway_ElCasador2":
			dialog.text = "Lo que digas. Pero el 'Meifeng' era mejor... Lástima que la dejaste desperdiciarse, Mi Señor Capitán. Buena suerte en Tortuga.";
			link.l1 = "Lo mismo para ti, Longway. Gracias.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
		break;
		
		case "PZ_Longway_WaitForShip2":
			NextDiag.TempNode = "PZ_Longway_WaitForShip1";
			
			dialog.text = "Aprecio su preocupación, Mi Señor Capitán, pero por favor apresúrese - no tenemos mucho tiempo.";
			link.l1 = "Lo sé. Pero no quieres ir tras una quimera, ¿verdad? Está bien, te encontraré un barco adecuado.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaTortugaCabin_1":
			dialog.text = "Estamos casi allí, Charles. ¿Has decidido por dónde empezar? Quizás tenga sentido que preguntemos a la gente en las calles...";
			link.l1 = "Tal vez sí. Pero no para nosotros, para mí. Tú te quedarás a bordo, Helen.";
			link.l1.go = "PZ_HelenaTortugaCabin_2";
		break;
		
		case "PZ_HelenaTortugaCabin_2":
			dialog.text = "Charles, por supuesto, todavía estoy inquieta por esos canallas y lo que han dicho, y tiene sentido que me quede bajo la protección de la tripulación... Pero que te dirijas solo a la guarida de la bestia no me hace sentir más segura.";
			link.l1 = "Entiendo. Pero si las cosas salen mal, es mucho más fácil huir solo, sabiendo que estás a salvo. Es una orden, Helen. Espérame aquí y trata de no preocuparte demasiado.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaCabin_Exit");
		break;
		
		case "PZ_MaryTortugaCabin_1":
			dialog.text = "Aquí está Tortuga, Charles, sí, ¿eh? No puedo esperar para ir llamando a algunas puertas, preguntando qué quería ese burro gordo de mí...";
			link.l1 = "Por eso mismo te quedas a bordo, querida mía.";
			link.l1.go = "PZ_MaryTortugaCabin_2";
			
			pchar.questTemp.MarySexBlock = true;
			pchar.quest.Mary_giveme_sex.over = "yes";
			pchar.quest.Mary_giveme_sex1.over = "yes";
		break;
		
		case "PZ_MaryTortugaCabin_2":
			dialog.text = "¡De ninguna manera! ¿Crees que voy a dejar que vayas a tierra solo?";
			link.l1 = "Creo que si Levasseur decide terminar lo que sus mercenarios no pudieron hacer, no tendremos oportunidad de defendernos. No quiero provocarlo innecesariamente, especialmente porque mi objetivo no es él, sino Joep van der Vink.";
			link.l1.go = "PZ_MaryTortugaCabin_3";
		break;
		
		case "PZ_MaryTortugaCabin_3":
			dialog.text = "Así que ahora estoy encerrado, sí, ¿eh?";
			link.l1 = "No te lo estoy ordenando, te lo estoy pidiendo, Mary.";
			link.l1.go = "PZ_MaryTortugaCabin_4";
		break;
		
		case "PZ_MaryTortugaCabin_4":
			dialog.text = "¿Y si te pasa algo en algún callejón de esa maldita isla?";
			link.l1 = "Entonces prometo que no jugaré al héroe. Y saber que estás a salvo me ayudará a correr más rápido. Así que espérame en el barco, y por el amor de Dios, no bajes a tierra, pase lo que pase.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaCabin_Exit");
		break;
		
		case "PZ_RobertMartin1":
			chrDisableReloadToLocation = true;
			
			dialog.text = "¿Quién eres tú? Dudo que hayas cruzado la playa solo para charlar.";
			link.l1 = "Así es. Charles de Maure. ¿Rober Martene?";
			link.l1.go = "PZ_RobertMartin2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_RobertMartin2":
			dialog.text = "¿El Charles de Maure? ¡Mierda, solo no me involucres en nada turbio. Sí, soy yo. Entonces, ¿qué quieres?";
			link.l1 = "Me dijeron que eres amigo de Joep van der Vink, y...";
			link.l1.go = "PZ_RobertMartin3";
		break;
		
		case "PZ_RobertMartin3":
			dialog.text = "¿Quién te dijo eso? Les sacaré las tripas. Bueno, nos conocemos, eso es todo. No quiero problemas porque te cruzaste con él.";
			link.l1 = "Je, rápido te rindes con tus amigos...";
			link.l1.go = "PZ_RobertMartin4";
		break;
		
		case "PZ_RobertMartin4":
			dialog.text = "No pienses eso. No te tengo miedo. Pero ¿por qué molestarse o incluso crearlo? No conozco a Joep tan íntimamente como te han dicho. ¿Lo estás buscando?";
			link.l1 = "Sí, algo así. Sé que ya dejó Tortuga, pero no estaría de más saber más sobre él - dónde ha estado, con quién ha hablado. ¿Puedes ayudar?";
			link.l1.go = "PZ_RobertMartin5";
		break;
		
		case "PZ_RobertMartin5":
			dialog.text = "No te serviría de todos modos, así que... ¿por qué no? Estaba en un burdel. El burdel. Creo que puedes permitírtelo, así que te lo digo.";
			link.l1 = "¿Un burdel nuevo? ¿Ya no te basta con uno?";
			link.l1.go = "PZ_RobertMartin6";
		break;
		
		case "PZ_RobertMartin6":
			dialog.text = "Bueno, no es nuevo, pero no mucha gente lo sabe. Y solo unos pocos pueden permitírselo. Supongo que ha llegado tu momento. Pero ten cuidado: solo se aceptan doblones. Si ofreces plata, te darán una patada en el trasero.";
			link.l1 = "Me lo imaginaba. ¿Y dónde dijiste que está este burdel?";
			link.l1.go = "PZ_RobertMartin7";
		break;
		
		case "PZ_RobertMartin7":
			dialog.text = "¿Ves ese edificio con las columnas? Ese es. ¡Y qué anfitriona tienen! De piel amarilla, ¡tan atractiva! Eh, ya veo que estás babeando, ¿eh?";
			link.l1 = "Heh-heh, en cierto modo. Gracias, Rober. No tendrás problemas hoy - has sido de gran ayuda para mí.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LighthouseMartinGo");
		break;
		
		case "PZ_MaryTortugaCabin_11":
			dialog.text = "¡Por fin has vuelto, Charles! No encontraba mi lugar, sí, ¿eh?";
			link.l1 = "No tardaré mucho, Mary. Tengo un pequeño asunto que atender... No te mantendré en suspense - es asunto de Longway. Necesito visitar un burdel local.";
			link.l1.go = "PZ_MaryTortugaCabin_12";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_MaryTortugaCabin_12":
			dialog.text = "Sabía que no debía dejarte ir a tierra solo. O te olvidaste de ponerte el sombrero y se te calentó la cabeza... ¡O te la golpeaste, sí, ¿eh?";
			link.l1 = "Mary, escúchame. Es posible que la dueña de este establecimiento sea la hermana de Longway. Para estar seguro, tendría que verla, pero eso es todo lo que haré. No puedo hacerlo sin entrar. Pero no quiero que pienses algo que no deberías.";
			link.l1.go = "PZ_MaryTortugaCabin_13";
		break;
		
		case "PZ_MaryTortugaCabin_13":
			dialog.text = "¿Estás seguro de que no me estás mintiendo, Charles?";
			link.l1 = "Mary, míralo de esta manera... ¿Has oído alguna vez de un hombre advirtiendo a su amada sobre...?";
			link.l1.go = "PZ_MaryTortugaCabin_14";
		break;
		
		case "PZ_MaryTortugaCabin_14":
			dialog.text = "Detente ahí mismo, Charles, ni siquiera quiero pensarlo. Creo en ti y confío. Y espero que no te quedes allí más tiempo del necesario.";
			link.l1 = "No un minuto más, cariño, te lo prometo. Entrar y salir, ya verás.";
			link.l1.go = "PZ_PredupredilNashuDevushku";
		break;
		
		case "PZ_HelenaTortugaCabin_11":
			dialog.text = "¡Charles! Has regresado incluso más rápido de lo que esperaba. Pero, ¿qué ha pasado? No tienes buen aspecto... ¿Descubriste algo sobre Joep van der Vink?";
			link.l1 = "Aún no. He aprendido algunas cosas, pero para ir más allá... necesito ir a un... burdel. No por lo que podrías pensar, claro.";
			link.l1.go = "PZ_HelenaTortugaCabin_12";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_HelenaTortugaCabin_12":
			dialog.text = "¿Un burdel? No sabía que estos lugares ofrecieran algo más que lo obvio. Ш: Necesito hablar con el dueño, eso es todo. Y no es cualquier burdel. Se rumorea que es un establecimiento muy caro, solo para miembros de la alta sociedad...";
			link.l1 = "Prometo que voy estrictamente por asuntos de Longway. Es muy posible que la dueña de ese lugar sea su hermana. No estaré allí mucho tiempo.";
			link.l1.go = "PZ_HelenaTortugaCabin_13";
		break;
				
		case "PZ_HelenaTortugaCabin_13":
			dialog.text = "Bueno, entonces es justo para ti, cariño. Oh, estoy bromeando. Aun así, no estoy encantada de que vayas allí. Pero... Como desees. No estás obligado a informarme sobre tales cosas. Nunca te prometí que no dormiría con otro hombre. Y sin embargo, no lo hago. Porque es algo que doy por hecho.";
			link.l1 = "Bajo otras circunstancias, te habría llevado conmigo, pero...";
			link.l1.go = "PZ_HelenaTortugaCabin_14";
		break;
		
		case "PZ_HelenaTortugaCabin_14":
			dialog.text = "Gracias, pero no gracias. Charles, no te preocupes. No soy una tonta chica celosa. Bueno, tal vez celosa, pero no tonta. Y te creo. ¡Tonta yo!";
			link.l1 = "Gracias, Helen. Regresaré enseguida.";
			link.l1.go = "PZ_PredupredilNashuDevushku";
		break;
		
		case "PZ_PredupredilNashuDevushku":
			DialogExit();
			LAi_SetActorType(npchar);
			pchar.questTemp.PZ_PredupredilNashuDevushku = true;
		break;
		
		case "PZ_ElitaShluha_1":
			dialog.text = "¿Oh, una cara nueva en nuestro establecimiento? Bienvenido, monsieur. Comida, vino añejo, un baño caliente - todo te espera si puedes permitirte pasar tiempo con uno de nosotros.";
			link.l1 = "Gracias por tu bienvenida, mademoiselle. Pero no estoy aquí por eso. Estoy buscando a alguien...";
			link.l1.go = "PZ_ElitaShluha_2";
			
			// Убираем Мартэна с Маяка
			sld = characterFromID("PZ_RobertMartin");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			
			for (i=1; i<=3; i++)
			{
				sld = characterFromID("PZ_MayakPiraty_"+i);
				sld.lifeday = 0;
			}
			
			sld = characterFromID("PZ_RobertMartin_CloneMayakShip");
			sld.lifeday = 0;
			
			locations[FindLocation("Mayak6")].DisableEncounters = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Mayak6")], false);
			RemoveGeometryFromLocation("Mayak6", "smg");
		break;
		
		case "PZ_ElitaShluha_2":
			dialog.text = "Sólo con el corazón se puede ver bien; lo esencial es invisible a los ojos.";
			link.l1 = "Hermoso. Nunca había escuchado esas líneas antes.";
			link.l1.go = "PZ_ElitaShluha_3";
		break;
		
		case "PZ_ElitaShluha_3":
			dialog.text = "Nos educamos aquí, no somos solo muñecas. La anfitriona cree que es esencial para nuestro establecimiento.";
			link.l1 = "¡La anfitriona! Esa es a quien busco. Escuché que tiene la piel amarilla. Dime, ¿es cierto? ¿Cómo se llama, por cierto?";
			link.l1.go = "PZ_ElitaShluha_4";
		break;
		
		case "PZ_ElitaShluha_4":
			dialog.text = "Es cierto. Pero tiene mejor acumen de negocios que muchas mujeres blancas. Su nombre es Belle Etoile. Pero basta de charla.";
			link.l1 = "¿Basta de charla, dices? Estoy aquí para hablar. Haré unas cuantas preguntas más y luego me iré.";
			link.l1.go = "PZ_ElitaShluha_5";
		break;
		
		case "PZ_ElitaShluha_5":
			dialog.text = "¿Y cuál es el beneficio para el establecimiento? Aquí no pagan por cuerpos, sino por tiempo. ¿Quieres hablar? Eres bienvenido. Pero el dinero por adelantado. Y susurraremos en la habitación, lejos de oídos curiosos. No me importa lo que hagamos allí, no me importa si encendemos velas y rezamos. Un cliente una vez me pidió que le ayudara a escribir un poema. Otro para hablar de sus problemas, llamándome su buen amigo. Y un tercero, solo para encender velas, para luego...";
			link.l1 = "Bueno, no quiero saberlo - ya he oído algo desagradable recientemente. ¿Cuánto te debo?";
			link.l1.go = "PZ_ElitaShluha_6";
		break;
		
		case "PZ_ElitaShluha_6":
			dialog.text = "Doscientos cincuenta doblones. Sin regateo. Si nos damos cuenta de que estamos tratando con un farsante sin un centavo, lo echamos sin remordimientos. Y si es rico pero avaro, subimos el precio: pagará de todos modos.";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "Ahí lo tienes, doscientas cincuenta piezas de oro.";
				link.l1.go = "PZ_ElitaShluha_7";
			}
			link.l2 = "¡Vaya, este lugar es más caro que ese burdel en Jamaica! ¿Puedo volver más tarde cuando tenga el oro?";
			link.l2.go = "PZ_ElitaShluha_Otkaz_1";
		break;
		
		case "PZ_ElitaShluha_7":
			dialog.text = "Bien. ¿Por dónde empezamos? Cena, con o sin velas, baño, conversación?";
			link.l1 = "No tengo mucho tiempo, así que vayamos directo a mis preguntas. Guía el camino.";
			link.l1.go = "PZ_ElitaShluha_IdemVKomnatu";
			RemoveDublonsFromPCharTotal(250);
		break;
		
		case "PZ_ElitaShluha_Otkaz_1":
			dialog.text = "Por supuesto que puedes. La paciencia es una de las virtudes de una cortesana. Echar a un mendigo es una cosa. Dejar ir a un caballero adinerado como tú para que consiga su dinero, o incluso lo pida prestado, es algo muy distinto.";
			link.l1 = "Las virtudes de una cortesana... Irónico. Regresaré enseguida.";
			link.l1.go = "PZ_ElitaShluha_Otkaz_2";
		break;
		
		case "PZ_ElitaShluha_Otkaz_2":
			DialogExit();
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_ElitaShluha_"+i);
				LAi_CharacterDisableDialog(sld);
			}
			LAi_CharacterEnableDialog(npchar);
			npchar.dialog.filename = "Quest\CompanionQuests\Longway.c";
			npchar.dialog.currentnode = "PZ_ElitaShluha_Again";
		break;
		
		case "PZ_ElitaShluha_Again":
			dialog.text = "¡Bienvenido de nuevo, monsieur! Entonces, ¿quién eres? ¿Un caballero adinerado o un farsante?";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "Por supuesto, soy un caballero adinerado, mademoiselle. Aquí está su oro, todos los doscientos cincuenta doblones. No hay necesidad de contarlos.";
				link.l1.go = "PZ_ElitaShluha_Again_1";
			}
			link.l2 = " Todavía me falta, solo ten paciencia conmigo.";
			link.l2.go = "exit";
			NextDiag.TempNode = "PZ_ElitaShluha_Again";
		break;
		
		case "PZ_ElitaShluha_Again_1":
			dialog.text = "No contamos aquí. Hmm, algunas de las monedas parecen dobladas y rotas - a la ama no le gustará mucho eso, pero al menos es todo oro auténtico.";
			link.l1 = "Qué... persona tan elegante es ella.";
			link.l1.go = "PZ_ElitaShluha_Again_2";
			RemoveDublonsFromPCharTotal(250);
		break;
		
		case "PZ_ElitaShluha_Again_2":
			dialog.text = "Así es. Madame Etoile puede ser suave y cariñosa, puede ser estricta, y puede ser despiadada. Por eso no contamos, por cierto. La patrona no siempre es pagada de inmediato, pero siempre recibe lo que le corresponde. Si no es en oro, entonces en sangre. Cualquier casa de tolerancia necesita protectores y padrinos. Y los nuestros están a la altura del estatus del establecimiento.";
			link.l1 = "Ya he pagado, así que guía el camino.";
			link.l1.go = "PZ_ElitaShluha_IdemVKomnatu";
		break;
		
		case "PZ_ElitaShluha_IdemVKomnatu":
			DialogExit();
			pchar.PZ_ElitaShluha = npchar.id;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload3", "PZ_ElitaShluha_VKomnate", -1);
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, npchar, "", -1);
			bDisableCharacterMenu = true;
		break;
		
		case "PZ_ElitaShluha_8":
			dialog.text = "Entonces, ¿qué preguntas tienes, monsieur? Intentaré satisfacer tu... curiosidad.";
			link.l1 = "Sabes lo que me interesa, mademoiselle: tu señora, Madame Étoile.";
			link.l1.go = "PZ_ElitaShluha_9";
		break;
		
		case "PZ_ElitaShluha_9":
			dialog.text = "¿Qué puedo decir sobre ella? Sigue siendo un misterio, incluso para nosotros. Aunque se preocupa por nuestro bienestar, salud y seguridad, no socializa ni se acerca a ninguno de nosotros.";
			link.l1 = "Quizás no le gusten las conversaciones largas. Dime, ¿habla con acento?";
			link.l1.go = "PZ_ElitaShluha_10";
		break;
		
		case "PZ_ElitaShluha_10":
			dialog.text = "No, ¿qué te hace pensar eso? ¿Solo porque tiene la piel amarilla? Habla francés puro y varios otros idiomas. Y puede mantener una conversación de una hora sobre cualquier tema con invitados y posibles interesados.";
			link.l1 = "No me digas. Interesante... ¿Está aquí ahora? Si es así, simplemente entraré a verla y no perderé más de su verdaderamente... valioso tiempo para que pueda volver al trabajo.";
			link.l1.go = "PZ_ElitaShluha_11";
		break;
		
		case "PZ_ElitaShluha_11":
			dialog.text = "No hay mucho a lo que volver, aunque el objetivo de nuestra anfitriona es hacer de este lugar el mejor del Archipiélago. Un lugar elitista, donde ningún mercader, noble o simplemente una persona educada se avergonzaría de venir, porque ofrecemos mucho más que nuestros cuerpos.";
			link.l1 = "Pero no tiene mucho éxito en ello, ¿verdad?";
			link.l1.go = "PZ_ElitaShluha_12";
		break;
		
		case "PZ_ElitaShluha_12":
			dialog.text = "Cómo decirlo... Ella nos ve a cada uno de nosotros no solo como una mercancía, como en establecimientos más simples, sino como un proyecto. Ropa cara, medicina, educación - invierte en cada uno de nosotros. ¡Y si estuviéramos en una gran ciudad del Viejo Mundo, habría triunfado! Pero aquí... Incluso un comerciante talentoso no ganará nada si los bienes son tan caros que casi nadie puede comprarlos. Incluso si bajamos los precios, aún estamos destinados a ir a la quiebra algún día.";
			link.l1 = "Lamento escuchar eso. Entonces, ¿dónde está tu ama ahora?";
			link.l1.go = "PZ_ElitaShluha_13";
		break;
		
		case "PZ_ElitaShluha_13":
			dialog.text = "Estamos llevando una buena vida aquí hasta ahora, te lo puedo asegurar. Viene con el precio de ganársela y mantener sus estándares... En cuanto a la dama, se fue a Española, para discutir la posibilidad de mudarnos todos a Puerto Príncipe - después de todo, allí convergen más rutas comerciales, y nuestro comercio no estará inactivo ni sufrirá pérdidas casi constantes allí.";
			link.l1 = "¿Es así? ¿No invirtió Levasseur en este lugar para asegurar su estabilidad?";
			link.l1.go = "PZ_ElitaShluha_14";
		break;
		
		case "PZ_ElitaShluha_14":
			dialog.text = "No mucho. Vino a nosotros y dijo que solo invertiría en grande si fuéramos a su lugar de vez en cuando. Pero la dama se negó rotundamente. Tanto que Su Gracia se quedó desconcertado por un segundo. Nunca los había visto así.";
			link.l1 = "Heh-heh, mira eso. Parece que ella sabe... Valiente, muy valiente de su parte.";
			link.l1.go = "PZ_ElitaShluha_15";
		break;
		
		case "PZ_ElitaShluha_15":
			dialog.text = "¿Sabes qué? Sin embargo, ya que estamos hablando tan bien, te diré algo más, pero es un gran secreto, así que no lo discutas con nadie.";
			link.l1 = "Oh no, mademoiselle. Le aseguro que no busco hacerle daño a su dama de ninguna manera. Por favor, continúe.";
			link.l1.go = "PZ_ElitaShluha_16";
		break;
		
		case "PZ_ElitaShluha_16":
			dialog.text = "No sé siquiera si podrías hacerle daño, porque Belle Etoile practica esgrima todos los días, y no tiene un oponente digno en toda la ciudad. Además de Port-au-Prince, ¡planea ofrecer a Marcus Tyrex invertir! O más bien, obtener un préstamo de él. ¿Puedes imaginarlo?";
			link.l1 = "Sí, y siento que hoy voy a tener una conversación muy dura con otra mujer que practica esgrima regularmente... Bueno, gracias por compartir, mademoiselle. Que tenga un buen día y clientes generosos.";
			link.l1.go = "PZ_ElitaShluha_17";
		break;
		
		case "PZ_ElitaShluha_17":
			dialog.text = "Gracias. Pero, ¿a qué viene tanta prisa? Ya has pagado todo, y no hemos hablado tanto tiempo. Además, hay algo refinado en ti, monsieur. Algo mucho más que los raros hombres ricos que vienen a nuestra casa. ¿Disfrutamos de nuestra compañía de verdad?";
			link.l1 = "Sabes... ¿qué demonios? ¿Por qué estoy fingiendo y mintiéndome a mí mismo como si no quisiera esto? Una oportunidad con una mujer como tú es muy rara.";
			link.l1.go = "PZ_ElitaShluha_YesSex";
			link.l2 = "Oh, lamento decir que no, mademoiselle. Solo vine aquí para hablar. Además... tengo a alguien esperándome.";
			link.l2.go = "PZ_ElitaShluha_NoSex";
		break;
		
		case "PZ_ElitaShluha_NoSex":
			dialog.text = "Como si eso alguna vez detuviera a alguien. En ese caso, mereces respeto, monsieur. Estoy muy feliz por tu 'alguien'.";
			link.l1 = "Gracias de nuevo, mademoiselle. Adiós.";
			link.l1.go = "PZ_ElitaShluha_NoSex_2";
		break;
		
		case "PZ_ElitaShluha_NoSex_2":
			DialogExit();
			AddQuestRecord("PZ", "30");
			chrDisableReloadToLocation = false;
			bDisableFastReload = true;
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_ElitaShluha_"+i);
				LAi_CharacterDisableDialog(sld);
			}
			npchar.lifeday = 0;
			
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1 = "location";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1.location = "Tortuga_town";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition = "PZ_TortugaKlemanLebren";
			DelMapQuestMarkCity("Tortuga");
			AddMapQuestMarkCity("LaVega", false);
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku"))
			{
				setCharacterShipLocation(pchar, "Tortuga_town");
				setWDMPointXZ("Tortuga_town");
			}
		break;
		
		case "PZ_ElitaShluha_YesSex":
			dialog.text = "Gracias. ¿Qué te parece un baño caliente juntos, para empezar?";
			link.l1 = "Ambas manos a favor.";
			link.l1.go = "PZ_ElitaShluha_YesSex_2";
		break;
		
		case "PZ_ElitaShluha_YesSex_2":
			DialogExit();
			LAi_SetStayType(pchar);
			DoQuestCheckDelay("PlaySex_1", 1.0);
			DoQuestCheckDelay("PZ_ElitaShluha_Fuck", 1.0);
		break;
		
		case "PZ_ElitaShluha_After":
			dialog.text = "Esa fue una experiencia mágica, monsieur. No creía que un hombre pudiera sorprenderme así. Sabes cómo dar placer a una mujer...";
			link.l1 = "Depende de la mujer.";
			link.l1.go = "PZ_ElitaShluha_After_2";
		break;
		
		case "PZ_ElitaShluha_After_2":
			dialog.text = "¿Lo lamentas?";
			link.l1 = "Ahora mismo, definitivamente no. Adiós, mademoiselle.";
			link.l1.go = "PZ_ElitaShluha_After_3";
		break;
		
		case "PZ_ElitaShluha_After_3":
			DialogExit();
			AddQuestRecord("PZ", "30");
			chrDisableReloadToLocation = false;
			bDisableFastReload = true;
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_ElitaShluha_"+i);
				LAi_CharacterDisableDialog(sld);
			}
			npchar.lifeday = 0;
			LAi_SetPlayerType(pchar);
			pchar.questTemp.PZ.EliteWhoreFucked = true; // флаг того, что секс был (понадобится для диалога с Тираксом)
			
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1 = "location";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1.location = "Tortuga_town";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition = "PZ_TortugaKlemanLebren";
			DelMapQuestMarkCity("Tortuga");
			AddMapQuestMarkCity("LaVega", false);
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku"))
			{
				setCharacterShipLocation(pchar, "Tortuga_town");
				setWDMPointXZ("Tortuga_town");
			}
		break;
		
		case "PZ_KlemanLebren_1":
			dialog.text = "¡Mira por dónde vas, farsante!";
			link.l1 = "¡Cuida tu lengua!";
			link.l1.go = "PZ_KlemanLebren_2";
		break;
		
		case "PZ_KlemanLebren_2":
			dialog.text = "Estaba mirando por dónde iba mientras tú contabas cuervos.";
			link.l1 = "Podrías haber dado la vuelta si hubieras estado buscando, ¿no es así?";
			link.l1.go = "PZ_KlemanLebren_3";
		break;
		
		case "PZ_KlemanLebren_3":
			dialog.text = "¿Por qué debería rodearte?!";
			link.l1 = "Sugiero que averigüemos fuera de la ciudad quién debe qué y a quién.";
			link.l1.go = "PZ_KlemanLebren_4";
		break;
		
		case "PZ_KlemanLebren_4":
			dialog.text = "Mm-mm, no. No sabía que su Señoría estaba tan disgustado por el toque involuntario de un simple hombre.";
			link.l1 = "¿Puedes repetirlo?";
			link.l1.go = "PZ_KlemanLebren_5";
		break;
		
		case "PZ_KlemanLebren_5":
			dialog.text = " Hmm, lo siento. No era mi intención empujarte.";
			link.l1 = "Eso está mejor.";
			link.l1.go = "PZ_KlemanLebren_6";
		break;
		
		case "PZ_KlemanLebren_6":
			DialogExit();
			
			LAi_LocationFightDisable(loadedLocation, false);
			chrDisableReloadToLocation = false;
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4", "", "", "", "", -1);
			npchar.location = "None";
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				sld = CharacterFromID("Mary");
				DelLandQuestMark(sld);
				if (CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku"))
				{
					PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1 = "location";
					PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1.location = "Tortuga";
					PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition = "PZ_TortugaRazgovorVKauteSDevushkoy";
				}
				else
				{
					ChangeCharacterAddressGroup(sld, "Tortuga_town", "rld", "loc0");
					sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
					sld.dialog.currentnode = "PZ_MaryRazgovorOBordeli_Bad_1";
					LAi_SetStayType(sld);
					CharacterTurnToLoc(sld, "quest", "quest1");
					sld.talker = 5;
					chrDisableReloadToLocation = true;
					LAi_LocationFightDisable(loadedLocation, true);
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				sld = CharacterFromID("Helena");
				DelLandQuestMark(sld);
				PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1 = "location";
				PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1.location = "Tortuga";
				PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition = "PZ_TortugaRazgovorVKauteSDevushkoy";
			}
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_1":
			dialog.text = "Si hubieras llegado media hora tarde, Charles, ya estaríamos haciendo añicos este sucio nido con nuestras balas de cañón, ¡sí, ¿eh?! ¿Encontraste lo que buscabas? ¿Es ella, la hermana de Longway? ¿La viste?";
			link.l1 = "Shh, Mary, no hables así. No, no llegué a conocer a Chang Xing...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_2";
			
			DeleteAttribute(pchar, "questTemp.MarySexBlock");
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_2":
			dialog.text = "¿Entonces qué demonios te tomó tanto tiempo? ¿Qué estabas haciendo allí?";
			link.l1 = "No tienes nada de qué preocuparte. Tan pronto como descubrí todo lo que pude, me fui de ese lugar, tal como te lo prometí.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_3";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_3":
			dialog.text = "¡Solo escúpelo, sí, ¿eh?!";
			link.l1 = "El dueño no está en Tortuga en este momento. La demanda por sus servicios es baja aquí ya que emplea a damas bien educadas con ropas caras, y solo aceptan oro como pago...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_4";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_4":
			dialog.text = "¿También les pagaste?!";
			link.l1 = "De lo contrario, ni siquiera me habrían hablado. Con ese tipo de enfoque, no es de extrañar que no tengan muchos clientes. La madame ha decidido trasladar su negocio a Puerto Príncipe, esperando atraer a una clientela más adinerada. Pero claramente le falta dinero ya que ha decidido acudir a Marcus Tyrex en busca de un préstamo...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_5";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_5":
			dialog.text = "¿La conoce?";
			link.l1 = "Lo averiguaremos cuando lleguemos a La Vega. Y si nos damos prisa y dejamos de perder el tiempo con charlas innecesarias, atraparemos a esa mujer asiática, quienquiera que sea.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_6";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_6":
			dialog.text = "Era innecesario ir a ese burdel, Charles. Estoy segura de que podríamos haber averiguado todo esto en la taberna o en las calles si lo intentáramos lo suficiente, sí, ¿eh?";
			link.l1 = "La próxima vez te llevaré conmigo para que no llenes tu linda cabecita pelirroja de tonterías, ¿eh? Ahora, vamos al grano.";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_1":
			dialog.text = "¡Oh, veo que llego un poco tarde, sí, ¿eh?! Bueno, espera, sinvergüenza...";
			link.l1 = "¡Mary, qué diablos haces aquí?! ¡Te dije que te quedaras en el barco!";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_2";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_2":
			dialog.text = "¿Así que no te detendría de divertirte con las rameras? ¡Ni se te ocurra negarlo, Charles! ¡La tripulación te vio allí, sí, ¿eh?! ¡¿Cómo pudiste?!";
			link.l1 = "Eso es lo que pensé. Supongo que debería haberlos llevado conmigo, para que pudieran ver lo que estaba haciendo - o más bien, lo que no estaba haciendo - y no hacer un escándalo por ello...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_3";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_3":
			dialog.text = "¿Acusas a nuestros muchachos de mentir? ¿Después de lo que hiciste tú, bruto?";
			link.l1 = "Solo les acuso de una estupidez sin igual. Sin entender la situación, tú...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_4";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_4":
			dialog.text = "Oh-oh, Charles, no creo que a ti y a tus rameras os hubiera gustado cómo entendí la situación si hubiera llegado a ese agujero a tiempo. Pero tienes suerte, tuve que remar esta maldita barca yo solo...";
			link.l1 = "Dicen que el trabajo físico arduo despeja la cabeza de pensamientos innecesarios. Pero aún te sobran muchos, así que también estás remando de vuelta.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_5";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_5":
			dialog.text = "¡No me muevo, sí, ¿eh?";
			link.l1 = "Mary, no voy a tener esta conversación aquí frente a los hombres de Levasseur. Cálmate, mira a tu alrededor y toma una decisión. Este no es ni el momento ni el lugar.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_6";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_6":
			dialog.text = "A la mierda contigo. Todavía tengo mis cosas en el camarote... ¡Pero no creas que voy a remar otra vez, sí, ¿eh! Debe quedar algo de noble en ti!";
			link.l1 = "Soy un canalla y un bruto, ¿recuerdas? Lo demostraré en el barco, pero primero tengo que llegar allí. Así que tus súplicas son inútiles.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_7";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_7":
			DialogExit();
			LAi_LocationFightDisable(loadedLocation, false);
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", Get_My_Cabin(), "rld", "loc1", "OpenTheDoors", -1);
			
			PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1 = "location";
			PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1.location = "Tortuga";
			PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition = "PZ_TortugaRazgovorVKauteSDevushkoy";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_8":
			dialog.text = "¡Tienes a toda la tripulación riéndose de ti, sí, ¿eh?";
			link.l1 = "Bueno, tal vez a ti también. No han visto un espectáculo así en mucho tiempo. Ahora que tu temperamento se ha calmado un poco, déjame contarte lo que sucedió.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_9";
			
			DeleteAttribute(pchar, "questTemp.MarySexBlock");
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_9":
			dialog.text = "Charles, ya lo he escuchado todo. Solo tengo una pregunta: ¿acaso no fui lo suficientemente buena para ti? ¿Hay algo que me falta?";
			link.l1 = "No es cortés, pero responderé con una pregunta: ¿alguna vez te he dado una buena razón para no confiar en mí? ¿Eh? No recuerdo tal cosa. Así que respira hondo y escúchame. No pude averiguar mucho sobre Joep van der Vink, excepto que había estado en un burdel. No el que está cerca del 'Cuervo Cantante', sino otro cerca del muelle. No lo conocía antes... a diferencia, aparentemente, de nuestros marineros, que te pusieron al tanto. Aunque a ellos no se les habría permitido ir allí...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_10";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_10":
			dialog.text = "¿Qué tipo de burdel no deja entrar a los marineros, sí, ¿eh?";
			link.l1 = "Un burdel donde emplean a damas vestidas de seda que tienen más que aire en sus cabezas. Y sus servicios se pagan exclusivamente en doblones de oro. No es solo un capricho de cualquiera, sino la orden de su misteriosa ama, Belle Etoile.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_11";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_11":
			dialog.text = "Misterioso, sí, ¿eh?";
			link.l1 = "No es solo eso. Ella es asiática.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_12";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_12":
			dialog.text = "¿Asiática? ¿La madama del burdel en Tortuga?";
			link.l1 = "Podría ser Chang Xing. Por eso fui allí, quería verla con mis propios ojos. Eso es todo.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_13";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_13":
			dialog.text = "¿Cómo es ella?";
			link.l1 = "No tengo idea. Ella no estaba allí, así que tuve que charlar con otra... estrella.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_14";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_14":
			dialog.text = "¿Era asiática también, sí, ¿eh?";
			link.l1 = "No, ella era blanca. Me dijo que Belle Etoile no ha estado yendo tan bien últimamente, así que decidió mudarse a Puerto Príncipe. Tiene sentido, ya que la gente allí sería más rica. La madame debe estar corta de dinero ya que necesita un préstamo para abrir un comercio en Española, que piensa tomar de Tyrex. Así que si nos apresuramos a La Vega, podemos interceptarla antes de que Marcus se encuentre con ella.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_15";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_15":
			dialog.text = "No me importa un comino ella, ni Marcus, ni nadie más, ¿sí, eh? Charles, solo dime una cosa: ¿has estado con alguna de las chicas de su burdel?";
			link.l1 = "No necesito eso, Mary. Te tengo a ti, la mejor chica del mundo. No entiendo por qué no te das cuenta de eso.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_16";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_16":
			dialog.text = "En realidad, es muy fácil descubrir la verdad, sí, ¿eh? Je je. Si no has estado con nadie, debes estar lleno de energía ahora mismo. Eso es lo que vamos a comprobar ahora, sí, ¿eh?";
			link.l1 = "Mary, por favor...";
			link.l1.go = "exit";
			pchar.quest.sex_partner = Npchar.id;
			AddDialogExitQuest("cabin_sex_go");
			pchar.questTemp.PZ_MaryRazgovorOBordeli = true;
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_17":
			DeleteAttribute(pchar, "questTemp.PZ_MaryRazgovorOBordeli");
			if (CheckAttribute(pchar, "questTemp.PZ.EliteWhoreFucked"))
			{
				if (IsCharacterPerkOn(pchar, "Medic"))
				{
					notification("Excellent Health", "Medic");
					dialog.text = "(Excelente Salud) Uf... Parece que no mentías, Charles, sí, ¿eh?";
					link.l1 = "No tengo necesidad de engañarte, mi querida...";
					link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_18";
				}
				else
				{
					notification("Perk check failed", "Medic");
					dialog.text = "Charles, ¿estás... estás hablando en serio? ¿Qué fue eso?";
					link.l1 = "Oh, ese calor no me sienta bien. Ejem.";
					link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_19";
				}
			}
			else
			{
				dialog.text = "Uf... Parece que no estabas mintiendo, Charles, sí, ¿eh?";
				link.l1 = "No tengo necesidad de engañarte, mi querida...";
				link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_18";
			}
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_18":
			dialog.text = "¡Pero ese paseo en el bote no lo olvidaré por mucho tiempo!";
			link.l1 = "¡Ja!";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_19":
			dialog.text = "¿Nunca te has quejado de eso antes, verdad?";
			link.l1 = "Intenta correr por la maldita isla...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_20";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_20":
			dialog.text = "¡Y los burdeles, sí, ¿eh?! ¿De verdad...";
			link.l1 = "Mary, lo siento.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_21";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_21":
			dialog.text = "¿Qué?! Entonces tú eres...";
			link.l1 = "No lo lamento. Mierda. Quiero decir, no estuve con nadie más que contigo, te lo dije. Solo que... no podía calmar mi mente, eso es todo. Es difícil hacerlo, ya sabes, con los cañones de La Roche apuntándote.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_22";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_22":
			dialog.text = "Esa es una buena excusa, Charles. De acuerdo, te creeré. Esta vez... Pero debes saber que todavía estoy molesta contigo, sí, ¿eh?";
			link.l1 = "Ganaré tu perdón, lo prometo.";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_1":
			dialog.text = "Bueno, galán, dime qué averiguaste. ¿Valió la pena arriesgar mi favor, sí, ¿eh?";
			link.l1 = "No puedo saber si estás bromeando o hablando en serio. Valió la pena, aunque no vi a la _Hostess con mis propios ojos. Es asiática y se llama Belle Etoile, una estrella maravillosa. No es su verdadero nombre, por supuesto...";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_2";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_2":
			dialog.text = "¿Y para eso, tenías que ir a un burdel? ¿No podías averiguarlo en la posada? Ш: Realmente no hablan mucho de este lugar en el pueblo. ¿Por qué? Es una buena pregunta. Puedes preguntarle a Belle Etoile ella misma - se ha ido a Española.";
			link.l1 = "No hablan mucho de este lugar en la ciudad. ¿Por qué? Es una buena pregunta. Puedes preguntarle a Belle Etoile ella misma - se ha ido a Española.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_3";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_3":
			dialog.text = "¿Tortuga no fue suficiente para ella?";
			link.l1 = "El comercio, al parecer, no va bien aquí. Ella no emplea a chicas del puerto comunes, sino a damas ricamente vestidas y educadas.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_4";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_4":
			dialog.text = "¿Y por qué harían eso?";
			link.l1 = "Esa es otra buena pregunta. De todos modos, nuestro pajarito ha decidido volar a Puerto Príncipe, el feudo de de Mussac. Pero el préstamo para esta empresa debía obtenerse de nada menos que Tyrex.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_5";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_5":
			dialog.text = "Quiero que esta historia termine pronto. No perdamos tiempo y pongamos rumbo a La Vega.";
			link.l1 = "Eso es lo que haremos.";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_1":
			dialog.text = "Eres un hombre valiente, Charles, te lo concedo. Apareces tan fácilmente, con una cara tan seria, como si nada hubiera pasado.";
			link.l1 = "Supongo que uno de los tripulantes soltó la lengua. Sin contexto alguno, por supuesto. Porque realmente no pasó nada, al menos no lo que estás pensando.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_2";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_2":
			dialog.text = "Me alegra que no lo hayas negado, Charles.";
			link.l1 = "Iba a contártelo todo, Helen.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_3";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_3":
			dialog.text = "No, Charles. Los detalles no me interesan mucho. Pero las razones sí. Dime, ¿hay algo malo conmigo?";
			link.l1 = "Empecemos por las razones. Descubrí que hay dos burdeles en Tortuga. Uno es muy conocido. Del otro, la gente sabe, pero pocos quieren hablar. Lo regenta una mujer asiática...";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_4";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_4":
			dialog.text = "¿Estás inventando esto sobre la marcha?";
			link.l1 = "¿Por qué demonios haría eso, Helen?! Si no me crees, ellos te lo confirmarán en el lugar!";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_5";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_5":
			dialog.text = "Primero, me dijiste que no bajara a tierra, así que no hay manera de que pueda llegar allí. En segundo lugar, ¿quién demonios crees que soy?! ¡No me acercaré a un lugar así! En tercer lugar... solo continúa.";
			link.l1 = "Bien. Decidí ir allí para ver a Madame Étoile con mis propios ojos. ¡Esa era mi única intención, maldita sea!";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_6";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_6":
			dialog.text = "Supongo. ¿La conociste?";
			link.l1 = "No. Se ha ido a La Española. Las cosas no le van bien aquí, así que decidió probar suerte en Puerto Príncipe. Allí, las damas vestidas de seda y bien educadas que trabajan en su establecimiento pueden traerle más ganancias que en Tortuga...";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_7";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_7":
			dialog.text = "¿Bien vestidos y educados? Vaya, lo que la vida puede traerte. Pero deberías gustarles tal como son.";
			link.l1 = "Helen, detente. No he hecho nada para ganarme tu desconfianza.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_8";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_8":
			dialog.text = "Es cierto. Si hubieras intentado engañarme, no estarías tan tranquilo. Pero deberías haberme advertido de tus planes, Charles.";
			link.l1 = "Tienes razón, cariño. Pero decidí ahorrar algo de tiempo. Mi error.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_9";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_9":
			dialog.text = "Está bien. ¿Y ahora qué, trazamos rumbo hacia Port-au-Prince?";
			link.l1 = " La Vega. No te sorprendas, Helen. Madame Belle Etoile no está bien. Necesitaba un préstamo para trasladar su negocio a Puerto Príncipe, así que decidió pedírselo a Marcus. Si nos damos prisa, podemos alcanzarla allí. Así que no perdamos ni un minuto.";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_NaLaVega":
			DialogExit();
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) 
			{
				AddLandQuestMark(characterFromId("Terrax"), "questmarkmain");
				QuestSetCurrentNode("Terrax", "PZ1");
			}
			else 
			{
				AddLandQuestMark(characterFromId("Vensan"), "questmarkmain");
				QuestSetCurrentNode("Vensan", "PZ1");
			}
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			Island_SetReloadEnableGlobal("Tortuga", true);
			bQuestDisableMapEnter = false;
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				sld = CharacterFromID("Mary");
				AddPassenger(pchar, sld, false);
				Return_MaryOfficer();
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				sld = CharacterFromID("Helena");
				AddPassenger(pchar, sld, false);
				Return_HelenaOfficer();
			}
			if (!CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku")) AddQuestRecord("PZ", "31");
		break;
		
		case "PZ_KlemanLebren_7":
			dialog.text = "¡No puedo creer que un imbécil como tú y tu chusma nos hayan derrotado!";
			link.l1 = "Tú...";
			link.l1.go = "PZ_KlemanLebren_8";
		break;
		
		case "PZ_KlemanLebren_8":
			dialog.text = "Oh, ¿me reconoces?";
			link.l1 = "¿Nos hemos conocido?";
			link.l1.go = "PZ_KlemanLebren_9";
		break;
		
		case "PZ_KlemanLebren_9":
			dialog.text = "¿¡Qué?! ¿Me estás jodiendo?!";
			link.l1 = "No puedo recordar toda la escoria incivilizada que encuentro. Mejor dinos quién te envió a matarnos. ¿O tal vez solo querían deshacerse de ti?";
			link.l1.go = "PZ_KlemanLebren_10";
		break;
		
		case "PZ_KlemanLebren_10":
			dialog.text = "No diré nada a alguien como tú. ¡Te crees tan malditamente superior! Veamos si puedes respaldar eso de nuevo después de nuestro pequeño descanso aquí.";
			link.l1 = "Lástima. Eres repugnante, pero podría haberte dejado en otra isla. Ahora lo único que puedo hacer es enviarte al otro lado.";
			link.l1.go = "PZ_KlemanLebren_11";
		break;
		
		case "PZ_KlemanLebren_11":
			pchar.questTemp.PZ.HeavyFrigateAbordage = true; // флаг - абордаж был
			
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PZ_Tichingitu_11":
			dialog.text = "¿Llamándome, Capitán?";
			link.l1 = "Sí, compañero. Informa los daños.";
			link.l1.go = "PZ_Tichingitu_12";
		break;
		
		case "PZ_Tichingitu_12":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Hay una tormenta violenta. El barco cruje y cruje; se tambalea mucho.";
			link.l1 = "Sí, lo he notado. Tichingitu, mi amigo. Yo y el "+sStr+"  iré a tierra. Tú te quedas a cargo. Comienza las reparaciones de inmediato - hasta que la tormenta se calme, no tiene sentido ir al astillero. Además, no estaremos aquí mucho tiempo.";
			link.l1.go = "PZ_Tichingitu_13";
		break;
		
		case "PZ_Tichingitu_13":
			dialog.text = "Hacer que todo parezca mejor.";
			link.l1 = "Estupendo, gracias. Entonces vamos a la ciudad sin preocupaciones.";
			link.l1.go = "PZ_Tichingitu_14";
		break;
		
		case "PZ_Tichingitu_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "PZ_PoP_Rain_4", -1);
		break;
		
		case "PZ_Matros_1":
			dialog.text = "¿Monseigneur le Capitaine? Es un honor. Pero usualmente llamas a Alonso en momentos como este. ¿Está todo bien, si puedo preguntar?";
			link.l1 = "Sí, todo está bien. Pero nuestro Alonso es más de destruir, no de arreglar nada. En todos los sentidos de la palabra. ¿Qué tan mal está el barco?";
			link.l1.go = "PZ_Matros_2";
		break;
		
		case "PZ_Matros_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Alonso te diría que es pésimo, incluso si no estamos bajando. Mencionaste reparaciones, ¿empezamos con ellas?";
			link.l1 = "Sí, haz lo que puedas. Pero no planees un trabajo a gran escala a largo plazo: pronto levaremos anclas, justo después de que termine mis asuntos en la ciudad. Yo y "+sStr+" no estará allí, así que en caso de cualquier cosa, toma todas las decisiones tú mismo. Escucha a Alonso en todo.";
			link.l1.go = "PZ_Matros_3";
		break;
		
		case "PZ_Matros_3":
			dialog.text = "Como ordene, Monsieur le Capitaine.";
			link.l1 = "A sus órdenes.";
			link.l1.go = "PZ_Matros_4";
		break;
		
		case "PZ_Matros_4":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			Island_SetReloadEnableGlobal("Hispaniola2", true);
			bQuestDisableMapEnter = false;
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "PZ_PoP_Rain_4", -1);
		break;
		
		case "PZ_AnriTibo_1":
			dialog.text = "¡Saludos, monsieur! Bienvenido a Port-au-Prince.";
			link.l1 = "Y buen día para usted, monsieur. ¿Quién es usted, y a qué debo esta bienvenida? No diría que estoy de humor para una larga conversación bajo esta lluvia y después de una tormenta.";
			link.l1.go = "PZ_AnriTibo_2";
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_PoP_ChangShin", "Mei_Shin", "woman", "towngirl2", 30, FRANCE, 0, false, "quest"));
			FantomMakeCoolFighter(sld, 30, 80, 80, "blade_41", "", "", 0);
			sld.name = "Чанг";
			sld.lastname = "Шин";
			ChangeCharacterAddressGroup(sld, "PortPax_town", "goto", "goto16");
			EquipCharacterByItem(sld, "blade_41");
			GiveItem2Character(sld, "cirass8");
			EquipCharacterByItem(sld, "cirass8");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload8_back", "none", "", "", "", -1);
		break;
		
		case "PZ_AnriTibo_2":
			dialog.text = "Ah, no le quitaré mucho tiempo, Monsieur de Maure.";
			link.l1 = "¿Te conozco?";
			link.l1.go = "PZ_AnriTibo_3";
		break;
		
		case "PZ_AnriTibo_3":
			dialog.text = "Oh, no, pero todo el archipiélago sabe quién eres. ¡Ah, dónde están mis modales! Henri Thibaut, a su servicio. Soy el mensajero de Su Señoría, Monsieur de Mussac. Tan pronto como avistó su barco, me ordenó que le diera la más cálida bienvenida posible, monsieur.";
			link.l1 = "Bueno, eso explica mucho. Encantado de conocerte, Monsieur Thibaut.";
			link.l1.go = "PZ_AnriTibo_4";
		break;
		
		case "PZ_AnriTibo_4":
			dialog.text = "¡Y el placer es mutuo, Monsieur de Maure! Por favor, síganme. No es apropiado que un hombre de su estatura y su hermosa compañera estén confinados en esta taberna apestosa. Su Señoría les ha asignado una casa en la ciudad y me ha instruido para asistirles en todo lo que necesiten. Por favor, no olviden transmitir sus mejores deseos a Su Excelencia Poincy después.";
			link.l1 = "En realidad, mi misión es discreta. Sabes, Monsieur Thibaut, creo que...";
			link.l1.go = "PZ_AnriTibo_5";
		break;
		
		case "PZ_AnriTibo_5":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) StartInstantDialog("Helena", "PZ_HelenaPortPax1", "Quest\CompanionQuests\Longway.c");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) StartInstantDialog("Mary", "PZ_MaryPortPax1", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_HelenaPortPax1":
			dialog.text = "Charles. Rara vez te pido algo, y mucho menos interrumpirte, pero ¿podemos aprovechar su oferta? Estoy harta de mojarme bajo la lluvia. También me siento nauseabunda y mareada.";
			link.l1 = "Je-je, ¿estás seguro de que es la lluvia?";
			link.l1.go = "PZ_HelenaPortPax2";
		break;
		
		case "PZ_HelenaPortPax2":
			dialog.text = "¡Muerde tu lengua, Charles! De todas formas, quiero descansar. En una cama grande y sin olas.";
			link.l1 = "Está bien. Nos secaremos, tomaremos un descanso y luego volveremos al trabajo.";
			link.l1.go = "PZ_AnriTibo_6";
		break;
		
		case "PZ_MaryPortPax1":
			dialog.text = "¿Podemos descansar en esta casa? No me siento bien, y también estoy... cansada, Charles. Sí, ¿eh?";
			link.l1 = "Mary, querida, lo entiendo, pero tal vez deberíamos ir a la taberna. Todo esto huele mal, ¿no es así?";
			link.l1.go = "PZ_MaryPortPax2";
		break;
		
		case "PZ_MaryPortPax2":
			dialog.text = "¿Qué podría pasarme? Esto ni siquiera es Tortuga.";
			link.l1 = "Eso es lo que me asusta.";
			link.l1.go = "PZ_MaryPortPax3";
		break;
		
		case "PZ_MaryPortPax3":
			dialog.text = "¿Por favor? Si acaso, montaré una defensa en la habitación, tal como... aquella vez, sí, ¿eh? Me conoces mejor que nadie, Charles, así que sabes que puedo manejarlo.";
			link.l1 = "Está bien, está bien. Esperemos que esto no sea como aquella vez.";
			link.l1.go = "PZ_AnriTibo_6";
		break;
		
		case "PZ_AnriTibo_6":
			StartInstantDialog("Tibo", "PZ_AnriTibo_7", "Quest\CompanionQuests\Longway.c");
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) Return_MaryOfficer();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) Return_HelenaOfficer();
		break;
		
		case "PZ_AnriTibo_7":
			dialog.text = "¡Sabía que cambiarías de opinión, monsieur! En cuanto a tus preocupaciones, las entiendo perfectamente. Pero, verás, Su Excelencia Poincy y el gobernador son viejos amigos, y por lo tanto eres un invitado bienvenido en nuestra ciudad, Monsieur de Maure!";
			link.l1 = "Oh, bueno... Bueno, entonces, llévanos a la casa entonces.";
			link.l1.go = "PZ_AnriTibo_8";
		break;
		
		case "PZ_AnriTibo_8":
			dialog.text = "¡Ciertamente, monsieur! Sígueme, por favor.";
			link.l1 = "Gracias.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_GoToTiboHouse");
		break;
		
		case "PZ_AnriTibo_9":
			dialog.text = "Monsieur, el gobernador le está esperando. Ha pedido que vaya a verlo tan pronto como pueda - le gustaría hablar con usted en privado.";
			link.l1 = "¿Ya lo sabe?";
			link.l1.go = "PZ_AnriTibo_10";
		break;
		
		case "PZ_AnriTibo_10":
			pchar.questTemp.PZ.PortPaxMayorTalk = true; // флаг для разговора с губернатором
			
			dialog.text = "¡Por supuesto, él lo sabe! Por eso te está esperando. Deja que tu amada duerma dulcemente mientras vas a ver al monsieur de Mussac. Alguna tormenta no detendrá al famoso Charles de Maure, ¿verdad? Pero Su Señoría, como te das cuenta, no tiene mucho tiempo que perder entre citas...";
			link.l1 = "Bueno, eso es cierto, Monsieur Thibaut.";
			link.l1.go = "PZ_AnriTibo_11";
			
			for (i=1; i<=2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_PoP_Escort_"+i, "sold_fra_"+(rand(7)+1), "man", "man", sti(pchar.rank), FRANCE, -1, true, "soldier"));
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			}
		break;
		
		case "PZ_AnriTibo_11":
			StartInstantDialog("PZ_PoP_Escort_1", "PZ_AnriTibo_12", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_AnriTibo_12":
			dialog.text = "Te mostraremos el camino, Capitán.";
			link.l1 = "Oh, así que incluso tengo una escolta honoraria... Bueno, adelante, muestra el camino.";
			link.l1.go = "PZ_AnriTibo_13";
		break;
		
		case "PZ_AnriTibo_13":
			DoQuestReloadToLocation("PortPax_town", "reload", "houseF1", "PZ_PoP_EscortToGuber");
		break;
		
		case "PZ_Longway_71":
			dialog.text = "¡Señor Capitán!";
			link.l1 = "¡Longway! ¡Al barco! ¡Ahora!";
			link.l1.go = "PZ_Longway_72";
		break;
		
		case "PZ_Longway_72":
			dialog.text = "¡Pero vi a Chang Xing!";
			link.l1 = "¿Qué?! ¿Dónde? ¿Cuándo? ¿Está en tu barco?";
			link.l1.go = "PZ_Longway_73";
		break;
		
		case "PZ_Longway_73":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "¡No! Aquí en la ciudad, Longway la vio de lejos. No hay tiempo para alcanzarla - está abordando un galeón que acaba de zarpar!";
			link.l1 = "¡Alcanzaremos al galeón! Pero dime, ¿has visto "+sStr+" ¿en algún lugar?";
			link.l1.go = "PZ_Longway_74";
		break;
		
		case "PZ_Longway_74":
			dialog.text = "¡No! ¿Pasó algo?";
			link.l1 = "¡Sí, algo ha pasado! ¡Ella está en peligro! ¿Has visto al sobrino de Levasseur? ¡Se llama Henri Thibaut! ¡Desagradable, flaco, joven de cabello largo con un bigote gracioso!";
			link.l1.go = "PZ_Longway_75";
		break;
		
		case "PZ_Longway_75":
			dialog.text = "(en mandarín) No necesitas hablar de bigotes graciosos, Capitán... (en francés roto) ¡Lo vi! Él y los mercenarios también abordaron el mismo galeón.";
			link.l1 = "¡Demos caza inmediatamente!";
			link.l1.go = "PZ_Longway_76";
		break;
		
		case "PZ_Longway_76":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "¡Su nave está gravemente desgastada, Mi Señor Capitán!";
			link.l1 = "¡No me importa! "+sStr+"¡La vida de [[[VARx]]] está en juego!";
			link.l1.go = "PZ_Longway_77";
		break;
		
		case "PZ_Longway_77":
			if (CheckAttribute(pchar, "questTemp.PZ.LongwayMayfang"))
			{
				dialog.text = "Mi... 'Tu Meifeng' nos llevará a través de esto.";
				link.l1 = "¡Oh, lo hará! ¡Date prisa!";
				link.l1.go = "PZ_Longway_78";
			}
			else
			{
				dialog.text = "No nos lances a un ataque suicida. ¡Usa el barco que me proporcionaste antes!";
				link.l1 = "¡Buena idea, Longway! ¡Apresurémonos!";
				link.l1.go = "PZ_Longway_78";
			}
		break;
		
		case "PZ_Longway_78":
			DialogExit();
			chrDisableReloadToLocation = false;
			Island_SetReloadEnableGlobal("Hispaniola2", false);
			LocatorReloadEnterDisable("PortPax_town", "gate_back", true);
			SetCurrentTime(15, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			pchar.GenQuest.AbordageInStorm = true;	//Разрешить абордаж во время шторма
			SetLocationCapturedState("PortPax_town", false);

			LAi_LoginInCaptureTown(npchar, false);
			AddPassenger(pchar, npchar, false);
			Return_LongwayOfficer();
			
			if (GetCharacterIndex("Tichingitu") != -1)
			{
				sld = characterFromId("Tichingitu");
				AddPassenger(pchar, sld, false);
				Return_TichingituOfficer();
			}
			
			PChar.quest.PZ_PoP_Pogonya.win_condition.l1 = "location";
			PChar.quest.PZ_PoP_Pogonya.win_condition.l1.location = "Hispaniola2";
			PChar.quest.PZ_PoP_Pogonya.win_condition = "PZ_PoP_Pogonya";
			
			/*sld = GetCharacter(NPC_GenerateCharacter("PZ_ShipStasis", "panhandler_6", "man", "man", sti(pchar.rank), PIRATE, -1, false, "quest"));
			SetSPECIAL(sld, 1, 1, 1, 1, 1, 1, 1);
			SeaAI_SwapShipsAttributes(pchar, sld);
			if (CheckAttribute(pchar, "questTemp.PZ.LongwayMayfang"))	//Мейфенг
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_MAYFANG, true, pchar);
				pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS20;
				pchar.Ship.name = "Meifeng";
			}
			if (CheckAttribute(pchar, "questTemp.PZ.LongwayElCasador"))	//Эль Касадор
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_ELCASADOR, true, pchar);
				pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS32;
				pchar.Ship.name = "El Casador";
			}
			if (CheckAttribute(pchar, "questTemp.PZ.LongwayTorero"))	//Тореро
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_POLACRE_QUEST, true, pchar);
				pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS24;
				pchar.Ship.name = "Torero";
			}
			if (CheckAttribute(pchar, "questTemp.PZ.LongwaySchoonerW"))	//Военная шхуна
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_SCHOONER_W, true, pchar);
				pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS12;
				pchar.Ship.name = "Aztec";
			}
			if (CheckAttribute(pchar, "questTemp.PZ.LongwayBrig"))	//Бриг
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_BRIG, true, pchar);
				pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS16;
				pchar.Ship.name = "Aztec";
			}
			if (CheckAttribute(pchar, "questTemp.PZ.LongwayCorvette"))	//Корвет
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_CORVETTE, true, pchar);
				pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS16;
				pchar.Ship.name = "Aztec";
			}
			if (CheckAttribute(pchar, "questTemp.PZ.LongwayPolacre"))	//Полакр
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_POLACRE, true, pchar);
				pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS16;
				pchar.Ship.name = "Aztec";
			}
			if (CheckAttribute(pchar, "questTemp.PZ.LongwayXebek"))	//Шебека
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_XebekVML, true, pchar);
				pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS16;
				pchar.Ship.name = "Aztec";
			}
			if (CheckAttribute(pchar, "questTemp.PZ.LongwayBrigantine"))	//Бригантина
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_BRIGANTINE, true, pchar);
				pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS16;
				pchar.Ship.name = "Aztec";
			}
			SetBaseShipData(pchar);*/
			SeaAI_SwapShipsAttributes(pchar, CharacterFromID("PZ_ShipStasis"));
			AddCharacterGoodsSimple(pchar, GOOD_GRAPES, 300);
			AddCharacterGoodsSimple(pchar, GOOD_BOMBS, 200);
			AddCharacterGoodsSimple(pchar, GOOD_POWDER, 350);
			AddCharacterGoodsSimple(pchar, GOOD_FOOD, 150);
			AddCharacterGoodsSimple(pchar, GOOD_RUM, 50);
			AddCharacterGoodsSimple(pchar, GOOD_FOOD, 700);
			//SetCrewQuantityFull(pchar);
			pchar.ship.HP = sti(pchar.ship.HP) / 2;
			pchar.Ship.Crew.Quantity = sti(pchar.ship.Crew.Quantity) / 2;
			AddCrewMorale(Pchar, 100);
			ChangeCrewExp(pchar, "Sailors", 100);
			ChangeCrewExp(pchar, "Cannoners", 100);
			ChangeCrewExp(pchar, "Soldiers", 100);
			
			//Вражина
			sld = characterFromId("PZ_RobertMartin");
			sld.nation = PIRATE;
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				GiveItem2Character(sld, "blade_31");
				EquipCharacterByItem(sld, "blade_31");
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				GiveItem2Character(sld, "pirate_cutlass");
				EquipCharacterByItem(sld, "pirate_cutlass");
			}
			FantomMakeCoolSailor(sld, SHIP_GALEON_L, "Voltigeur", CANNON_TYPE_CANNON_LBS16, 50, 50, 50);
			sld.AlwaysEnemy = true;
			sld.AlwaysSandbankManeuver = true;
			sld.DontRansackCaptain = true;
			sld.ShipHideImmortal = 800;
			Group_FindOrCreateGroup("PZ_RM_Attack");
			Group_SetType("PZ_RM_Attack", "pirate");
			Group_AddCharacter("PZ_RM_Attack", "PZ_RobertMartin");
			Group_SetGroupCommander("PZ_RM_Attack", "PZ_RobertMartin");
			Group_SetTaskAttack("PZ_RM_Attack", PLAYER_GROUP);
			Group_SetAddress("PZ_RM_Attack", "Hispaniola2", "quest_ships", "Quest_ship_1");
			Ship_SetTaskAttack(SECONDARY_TASK, sti(sld.index), sti(pchar.index));
		break;
		
		case "PZ_RobertMartin_8":
			dialog.text = "Tú otra vez... Sabía que debería haberme negado y dejar que alguien más se llevara a tu chica.";
			link.l1 = "¿Dónde está ella?! ¡Dímelo! No... Cierra tu boca. ¡Solo hablarás en la bodega, con grilletes! ¿Me oyes?!";
			link.l1.go = "PZ_RobertMartin_9";
		break;
		
		case "PZ_RobertMartin_9":
			dialog.text = "...";
			link.l1 = "Su hoja. Si no empiezas a cantar ahora mismo, te haré pedazos con ella.";
			link.l1.go = "PZ_RobertMartin_10";
			/*RemoveAllCharacterItems(npchar, true);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) GiveItem2Character(pchar, "blade_31");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) GiveItem2Character(pchar, "pirate_cutlass");*/
		break;
		
		case "PZ_RobertMartin_10":
			dialog.text = "¡Tú... estás completamente loco!";
			link.l1 = "Ahora estás a punto de ver mi lado desagradable...";
			link.l1.go = "PZ_RobertMartin_11";
		break;
		
		case "PZ_RobertMartin_11":
			DialogExit();
			LAi_ReloadBoarding();
		break;
		
		case "PZ_RobertMartin_13":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "¿Eso es todo?";
			link.l1 = "¡Te lo pregunto de nuevo! ¿Dónde está "+sStr+"¿¡Dónde está la mujer china!? ¿Dónde está Henri Thibaut!?";
			link.l1.go = "PZ_RobertMartin_14";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "beatmarten_idle_1", "", 0.3);
		break;
		
		case "PZ_RobertMartin_14":
			dialog.text = "(escupe sangre) Pegas como una niña.";
			link.l1 = "¡Zorra! ¡Te sacaré cada palabra a golpes!";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DoprosRobertMartin_Trum_6");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "beatmarten_idle_1", "", 0.3);
		break;
		
		case "PZ_RobertMartin_16":
			dialog.text = "Patético. Aunque... lo diré. ¿Por qué no, ja ja? Están todos en el otro barco, justo en camino a Tortuga. Llegas demasiado tarde.";
			link.l1 = "Si siquiera un cabello cae de su cabeza...";
			link.l1.go = "PZ_RobertMartin_17";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "beatmarten_idle_2", "", 0.3);
			locCameraFromToPos(0.27, 14.52, -3.38, true, -1.80, 9.90, -1.76);
		break;
		
		case "PZ_RobertMartin_17":
			dialog.text = "¿Y de quién es la culpa?! ¡Tú mataste a Edgardo Sotta! ¡Por primera vez en su vida, Levasseur quiso probar a una chica y no lo consiguió de inmediato! ¡Primera vez que nuestra tripulación falló en cumplir su orden directa! El hombre puede ser tan aterrador como el diablo...";
			link.l1 = "¡Entonces seré más aterrador que el mismo diablo y te daré un infierno personal si no me dices lo que quiero saber, ¿me oyes?!";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) link.l1.go = "PZ_RobertMartin_Mary_1";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) link.l1.go = "PZ_RobertMartin_Helena_1";
		break;
		
		case "PZ_RobertMartin_Mary_1":
			dialog.text = "No me importan tus penas - de todos modos, ya estoy muerto, a juzgar por esos ojos locos tuyos. Sin embargo, te daré algo de crédito, de Maure.";
			link.l1 = "¿De qué demonios estás hablando?";
			link.l1.go = "PZ_RobertMartin_Mary_2";
		break;
		
		case "PZ_RobertMartin_Mary_2":
			dialog.text = "Levasseur prefiere a las rubias. Pero a mí siempre me han gustado más las pelirrojas, como tú, jejeje... ¡Qué picante tienes tú!";
			link.l1 = "Tienes razón, no sobrevivirás el día...";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DoprosRobertMartin_Trum_7");
		break;
		
		case "PZ_RobertMartin_Helena_1":
			dialog.text = "No me importa un comino lo que quieras. Pero déjame decirte lo que quiere Levasseur: chicas rubias bonitas, ¡ja ja ja ja ja ja ja ja ja! Primero, la tiene a ella...";
			link.l1 = "¡A-AH!";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DoprosRobertMartin_Trum_7");
		break;
		
		case "PZ_RobertMartin_19":
			dialog.text = "Gritar y golpear a un hombre desarmado - patético. Eso es todo lo que puedes hacer. Has perdido, de Maure. ¿Quieres saber cuándo realmente perdiste, cretino patético?";
			link.l1 = "Ilumíname. Pero si no me impresiona, perderás un dedo. O una oreja. O esos dientes podridos de tu apestosa boca. O tal vez algo más. La elección es tuya...";
			link.l1.go = "PZ_RobertMartin_20";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "beatmarten_idle_3", "", 0.3);
			//locCameraFromToPos(-1.75, 14.14, -0.31, true, 1.26, 11.00, -4.00);
			locCameraFromToPos(-2.47, 14.15, -0.01, true, 1.23, 10.92, -3.60);
		break;
		
		case "PZ_RobertMartin_20":
			dialog.text = "Je, je, tengo algo que tú no tienes. ¿Crees que Levasseur no sabía lo que ese viejo zorro Poincy estaba tramando contra él? ¡François lo sabe todo, todo! Incluso los barones de la Hermandad no se atreven a desafiarlo. Y tú, listo, lo hiciste. Pero...";
			link.l1 = "¡¿Pero qué?! ¡Ni se te ocurra alargar esto, maldita sea! ¡Empieza a hablar, o empezaré a romperte los dedos uno por uno!";
			link.l1.go = "PZ_RobertMartin_21";
		break;
		
		case "PZ_RobertMartin_21":
			dialog.text = "¡Ja, ja, valiente Capitán de Maure! Pero está bien. Yo, Henri, y la mujer de piel amarilla decidimos que lo mejor era destruirte aquí. Y echarle la culpa a Tyrex, para que los viejos tontos de la Hermandad comenzaran otra guerra entre ellos mismos. ¡O tal vez de Mussac, que ha estado metiendo su nariz donde no le corresponde...! Sabes, todos se reían de mí por navegar un galeón, pero soportó la tormenta con facilidad, a diferencia de tu pedazo de basura.";
			link.l1 = "¡Basta! ¿Dónde guarda Levasseur a sus víctimas?";
			link.l1.go = "PZ_RobertMartin_22";
		break;
		
		case "PZ_RobertMartin_22":
			dialog.text = "¿Así que sabes de su lugar secreto, el calabozo? ¡Oh sí, él es el verdadero maestro del calabozo, ja-ja-ja! ¿Pero realmente puedes desafiarlo? Lo dudo. ¿Quieres derrotar a la bestia? Entonces conviértete tú mismo en la bestia. A ver si puedes romperme como Francois rompe a esas chicas. Como pronto romperá a las tuyas...";
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
			{
				link.l1 = "¡Alo-o-on-s-o-o!!!";
				link.l1.go = "PZ_RobertMartin_23";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "PZ_LongwayKaznDialog_1";
			}
		break;
		
		case "PZ_RobertMartin_23":
			DialogExit();
			LAi_SetStayType(pchar);
			CharacterTurnByChr(pchar, CharacterFromID("PZ_RobertMartinPlennik"));
			LAi_Fade("PZ_AlonsoKazn", "");
		break;
		
		case "PZ_LongwayKaznDialog_1":
			DialogExit();
			LAi_SetStayType(pchar);
			CharacterTurnByChr(pchar, CharacterFromID("PZ_RobertMartinPlennik"));
			DoQuestCheckDelay("PZ_LongwayKazn_1", 1.0);
		break;
		
		case "PZ_LongwayKaznDialog_2":
			dialog.text = "";
			link.l1 = "¡Te dije que no te molestes, maldita sea!..";
			link.l1.go = "PZ_LongwayKaznDialog_3";
		break;
		
		case "PZ_LongwayKaznDialog_3":
			DialogExit();
			LAi_SetStayType(pchar);
			LAi_Fade("PZ_LongwayKazn_3", "");
		break;
		
		case "PZ_LongwayKaznDialog_4":
			dialog.text = "Permítame, Mi Señor Capitán.";
			link.l1 = "¿Longway? ¿Permitir qué?";
			link.l1.go = "PZ_LongwayKaznDialog_5";
		break;
		
		case "PZ_LongwayKaznDialog_5":
			dialog.text = "Los hombres blancos atormentan el cuerpo. Mi gente sabe que primero hay que atormentar el alma miserable, enloquecerla con un poco de dolor constante. No se puede simplemente tomar y atormentar sin preparación. Siempre se necesita un enfoque especial. Aquí necesitas... a Lynchy.";
			link.l1 = "Lynchy?";
			link.l1.go = "PZ_LongwayKaznDialog_6";
		break;
		
		case "PZ_LongwayKaznDialog_6":
			dialog.text = "Sí, Mi Señor Capitán. Muerte por mil cortes.";
			link.l1 = "¿Estás loco?! ¿Te has golpeado la cabeza? ¿De qué muerte estás balbuceando?! ¡Primero necesito hacerle hablar!";
			link.l1.go = "PZ_LongwayKaznDialog_7";
		break;
		
		case "PZ_LongwayKaznDialog_7":
			dialog.text = "Longway lo sabe, Mi Señor Capitán. Sabe qué hacer. Este bastardo me lo va a contar todo. Dame tiempo...";
			link.l1 = "¿Tiempo? ¿¡Tiempo?! Está bien... Hazlo. Solo por favor, te lo suplico, sácale todo, ¡todo!";
			link.l1.go = "PZ_LongwayKaznDialog_8";
		break;
		
		case "PZ_LongwayKaznDialog_8":
			DialogExit();
			LAi_SetActorType(npchar);
			CharacterTurnByChr(npchar, CharacterFromID("PZ_RobertMartinPlennik"));
			LAi_SetStayType(pchar);
			CharacterTurnByChr(pchar, CharacterFromID("PZ_RobertMartinPlennik"));
			LAi_FadeToBlackStart();
			DoQuestCheckDelay("PZ_LongwayKazn_4", 1.5);
		break;
		
		case "PZ_LongwayKaznDialog_9":
			dialog.text = "Mátame, solo mátame, por favor... ¿Qué más quieres de mí?!";
			link.l1 = "Nada más. Cierra la boca y muere.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayKazn_11");
		break;//
		
		case "PZ_LongwayKaznDialog_9_1":
			DialogExit();
			sld = CharacterFromID("PZ_RobertMartinPlennik")
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Shot", "1", 1.5);
			DoQuestCheckDelay("PZ_LongwayKazn_9", 0.9);
		break;
		
		case "PZ_LongwayKaznDialog_10":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Shot", "1", 1.5);
			DoQuestCheckDelay("PZ_LongwayKazn_9", 0.9);
		break;
		
		case "PZ_LongwayKaznDialog_11":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Tiro limpio, Mi Señor Capitán. Te dije que funcionaría.";
			link.l1 = "Sí. Buen trabajo. Entonces, al calabozo. ¡Izad todas las velas! Pon rumbo a Tortuga. Y que Dios ayude a esta maldita ciudad si una sola hebra de cabello cae de "+sStr+" cabeza...";
			link.l1.go = "PZ_LongwayKaznDialog_12";
		break;
		
		case "PZ_LongwayKaznDialog_12":
			DialogExit();
			ResetSound();
			chrDisableReloadToLocation = false;
			EndQuestMovie();
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			locCameraTarget(PChar);
			locCameraFollow();
			AddQuestRecord("PZ", "39");
			
			LAi_SetPlayerType(pchar);
			npchar.greeting = "Longway";
			Return_LongwayOfficer();
			
			bQuestDisableMapEnter = false;
			Island_SetReloadEnableGlobal("Hispaniola2", true);
			Island_SetReloadEnableLocal("Hispaniola2", "reload_2", true)
			Island_SetGotoEnableLocal("Hispaniola2", "reload_2", true);
			Island_SetReloadEnableLocal("Hispaniola2", "reload_3", true)
			Island_SetGotoEnableLocal("Hispaniola2", "reload_3", true);
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			DeleteAttribute(pchar,"questTemp.TimeLock");
			LocatorReloadEnterDisable("LaVega_ExitTown", "reload1_back", false);
			LocatorReloadEnterDisable("PortPax_town", "gate_back", false);
			LAi_LocationDisableOfficersGen("PortPax_town", false);
			LAi_LocationFightDisable(&Locations[FindLocation("PortPax_town")], false);
			DeleteAttribute(pchar, "GenQuest.AbordageInStorm");
			
			PChar.quest.PZ_Etap6_Start.win_condition.l1 = "location";
			PChar.quest.PZ_Etap6_Start.win_condition.l1.location = "Tortuga";
			PChar.quest.PZ_Etap6_Start.win_condition = "PZ_Etap6_Start";
			locations[FindLocation("Shore58")].DisableEncounters = true;
			SetTimerCondition("PZ_Etap6_Opozdal", 0, 0, 7, false);
			DelMapQuestMarkCity("PortPax");
			AddMapQuestMarkShore("Shore58", true);
			pchar.questTemp.PZ_FlagMartinInfo = true;
			
			// Компаньон-заглушка входит в состав нашей экскадры
			sld = CharacterFromID("PZ_ShipStasis");
			SetCompanionIndex(pchar, -1, sti(sld.index));
			SetCharacterRemovable(sld, true);
			SetShipRemovable(sld, true);
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.quest.meeting = true;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			sld.Dialog.CurrentNode = "hired";
			sld.Payment = true;
			sld.ship.HP = sti(sld.ship.HP) / 2;
			
			//
			makearef(arTmp, pchar.questTemp.PZ_PoP_More.ShipPos);
			QuestToSeaLogin_Prepare(stf(arTmp.x), stf(arTmp.z), arTmp.Island);
			DeleteAttribute(pchar, "questTemp.PZ_PoP_More.ShipPos");
			QuestToSeaLogin_Launch();
		break;
		
		case "PZ_AlonsoKaznDialog_1":
			dialog.text = "Dios mío... nunca te he visto ni escuchado... así, señor Capitán.";
			link.l1 = "¡Es todo tuyo, Alonso! Adelante, muéstrame lo que hace la Santa Inquisición con los hugonotes y sus secuaces... Y yo observaré... Luego puedes hacer lo que quieras con él.";
			link.l1.go = "PZ_AlonsoKaznDialog_2";
		break;
		
		case "PZ_AlonsoKaznDialog_2":
			dialog.text = "Sí sí, señor Capitán...";
			link.l1 = "";
			link.l1.go = "PZ_AlonsoKaznDialog_3";
		break;
		
		case "PZ_AlonsoKaznDialog_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, CharacterFromID("PZ_RobertMartinPlennik"), "PZ_AlonsoKazn_2", -1);
		break;
		
		case "PZ_AlonsoKaznDialog_4":
			dialog.text = "No tomará mucho tiempo, señor Capitán...";
			link.l1 = "¡Hazlo, por el amor de Dios!";
			link.l1.go = "PZ_AlonsoKaznDialog_5";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_RobertMartinPlennik"));
			LAi_ActorAnimation(npchar, "Barman_idle", "1", 5);
		break;
		
		case "PZ_AlonsoKaznDialog_5":
			DialogExit();
			LAi_SetStayType(pchar);
			LAi_FadeToBlackStart();
			DoQuestCheckDelay("PZ_AlonsoKazn_3", 1.5);
		break;
		
		case "PZ_AlonsoKaznDialog_6":
			dialog.text = "Levántate, pedazo de mierda. ¡Levántate, te dije!";
			link.l1 = "¿Está muerto? ¡¿Muerto?!";
			link.l1.go = "PZ_AlonsoKaznDialog_7";
			CharacterTurnByChr(npchar, CharacterFromID("PZ_RobertMartinPlennik"));
			CharacterTurnByChr(pchar, CharacterFromID("PZ_RobertMartinPlennik"));
		break;
		
		case "PZ_AlonsoKaznDialog_7":
			dialog.text = "Parece que sí, cap...";
			link.l1 = "¿¡Qué demonios hiciste?!";
			link.l1.go = "PZ_AlonsoKaznDialog_8";
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);
		break;
		
		case "PZ_AlonsoKaznDialog_8":
			dialog.text = "¡Quién diría que este patán resultaría ser tan débil! ¡También se ensució los calzones, el sucio canalla! ¡Maldita sea, el fuego fue innecesario...";
			link.l1 = "Vos... Bueno, échalo por la borda a los peces. Pon rumbo a Tortuga. Si es necesario, la desmantelaré ladrillo a ladrillo - primero La Roche, luego... Luego que Dios me ayude si no la encuentro viva...";
			link.l1.go = "PZ_AlonsoKaznDialog_9";
		break;
		
		case "PZ_AlonsoKaznDialog_9":
			DialogExit();
			ResetSound();
			chrDisableReloadToLocation = false;
			EndQuestMovie();
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			locCameraTarget(PChar);
			locCameraFollow();
			AddQuestRecord("PZ", "38");
			
			LAi_SetPlayerType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "", "", "", "", -1);
			npchar.lifeday = 0;
			npchar.location = "None";
			
			bQuestDisableMapEnter = false;
			Island_SetReloadEnableGlobal("Hispaniola2", true);
			Island_SetReloadEnableLocal("Hispaniola2", "reload_2", true)
			Island_SetGotoEnableLocal("Hispaniola2", "reload_2", true);
			Island_SetReloadEnableLocal("Hispaniola2", "reload_3", true)
			Island_SetGotoEnableLocal("Hispaniola2", "reload_3", true);
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			DeleteAttribute(pchar,"questTemp.TimeLock");
			LocatorReloadEnterDisable("LaVega_ExitTown", "reload1_back", false);
			LocatorReloadEnterDisable("PortPax_town", "gate_back", false);
			LAi_LocationDisableOfficersGen("PortPax_town", false);
			LAi_LocationFightDisable(&Locations[FindLocation("PortPax_town")], false);
			DeleteAttribute(pchar, "GenQuest.AbordageInStorm");
			
			PChar.quest.PZ_Etap6_Start.win_condition.l1 = "location";
			PChar.quest.PZ_Etap6_Start.win_condition.l1.location = "Tortuga";
			PChar.quest.PZ_Etap6_Start.win_condition = "PZ_Etap6_Start";
			locations[FindLocation("Shore58")].DisableEncounters = true;
			SetTimerCondition("PZ_Etap6_Opozdal", 0, 0, 7, false);
			DelMapQuestMarkCity("PortPax");
			AddMapQuestMarkShore("Shore58", true);
			
			// Компаньон-заглушка входит в состав нашей экскадры
			sld = CharacterFromID("PZ_ShipStasis");
			SetCompanionIndex(pchar, -1, sti(sld.index));
			SetCharacterRemovable(sld, true);
			SetShipRemovable(sld, true);
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.quest.meeting = true;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			sld.Dialog.CurrentNode = "hired";
			sld.Payment = true;
			sld.ship.HP = sti(sld.ship.HP) / 2;
			
			//
			makearef(arTmp, pchar.questTemp.PZ_PoP_More.ShipPos);
			QuestToSeaLogin_Prepare(stf(arTmp.x), stf(arTmp.z), arTmp.Island);
			DeleteAttribute(pchar, "questTemp.PZ_PoP_More.ShipPos");
			QuestToSeaLogin_Launch();
		break;
		
		case "PZ_Norman1":
			dialog.text = "Finalmente. Este trono es mío ahora. En esta roca edificaré...";
			link.l1 = "¿Qué demonios... En serio?";
			link.l1.go = "PZ_Norman2";
		break;
		
		case "PZ_Norman2":
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
			else sTemp = "Shark";
			
			dialog.text = "... mi Iglesia. Ahora soy el Papa de Roma. ¡No jures en la Casa de Dios!";
			link.l1 = "Y aquí pensé... Bueno, Su Santidad, ¿sería tan amable de decirle a sus fieles dónde la "+sTemp+" ¿es ahora?";
			link.l1.go = "PZ_Norman3";
		break;
		
		case "PZ_Norman3":
			dialog.text = "Está en una búsqueda sagrada. Una nueva cruzada, si se quiere. Va a tomar el dinero de los malvados y traérmelo a mí.";
			link.l1 = "A ti, correcto. ¿Mencionó cuándo volvería?";
			link.l1.go = "PZ_Norman4";
		break;
		
		case "PZ_Norman4":
			NextDiag.TempNode = "PZ_NormanBlock";
			
			dialog.text = "En un mes. Quizás un poco más tarde. Estoy esperando su regreso, junto con el resto de nuestro rebaño.";
			link.l1 = "Así que realmente está en el mar. Será mejor que me vaya antes de que me contagie de lo que tienes.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_NormanBlock":
			NextDiag.TempNode = "PZ_NormanBlock";
			
			dialog.text = "Los purificaré a todos en las sagradas llamas...";
			link.l1 = "Tu cabeza necesita una limpieza...";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaIslaTesoro1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				// ох, какой же костыль, м-м-мать...
				sld = characterFromId("Mary");
				if (sld.location != "Pirates_townhall")
				{
					if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "con Marcus";
					else sTemp = "with Steve";
					
					dialog.text = "¡Charles! ¿Qué puedo hacer por ti?";
					link.l1 = "¡Hola, Helen! Quiero hablar con "+sTemp+"¿Está arriba? ¿O está en la taberna?";
					link.l1.go = "PZ_HelenaIslaTesoroGood1";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
					else sTemp = "Steve";
					
					dialog.text = "¡Charles! Y... Ah, qué agradable sorpresa. ¿Qué puedo hacer por ustedes dos?";
					link.l1 = "Hola, Helen. ¿Dónde está "+sTemp+"¿?";
					link.l1.go = "PZ_HelenaIslaTesoroGoodMaryHere1";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
				else sTemp = "Shark";
				
				dialog.text = TimeGreeting()+"Charles. ¿Qué te trae por aquí?";
				link.l1 = TimeGreeting()+", Helen. Estoy buscando el "+sTemp+"¿Sabes dónde está?";
				link.l1.go = "PZ_HelenaIslaTesoroBad1";
			}
		break;
		
		case "PZ_HelenaIslaTesoroGood1":
			dialog.text = "Está fuera, pero me temo que se ha ido por mucho tiempo - al mar, para ser precisos.";
			link.l1 = "Maldita sea. ¿Pasó algo? ¿Dijo cuándo volvería?";
			link.l1.go = "PZ_HelenaIslaTesoroGood2";
		break;
		
		case "PZ_HelenaIslaTesoroGood2":
			dialog.text = "No lo hizo, pero no es nada serio - tiene una buena pista, como de costumbre. Generalmente regresa en un mes, dos como máximo. Sé cómo es, a veces yo mismo extraño la cubierta del barco...";
			link.l1 = "Siempre puedes ir al mar. Sería agradable hacerlo juntos alguna vez - tú en el 'Arcoíris', yo en el...";
			link.l1.go = "PZ_HelenaIslaTesoroGood3";
		break;
		
		case "PZ_HelenaIslaTesoroGood3":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodBlock";
			
			dialog.text = "Lo haría. Pero a tu... novia puede que no le guste. Y no quiero ser el tercero en discordia.";
			link.l1 = "Eh, lo siento, Helen, no quería ofenderte. Gracias por la charla. Hasta luego.";
			link.l1.go = "Exit";
		break;
		
		// Синистра, не забудь снять эту заглушку и вернуть дефолтную после этого этапа, плиз
		case "PZ_HelenaIslaTesoroGoodBlock":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodBlock";
			
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
			else sTemp = "Steve";
			
			dialog.text = "Charles, has vuelto. ¿Hay algo más en lo que pueda ayudarte?";
			link.l1 = "No, gracias, Helen. Solo quería comprobar si "+sTemp+" apareció.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaIslaTesoroBad1":
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Tyrex";
			else sTemp = "Steven";
			
			dialog.text = " Me sorprendería si vinieras a buscarme. En cuanto a "+sTemp+", está en el mar.";
			link.l1 = "¿Oh, de verdad? ¿Te dijo cuándo volvería?";
			link.l1.go = "PZ_HelenaIslaTesoroBad2";
		break;
		
		case "PZ_HelenaIslaTesoroBad2":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroBadBlock";
			
			dialog.text = "Aparentemente, está cansado de dirigir este sumidero y tiene que recordarse a sí mismo que todavía es capitán de un barco. No es la primera vez. Usualmente regresa en un mes, tal vez un mes y medio.";
			link.l1 = "Maldita sea, ¿así que los barones no siempre se quedan quietos así? Gracias, Helen. Adiós.";
			link.l1.go = "Exit";
		break;
		
		// Синистра, не забудь снять эту заглушку и вернуть дефолтную после этого этапа, плиз
		case "PZ_HelenaIslaTesoroBadBlock":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroBadBlock";
			
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
			else sTemp = "Steven";
			
			dialog.text = " "+sTemp+"Aún no ha vuelto, Charles";
			link.l1 = "Entiendo, solo estaba comprobando.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaIslaTesoroGoodMaryHere1":
			dialog.text = "Es un hombre libre, ¿verdad? Puede ir al mar cuando quiera.";
			link.l1 = "Por supuesto que puede. Entonces, ¿dónde está él?";
			link.l1.go = "PZ_HelenaIslaTesoroGoodMaryHere2";
		break;
		
		case "PZ_HelenaIslaTesoroGoodMaryHere2":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodMaryHereBlock";
			
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
			else sTemp = "the Shark";
			
			dialog.text = "Pero Charles, si no está en la isla, entonces ha ido a saquear a los españoles. Y ahora, si me disculpas, tengo mucho que hacer. Pasa de vez en cuando - normalmente, el "+sTemp+"   vuelve en aproximadamente un mes, a veces un poco más tarde.";
			link.l1 = "Bien, Helen, gracias. Nos mantendremos ocupados.";
			link.l1.go = "Exit";
		break;
		
		// Синистра, не забудь снять эту заглушку и вернуть дефолтную после этого этапа, плиз
		case "PZ_HelenaIslaTesoroGoodMaryHereBlock":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodMaryHereBlock";
			
			dialog.text = "No estoy de humor ahora mismo. Quizás vuelve en otro momento, ¿Charles?";
			link.l1 = "Claro, Helen. Perdona por molestarte. Cuídate.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_Longway_81":
			if (CheckAttribute(pchar, "questTemp.PZ_FlagMartinInfo"))
			{
				dialog.text = "Estamos en posición, Mi Señor Capitán. ¿Recuerda el camino?";
				link.l1 = "Por supuesto, Longway. Solo esperemos que no lo perdamos en ese maldito calabozo...";
				link.l1.go = "PZ_Longway_FlagMartinInfo_1";		//Sinistra
			}
			else
			{
				dialog.text = "Estamos en posición, Mi Señor Capitán. ¿Tienes un plan?";
				link.l1 = " Todavía estoy trabajando en ello... ¿Por qué, tienes algo en mente?";
				link.l1.go = "PZ_Longway_NotMartinInfo_1";		//Rebbebion
			}
			DelLandQuestMark(npchar);
			LAi_SetCheckMinHP(npchar, 1, true, "");		//На 6 эпизод даём Лонгвею бессмертие
			
			LocatorReloadEnterDisable("Tortuga_town", "houseS4", false);
		break;
		
		case "PZ_Longway_NotMartinInfo_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Bueno, supongo que si nos apresuramos a Chang Xing...";
			link.l1 = "Longway... Entiendo cuánto deseas ver a tu hermana, pero "+sStr+" está en peligro mortal ahora mismo, ¡y eso no es solo una figura retórica! Necesitas entender que salvarla es la primera prioridad.";
			link.l1.go = "PZ_Longway_NotMartinInfo_2";
		break;
		
		case "PZ_Longway_NotMartinInfo_2":
			dialog.text = "Mi Señor Capitán, dudo que realmente comprenda por lo que he estado pasando todos estos diez años. Por lo que estoy pasando ahora mismo.";
			link.l1 = "Sabes, de alguna manera, así es. Mi hermano está preso. Y aunque aún no le han hecho daño, en cualquier momento podrían hacerle lo que quieran.";
			link.l1.go = "PZ_Longway_NotMartinInfo_3";
		break;
		
		case "PZ_Longway_NotMartinInfo_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Pero ¿a dónde irías si solo fuera una dama "+sStr+" ¿quién necesitaba ser rescatado?";
			if (CheckAttribute(pchar, "questTemp.FMQT.GiveDiamonds") && !CheckAttribute(pchar, "questTemp.FMQT_ObchistilSunduk"))
			{
				link.l1 = "Hay un lugar... una persona... Pero no te preocupes por eso, Longway - tengo que manejarlo yo mismo.";
				link.l1.go = "PZ_GoMarceline1";
			}
			link.l2 = "En verdad, ni siquiera sé adónde ir. Si me pongo a husmear descuidadamente por todos lados, atraeré atención, y entonces "+sStr+"está definitivamente perdido. Así que... simplemente no sé.";
			link.l2.go = "PZ_GoTogether1";
		break;
		
		case "PZ_GoMarceline1":
			dialog.text = "¿Qué? ¿Por qué?";
			link.l1 = "No te dejarán entrar así como así - es la alta sociedad, maldita sea. Así que iré solo. Mientras tanto, tú ve con tu hermana. Me uniré a ti tan pronto como pueda. ¡Buena suerte, Longway!";
			link.l1.go = "PZ_GoMarceline2";
			RemovePassenger(pchar, npchar);
		break;
		
		case "PZ_GoMarceline2":
			dialog.text = "¡Aye! Gracias, Mi Señor Capitán. ¡Y buena suerte para usted también!";
			link.l1 = "Oh, gracias - lo necesito mucho hoy. Todos lo necesitamos.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_MarcelineLongwayGo");
		break;
		
		case "PZ_GoTogether1":
			dialog.text = "Mi Señor Capitán...";
			link.l1 = "No importa. Vamos a ver a tu hermana, Longway. Si nos separamos ahora, estamos muertos. Apresurémonos a ver a tu hermana y descubramos dónde está el escondite de Levasseur. Luego iremos juntos de nuevo, necesito toda la ayuda que pueda conseguir ahora. Espero que no sea demasiado tarde.";
			link.l1.go = "PZ_GoTogether2";
		break;
		
		case "PZ_GoTogether2":
			dialog.text = "No llegaremos tarde, Mi Señor Capitán. No demoremos más ni perdamos tiempo discutiendo. ¡Vamos a Chang Xing!";
			link.l1 = "Tienes razón, apresurémonos.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TogetherLongwayGo");
		break;
		
		case "PZ_FrenchSoldier1":
			dialog.text = "¿Adónde demonios vas? ¿Sabes siquiera a dónde lleva esa puerta?";
			link.l1 = "Lo sé perfectamente bien. Voy allí por negocios, no por curiosidad o para robar.";
			link.l1.go = "PZ_FrenchSoldier2";
		break;
		
		case "PZ_FrenchSoldier2":
			dialog.text = "¿Qué asuntos? Madame Levasseur no está disponible en este momento. Además, es una mujer casada; no está bien que la gente ronde por su casa.";
			link.l1 = "Casada, está bien. Pero ella tiene recepciones de vez en cuando, ¿eh? Incluyendo algunas privadas. Esta es una de esas veces. Me está esperando y tengo prisa.";
			link.l1.go = "PZ_FrenchSoldier3";
		break;
		
		case "PZ_FrenchSoldier3":
			dialog.text = "Me habría advertido si ese fuera el caso.";
			link.l1 = "Soy un tipo especial de invitado, del tipo que no necesita anuncios.";
			link.l1.go = "PZ_FrenchSoldier4";
		break;
		
		case "PZ_FrenchSoldier4":
			dialog.text = "¡Sí, el tipo de invitado que hará que Su Señoría ordene que me fusilen. O la misma Dama me despellejará!";
			link.l1 = " He sido huésped de Madame Marceline antes. Te aseguro, nada te pasará después, soldado.";
			link.l1.go = "PZ_FrenchSoldier5";
		break;
		
		case "PZ_FrenchSoldier5":
			dialog.text = "Pero claro, quedarse ciego y dejar entrar a todo el mundo, esa es la tarea de la guardia de la ciudad.";
			link.l1 = "No tengo tiempo para esto, mula terca...";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_FrenchSoldierFight");
		break;
		
		case "PZ_Marceline1":
			dialog.text = "Tú...";
			// начинаем проверять результат прохождения "Почти как дома"
			switch (pchar.questTemp.FMQT.Marceline)
			{
				// поделили алмазы и "охладили трахание, углепластики" (с)
				case "Fuck":
					link.l1 = "Oh sí, señora. Su caballero se complace en verla de nuevo. Veo que está sorprendida de verme. ¿No es mutua la alegría de este encuentro?";
					link.l1.go = "PZ_MarcelineFuck1";
				break;
				
				// поделили алмазы, без трахания и углепластиков
				case "NoFuck":
					link.l1 = "Sí, lo hice. Me doy cuenta de que puede que no sea el hombre más apuesto o digno de esta isla, como mencionaste durante nuestro último encuentro, pero al menos sabes que soy un hombre honesto. Escúchame, señora, no tomaré mucho de tu... precioso tiempo.";
					link.l1.go = "PZ_MarcelineNoFuck1";
				break;
				
				// "сошлись вот где-то посередине" (с)
				case "Deception":
					link.l1 = "Por el amor de Dios, cállese, señora, deje de gritar. No estoy aquí para vengarme de usted por engañar a su caballero y escapar con el tesoro del dragón. Y le aseguro, si quisiera matarla, simplemente le dispararía y huiría por mi vida. ¡Esto es Tortuga, después de todo! Pero creo que ya sabe que eso estaría por debajo de mí.";
					link.l1.go = "PZ_MarcelineDeception1";
				break;
			}
		break;
		
		case "PZ_MarcelineFuck1":
			dialog.text = "¡Oh, no! Pensé que... Bueno, ¡no importa! Verás, lenguas malvadas están esparciendo rumores sucios sobre mí, una pobre mujer que, aunque quisiera, no podría hacer daño a nadie ni defenderse de los enemigos. Además, ha pasado tanto tiempo... Pensé que venías a mí con malas intenciones, y no con buenas intenciones. Me alegra estar equivocada. Es difícil vivir cuando estás rodeada de malintencionados.";
			link.l1 = "¿Cómo podría hacerlo? Incluso si escuchara algo así, no creería ni una palabra. Pero tienes razón, no vine aquí solo para verte. Aunque me alegra haberlo hecho. Sé que esto sonará inusual, pero... esta vez tu caballero necesita tu ayuda, señora.";
			link.l1.go = "PZ_Marceline2";
		break;
		
		case "PZ_MarcelineNoFuck1":
			dialog.text = "Y eres mucho más sensible de lo que pensé. Sin embargo, no estás exento de fallas, Monsieur de Maure; esperaba que fueras más... refinado. De hecho... o siempre has sido así, o el Archipiélago ya te ha corrompido. Deberías volver a aprender a hablar con una dama. Pero tienes razón: eres un hombre honesto, aunque... sencillo.";
			link.l1 = "Y tú eres una mujer orgullosa y vengativa. Tus ojos, palabras y... acciones lo revelan. Así que si alguien me entenderá, eres tú. Tal como yo una vez te entendí. Así que no nos detengamos más en el pasado. ¿Puedes ayudarme, señora?";
			link.l1.go = "PZ_Marceline2";
		break;
		
		case "PZ_MarcelineDeception1":
			dialog.text = "Oh... Admito que fui cruel contigo en ese momento. ¡Pero solo porque no estaba completamente segura de ti, nada más! ¿Te habrías llevado todos los diamantes? ¿O habrías traído a mi esposo aquí, diciendo que aprendiste de nuestros sirvientes que le robé, negando tu parte en ello? Después de todo, todos buscan su favor, no el de una pobre mujer como yo... Ahora me doy cuenta de que estaba equivocada contigo. Por favor, acepta mis disculpas... mi caballero.";
			link.l1 = "No sé ahora si son sinceros o no. Pero no importa. Necesito tu ayuda, Madame Marceline. Es una cuestión de vida o muerte. Por favor, no te niegues.";
			link.l1.go = "PZ_Marceline2";
		break;
		
		case "PZ_Marceline2":
			dialog.text = "¿Mi ayuda...? Ciertamente no soy la última mujer del pueblo, pero mi influencia no es tan grande como todos creen. Soy una reina que reina, no que gobierna. Pero te escucharé. ¿Qué puede hacer mi humilde persona por ti?";
			link.l1 = "Me doy cuenta de que este es un tema desagradable para usted, pero estoy buscando a su marido, señora, y lo más pronto posible. El hecho es...";
			link.l1.go = "PZ_Marceline3";
		break;
		
		case "PZ_Marceline3":
			dialog.text = "¿Es una broma? ¿No está en la residencia en este momento? Entonces está fuera por asuntos de negocios. No puedo ayudarte, Monsieur de Maure.";
			link.l1 = "Desviaste la mirada. Tú sabes. Yo también lo sé. Solo necesito llegar allí. Por favor, no finjas que es la primera vez que oyes hablar del calabozo: eres demasiado inteligente para no saberlo.";
			link.l1.go = "PZ_Marceline4";
		break;
		
		case "PZ_Marceline4":
			dialog.text = "Oh, siento que esta conversación va a añadir otra cana a mi cabeza. Como si no tuviera ya suficientes primeras arrugas. ¿Qué rayos nos estás haciendo a todos, Francois...";
			link.l1 = "Un mechón gris sólo añadirá a tu nobleza y no te quitará tu belleza. Pero una buena y inocente chica ha caído en manos de tu esposo. ¡Y ahora corre el riesgo de perder su belleza, su salud y hasta su vida!... ¡Sabes lo que les ocurre a quienes quedan atrapados allí! Por favor, señora. Marceline... Ayuda a tu caballero.";
			link.l1.go = "PZ_Marceline5";
		break;
		
		case "PZ_Marceline5":
			dialog.text = "Ya no soy realmente tu caballero, ¿verdad? Vamos, no soy estúpida. Pero... te ayudaré, de Maure. Después de todo, no podía continuar para siempre. Y un día se habría hecho público. Lo que me importa ahora es salir a tiempo y de la manera correcta. Y... no puedo condenarte a un sufrimiento eterno causado por lo que mi ‘marido' hará a tu... conocido.";
			link.l1 = "Puede que ya no sea tu caballero, señora. Pero tampoco has sido mi dama desde el principio. Sin embargo, te estaré agradecido por el resto de mi vida. Entonces, ¿dónde está este lugar?";
			link.l1.go = "PZ_Marceline6";
		break;
		
		case "PZ_Marceline6":
			dialog.text = "Bueno, te tomaré la palabra, Charles. En las mazmorras de la ciudad. Hay un gran barril en uno de los callejones sin salida, y junto a él comienza un pasaje que lleva a la guarida de ese demonio. No miré dentro. Solo lo seguí una vez, hace mucho tiempo. Y me asusté cuando escuché los gritos inhumanos de esas pobres criaturas.";
			link.l1 = "Ha salvado muchas vidas hoy, señora. No solo la de mi querida, sino también todas aquellas que podrían haber caído ante su esposo en el futuro. Gracias.";
			link.l1.go = "PZ_Marceline7";
		break;
		
		case "PZ_Marceline7":
			dialog.text = "Ah, déjame con estas palabras vacías, monsieur. Me has pedido mucho. Y corrí un gran riesgo. Ahora intenta hacer que tu nueva misión en la guarida del dragón sea un éxito... mi caballero.";
			link.l1 = "Haré todo lo posible. Adiós, Marceline.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_MarcelineOver");
		break;
		
		case "PZ_ElitaShluha_18":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko") && !CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				dialog.text = "¿Así que es un bandido, monsieur...? No contratamos chicas nuevas así; todas vinimos aquí voluntariamente. Voy a tener que pedirle a usted y a su... cómplice que salgan. Y me aseguraré de que esta chica reciba tratamiento. ¡Si no, le denunciaré a las autoridades!";
				link.l1 = "Nosotros no somos bandidos. Pero esta muchacha está a la altura de cualquiera de ellos. No lleva una espada solo para lucirla. Está herida. Este hombre es amigo mío y también hermano de vuestra señora. Así que, dejadnos verla.";
				link.l1.go = "PZ_ElitaShluha_WithLongwayAndGirl1";
			}
			else
			{
				dialog.text = "¡Qué bueno verte de nuevo, monsieur! Pero sabes que no aceptamos invitados... de baja clase aquí. Incluso si tienen referencias y están pagados. Especialmente los trabajadores de piel amarilla o los esclavos negros. Me temo que tu amigo tendrá que irse.";
				link.l1 = "No digas eso delante de tu ama. Ella también tiene la piel amarilla. Y este no es un trabajador, sino su hermano. No interferirías en una reunión familiar, ¿verdad?";
				link.l1.go = "PZ_ElitaShluha_WithLongway1";
			}
		break;
		
		case "PZ_ElitaShluha_18_1":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko") && !CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				dialog.text = "Cada vez es peor. Primero el obrero amarillo loco y ahora tú. No, monsieur, no pagamos por las chicas que nos traen a la fuerza; todas están aquí por voluntad propia.";
				link.l1 = "Salvé a esta chica, y nunca trabajará en un lugar que esté por debajo de ella. ¿Un trabajador, dices?";
				link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithGirl1";
			}
			else
			{
				dialog.text = "Oh monsieur, ¡qué mal momento! Hoy no aceptamos más huéspedes - puedes ver por ti mismo lo que ha ocurrido aquí.";
				link.l1 = "Por eso estoy aquí. Fue un hombre de piel amarilla quien organizó todo esto, ¿verdad?";
				link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithoutGirl1";
			}
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithGirl1":
			dialog.text = "¡Sí, monsieur, un jornalero! ¡Apenas podíamos entender lo que decía! Este harapiento irrumpió y exigió ver a la dama. Nos aseguró que era su hermano. Llamamos a los hombres, pero...";
			link.l1 = "Ese no es un obstáculo para él. ¿Qué pasó entonces?";
			link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithGirl2";
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithGirl2":
			for (i = 1; i <= 4; i++)
			{
				sld = characterFromId("PZ_EliteBrothelMercenary" + i);
				sld.lifeday = 0;
			}
			
			dialog.text = "Resultó que no mentía. La dama salió a nuestro encuentro y lo reconoció. De hecho, todavía están hablando en su lujoso lugar.";
			link.l1 = "Quién sabe qué pasa por su cabeza, sin embargo. Vamos a entrar allí, la salvaremos si es necesario. No hagas un escándalo, destruirá la reputación del lugar.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_EliteBrothelCreateChangShin");
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithoutGirl1":
			dialog.text = "Así es, monsieur. Dijo que era el hermano de la dama.";
			link.l1 = "Y no lo dejaste entrar...";
			link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithoutGirl2";
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithoutGirl2":
			dialog.text = "¡Por supuesto que no! La dama está exquisitamente vestida y habla sin acento, a diferencia de ese trabajador. Intentamos ahuyentarlo, ¡y derribó a todos los guardias, ¿puedes imaginarlo?!";
			link.l1 = "Puedo imaginarlo fácilmente. ¿Y dónde está ahora?";
			link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithoutGirl3";
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithoutGirl3":
			for (i = 1; i <= 4; i++)
			{
				sld = characterFromId("PZ_EliteBrothelMercenary" + i);
				sld.lifeday = 0;
			}
			
			dialog.text = "Él y la dama todavía están hablando de algo, pero no podemos entender de qué se trata - probablemente en su propio idioma.";
			link.l1 = "Iré con ellos. Quizás su dama necesite ayuda. No llames a los guardias; si se hace público, nadie volverá a tocar a tu puerta.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_EliteBrothelCreateChangShin");
		break;
		
		case "PZ_ElitaShluha_WithLongway1":
			dialog.text = "¿Un hermano? La señora es digna, que es más de lo que puedo decir de este ‘hermano’ suyo. No hay necesidad de jugar con su cabeza o intentar estafarla con este jornalero. Llévenselo.";
			link.l1 = "Te dije que se perdieron hace mucho tiempo. Él es simplemente menos afortunado. Pagaremos el establecimiento nosotros mismos por nuestro tiempo. Avisa a la señora ahora.";
			link.l1.go = "PZ_ElitaShluha_WithLongway2";
		break;
		
		case "PZ_ElitaShluha_WithLongway2":
			dialog.text = " Ella no tiene nada de qué preocuparse contigo. Y no me gusta tu persistencia. ¡Chicos! ¡Echen a ese trabajador! ¡Y a su maestro equivocado también!";
			link.l1 = "¡Maldita sea! ¡Tanta arrogancia para una cortesana!";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_EliteBrothelFight");
		break;
		
		case "PZ_ElitaShluha_WithLongwayAndGirl1":
			dialog.text = "¡De ninguna manera! ¿Dejar a la señorita sola con toda esta extraña compañía suya? Solo si vas allí solo, monsieur. Y tus... amigos esperarán afuera - tenemos un establecimiento decente aquí.";
			link.l1 = "¿Por qué te preocupas por ella? Todo el mundo sabe que es una de las mejores espadachinas de Tortuga. Y mis amigos son más decentes que la mayoría de la gente en esta ciudad.";
			link.l1.go = "PZ_ElitaShluha_WithLongwayAndGirl2";
		break;
		
		case "PZ_ElitaShluha_WithLongwayAndGirl2":
			dialog.text = "¡Muchachos! ¡Hay un bandido herido y un obrero sucio aquí! ¡Quieren algo de nuestra señora! ¡Encárguense de ellos!";
			link.l1 = "Qué dedicación, maldita sea...";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_EliteBrothelFight");
		break;
		
		case "PZ_ChangShin1":
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
			
			// итак, снова проверка по результатам прохождения. Лонгвэй с нами, тян ещё в пыточной
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "¿Tengo entendido que eres Charles de Maure? Y esto... Oh.";
				link.l1 = "Y tú debes ser Belle Etoile. ¿O debería decir Chang Xing? Y sí, este es tu hermano. Te ha estado buscando durante más de una década. Él y yo tenemos muchas, muchas preguntas para ti. Y no mucho tiempo.";
				link.l1.go = "PZ_ChangShin_WithLongway1";
			}
			// пришли с Лонгвэем и тян
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom") && CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				dialog.text = "¡Dios mío, sobreviviste! Tienes un defensor bastante bueno, aunque llegó un poco tarde. Mejor que el que aparentemente me considera su protector y ahora está junto a ti. El cielo te favorece, querida niña.";
				link.l1 = "Veo que ya lo sabes. Eso es aún mejor, no hay necesidad de explicar. Pero dime, ¿de qué te ríes, Chang Xing? Te gusta ver sufrir a otras chicas, ¿verdad? Después de todo, las vendes.";
				link.l1.go = "PZ_ChangShin_WithLongwayAndGirl1";
			}
			// Лонгвэй с нами, тян на небесах
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom") && CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
				dialog.text = "Charles de Maure, ¿verdad? Escuché que querías verme. Entonces, ¿qué te preocupa? ¿No te gustó el servicio en nuestro establecimiento la última vez que estuviste aquí?";
				link.l1 = "Acabo de venir de otro establecimiento tuyo, Chang Xing. "+sStr+", mi amante, está muerto. Y sé que tú también jugaste un papel en ello.";
				link.l1.go = "PZ_ChangShin_GirlDied1";
			}
		break;
		
		case "PZ_ChangShin_WithLongway1":
			dialog.text = "Chang Xing... Hace mucho tiempo que no oigo ese nombre. Hace mucho tiempo. Gente blanca... siempre tienen prisa. ¿Qué tal una reunión familiar tranquila? Aunque no me importa. Dejé de depender de los demás hace años. ¿Por qué no dices nada, hermano mío? ¿No estás feliz de ver a tu propia hermana? Después de todo, me has estado buscando tan implacablemente.";
			link.l1 = "Tenemos otros asuntos urgentes y más importantes que atender. Habla con tu hermana, Longway. Pero recuerda adónde debemos ir. Necesitamos apresurarnos. Y también tengo preguntas para ella.";
			link.l1.go = "PZ_Longway_SisterDialog1";
		break;
		
		case "PZ_Longway_SisterDialog1":
			locCameraFromToPos(0.65, 2.59, -3.06, true, 0.23, 0.34, -5.21);
			
			sld = characterFromId("Longway");
			ChangeCharacterAddressGroup(sld, "Tortuga_brothelElite_room2", "goto", "goto8");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("PZ_ChangShin"));
			
			sld = characterFromId("PZ_ChangShin");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("Longway"));
			
			dialog.text = "(En mandarín) ¿Longway, eh? Bueno, aparte del nombre, no has cambiado mucho... Chang Tu.";
			link.l1 = "(En mandarín) Pero has cambiado mucho, hermana. ¿Qué sucedió? Tu mirada solía ser tan cálida como el sol del mediodía. Ahora es fría y no expresa más que desprecio. ¿Y tu voz? Solía encantarme hacerte reír y escuchar esas campanas plateadas sonando... Ahora es más fría que un Goango en invierno. Y llevas su ropa. Y vendes a las mujeres tú misma, aunque una vez fuiste secuestrada por Fermentelos.";
			link.l1.go = "PZ_Longway_SisterDialog2";
		break;
		
		case "PZ_Longway_SisterDialog2":
			dialog.text = "¿Vienes a sermonearme, aunque una vez trabajaste para Rodenburg, uno de los mayores canallas del archipiélago? ¿Crees que no sabía de ti? Siempre lo supe. No te corresponde juzgar en qué me he convertido y por qué, mi desorientado hermano mayor.";
			link.l1 = "Entonces déjame averiguarlo, ¡Xing! Y dime. Si sabías que estaba en el Archipiélago, ¿por qué no quisiste encontrarte conmigo después de todos estos años? He dedicado toda mi vida a buscarte...";
			link.l1.go = "PZ_Longway_SisterDialog3";
		break;
		
		case "PZ_Longway_SisterDialog3":
			dialog.text = "Porque ni tú ni el Cielo me protegieron del más terrible de los destinos. Entonces me di cuenta de que nadie en este mundo necesita a nadie más. Solo podemos confiar en nosotros mismos. Bueno, te lo diré si quieres saberlo. Pero hablaré en su idioma. Estoy seguro de que a él también le gustaría escucharlo. Entiendes francés, ¿no, Tu?";
			link.l1 = "(en francés roto): Sí, hablo ese idioma.";
			link.l1.go = "PZ_Longway_SisterDialog4";
		break;
		
		case "PZ_Longway_SisterDialog4":
			dialog.text = "Ja ja ja, ¡oh, cielo! Tu acento es terrible. Aunque no es tu culpa, la pronunciación y escritura francesa son realmente difíciles.";
			link.l1 = "Ríes diferente ahora, hermana...";
			link.l1.go = "PZ_ChangShin_WithLongway3";
		break;
		
		/*case "PZ_Longway_SisterDialog5":
			Return_LongwayOfficer();
			
			StartInstantDialog("PZ_ChangShin", "PZ_ChangShin_WithLongway3", "Quest\CompanionQuests\Longway.c");
		break;*/
		
		case "PZ_ChangShin_WithLongway3":
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
			dialog.text = "Mi querido hermano quiere saber qué me ha pasado a lo largo de los años. Creo que sería bueno que tú también escuches, ya que dijiste que tienes preguntas. Así que no te preocupes, te lo contaré todo en francés.";
			link.l1 = "Dime solo lo esencial: cuando Longway me contó su historia de vida, tomó unas buenas horas. Y ahora tengo prisa.";
			link.l1.go = "PZ_ChangShin_WithLongway4";
		break;
		
		case "PZ_ChangShin_WithLongway4":
			dialog.text = "Serás paciente. Lo guardé todo para mí durante más de un año. Y si interrumpes, no responderé a ninguna de tus preguntas.";
			link.l1 = "Está bien... Entonces sigue.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_ChangShin_WithLongwayAndGirl1":
			dialog.text = "¿Dónde están tus modales, Charles de Maure? Me dijeron que eras un hombre de magníficos modales y un modelo para los galanes. Solo rumores, pero en realidad... ¿un fracaso? Eso pensaba. Y te equivocas, odio a todos los hombres y mujeres por igual. De hecho, no confío en nadie, no me sorprendo, no espero nada. Con gusto aplastaría tus testículos si pudiera ponerte las manos encima. Pero oír mi verdadero nombre después de tantos años fue un poco... refrescante.";
			link.l1 = "Soy un galán para las damas, no para brujas como tú. Y de todos modos, ¿qué esperabas, considerando que estás involucrada en atormentar a la persona que más me importa? Apenas puedo contenerme de hacerte algo a ti también. No menos importante por su bien. Longway es mi amigo. Y tú eres su familia. Te ha estado buscando por más de una década. Y se merece hablar contigo.";
			link.l1.go = "PZ_ChangShin_WithLongwayAndGirl2";
		break;
		
		case "PZ_ChangShin_WithLongwayAndGirl2":
			dialog.text = "Qué sentimental. Y qué triste que no me importe. Pero no te vas a escapar tan fácilmente ahora, ¿verdad, tú? No por matarte y a todos ustedes por llegar tarde una vez. Pero saber... Supongo que sí mereces saberlo. Me conociste cuando no era así, hermano.";
			link.l1 = "No importa lo que te haya pasado... siempre tenías una elección, Chang Xing.";
			link.l1.go = "PZ_ChangShin_WithLongwayAndGirl3";
		break;
		
		case "PZ_ChangShin_WithLongwayAndGirl3":
			dialog.text = "Eres aún joven y no sabes cómo funciona el mundo, Charles de Maure. Solo hay una elección real en la vida: vivir o morir. Creo que también sería bueno que supieras todo. Así que contaré mi historia en francés. Lo hablas, ¿verdad, Tú?";
			link.l1 = "Con acento. Pero lo entiende muy bien. Puede comenzar.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_ChangShin_GirlDied1":
			dialog.text = "¿Y dónde has estado todo este tiempo? Española está a solo uno o dos días. Su muerte también es culpa tuya. Y tú. Llegas más de una década tarde. Nuestros salvadores, nuestros protectores. Cuanto antes aprenda una mujer a defenderse, mejor. Algunas lo hacen a tiempo, otras no. Y hay quien no tiene suficiente cerebro para entenderlo.";
			link.l1 = "Ten cuidado con cada palabra que digas a continuación. Aún no te he hecho pedazos solo por mi amigo, tu hermano. No tienes idea de lo que él pasó por ti.";
			link.l1.go = "PZ_ChangShin_GirlDied2";
		break;
		
		case "PZ_ChangShin_GirlDied2":
			dialog.text = "Dudo mucho que haya pasado por algo remotamente similar a lo que yo he pasado.";
			link.l1 = "Entonces cuéntanos.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_ChangShin2":
			dialog.text = "Bueno, ¿qué puedo decir? Era joven, estúpida y ingenua en aquel entonces. E intolerante. ¿Ya te contó Tu sobre cómo fui secuestrada por Oliverio Fermentelos después de que mató a mis padres y a mí?";
			link.l1 = "Así es.";
			link.l1.go = "PZ_ChangShin3";
		break;
		
		case "PZ_ChangShin3":
			dialog.text = "Me cortejó y confesó sus sentimientos, pero lo rechacé. Y fue entonces cuando masacró a nuestra familia y me secuestró. Y luego...";
			link.l1 = "Puedo adivinar.";
			link.l1.go = "PZ_ChangShin4";
		break;
		
		case "PZ_ChangShin4":
			dialog.text = "Ojalá pudieras. Luego me confesó sus sentimientos de nuevo, apasionado y entre lágrimas, diciendo que era la única manera, porque mi familia nunca me dejaría ir con él.";
			link.l1 = "Locura...";
			link.l1.go = "PZ_ChangShin5";
		break;
		
		case "PZ_ChangShin5":
			dialog.text = "Heh, una palabra para describir toda mi vida desde entonces. Lo rechacé de nuevo. Y así fue por un tiempo. Pero claramente, no podía durar para siempre, porque estaba completamente a su merced.";
			link.l1 = "¿Entonces sí sucedió?";
			link.l1.go = "PZ_ChangShin6";
		break;
		
		case "PZ_ChangShin6":
			dialog.text = "Por supuesto. Me tomó por la fuerza, brutal y despiadadamente. No es que eso le importe a los violadores, pero ¿acaso no me había confesado antes, entre lágrimas, su gran amor? ¡Pfft! El amor, al parecer, se había esfumado. Y todo esto continuaba día tras día como una rutina. Al principio, gritaba y me resistía, pero luego dejé de hacerlo - ¿cuál era el sentido de todos modos...?";
			link.l1 = "Pero Fermentelos recibió lo que merecía, y tú terminaste aquí. ¿Cómo sucedió eso?";
			link.l1.go = "PZ_ChangShin7";
		break;
		
		case "PZ_ChangShin7":
			dialog.text = "Bueno, pronto se hartó de mí. Es gracioso, ¿no? Mató a mis padres y a los de Tu, me robó, me deshonró regularmente, solo para desecharme al final. Vino a este Archipiélago y me vendió a Levasseur como esclava.";
			link.l1 = "No se lo desearía ni a mi enemigo. Entonces, ¿cómo sobreviviste? ¿Y cómo es que terminaste libre en primer lugar? Por lo que he escuchado, Levasseur nunca dejaba salir a las mujeres de su escondite. Siempre se deshacía de ellas.";
			link.l1.go = "PZ_ChangShin8";
		break;
		
		case "PZ_ChangShin8":
			dialog.text = "Así son las cosas ahora. Levasseur era diferente entonces. No, siempre fue un animal. Pero al principio, de vez en cuando secuestraba a jóvenes colonos locales, los violaba en su sótano y se deshacía de ellos casi inmediatamente para evitar pagar por su silencio. Rara vez los mantenía más de unos pocos días en aquellos años. Conmigo, en cambio, fue diferente desde el principio.";
			link.l1 = "Porque eras un esclavo, ¿verdad?";
			link.l1.go = "PZ_ChangShin9";
		break;
		
		case "PZ_ChangShin9":
			dialog.text = "Exactamente. El principal deseo de Levasseur no era solo el placer físico. Ni siquiera una sensación momentánea de poder sobre sus víctimas, pues lo tiene sobre toda la isla. Pero...";
			link.l1 = "... el placer de verlos romperse: su voluntad, su aspecto, su voz, su comportamiento.";
			link.l1.go = "PZ_ChangShin10";
		break;
		
		case "PZ_ChangShin10":
			dialog.text = "Sí. Veo que hiciste tus deberes, Capitán. Pero en ese sentido, no le resulté divertida - Fermentelos me trajo ya rota. Y Levasseur no me consideraba hermosa - no le gustan las mujeres asiáticas. Sabes, por alguna razón esto me ha afectado tanto - me doy cuenta de que soy atractiva, pero no creo que sea realmente hermosa. Y no lo creo cuando la gente me lo dice. Incluso ahora, cuando hago ejercicio, uso sedas, y me rocío con fino perfume. No es que necesite la aprobación de mi torturador, pero...";
			link.l1 = "Bueno, entonces repetiré mi pregunta una vez más: ¿cómo sobreviviste? Tan pronto como se aburre de una mujer, se deshace de ella. Contigo, se aburrió desde el principio, como dices.";
			link.l1.go = "PZ_ChangShin11";
		break;
		
		case "PZ_ChangShin11":
			dialog.text = "Supongo que el hecho de que lo aburriera desde el principio tuvo un efecto. Y el hecho de que yo fuera una esclava - no podía ir a ningún lado ni decir nada. Las esclavas han sido tratadas así durante miles de años. Empezó a pensar en cómo hacer que el tiempo que pasaba conmigo fuera 'divertido' para él.";
			link.l1 = "Supongo que así nacieron sus adicciones, en su forma actual.";
			link.l1.go = "PZ_ChangShin12";
		break;
		
		case "PZ_ChangShin12":
			dialog.text = "Exactamente. Al principio, eran las palizas, los escupitajos y otras humillaciones. Y las burlas, tanto de mi apariencia personal como de mi origen, de mi sangre. Y luego vinieron las primeras torturas: cuchillos, tenazas, una sartén... Por eso llevo ropa tan cerrada: todo mi cuerpo está lleno de cicatrices, quemaduras y mutilaciones. Y por eso nunca más planeo desnudarme frente a un hombre. Nunca más. Entonces finalmente entendí lo que debería haber comprendido cuando Fermentelos me secuestró.";
			link.l1 = "¿Qué fue eso?";
			link.l1.go = "PZ_ChangShin13";
		break;
		
		case "PZ_ChangShin13":
			dialog.text = "Que ya no debería ser una marioneta indefensa. Al contrario, debería tener el control de mi vida. En mi caso, una mujer solo puede cambiar su vida de alguna manera controlando a los hombres que la rodean.";
			link.l1 = "No diría que Levasseur puede ser controlado.";
			link.l1.go = "PZ_ChangShin14";
		break;
		
		case "PZ_ChangShin14":
			dialog.text = "Y no te equivocarías. Pero es posible influir en él con cuidado. Levasseur odia tanto la obediencia completa desde el principio como las discusiones o súplicas. También lo hace la adulación, al parecer dándose cuenta de qué cerdo era realmente. Esto lo comprendí de inmediato, a un costo bastante agonizante. Pero, cuando estaba satisfecho con todo después de otra noche de tortura y violencia, era posible hablar con él suavemente. Puede que no sea de noble cuna, pero no me falta inteligencia.";
			link.l1 = "¿Y de qué hablasteis?";
			link.l1.go = "PZ_ChangShin15";
		break;
		
		case "PZ_ChangShin15":
			dialog.text = "Desperté su interés. Sugerí ideas para la tortura, aconsejé qué dispositivos de tortura es mejor no usar y con cuáles vale la pena empezar. Al principio, por supuesto, lo probó todo conmigo. Pero luego... empezó a respetarme, a su manera retorcida. ¿Qué pasa por su cabeza? Intenté averiguar cómo llegó a ser así, pero volvió a golpearme casi hasta matarme. Luego trajo a un médico personal.";
			link.l1 = "Eso es aún más extraño y repugnante de lo que ya he oído sobre él.";
			link.l1.go = "PZ_ChangShin16";
		break;
		
		case "PZ_ChangShin16":
			dialog.text = "Ya no exigía que me entregara a él. Me llamaba alumna. Pero siempre decía que, como su proyecto, yo era una completa decepción. Supongo que para mantenerme alerta. Así que empezó a enseñarme esgrima e idiomas. Aunque me mantenía en el sótano, era yo, no su esposa, quien recibía todos los vestidos caros.";
			link.l1 = "Un proyecto sin duda. Puedes ver un claro paralelo con la forma en que manejas el lugar.";
			link.l1.go = "PZ_ChangShin17";
		break;
		
		case "PZ_ChangShin17":
			dialog.text = "No había pensado en eso, hmmm. Y no me gusta tu comparación, porque yo no torturo a mis empleadas. Y no dejo que mis clientes lo hagan. Aunque odio a esas zorras y envidio su belleza. Y no tengo nada en común con ese cerdo, recuerda eso.";
			link.l1 = "¿Cómo conseguiste este burdel?";
			link.l1.go = "PZ_ChangShin18";
		break;
		
		case "PZ_ChangShin18":
			dialog.text = "De Levasseur, por supuesto. Durante un tiempo, me mantuvo en su lugar. De vez en cuando, incluso pedía consejo sobre cómo quebrar a esta chica o aquella. Después de todo, yo era especial para él, aunque nunca lo admitiría. Yo fui la primera. Vi todo.";
			link.l1 = "¿Quién aprendió de quién, otra vez?";
			link.l1.go = "PZ_ChangShin19";
		break;
		
		case "PZ_ChangShin19":
			dialog.text = "¡No soy así! ¡Odio con toda mi alma a cualquiera que lo tuviera todo servido en bandeja! ¡No es justo! ¡Este burdel fue idea mía! Mis trabajadoras son hijas de comerciantes, funcionarios y nobles que a veces caían con Levasseur. Le pedí que me las diera. La tortura y la humillación en un sótano secreto es una cosa. Pero las actividades públicas de una cortesana para gente como ellos son algo completamente diferente.";
			link.l1 = "No diría que tus trabajadoras se ven tan humilladas, miserables y rotas.";
			link.l1.go = "PZ_ChangShin20";
		break;
		
		case "PZ_ChangShin20":
			dialog.text = "Porque saben lo que Levasseur o incluso yo les haríamos si se atrevieran a hacer el más mínimo ruido. Pero tienes razón en parte, por supuesto. El vino, la comida, las sedas, la falta de tortura diaria: muchos de ellos comenzaron a verme como un salvador. ¡Malditos idiotas! Solo unos pocos no están contentos de estar aquí. Algunos de ellos los entregó con el corazón apesadumbrado. Y se reiría, diciendo que siempre podría devolverle a cualquiera de ellos a cambio de resolver los problemas de dinero de mi lugar. Pero siempre dije que no. Al menos así traerían de vuelta el oro en lugar de morir en el sótano por nada. Sería una salida demasiado fácil para ellos.";
			link.l1 = "Qué lástima que no todos se sintieron humillados, cambiando los claustros peores que la Santa Inquisición por una jaula dorada como tu burdel...";
			link.l1.go = "PZ_ChangShin21";
		break;
		
		case "PZ_ChangShin21":
			dialog.text = "¿Me juzgas? No solo quería sobrevivir, sino construir un comercio exitoso. Aunque sin saberlo, Levasseur me estaba agradecido. Aun cuando ya no era una esclava, no podía dejarme ir. Todavía me forzaban a trabajar para él y ayudar a sus secuaces. Especialmente a su escuálido sobrino, que babeaba cada vez que me veía. Pero no se atrevía a atacarme ni a hablarme de mala manera. Asqueroso. Sabes, aunque me llamaba una decepción, era más útil que Thibaut y Martene juntos. Los acompañaba con bastante frecuencia bajo sus órdenes, como lo hice entonces en Port-au-Prince.";
			link.l1 = "Eso explica muchas cosas...";
			link.l1.go = "PZ_ChangShin22";
		break;
		
		case "PZ_ChangShin22":
			dialog.text = "Así es. Escucha. No torturé a tu amante. Al igual que no he torturado a ninguna chica con estas manos, aunque a veces haya dado consejos a Levasseur. Pero ya que estamos en el tema...";
			link.l1 = "¿Qué?";
			link.l1.go = "PZ_ChangShin23";
		break;
		
		case "PZ_ChangShin23":
			dialog.text = "Como también sabrás, Levasseur a veces exige que le traigan a cierta chica que fue vista en Tortuga, y luego dejó la isla. O alguien lo sorprendería y le traería a una desconocida para ganarse su favor, como fue mi caso. Secuestrar a tu amada fue idea mía.";
			link.l1 = "¿Qué acabas de decir...?";
			link.l1.go = "PZ_ChangShin24";
		break;
		
		case "PZ_ChangShin24":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Al principio, estábamos considerando capturar a esa rubia que solía estar tan cerca de ti. Pero como ahora es intocable, y como ya le hemos prometido una chica, la pelirroja debía bastar.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "He oído rumores sobre tu preciosa compañera que nunca se separa de tu lado. Teniendo en cuenta el amor de Levausser por las rubias, me costó muy poco venderle esta idea.";
			dialog.text = "Sotta, su chucho, se suponía que debía traerle al mulato, la esposa de Lutter. Pero mataste a Sotta, así que - nada de mulato para el grandullón. Levasseur estaba furioso. Todos recibieron una paliza - Thibaut, Martene, incluso yo. No sé quién me hizo enojar más: él, porque me golpeó de nuevo, o tú, que lo causaste..."+sStr+"";
			link.l1 = "Así que ni siquiera es por él... Tú hiciste esto.";
			link.l1.go = "PZ_ChangShin25";
		break;
		
		case "PZ_ChangShin25":
			dialog.text = "No espero siquiera tu perdón, y, además, no lo necesito. Si quieres sangre, tendrás sangre. Y lo lamentarás mucho. Pero no rechazaré la comprensión. Podría usarla por primera vez en largos diez años. Todo lo que hice fue hacer lo mejor para salir de Tortuga algún día. ¿Tienes alguna pregunta para mí, Charles de Maure?";
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo") && !CheckAttribute(pchar, "questTemp.PZ_FlagMarselinaInfo") && !CheckAttribute(pchar, "questTemp.PZ_FlagMartinInfo"))
			{
				link.l1 = "Pero estabas involucrado en el secuestro. Y sabes dónde Levasseur guarda a sus víctimas. Dime dónde está. Y si lo peor no ha pasado, pensaré seriamente en no tomar represalias contra ti.";
				link.l1.go = "PZ_ChangShinDontKnow1";
			}
			else
			{
				link.l1 = "Bueno, por fin todo está encajando...";
				link.l1.go = "PZ_ChangShin26";
			}
		break;
		
		case "PZ_ChangShinDontKnow1":
			dialog.text = "Lo sé porque estuve allí. Y si tienes la impresión de que estoy mutuamente y malsanamente apegado a él, estás muy equivocado. Me alegraría ver a alguien poner a ese cerdo en un asador.";
			link.l1 = "No tengo tiempo, Chang Xing. ¿Dónde está?";
			link.l1.go = "PZ_ChangShinDontKnow2";
		break;
		
		case "PZ_ChangShinDontKnow2":
			dialog.text = "¿Conoces la mazmorra local bajo las calles de la ciudad? Ahí es a donde vas. En uno de los callejones sin salida hay un gran barril de vino, y junto a él comienza un pasaje secreto hacia su sala de placeres, como a veces la llama.";
			link.l1 = "Bueno, finalmente todo está encajando...";
			link.l1.go = "PZ_ChangShin26";
		break;
		
		case "PZ_ChangShin26":
			if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") && CheckAttribute(pchar, "questTemp.PZ_FlagShip")) StartInstantDialog("Longway", "PZ_Longway_SisterDialog6", "Quest\CompanionQuests\Longway.c");
			else
			{
				dialog.text = "Bien por ti. Ahora vete. Por mucho que quisiera hablar después de tantos años, darme cuenta de que conoces todos mis secretos, sabes lo que me hicieron, es repugnante. Verte solo me enfurece ahora. Ah, y Tu se queda conmigo.";
				link.l1 = "¿Por qué es eso?";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet1";
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet1":
			dialog.text = "¿Quizás porque soy su familia? Y porque veo cómo es contigo: un murmurador abatido y miserable que ni siquiera ha tenido tiempo de aprender bien el idioma y empezar a hablar correctamente. Sin embargo, me dijo que ustedes dos eran amigos. Está claro cómo lo has influenciado. Al menos haré de él un hombre.";
			link.l1 = "¿Y estás realmente contento contigo mismo? ¿En qué lo convertirás? ¿En una criatura cruel y amargada que comercia con vidas?";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet2";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet2":
			StartInstantDialog("Longway", "PZ_Longway_SisterDialog_Ubezhdaet3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet3":
			if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") || CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
			{
				dialog.text = "Mi Señor Capitán, por favor deténgase. Le pido que deje a mi hermana en paz. Y... me quedaré con ella.";
				link.l1 = "¿Tú... qué? Longway... pero, ¿por qué? ¿No puedes ver en qué se ha convertido?";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet4";
			}
			else
			{
				dialog.text = "¿Eres diferente? Has cambiado con el tiempo. Para peor. Al principio, eras educado y comprensivo. Pero luego te volviste grosero, incluso más grosero que Rodenburg. Y cuando necesitaba un buen barco para atrapar a Van der Vink, ¡me diste una porquería!";
				link.l1 = "Longway...";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet8";
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Una vez zarpé y pasé todos estos años solo para encontrar y salvar a mi hermana. Y ahora ella está aquí y a salvo. Mi misión está completa. Y... Mi nombre es Chang Tu. Longway es el nombre que me dio el traidor Van Merden, por si lo has olvidado. Pero Chang Tu es un hombre libre. El largo viaje de Chang Tu finalmente ha terminado.";
			link.l1 = "Te convertirá en un sirviente como una vez lo hizo Rodenburg. Te presionará porque eres de la familia. ¿Y te pondrás tan fácilmente del lado de quien me causó a mí y "+sStr+"¿tanto dolor?";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet5";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet5":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Ahora mismo, eres tú quien presiona a Chang Tu. Por favor, déjame ir. Estoy muy cansado. Eres un buen hombre, Capitán - el Cielo puede dar fe de eso. Pero no eres mi familia. Ella sí lo es. Si no me quedo, entonces todos estos años habrán sido en vano. Ahora seré su estrella guía y reavivaré su fuego apagado - cálido y reconfortante, no quemando todo lo que toca.";
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				link.l1 = "Hmm, tienes razón. Tal vez estoy presionando demasiado en este momento. Bueno, siempre te he respetado. Te deseo un esperado reencuentro familiar con tu hermana. Pero te advierto, no encontrarás paz con ella.";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet6";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko") && !CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva")) 
				{
					pchar.questTemp.PZ_LongwayHochetMira = true;
					link.l1.go = "PZ_Longway_SisterDialog_ReactiaDevushek";
				}
				
			}
			else
			{
				link.l1 = "¡No puedes dejarme ahora! Todavía necesito salvar "+sStr+"¡de Levasseur! ¿Quieres que vaya allí sola? Ayúdame, Longway. Y luego te dejaré ir. Te lo prometo.";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet6";
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet6":
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				dialog.text = "Puedo manejarlo. No necesitas preocuparte más por mí. Gracias.";
				link.l1 = "   Parece que tu hermana está enojada porque hemos decidido separarnos pacíficamente.  ";
			}
			else
			{
				dialog.text = "Lo descubrirás, Mi Señor Capitán. Eres el hombre más inteligente que jamás he visto. Puedes manejar fácilmente a ese gusano que solo está acostumbrado a atormentar mujeres. Te lo suplico, no me obligues. ¡Mi hermana tiene tanto que contarme! Y... mi nombre es Chang Tu.";
				link.l1 = "¡¿Te das cuenta de que al dejarme ahora, me estás traicionando?! ¡Sobre todo por quedarte con ella, la mujer que comenzó todo esto!";
			}
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet7";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet7":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				dialog.text = "No temas, Capitán. Aunque hable de mí sin respeto, soy el hermano mayor y su último pariente varón. Puedes irte. No dejaré que te mate. Adiós.";
				link.l1 = "Adiós... Chang Tu.";
				DeleteAttribute(pchar, "questTemp.PZ_LongwayRyadom");
				AddDialogExitQuest("PZ_BrothelTeleportVZal");	//Мирно разошлись
			}
			else
			{
				dialog.text = "He dicho todo lo que tenía que decir. Adiós, Capitán. Y buena suerte para usted. Chang Tu siempre será un hombre libre. No lo olvide.";
				link.l1 = "¿Y esto es lo que obtengo después de que renuncié a todo y te ayudé en tu búsqueda?! ¿Después de lo que le están haciendo a "+sStr+"¿¡Ahora?! Eres un traidor, Chang Tu. Y morirás como tal, los dos, ¡malditas serpientes!";
				link.l1.go = "exit";
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				AddDialogExitQuest("MainHeroFightModeOn");
				AddDialogExitQuest("PZ_ChangShinAndLongwayFightMe");
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet8":
			dialog.text = "Mi nombre es Chang Tu. Longway está muerto. Tú lo mataste. Ya no eres mi Capitán. Y ahora morirás. Mi familia finalmente encontrará la paz, y nuestra estrella brillará intensamente en el cielo nocturno.";
			if (IsCharacterPerkOn(pchar, "Trustworthy") && GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 85)
			{
				link.l1 = "(Confiable) (Liderazgo) Longway... Chang Tu. Detente. Sé que no fui el Capitán perfecto para ti. Pero, ¿realmente deseas matarme tanto por esto? ¿Después de todo lo que hemos pasado? Primero Rodenburg, ahora la búsqueda de tu hermana.";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet9";
				notification("Trustworthy", "Trustworthy");
				notification("Skill Check Passed", SKILL_LEADERSHIP);
			}
			else
			{
				link.l1 = "Longway, soy tu Capitán. No soy tu familia ni tu niñera. Yo doy órdenes, sin preocuparme si te he insultado sin querer. Estás haciendo demandas como si fuéramos viejos cónyuges, por Dios...";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet15";
				if (!IsCharacterPerkOn(pchar, "Trustworthy")) notification("Perk Check Failed", "Trustworthy");
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 85) notification("Skill Check Failed (85)", SKILL_LEADERSHIP);
			}
			link.l2 = "Sí. Ahora lo veo. Eres igual de escoria podrida que solo se preocupa por sí misma... Longway. Igual que tu hermana. Mi familia sobrevivirá al día. La tuya - no. ¡Vete al infierno!";
			link.l2.go = "PZ_Longway_SisterDialog_Ubezhdaet8_1";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet8_1":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetFightMode(pchar, true);
			DoQuestCheckDelay("PZ_ChangShinAndLongwayFightMe", 0.5);
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet9":
			dialog.text = "Si la elección es entre tú y mi familia, todavía elijo a la familia, aunque sea una elección difícil.";
			link.l1 = "¿Una familia que no movió un dedo mientras tú la buscabas todos estos años? ¡Oh, pero entonces llegó el momento adecuado! En cuanto a mí, renuncié a todo para ayudarte. Tú, aquí mismo, eres el resultado de eso. Maldición, ¡soy más familia para ti que ella, amigo mío!";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet10";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet10":
			dialog.text = "Tienes razón. Como siempre, tienes razón. ¿Me perdonará, Mi Señor Capitán?";
			link.l1 = "¡No hay nada que perdonar! Tienes razón en algo: no siempre fui el Capitán que mereces. Supongo que ahora estamos a mano. Por cierto, ¿cómo prefieres que te llame de ahora en adelante? ¿Longway? ¿O es Chang Tu?";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet11";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet11":
			dialog.text = "Que sea Longway. Ya estoy acostumbrado a que me hables así.";
			link.l1 = "Entonces olvidemos todas las discrepancias y bienvenido a bordo de nuevo, Longway.";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet12";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet12":
			StartInstantDialog("PZ_ChangShin", "PZ_Longway_SisterDialog_Ubezhdaet13", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet13":
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			dialog.text = "¡¿Tú! ¿Qué estás diciendo?! ¡¿Por qué te detuviste?! ¡Mátalo! ¡Siempre serás solo un peón para él! ¡Tu familia soy yo y solo yo!";
			link.l1 = "Está tan enfadada, ¿verdad, Longway? Ya no eres de su familia, Xing. Eso terminó cuando supiste de la llegada de Longway al Archipiélago y decidiste ignorarlo. Nos vamos.";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet14";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet14":
			dialog.text = "Supongo que nunca tuve una verdadera oportunidad de erradicar esa mentalidad de esclavo en él. No puedo salvarlo. Entonces los mataré a ambos yo mismo.";
			link.l1 = "Eres tú quien no puede ser salvado aquí. Sabes, fui demasiado comprensiva y perdoné demasiado contigo. Pero esto es aún mejor. Creo que incluso Longway se ha dado cuenta de la serpiente que eres. No te llorará demasiado.";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinFightWithLongway");
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet15":
			dialog.text = "¡Las bromas son inapropiadas ahora! ¡Escondes tu miedo y fracaso detrás de ellas! Lo cual solo me convence más. Defiéndete, de Maure. Porque Chang Tu no tiene intención de perdonarte.";
			link.l1 = "Lo siento que haya terminado así. Pero si es lo que quieres, que así sea. En ese caso, tampoco recibirás piedad de mí.";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinAndLongwayFightMe");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaDevushek":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) StartInstantDialog("Mary", "PZ_Longway_SisterDialog_ReactiaMary", "Quest\CompanionQuests\Longway.c");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) StartInstantDialog("Helena", "PZ_Longway_SisterDialog_ReactiaHelena", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayHochetMira"))
			{
				dialog.text = "Carlos, escucha...";
				link.l1 = "Helen?";
			}
			else
			{
				dialog.text = "Charles, Longway, deténganse...";
				link.l1 = "Helen, será mejor que te pongas detrás de mí ahora. Me sentiría más seguro si lo hicieras, por si nos atacan.";
			}
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena2";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena2":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayHochetMira"))
			{
				dialog.text = "Estoy tan cansada que apenas puedo mantenerme en pie. Sólo quiero salir de aquí. No vamos a arrastrar a Longway de vuelta al barco si no quiere venir, ¿verdad? Seré su navegante y primer oficial, mi Capitán. Con suerte, su más confiable y amada también. Además, tiene razón, no somos su familia. Lo es, para bien o para mal.";
				link.l1 = "¿Pero qué pasa con ella? Ella es la razón por la que te torturaron; todo fue idea suya. Y ella es la que te secuestró.";
			}
			else
			{
				dialog.text = "Pero no lo harán, ¿verdad? Vámonos ahora, eso es todo. Si esto es lo que piensa de nosotros después de todo lo que hemos hecho por él, no tiene sentido intentar cambiar su opinión. Las acciones hablan más fuerte que las palabras. Si quiere quedarse con su hermana, que lo haga.";
				link.l1 = "Helen, has sufrido tanto por su culpa...";
			}
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena3";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena3":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayHochetMira"))
			{
				dialog.text = "Deja a esa demonio con sus demonios. Pronto consumirán su alma. Y las nuestras merecen un buen descanso. Vámonos.";
				link.l1 = "Sí. Supongo que deberíamos. Vámonos de aquí, mi ángel. Y tú - Longway, o Chang Tu - adiós.";
			}
			else
			{
				dialog.text = "Pero no morí. Y lo peor no sucedió. Estoy aquí, contigo, y eso es lo que importa. Y Levasseur está muerto. Sin él, ella no es nada. Su lugar está perdiendo dinero y pronto se irá a pique. Y ellos se hundirán con él. Vamos, mi capitán. No hay nada más que hacer aquí.";
				link.l1 = "No discutiré, Helen.";
			}
			AddDialogExitQuest("PZ_BrothelTeleportVZal");		//Мирно разошлись
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena4":
			StartInstantDialog("Helena", "PZ_Longway_SisterDialog_ReactiaHelena5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena5":
			dialog.text = "¿A dónde vas?";
			link.l1 = "¿Qué, sorprendido de que no estemos deseando destripar a ti y a tu hermana, Longway? Esa es la diferencia entre nosotros. Y aún piensas que soy el malo... Pero bueno, mira. Si quieres matarme, eso significa que también tendrás que matar a Helen. Está herida, lastimada. ¿Realmente quieres hacer eso?";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena6";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena6":
			dialog.text = "Ajá.";
			link.l1 = "Puedo ver la duda en tus ojos, aunque guardes muchos rencores contra mí. Pero tomemos ambos ejemplo de Helen, ¿de acuerdo? Nadie en nuestra tripulación es más amable o indulgente que ella. Nos vamos. Y si queda algo de bondad o sentido en ti, no te interpondrás en nuestro camino.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena7";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena7":
			dialog.text = "Sé así. Me disculpo. Pero ya no eres mi Capitán.";
			link.l1 = "De alguna manera lo superaré. Le deseo a ti y a tu hermana lo mejor, a pesar de lo que ella ha hecho. Adiós, Longway.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_BrothelTeleportVZal");		//Мирно разошлись
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary":
			dialog.text = "Vamos, Charles, es hora de aplastar este motín.";
			link.l1 = "Dios sabe que no quería hacer eso... y aún no quiero hacerlo.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary2";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary2":
			dialog.text = "¿No lo harás? Charles, escúchame. Has hecho tanto por él, ¿y qué has recibido a cambio? ¡Traición y palabras desagradables, sí, ¿eh?! ¿Realmente vas a dejarlo pasar?";
			link.l1 = "No quiero derramar la sangre de Longway. No he olvidado que una vez fuimos amigos.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary3";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary3":
			dialog.text = "¡Al diablo con amigos así, son peores que los enemigos, sí, ¿eh?! Charles, mírame. Mira lo que me pasó por culpa de su hermana, que se burló, insultó y humilló en el camino a esta maldita isla!";
			link.l1 = "Mary, entiendo... estás muy, muy enfadada ahora mismo...";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary4";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary4":
			dialog.text = "¡Oh no, Charles, no estoy solo enfadada, no... ¡Estoy furiosa! Y no solo por lo que ese miserable bastardo te dijo. Mírame de nuevo, Charles, e imagina cuántas más chicas pasarán por esto si no ponemos fin a esto. Aquí y ahora.";
			link.l1 = "No harán daño a nadie más. Levasseur está muerto.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary5";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary5":
			dialog.text = "Charles, ¿realmente escuchaste la herejía que estaba soltando? Ella es tan responsable de lo que ocurrió en ese sótano como ese cerdo apestoso. Ahora mira a Longway - o como quiera que se llame ahora. ¡Mira qué rápido logró ponerlo de su lado, sí, ¿eh?! ¿Quién sabe qué otras ideas enfermas pondrá en la cabeza de ese traidor? ¿Crees que esa demonio tendrá muchos problemas en empujarlo por el camino de Levasseur? No pienses en lo que es ahora, Charles. Piensa en qué tipo de monstruo podría convertirse en un año... o incluso en un mes. Sabes que tengo razón, ¿no es así?";
			link.l1 = "Por mucho que me pese admitirlo, no tengo nada para contradecirte, Mary...";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary6";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary6":
			StartInstantDialog("PZ_ChangShin", "PZ_Longway_SisterDialog_ReactiaMary7", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary7":
			dialog.text = "¡Ja-ja-ja! Fascinante, qué espectáculo. No me había reído tan de corazón en mucho tiempo. Y tiene agallas, eso se lo reconozco.";
			link.l1 = "Cierra la boca, perra.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary8";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary8":
			dialog.text = "Eso es divertido, ¿verdad, de Maure? Me encantaría ver cómo Tu te derriba yo mismo. Y aquí tu mujer es tan sedienta de sangre como yo. Muy bien. No me quedaré de brazos cruzados; he entrenado con Levasseur y algunos de los peces gordos de Tortuga. Veamos qué dúo sale ganando.";
			link.l1 = "No tuviste un buen maestro. Y has enfadado a Mary. Estás acabado. Incluso si yo no estuviera aquí, tu dúo no tendría ninguna oportunidad contra ella.";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinAndLongwayFightMe");
		break;
		
		case "PZ_Longway_SisterDialog6":
			dialog.text = "Sí. Finalmente. ¿Puede Longway hablar con mi hermana otra vez, Mi Señor Capitán? No mucho tiempo.";
			link.l1 = "Por supuesto. Solo hazlo rápido - no tenemos mucho tiempo.";
			link.l1.go = "PZ_Longway_SisterDialog7";
		break;
		
		case "PZ_Longway_SisterDialog7":
			dialog.text = "Longway hágalo rápido.";
			link.l1 = "Bien.";
			link.l1.go = "PZ_Longway_SisterDialog7_1";
		break;
		
		case "PZ_ChangShin26":
			StartInstantDialog("СhangShin", "PZ_Longway_SisterDialog7_1", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog7_1":
			locCameraFromToPos(0.65, 2.59, -3.06, true, 0.23, 0.34, -5.21);
			
			sld = characterFromId("Longway");
			ChangeCharacterAddressGroup(sld, "Tortuga_brothelElite_room2", "goto", "goto8");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("PZ_ChangShin"));
			
			sld = characterFromId("PZ_ChangShin");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("Longway"));
			
			dialog.text = "¿Y qué era lo que querías decirme, hermano mío?";
			link.l1 = "Longway está muy decepcionado contigo, Xing.";
			link.l1.go = "PZ_Longway_SisterDialog8";
		break;
		
		case "PZ_Longway_SisterDialog8":
			dialog.text = "(En mandarín) ¿Por qué no hablas nuestro idioma si querías hablar de nuevo, Tú? ¿Te avergüenzas de él? Si yo fuera tú, estaría más avergonzado de tu acento.";
			link.l1 = "No. Longway no tiene secretos para Mi Señor Capitán. Ya no más.";
			link.l1.go = "PZ_Longway_SisterDialog9";
		break;
		
		case "PZ_Longway_SisterDialog9":
			dialog.text = "(en francés) Primero Rodenburg, ahora de Maure. Siempre necesitas un ‘monsieur’. No has logrado nada aquí en más de una docena de años. Ni siquiera puedes aprender ninguno de sus idiomas. ¡Y son mucho más simples que los nuestros! Si alguien es una decepción, eres tú.";
			link.l1 = "Pero no trafico con mujeres. No participo en su secuestro y tortura.";
			link.l1.go = "PZ_Longway_SisterDialog10";
		break;
		
		case "PZ_Longway_SisterDialog10":
			dialog.text = "¿Hablas en serio? ¿Debería enumerar las cosas que has hecho por Rodenburg? Lo que yo he estado haciendo sería un juego de niños en comparación.";
			link.l1 = "Tenía un propósito: encontrarte. Pero ni siquiera querías verme. Y cuando te encontré, encontré un monstruo, no la cálida estrella guía que una vez brilló en mi camino.";
			link.l1.go = "PZ_Longway_SisterDialog11";
		break;
		
		case "PZ_Longway_SisterDialog11":
			dialog.text = "¿Un monstruo? Bueno, quizás tengas razón. Ya no soy la chica alegre que conocías. Si hubiera seguido así, la vida me habría masticado y escupido. Tuve que hacerme mis propios dientes. Mi estrella se extinguió hace mucho tiempo. Pero sigo siendo tu hermana, Tú.";
			link.l1 = "No. Ya no eres mi hermana.";
			link.l1.go = "PZ_Longway_SisterDialog12";
		break;
		
		case "PZ_Longway_SisterDialog12":
			dialog.text = "¿Renunciando a mí tan fácilmente después de todos estos años? Je... Y quién sabe, tal vez seguiría siendo el mismo si hubieras llegado a casa a tiempo para matar a Fermentelos ese día.";
			link.l1 = "Tienes razón. En parte, también es mi culpa. Es mi responsabilidad. Y lo terminaré. Te liberaré de tu miseria. Pondré fin a esta miserable existencia.";
			link.l1.go = "PZ_Longway_SisterDialog13";
		break;
		
		case "PZ_Longway_SisterDialog13":
			dialog.text = "¿Realmente vas a matar a tu propia hermana, Chung Tu? No es que lo logres, pero el hecho es...";
			link.l1 = "Ya no eres mi hermana. Xing murió hace diez años. Y hoy es el día en que Chung Tu finalmente muere. De ahora en adelante y para siempre, mi nombre es... Longway.";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinFightWithLongway");
		break;
		
		case "PZ_Longway_FlagMartinInfo_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Primero, rescatamos a Chang Xing.";
			link.l1 = "¿Qué?! No parece que lo entiendas, amigo mío. Tu hermana no está en peligro inmediato, pero "+sStr+"es. ¿Y necesito recordarte que Chang Xing tiene tanta culpa de esto como Martene y Thibaut?";
			link.l1.go = "PZ_Longway_FlagMartinInfo_2";
		break;
		
		case "PZ_Longway_FlagMartinInfo_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "¡Eso no es cierto! Ella es...";
			link.l1 = "¿Tienes alguna idea de lo que podría estar haciendo Levasseur a "+sStr+" ¿mientras estamos aquí discutiendo?";
			link.l1.go = "PZ_Longway_FlagMartinInfo_3";
		break;
		
		case "PZ_Longway_FlagMartinInfo_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Pero Chang Xing es lo único que me queda, Capitán... Tu familia sigue intacta...";
			link.l1 = +sStr+" puede que no sea mi esposa, pero es tan querida para mí como mi propia familia.";
			link.l1.go = "PZ_Longway_FlagMartinInfo_4";
		break;
		
		case "PZ_Longway_FlagMartinInfo_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Chang Xing es mi última estrella guía, Capitán. Además, me debes por sacar esa confesión de Robert Marten.";
			if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") && CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
			{
				link.l1 = " Iremos tras tu hermana, te lo prometo. Pero Levasseur no la ha tocado en todo este tiempo. "+sStr+" está en un peligro mucho mayor que Chang Xing. Ayúdame a salvarla primero, y te estaré en una gran deuda.";
				link.l1.go = "PZ_Longway_FlagMartinInfo_VD1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") || CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
				{
					if (IsCharacterPerkOn(pchar, "Trustworthy") && GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 85)
					{
						link.l1 = "(Confiable) (Liderazgo) Iremos tras tu hermana, te lo prometo. Pero Levasseur no la ha tocado en todo este tiempo."+sStr+" está en un peligro mucho mayor que Chang Xing. Ayúdame a salvarla primero, y te deberé una muy grande.";
						link.l1.go = "PZ_Longway_FlagMartinInfo_VD1";
						notification("Trustworthy", "Trustworthy");
						notification("Skill Check Passed", SKILL_LEADERSHIP);
					}
					else
					{
						link.l1 = "¡Escúchame! Tu hermana está a salvo. Pero "+sStr+" ahora está en manos de un pervertido, ¡que podría estar torturándola en este mismo momento, o peor! ¿Crees que Levasseur permitiría que tu hermana fuese dueña de un establecimiento tan elegante si la tratara como a las otras pobres chicas en su calabozo?";
						link.l1.go = "PZ_Longway_FlagMartinInfo_netVD1";
						if (!IsCharacterPerkOn(pchar, "Trustworthy")) notification("Perk Check Failed", "Trustworthy");
						if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 85) notification("Skill Check Failed (85)", SKILL_LEADERSHIP);
					}
				}
			}
			link.l2 = "No perderé tiempo en discusiones inútiles. Cada uno de nosotros tiene sus propias prioridades. Sepáremonos de nuevo. Que mi Dios me ayude y el tuyo te ayude a ti.";
			link.l2.go = "PZ_Longway_FlagMartinInfo_Razdelimsya";
			link.l3 = "Tienes razón. Te debo una. Está bien, hazlo a tu manera. Además, sin ti, quizás no pueda lidiar con Levasseur y sus hombres. Pero si algo le pasa a "+sStr+" mientras tratamos con tu hermana...";
			link.l3.go = "PZ_Longway_FlagMartinInfo_IdemKSestreLongweya";
		break;
		
		case "PZ_Longway_FlagMartinInfo_Razdelimsya":
			dialog.text = "Gracias por entender, Mi Señor Capitán. ¡Buena suerte a usted!";
			link.l1 = "Y a ti, Longway.";
			link.l1.go = "PZ_Longway_FlagMartinInfo_SharleOdinVPodzemelie";
		break;
		
		case "PZ_Longway_FlagMartinInfo_IdemKSestreLongweya":
			dialog.text = "Las amenazas vacías son amenazas sin valor, Mi Señor Capitán. Debemos apresurarnos, para llegar a tiempo para todo.";
			link.l1 = "¡Espero que tu Dios lo escuche. Vamos!";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TogetherLongwayGo");
		break;
		
		case "PZ_Longway_FlagMartinInfo_netVD1":
			dialog.text = "Dejaré pasar eso por respeto, Mi Señor Capitán. Solo esta vez. La próxima vez te golpearé. Ahora voy tras mi hermana, con o sin tu aprobación.";
			link.l1 = "No perderé más tiempo discutiendo contigo, Longway. Al final, todos tenemos algo que valoramos más que cualquier otra cosa.";
			link.l1.go = "PZ_Longway_FlagMartinInfo_SharleOdinVPodzemelie";
		break;
		
		case "PZ_Longway_FlagMartinInfo_SharleOdinVPodzemelie":
			pchar.questTemp.PZ_DevushkaRanena_Legko = true;
			LAi_LocationDisableOfficersGen("Tortuga_Cave", true);
			DoQuestReloadToLocation("Tortuga_Cave", "reload", "reload2", "PZ_Etap6TortugaPodzemelie");
		break;
		
		case "PZ_Longway_FlagMartinInfo_VD1":
			dialog.text = "Mm-hmm, está bien, Mi Señor Capitán. Pero entonces debemos apresurarnos.";
			link.l1 = "Correcto. Gracias, Longway.";
			link.l1.go = "PZ_Longway_FlagMartinInfo_VD2";
		break;
		
		case "PZ_Longway_FlagMartinInfo_VD2":
			pchar.questTemp.PZ_LongwayRyadom = true;
			pchar.questTemp.PZ_DevushkaRanena_Legko = true;
			LAi_LocationDisableOfficersGen("Tortuga_Cave", true);
			DoQuestReloadToLocation("Tortuga_Cave", "reload", "reload2", "PZ_Etap6TortugaPodzemelie");
		break;
		
		case "PZ_TortureRoom_Levasser_1":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "Vaya, vaya, a quién diablos tenemos aquí... Maldita sea. Charles de Maure y su chucho de ojos rasgados.";
				link.l1 = "Solo hay un perro mestizo aquí. Si quieres verlo, mírate en el espejo, bastardo hugonote. O simplemente mira a tu sobrino. Aunque él se parece más a una rata sarnosa.";
				link.l1.go = "PZ_TortureRoom_Levasser_2";
			}
			else
			{
				dialog.text = "¡Te dije que no me molestes! Ah, Charles de Maure, jejeje. Qué persistente pequeña plaga.";
				link.l1 = "Así soy yo. Ahora cállate la maldita boca y...";
				link.l1.go = "PZ_TortureRoom_Levasser_1_1";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne") || CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo") || CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal")) Achievment_Set("ach_CL_130");
			}
			locCameraSleep(true);
			sld = CharacterFromID("Tibo");
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto2");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("Levasser"));
		break;
		
		case "PZ_TortureRoom_Levasser_1_1":
			dialog.text = "¡No estás en tu propio barco, cachorro! ¡En esta isla solo hay un hombre, y ese soy yo!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_Etap6TortugaPytochnaya9");
		break;
		
		case "PZ_TortureRoom_Levasser_2":
			StartInstantDialog("Tibo", "PZ_TortureRoom_Levasser_3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_3":
			dialog.text = "¡Cómo te atreves, escoria!";
			link.l1 = " ";
			link.l1.go = "PZ_TortureRoom_Levasser_4";
			sld = CharacterFromID("Tibo");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_4":
			StartInstantDialog("Levasser", "PZ_TortureRoom_Levasser_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_5":
			dialog.text = "¡Cálmate, sobrino! Monsieur de Maure está a punto de recibir una lección de buenos modales.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_Etap6TortugaPytochnaya9");
			sld = CharacterFromID("Tibo");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("Levasser"));
		break;
		
		case "PZ_TortureRoom_Levasser_6":
			if (!CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal"))
			{
				dialog.text = "¿Te di permiso para chillar?!";
			}
			else
			{
				dialog.text = "¿Dónde se ha ido todo ese fuego, eh, cosa bonita? Ah, creo que lo entiendo...";
			}
			link.l1 = "¡Déjala en paz, maldito bastardo!";
			link.l1.go = "PZ_TortureRoom_Levasser_7";
			LAi_SetActorType(npchar);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) LAi_ActorTurnToCharacter(npchar, CharacterFromID("Mary"));
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) LAi_ActorTurnToCharacter(npchar, CharacterFromID("Helena"));
		break;
		
		case "PZ_TortureRoom_Levasser_7":
			dialog.text = "Heh-heh-heh... Puedes gritarme e insultarme todo lo que quieras, pero veo cómo tiemblas como una hoja al viento. Veo el miedo en tus ojos. Tú y Henri tenéis eso en común. Sin ofender, sobrino.";
			link.l1 = "Tienes razón, es miedo. Pero no a ti, escoria.";
			link.l1.go = "PZ_TortureRoom_Levasser_7_1";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_7_1":
			dialog.text = "Por supuesto, por supuesto. Ya lo he oído todo antes - que no temes a nadie, de Maure. Ella me lo dijo. 'Oh, Charles vendrá, Charles me salvará... Charles esto, Charles aquello...' Bueno, Charles está aquí. Charles tiene un asiento en primera fila. Henri, haz que nuestro invitado se sienta cómodo.";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_8";
		break;
		
		case "PZ_TortureRoom_Levasser_8":
			StartInstantDialog("Tibo", "PZ_TortureRoom_Levasser_9", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_9":
			if (CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal"))
			{
				dialog.text = "No hay necesidad de eso, Tío. Me temo que has ido un poco demasiado lejos esta vez...";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "Tío, voy a necesitar tu ayuda con este...";
				}
				else
				{
					dialog.text = "¿Debería acabar con él, Tío, o dejar que observe primero?";
				}
			}
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_10";
			LAi_SetActorType(npchar);
			//LAi_ActorTurnToCharacter(npchar, CharacterFromID("Levasser"));
			LAi_ActorTurnToLocator(npchar, "goto", "goto8");
			locCameraFromToPos(-15.67, 2.57, -1.23, true, -17.49, 1.42, -3.26);
		break;
		
		case "PZ_TortureRoom_Levasser_10":
			StartInstantDialog("Levasser", "PZ_TortureRoom_Levasser_11", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_11":
			if (CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal"))
			{
				dialog.text = "¡No fui yo, fue Monsieur Caballero Blanco aquí quien tardó demasiado en venir al rescate. Parece que el espectáculo ha terminado, ja-ja-ja-ja!";
				link.l1 = "Dios, no...";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_TortureRoom_Levasser_DevushkaMertva");
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "Eso pensé. ¿Cómo lograste llegar a esta edad? Por cierto, la misma pregunta para ti, de Maure.";
					link.l1 = "¡No tienes idea de cuántas preguntas tengo para ti, carnicero!";
				}
				else
				{
					dialog.text = "Desearía que nuestra pequeña actuación tuviera público... Pero no creo que Monsieur Terco aquí nos dé ese placer.";
					link.l1 = "El único placer que alguien obtiene soy yo - ¡destripándote, carnicero!";
				}
				link.l1.go = "PZ_TortureRoom_Levasser_14";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				locCameraFromToPos(-16.74, 2.58, -0.51, true, -13.13, -0.72, 2.49);
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
			{
				locCameraFromToPos(-18.38, 1.77, 2.73, true, -20.53, 0.01, 0.32);
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
			{
				locCameraFromToPos(-16.97, 2.09, 3.98, true, -20.02, -0.17, 2.28);
			}
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Tibo"));
		break;
		
		case "PZ_TortureRoom_Levasser_12":
			dialog.text = "¡Vamos, adelante, recógela! ¡Ja-ja-ja!";
			link.l1 = "¡Malditos animales, haré que se arrepientan de haber nacido!";
			link.l1.go = "PZ_TortureRoom_Levasser_13";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_13":
			DialogExit();
			EndQuestMovie();
			locCameraSleep(false);
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			LAi_SetPlayerType(pchar);
			locCameraTarget(PChar);
			locCameraFollow();
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				sld = CharacterFromID("Longway");
				ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
				Return_LongwayOfficer();
				PlaySound("VOICE\Russian\hambit\Longway-02.wav");
			}
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("Levasser");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld = CharacterFromID("Tibo");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "PZ_TortureRoom_Levasser_DevushkaMertva5");
		break;
		
		case "PZ_TortureRoom_Levasser_14":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "¿Carnicero? Me considero más un artista, un pintor; por lo menos intentarías verlo como arte... Observa.\n¿Te gusta mi obra? Verdaderamente una de mis obras maestras. Para ser completamente honesto, prefiero a las rubias, pero ella... Al final, le perdoné ese feo color de cabello. No era solo el cabello - ¡la chica es como el fuego! Casi me quemo. ¡Luchó, mordió, gruñó como un animal salvaje! Me recordó a un salvaje de piel roja, con el que me divertí mucho, aunque no por mucho tiempo...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "¿Carnicero? Me considero más un artista, un pintor - al menos intenta verlo como arte... Observa.\nMira, aún no he terminado con ella - todavía hay mucho espacio vacío en este lienzo. No solo es hermosa, sino que es dura como una roca y fría como el hielo. Incluso tuve que sudar un poco para hacerla gritar. Aguantó hasta el final, solo para no darme el placer de escuchar su hermosa voz.";
			}
			link.l1 = "Liberala ahora, degenerado.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_Etap6TortugaPytochnaya13");
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_15":
			dialog.text = "¿A dónde crees que vas? Este pedazo de carne es ahora mi propiedad. Al igual que todo lo que lo rodea: esta ciudad, esta fortaleza... Yo soy Tortuga. Y tú y Poincy, ese viejo pavo apestoso, nunca podrán cambiar eso.";
			link.l1 = "Levasseur, tú...";
			link.l1.go = "PZ_TortureRoom_Levasser_16";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_16":
			dialog.text = "Es Signor de René de Buaduflé de Lettre para usted.";
			link.l1 = "No me importa un carajo. Desenvaina tu espada y muéstrame tu valía en una pelea - con un hombre, no con una chica indefensa.";
			link.l1.go = "PZ_TortureRoom_Levasser_17";
		break;
		
		case "PZ_TortureRoom_Levasser_17":
			dialog.text = "¡Y qué hombre eres! Pero tienes razón, yo mismo estoy cansado de tanta charla. Quiero volver con... mi dama. Pero te haré una última pregunta. ¿Cómo llegaste aquí? ¿Quién reveló la ubicación de este lugar? Solo un puñado de personas lo sabe.";
			if (CheckAttribute(pchar, "questTemp.PZ_FlagMartinInfo"))
			{
				link.l1 = "Tu amigo común, Martene, cantó como un ruiseñor. Aunque, en realidad, chilló más como un cerdo en un matadero...";
				link.l1.go = "PZ_TortureRoom_Levasser_FlagMartinInfo_1";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_FlagMarselinaInfo"))
			{
				link.l2 = "Tal vez sea mejor mantenerlo en secreto para ti. Me temo que podría herir tu ego, Signor de René... algo.";
				link.l2.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_1";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
			{
				link.l3 = "Una de tus víctimas, Levasseur.";
				link.l3.go = "PZ_TortureRoom_Levasser_FlagShinInfo_1";
			}
		break;
		
		case "PZ_TortureRoom_Levasser_FlagShinInfo_1":
			dialog.text = "¡Mentiroso, bribón! ¡Nadie sale de estos muros!";
			link.l1 = "Usa tu memoria, vamos. Había uno. Chang Xing.";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagShinInfo_2";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagShinInfo_2":
			dialog.text = "No puede ser. No ella. Algunas de mis ideas fueron engendradas por ese pequeño demonio. Oh-oh, nos enseñamos mucho mutuamente, jeje. ¿Ha decidido limpiar su conciencia al final? Lo dudo. Después de todo, lo borré todo de su mente hace mucho tiempo.";
			link.l1 = "Ahora voy a grabarte en seco. Una gota a la vez.";
			link.l1.go = "PZ_TortureRoom_Levasser_Bitva";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMartinInfo_1":
			dialog.text = "¡Y tú me llamas carnicero, miserable hipócrita! Je-je... Pero mientras él arda en el Infierno, no tengo nada que temer.";
			link.l1 = "Él te está esperando allí. Y tu bribón de sobrino también. No lo decepcionemos.";
			link.l1.go = "PZ_TortureRoom_Levasser_Bitva";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_1":
			dialog.text = "¿Qué tal si lastimo un poco más a este juguete? Le rajo el vientre o la garganta, y la veo desangrarse mientras tú tratas de llegar hasta ella...";
			link.l1 = "Lo que digas, Levasseur, lo que digas... Tu esposa te manda saludos. Y con ello, una reverencia de despedida.";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_2";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_2":
			dialog.text = "¿QUÉ?! Ja-ja... Maldita Marceline... ¡Maldita perra, perra, perra, perra!";
			link.l1 = "Ella lo es. Se merecen el uno al otro. Aunque ella tiene un poco más de cabeza, al menos a primera vista.";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_3";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_3":
			dialog.text = "Voy a poner su cabeza de gallina en una pica. Pero antes de eso... oh-oh, muchas, muchas cosas le pasarán a esa puta... Incluso dejaré que mi nuevo juguete descanse un poco. ¡Espera! Tengo una mejor idea. Se la prestaré a Henri. Por un tiempo, por supuesto.";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_4";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_4":
			StartInstantDialog("Tibo", "PZ_TortureRoom_Levasser_FlagMarselinaInfo_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_5":
			dialog.text = "¿De verdad? ¡Gracias, tío!";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_6";
			CharacterTurnByChr(npchar, CharacterFromID("Levasser"));
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_6":
			StartInstantDialog("Levasser", "PZ_TortureRoom_Levasser_FlagMarselinaInfo_7", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_7":
			dialog.text = "Merecerlo primero - échame una mano con este, ¿eh?";
			link.l1 = "Está a punto de perder el control.";
			link.l1.go = "PZ_TortureRoom_Levasser_Bitva";
			CharacterTurnByChr(npchar, CharacterFromID("Tibo"));
		break;
		
		case "PZ_TortureRoom_Levasser_Bitva":
			DialogExit();
			EndQuestMovie();
			locCameraSleep(false);
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			LAi_SetPlayerType(pchar);
			locCameraTarget(PChar);
			locCameraFollow();
			
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				sld = CharacterFromID("Longway");
				ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
				Return_LongwayOfficer();
				PlaySound("VOICE\Russian\hambit\Longway-02.wav");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = CharacterFromID("Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sld = CharacterFromID("Helena");
			LAi_SetImmortal(sld, true);
			
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("Levasser");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetCheckMinHP(sld, 1, true, "PZ_Etap6TortugaPytochnaya19");
			sld = CharacterFromID("Tibo");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		break;
		
		case "PZ_TortureRoom_Longway_1":
			dialog.text = "Señor Capitán... Longway ofrece sus condolencias. Hicimos todo lo que pudimos.";
			link.l1 = "No todo, ni mucho menos lo suficiente.";
			link.l1.go = "PZ_TortureRoom_Longway_2";
		break;
		
		case "PZ_TortureRoom_Longway_2":
			dialog.text = "Longway va a buscar a Chang Xing. ¿Vendrás conmigo?";
			link.l1 = "Sí, voy contigo, Longway. Pero recuerda, tu hermana también tuvo un papel muy activo en este sangriento espectáculo. Va a tener que esforzarse mucho para convencerme de que la perdone. Y tú no la ayudarás. Ahora vamos, es hora de terminar esto.";
			link.l1.go = "PZ_TortureRoom_Longway_3";
		break;
		
		case "PZ_TortureRoom_Longway_3":
			DialogExit();
			Return_LongwayOfficer();
			chrDisableReloadToLocation = false;
		break;
		
		case "PZ_TortureRoom_Devushka_1":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "¡Charles, lo sabía, sí, ¿eh?! ¡Sabía que vendrías! Siempre lo haces, ¿verdad?";
					link.l1 = "No quisiera probar eso por cuarta vez, Mary... Esos canallas, ellos...";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "¡Oh, mi Capitán, no te das cuenta de lo oportuno que eres. Esos... esos monstruos...";
					link.l1 = "Ya terminó, Helen. Está bien, ya todo terminó. Oh Dios mío, ¿qué te han hecho...";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "¡Charles, estás aquí! Lo sabía, lo sabía, sí, ¿eh?";
					link.l1 = "Estaba navegando a toda vela, huyendo por mi vida, Mary. Tú... ¿lo hicieron?..";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Mi Capitán... Estás aquí... Casi había perdido la esperanza...";
					link.l1 = "Vine tan rápido como pude, Helen. Lamento que haya tardado tanto.";
				}
				locCameraFromToPos(-15.32, 1.24, 1.31, true, -14.25, -1.00, -1.50);
			}
			link.l1.go = "PZ_TortureRoom_Devushka_2";
		break;
		
		case "PZ_TortureRoom_Devushka_2":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "No, Charles, no. Intentaron, pero los enfrenté lo mejor que pude. Por eso me golpearon tan fuerte... Por favor, Charles, salgamos de aquí... sí, ¿eh?";
					link.l1 = "Enseguida, querida. Una última cosa por hacer.";
					link.l1.go = "PZ_TortureRoom_Devushka_3";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "¡No lo hicieron, Charles! No lo hicieron. Lo demás sanará. Por favor, llévame lejos de aquí.";
					link.l1 = "Por supuesto, mi querida. Solo queda una cosa por hacer aquí.";
					link.l1.go = "PZ_TortureRoom_Devushka_3";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "No, Charles, no. Lo intentaron, pero llegaste justo a tiempo. Como aquella vez. ¿Cuántas veces van ya?";
					link.l1 = "No he llevado la cuenta, Mary. Y nunca lo haré.";
					link.l1.go = "PZ_TortureRoom_Devushka_2_1";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Llegaste... justo a tiempo. Lo peor no ocurrió. Ahora, por favor, salgamos de aquí. A cualquier parte.";
					link.l1 = "Levántate, Helen. Sube arriba. Tengo que encargarme de este canalla primero.";
					link.l1.go = "PZ_TortureRoom_Devushka_3";
				}
			}
		break;
		
		case "PZ_TortureRoom_Devushka_2_1":
			dialog.text = "Y no dejaré de contar. Ahora salgamos de este lugar, por favor.";
			link.l1 = "Por supuesto, querida. No hay nada más que hacer aquí. Excepto una cosa.";
			link.l1.go = "PZ_TortureRoom_Longway_3";
		break;
		
		case "PZ_TortureRoom_Devushka_3":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko")) AddPassenger(pchar, npchar, false);
			LAi_SetPlayerType(pchar);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) Return_MaryOfficer();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) Return_HelenaOfficer();
		break;
		
		case "PZ_TortureRoom_Levasser_18":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "Entonces, ¿qué, kha-kha, no tienes agallas, mocoso? Pídele a tu cerdo culo amarillo que te eche una mano... O hazlo tú mismo y así tendrás una razón para contarle a Poincy lo valiente que eres.";
				link.l1 = "Preferiría decirle a todos qué pedazo de mierda cobarde fuiste en su lugar.";
			}
			else
			{
				dialog.text = "¿Qué, de verdad quieres verme desangrar hasta morir? Lo estás disfrutando, ¿eh? Le contarás a tu mujer qué héroe eres. ¿Ves ese esqueleto allá arriba en la pared? La esposa del banquero de Santiago... Su hombre también pensaba que era un héroe, pero resultó ser solo un buen gritón - cuando lo giré en esa rueda...";
				link.l1 = "Podría arrastrar tu cadáver sobre eso, canalla, pero temo que no soportaría el peso de tu trasero.";
			}
			link.l1.go = "PZ_TortureRoom_Levasser_19";
		break;
		
		case "PZ_TortureRoom_Levasser_19":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "Cobarde? Oh, ja-ja, vamos...";
				link.l1 = "La crueldad no es lo opuesto a la cobardía. Pero alguien como tú no conocería la diferencia.";
				link.l1.go = "PZ_TortureRoom_Levasser_20";
			}
			else
			{
				dialog.text = "Eso es muy astuto. Recuerda mis palabras, de Maure: morirás igual que ese pez gordo, ronco por tus propios gritos y sordo por los llantos de tus...";
				link.l1 = "Arde en el infierno, escoria.";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_TortureRoom_Levasser_Mertv1");
			}
		break;
		
		case "PZ_TortureRoom_Levasser_20":
			dialog.text = "Sí, no soy mucho de filosofar, lo admito. ¿Ves ese esqueleto en la pared, de Maure? Eso es todo lo que queda de la esposa del banquero de Santiago. A él también le gustaba hablar en grande, pero todo eso se detuvo cuando empecé a enrollar su cuerpo en esa rueda. Todo lo que quedó fue su grito, que casi me dejó sordo...";
			link.l1 = "Terminemos con esto.";
			link.l1.go = "PZ_TortureRoom_Levasser_21";
		break;
		
		case "PZ_TortureRoom_Levasser_21":
			StartInstantDialog("Longway", "PZ_TortureRoom_Levasser_22", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_22":
			dialog.text = "Espera un momento, Mi Señor Capitán... No seas tan rápido.";
			link.l1 = "¿Qué pasa, Longway?";
			link.l1.go = "PZ_TortureRoom_Levasser_23";
		break;
		
		case "PZ_TortureRoom_Levasser_23":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "No lo mates. Demasiado simple. Merece algo peor.";
			link.l1 = "Estás enfadado por tu hermana, amigo mío. Y yo estoy furioso por lo que él le hizo a "+sStr+"... y lo que pudo haberle hecho a ella. Pero no soy un animal como él. Podría quemarlo con brasas de ese brasero, romperle los huesos en esa rueda... Podría encadenarlo y dejar que muera desangrado. Pero no puedo arriesgarme a que uno de sus secuaces lo salve. No puedo correr ese riesgo.";
			link.l1.go = "PZ_TortureRoom_Levasser_24";
		break;
		
		case "PZ_TortureRoom_Levasser_24":
			dialog.text = "Espera, Mi Señor Capitán. Eso no es lo que quise decir. Estoy hablando de Poincy.";
			link.l1 = "¿Qué hay de él?";
			link.l1.go = "PZ_TortureRoom_Levasser_25";
		break;
		
		case "PZ_TortureRoom_Levasser_25":
			dialog.text = "Piensa en cómo te recompensaría si le llevaras a este animal con vida. Te bañaría en doblones. Y esa escoria preferiría morir aquí que pudrirse en una mazmorra en Capsterville.";
			link.l1 = "Puede que tengas razón, Longway. Pero no sé qué pasó exactamente entre este canalla y el Caballero. Créeme, conozco a esta gente mejor que tú. Si todo se trata de dinero, como dicen, estos dos podrían llegar a un acuerdo. Poincy podría dejarlo ir, y otra sala como esta podría aparecer en alguna otra isla o en una de las ciudades del Viejo Mundo.";
			link.l1.go = "PZ_TortureRoom_Levasser_26";
			link.l2 = "No es mala idea, Longway. Sin embargo, dudo que el Chevalier sea tan generoso... No está en su naturaleza realmente. Pero para mí, no se trata del dinero de todos modos. ¡Levántalo! Y cura sus heridas para que no muera antes de tiempo.";
			link.l2.go = "PZ_TortureRoom_Levasser_28";
		break;
		
		case "PZ_TortureRoom_Levasser_26":
			StartInstantDialogNoType("Levasser", "PZ_TortureRoom_Levasser_27", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_27":
			dialog.text = "Pero primero, voy a por ti. Y tu compañero. No te tocaré, hombre de ojos estrechos, no vales mi tiempo.";
			link.l1 = "¿Ves, Longway? Todo esto tiene que parar ahora. Aquí y ahora.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_TortureRoom_Levasser_Mertv1");
		break;
		
		case "PZ_TortureRoom_Levasser_28":
			StartInstantDialogNoType("Levasser", "PZ_TortureRoom_Levasser_29", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_29":
			dialog.text = "Espera un minuto, Capitán, espera un minuto, kha-kha.";
			link.l1 = "¿Qué sucede, señor exgobernador?";
			link.l1.go = "PZ_TortureRoom_Levasser_30";
		break;
		
		case "PZ_TortureRoom_Levasser_30":
			dialog.text = "Mi llave está en algún lugar de esta habitación. Abre un cofre en mi oficina. Hay doscientos mil en plata y una buena espada. Si eso no es suficiente, en el dormitorio de mi esposa, en la cómoda, hay una colección de gemas caras.";
			link.l1 = "   Hmm, ¿y qué quieres a cambio?   ";
			link.l1.go = "PZ_TortureRoom_Levasser_31";
		break;
		
		case "PZ_TortureRoom_Levasser_31":
			dialog.text = "Una bala. Acábame. Aquí y ahora.";
			link.l1 = "¿Y qué hay del Chevalier de Poincy? He oído que son viejos amigos... ¿No quieres verlo?";
			link.l1.go = "PZ_TortureRoom_Levasser_32";
		break;
		
		case "PZ_TortureRoom_Levasser_32":
			dialog.text = "¡Al diablo con Poincy! Entonces, ¿aceptas o no?";
			link.l1 = "No realmente, Monsieur de... No quiero enumerar tu nombre completo.";
			link.l1.go = "PZ_TortureRoom_Levasser_33";
		break;
		
		case "PZ_TortureRoom_Levasser_33":
			dialog.text = "¿No es eso suficiente para ti? Bien, hay más...";
			link.l1 = "Los gritos de tus víctimas deben haberte dejado sordo, Levasseur. Te dije, no se trata del dinero. ¿Tienes razón para temer a Poincy, verdad? Ni siquiera quiero saber qué te hará. Pero si sirve como un poco de retribución por tu... arte, que así sea.";
			link.l1.go = "PZ_TortureRoom_Levasser_34";
			pchar.questTemp.PZ_LevasserPlenen = true;
			pchar.questTemp.PZ_LevasserPobezhden = true;
		break;
		
		case "PZ_TortureRoom_Levasser_34":
			dialog.text = "Así que eso es lo que realmente eres, ja-ja... No mejor que yo.";
			link.l1 = "Basta. ¡Longway, levántalo!";
			link.l1.go = "PZ_TortureRoom_Levasser_35";
		break;
		
		case "PZ_TortureRoom_Levasser_35":
			DialogExit();
			
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1 = "locator";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1.location = "Tortuga_Torture_room";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1.locator_group = "reload";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1.locator = "reload1";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition = "PZ_TortureRoom_Levasser_ObratnoNaBereg";
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) Return_MaryOfficer();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) Return_HelenaOfficer();
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom")) Return_LongwayOfficer();
			sld = CharacterFromID("Levasser");
			sld.location = "None";
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
				{
					dialog.text = "Nuestro barco... Nunca pensé que estaría tan contento de verla... sí, ¿eh? Al fin, esta pesadilla ha terminado.";
				}
				else
				{
					dialog.text = "Finalmente ha terminado. ¿A dónde ahora, Charles?";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
				{
					dialog.text = "No puedo creer que todo haya terminado... ¿Qué hacemos ahora, mi Capitán?";
				}
				else
				{
					dialog.text = "Bueno, eso es todo, mi Capitán. ¿Qué hacemos ahora?";
				}
			}
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
			{
				link.l1 = "Lamentablemente, aún no ha terminado. Chang Xing... Esta historia solo termina de verdad cuando obtenga respuestas de ella.";
				link.l1.go = "PZ_Etap6_NaBeregu_DevaZdorovaya_2";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
				{
					link.l1 = "Pon rumbo a Capsterville. Es hora de que Monsieur Levasseur pase a la historia.";
				}
				else
				{
					link.l1 = "La misión del Caballero está completa. Necesito informárselo. Sin embargo, omitiré algunos detalles. Solo espero que cumpla su palabra y libere a Michel...";
				}
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_Final_SdaemKvestPuansi");
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Yo también, sí, ¿eh? Así que voy contigo. Y ni siquiera trates de discutir conmigo, Charles.";
				link.l1 = "Mary, querida, necesitas descansar. Estás a punto de desmayarte...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Iré contigo.";
				link.l1 = "Helen, casi mueres a manos de ese demonio. Apenas puedes mantenerte en pie...";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaZdorovaya_3";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Te necesito, Charles. Y tú me necesitas. Y si alguien va a desmayarse esta noche, será Chang Xing. En el suelo de su burdel, con una bala entre los ojos.";
				link.l1 = "Sí, Levasseur no te quitó el espíritu combativo. Te enviaría de vuelta al barco, pero sé que de todos modos me seguirías...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Pero todavía puedo empuñar una espada. Charles, tengo que estar allí. Necesito entender qué la llevó a hacerlo. ¿Entiendes por qué esto es tan importante para mí?";
				link.l1 = "Entiendo que necesitas descanso y curación. Y un descanso prolongado, además.";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaZdorovaya_4";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Me conoces demasiado bien, Charles, sí, ¿eh? Así que dejemos la charla y terminemos con esto.";
				link.l1 = "Como quieras. Pero mantente alerta. Nadie sabe qué sorpresas nos esperan ahí afuera.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Puede esperar. Viniste por mí, y ahora voy contigo. Quieras o no.";
				link.l1 = "Veo que todavía tienes agallas, Helen. Bien. Quédate detrás de mí, y por el amor de Dios, ten cuidado.";
			}
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_SDevushkoyKShin");
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_1":
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "Nuestra nave... No puedo creer que vuelva a abordarla, sí, ¿eh?";
					link.l1 = "Te está esperando, Mary. Una comida abundante y una cama suave también...";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Uf... No pensé que llegaría al barco por mis propios pies.";
					link.l1 = "Eres la persona más resistente que he conocido, Helen. Ahora entra y luego ve a la cama...";
				}
				link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_2";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "Nuestra nave... No puedo creer que vuelva a abordarla, sí, ¿eh?...";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Uf... No pensé que llegaría al barco por mis propios medios.";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
				{
					link.l1 = "Pon rumbo a Capsterville. Es hora de que Monsieur Levasseur se convierta en parte de la historia.";
				}
				else
				{
					link.l1 = "La misión del Caballero ha sido completada. Necesito informárselo. Sin embargo, omitiré algunos detalles. Solo espero que cumpla su palabra y Michel sea liberado...";
				}
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_Final_SdaemKvestPuansi");
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Y tú, Charles... ¿Por qué esa mirada? Estás tramando algo otra vez, ¿verdad?";
				link.l1 = "Chang Xing. Debo llegar a ella también.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "¿Y tú? ¿A dónde vas?";
				link.l1 = "Para ver a Chang Xing. Ella es el último capítulo de esta pesadilla.";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_3";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "¡Entonces voy contigo! Ella me debe una grande, sí, ¿eh?";
				link.l1 = "Mary, querida, apenas llegaste al barco. Y no puedes sostener una espada ahora mismo. Haré que pague por lo que te ha hecho, lo juro por Dios. Pero me sentiré mucho mejor si te quedas en el barco, sabiendo que estás a salvo.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Mi Capitán, me gustaría mucho ir contigo... Por favor, ten cuidado. ¿Quién sabe de qué más es capaz? Ella me sujetó mientras ese cachorro Thibaut...";
				link.l1 = "Lo peor ya pasó, Helen. Todo terminará pronto, te lo prometo.";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_4";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "Bueno, al menos Longway te cubrirá las espaldas en mi ausencia. ¡Pero si algo te pasa, yo mismo enviaré a él y a Chang Xing al fondo del mar!";
					link.l1 = "Todo estará bien. Ahora ve a descansar. Volveré antes de que te des cuenta.";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_7";
				}
				else
				{
					dialog.text = "¿A dónde se ha ido Longway, Charles?";
					link.l1 = "Fue tras Chang Xing sin mí. No pude detenerlo, pero ¿qué podía hacer?";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_5";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "Bueno, al menos Longway va contigo. Es un consuelo, al menos.";
					link.l1 = "¿Ves? No hay necesidad de preocuparse. No tardaré mucho.";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_7";
				}
				else
				{
					dialog.text = "¿Dónde está Longway? Acabo de darme cuenta de que no está aquí.";
					link.l1 = "Fue a ver a su hermana sin mí. No lo culpo. Ha esperado demasiado por este momento.";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_5";
					
				}
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_5":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Charles, tengo un mal presentimiento sobre esto...";
				link.l1 = "Lo sé. Esta pesadilla ha durado demasiado, y el final está cerca. Lo peor ya pasó.";
				link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_6";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "¿Quién sabe lo que pasa por su mente, Charles? Mantén los ojos abiertos, sí, ¿eh?";
				link.l1 = "Lo haré. Volveré pronto, Helen."link.l1.go ="¿Cómo es que me has encontrado? ¡Pensé que estaba sola, sin esperanza! Gracias, Mi Señor Capitán. Nunca olvidaré esto.";
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_6":
			dialog.text = "Prométeme que estarás listo para cualquier cosa.";
			link.l1 = "Lo soy, y lo seré. Volveré pronto, Mary.";
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_7";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_7":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom")) StartInstantDialog("Longway", "PZ_Etap6_NaBeregu_DevaBolnaya_8", "Quest\CompanionQuests\Longway.c");
			else
			{
				DialogExit();
				LAi_SetPlayerType(pchar);
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = CharacterFromID("Mary");
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sld = CharacterFromID("Helena");
				LAi_ActorRunToLocation(sld, "reload", "sea", "", "", "", "", -1);
				sld.location = "None";
				AddQuestRecord("PZ", "51");
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) AddQuestUserData("PZ", "sText", "Mary");
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) AddQuestUserData("PZ", "sText", "Helen");
				PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition.l1 = "location";
				PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition.l1.location = "Tortuga_brothelElite";
				PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition = "PZ_Etap6_BrothelPoiskSestry";
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_8":
			dialog.text = "Longway te ayudó, Capitán. Ahora es tu palabra la que debes cumplir.";
			link.l1 = "Escuchaste todo, Longway. Vamos a ver a tu hermana.";
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_9";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_9":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Señor Capitán, Longway tiene una última petición: deja que Chang Xing se explique. Escúchala antes de tomar cualquier decisión.";
			link.l1 = "¿Qué le sucedió a "+sStr+" está sobre ella. Pero primero le daré la oportunidad de explicarse.";
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_10";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_10":
			dialog.text = "Longway confía en tu palabra, tu juicio y tu bondad.";
			link.l1 = "Compañero, no hay lugar para la razón o la bondad en este maldito lío. Y ya es hora de acabar con esto.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_SLongwayKShin");
		break;
		
		case "PZ_LongwayPrishelOdin":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sStr = "Helen";
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				dialog.text = "Mi Señor Capitán...";
				link.l1 = +sStr+"está muerto.";
				link.l1.go = "PZ_LongwayPrishelOdin2";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					dialog.text = "Capitán, señora "+sStr+", es un placer verte. Este es... Chang Xing.";
					link.l1 = "He adivinado, Longway. Retrocede. Has tenido mucho tiempo para hablar con tu hermana. Ahora ella debe responder a "+sStr+" por ayudar a los secuaces de Levasseur a secuestrarla.";
					link.l1.go = "PZ_LongwayPrishelOdin7";
				}
				else
				{
					dialog.text = "Has venido... ¿Dónde está la dama "+sStr+"¿Es ella...?";
					link.l1 = "No, Longway. Gracias a Dios, no. La llevé al barco. De lo contrario, ni siquiera estaría teniendo esta conversación ahora mismo. Sin embargo, aún no va a ser fácil ni agradable.";
					link.l1.go = "PZ_LongwayPrishelOdin12";
				}
			}
		break;
		
		case "PZ_LongwayPrishelOdin2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Chang Xing y yo ofrecemos nuestras condolencias...";
			link.l1 = "¿Condolencias de parte de Chang Xing?! ¡Podrías ofrecer condolencias en nombre de Levasseur, Longway! Sabes muy bien que ella participó en el secuestro de "+sStr+" junto con los otros sus secuaces! Y ahora ella se ha ido...!";
			link.l1.go = "PZ_LongwayPrishelOdin3";
		break;
		
		case "PZ_LongwayPrishelOdin3":
			dialog.text = "Nosotros... Entiendo lo que sientes ahora, Mi Señor Capitán.";
			link.l1 = "¿Oh, de veras?";
			link.l1.go = "PZ_LongwayPrishelOdin4";
		break;
		
		case "PZ_LongwayPrishelOdin4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Perdí a mis padres, como recordarás. Si es que recuerdas. Además, no fue Chang Xing quien torturó y mató "+sStr+"Entiendo tu dolor, tu furia. Pero la culpa de mi hermana no es tanta como para que la consideres. Por favor, escúchame.";
			link.l1 = "Lo recuerdo. Escucharé tu historia. ¡Pero hazlo rápido! Y sé que no puedo dejar que algo así quede sin castigo.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayPrishelOdin_ChangShinNext");
		break;
		
		case "PZ_LongwayPrishelOdin5":
			dialog.text = "Entonces será mejor que lo cuente todo de nuevo, Monsieur de Maure. Nuestro francés de Tu es tan malo que casi lo atacas.";
			link.l1 = "Deberías haber mantenido la boca cerrada. No iba a atacar a Longway, pero tú... Tú eres el responsable de su muerte.";
			link.l1.go = "PZ_LongwayPrishelOdin6";
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
		break;
		
		case "PZ_LongwayPrishelOdin6":
			dialog.text = "Discutiría eso, pero me doy cuenta de que preferiría no hacerlo. Tu hablaste de ti como una persona de respeto y comprensión. ¿Pero es realmente así? ¿Tiene sentido que empiece siquiera a hablar? ¿O ya has tomado una decisión?";
			link.l1 = "Sabes cómo meterte en la cabeza de alguien, mademoiselle. Realmente no vale la pena discutir ahora. Pero si quieres intentar justificarte... Bueno, adelante. Por el bien de Longway, te escucharé.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_LongwayPrishelOdin7":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Puede explicarlo todo, Mi Señor Capitán... No es lo que crees... No realmente...";
			link.l1 = "Entonces explícalo. Pero no a mí. "+sStr+"Mírala a los ojos. Mira sus moretones y heridas. Y dile que no fue así.";
			link.l1.go = "PZ_LongwayPrishelOdin8";
		break;
		
		case "PZ_LongwayPrishelOdin8":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Mis disculpas en nombre de Xing, Capitán...";
			link.l1 = "Por la sonrisa en su cara, parece que lo haces en vano. No merece tus disculpas.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayPrishelOdin_ChangShinNext");
		break;
		
		case "PZ_LongwayPrishelOdin9":
			dialog.text = "Está siendo demasiado duro con él, Monsieur de Maure. Aunque probablemente esté acostumbrado a tratarlo de esa manera, como a un típico trabajador de piel amarilla.";
			link.l1 = "¿Estás intentando poner a Longway en mi contra? No funcionará. Siempre lo he tratado con respeto, y él lo sabe. Eso es todo lo que importa. Me doy cuenta de que jugar juegos es lo único que te queda ahora.";
			link.l1.go = "PZ_LongwayPrishelOdin10";
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
		break;
		
		case "PZ_LongwayPrishelOdin10":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "¿Qué quieres hacer? ¿Llevarte al pobre Tu lejos de su familia? ¿Cuando finalmente los encontró de nuevo después de diez años?";
			link.l1 = "La sangre no siempre hace una familia. Pero, ¿qué sugieres que hagamos? ¿Dejar lo que le hiciste a "+sStr+" ¿Quedará impune? ¿Y que Longway visite de vez en cuando a una mujer que comercia con otras chicas sin dudarlo?";
			link.l1.go = "PZ_LongwayPrishelOdin11";
		break;
		
		case "PZ_LongwayPrishelOdin11":
			dialog.text = "Bueno, para empezar, escucha. A diferencia de él, puedo repetir lo que le acabo de decir en perfecto francés. Mi historia. Mirándote directamente a los ojos, o incluso a los de ella. Y todo eso sin el acento del que probablemente ya estás harto. Después de todo, ¿qué tenemos todos que perder?";
			link.l1 = "Estoy acostumbrado al acento de Longway; es parte de lo que significa para mí. Te escucharé, pero sólo por el bien de mi amigo. Continúa.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_LongwayPrishelOdin12":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "¿Por qué no, Mi Señor Capitán...?";
			link.l1 = "¿Realmente necesitas preguntar? Ella estuvo involucrada en el secuestro de "+sStr+", ¿verdad?";
			link.l1.go = "PZ_LongwayPrishelOdin13";
		break;
		
		case "PZ_LongwayPrishelOdin13":
			dialog.text = "Yo... sinceramente me disculpo. Es mi culpa también, por no haber podido salvar a mi hermana hace diez años, de mantenerla a salvo de todo esto.";
			link.l1 = "No deberías disculparte por aquellos que no tienen el más mínimo remordimiento, Longway. ¿Has terminado aquí? Es mi turno de hablar con ella.";
			link.l1.go = "PZ_LongwayPrishelOdin14";
		break;
		
		case "PZ_LongwayPrishelOdin14":
			dialog.text = "¡Mi Señor Capitán, espere! Chang Xing no es como Levasseur. No del todo. Ella me contará sobre su vida durante estos diez años. Déjame contártelo también.";
			link.l1 = "Está bien, Longway. Te escucho. Mucho depende de lo que me digas.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayPrishelOdin_ChangShinNext");
		break;
		
		case "PZ_LongwayPrishelOdin15":
			dialog.text = "Si eres tú quien lo cuenta, a todos nos dará dolor de cabeza. Permíteme, Tú. Charles de Maure, supongo.";
			link.l1 = "Correcto. Y tú eres Belle Etoile, también conocida como Chang Xing. Participaste en el secuestro de mi amada, junto con Thibaut y Martene. Y sonríes cuando lo menciono. ¿Recuerdos felices?";
			link.l1.go = "PZ_LongwayPrishelOdin16";
		break;
		
		case "PZ_LongwayPrishelOdin16":
			dialog.text = "Es estúpido negarlo. Pero, ¿qué importa ahora? ¿Vas a torturarme delante de mi hermano? ¿O incluso pedirle que te ayude a torturarme? ¿O simplemente me matarás? ¿Realmente le harías eso a él?";
			link.l1 = "Como dije, a pesar de todo lo que me gustaría hacer ahora mismo, todavía estoy hablando contigo. No insistas. Dime lo que le dijiste antes. Y luego veremos a dónde vamos todos desde ahí.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_Longway_91":
			if (!CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				dialog.text = "Aún no puedo creer que Chang Xing se convertiría en... esto.";
				link.l1 = "La gente cambia, Longway. Cualquiera puede ser quebrado o tener las últimas gotas de bondad y fe arrancadas de ellos.";
				link.l1.go = "PZ_Longway_ToGirl1";
			}
			else
			{
				dialog.text = "Longway todavía no puede creer que mi hermana se haya convertido en... esto. ¿Por qué... por qué? Si tan sólo hubiera estado en casa ese día...";
				link.l1 = "No te martirices con los 'qué pasaría si'. Además, no te quedaste de brazos cruzados todos esos años: te esforzaste muchísimo por arreglar las cosas.";
				link.l1.go = "PZ_Longway_ToShore1";
			}
		break;
		
		case "PZ_Longway_ToGirl1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Eh... Supongo que así es como es, Mi Señor Capitán.";
			link.l1 = "Salgamos de aquí. Todavía tenemos que limpiar el desorden que dejó atrás y salvar el "+sStr+" lo antes posible.";
			link.l1.go = "PZ_Longway_ToGirl2";
		break;
		
		case "PZ_Longway_ToGirl2":
			dialog.text = "Sí. Necesitamos darnos prisa - ya se ha retrasado demasiado por mi culpa.";
			link.l1 = "No es tu culpa, Longway. ¡Apresurémonos!";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LeaveEliteBrothel");
		break;
		
		case "PZ_Longway_ToShore1":
			dialog.text = "Bien. Gracias por tu apoyo, Mi Señor Capitán.";
			link.l1 = "No lo menciones. Ella no merecía tu dedicación de todos modos - no fue ella quien te buscó, incluso cuando pudo haberlo hecho. Tu estrella hace mucho que se ha apagado, y ella dejó de ser tu familia hace mucho tiempo. Nosotros somos tu familia ahora, Longway.";
			link.l1.go = "PZ_Longway_ToShore2";
		break;
		
		case "PZ_Longway_ToShore2":
			dialog.text = "Aye... Así es. Y yo estaba demasiado ciego para verlo todo este tiempo.";
			link.l1 = "Más vale tarde que nunca. Ahora vamos a casa, nuestro barco nos espera.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LeaveEliteBrothel");
		break;
		
		case "PZ_Mary_91":
			dialog.text = "Está bien. No tienes idea de cuánto deseaba esto.";
			link.l1 = "Creo que sí. ¿Cómo te sientes, Mary? La razón por la que quería evitar el derramamiento de sangre era porque no estaba seguro de si podrías sostener tu espada con la misma firmeza de siempre; uno de ellos podría haber ganado ventaja mientras yo estaba ocupado con otro.";
			link.l1.go = "PZ_Mary_92";
		break;
		
		case "PZ_Mary_92":
			dialog.text = "Me subestimas. Además, la ira es un demonio de medicina. No tenía duda de que te apresurarías a salvarme, como siempre lo haces, sí, ¿eh? Sabes, Charles... Aunque me llames tu Talismán Rojo, ¿qué tal si tú también eres el mío? Siempre sucede algo increíble cuando estamos juntos.";
			link.l1 = "¿Soy tu talismán? Vaya, me gusta esa idea.";
			link.l1.go = "PZ_Mary_93";
		break;
		
		case "PZ_Mary_93":
			dialog.text = "¡Ahí lo tienes, ya estás sonriendo! Ahora salgamos de este lugar asqueroso - date prisa, muévete, sí, ¿eh?";
			link.l1 = "Je-je, este lío me golpeó duro. Ojalá pudiera haber terminado de otra manera.";
			link.l1.go = "PZ_Mary_94";
		break;
		
		case "PZ_Mary_94":
			dialog.text = "No. No había forma de salvarla, Charles. Y arrastró a Longway con ella. Él tomó su decisión, y no nos dejó opción. Piensa en todas las personas a las que hemos ayudado hoy.";
			link.l1 = "Una vez más, no tengo nada que contradecirte, Mary. Y esta vez, ni siquiera quiero hacerlo. Ven, mi Talismán Rojo...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LeaveEliteBrothel");
		break;
		
		case "PZ_ElitaShluha_Final1":
			if (CheckAttribute(pchar, "questTemp.PZ_ChangShinMertva"))
			{
				dialog.text = "¿Qué sucedió allí, monsieur? Oímos maldiciones y gritos. Pero no nos atrevimos a pedir ayuda hasta que todo terminó.";
				link.l1 = "Y con razón. Su anfitriona está muerta. Son libres de irse. Si yo fuera ustedes, recogería el tesoro del establecimiento, lo dividiría y huiría de la isla lo antes posible. Sé que son damas honorables, no simples prostitutas, así que tendrán un futuro más allá de este miserable lugar.";
				link.l1.go = "PZ_ElitaShluha_Final2";
			}
			else
			{
				dialog.text = "Ah, eres tú, monsieur. ¿Sabes cuándo bajará la anfitriona?";
				link.l1 = "No pronto.  Y yo me alejaría de la puerta si fuera tú. Y nunca hables con ella sobre esta noche - no compartirá nada, y los gatos curiosos pierden sus vidas de inmediato. Parece que a tu señora no le gusta que nadie husmee en sus secretos.";
				link.l1.go = "PZ_ElitaShluha_Final3";
			}
		break;
		
		case "PZ_ElitaShluha_Final2":
			dialog.text = "¿La mataste?!";
			link.l1 = "Hice. Y si te demoras o intentas llamar a los guardias, sería tu mayor error. Ella nunca fue una santa patrona para ti; no importa cuánta seda y educación te dio, estabas encarcelada aquí, obligada a entregarte a cualquier chusma que ella señalara. Les deseo la mejor de las suertes para salir de aquí. Adiós, señoras.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_ToTortugaStreets");
		break;
		
		case "PZ_ElitaShluha_Final3":
			dialog.text = "¿De verdad está bien? ¿Podemos entrar? ¿Necesitamos llamar a los guardias?";
			link.l1 = "  Nunca estará bien. Puedes intentar preguntarle a ella misma... bajo tu propio riesgo. Todavía está hablando con su hermano. Y no creo que les guste ser interrumpidos. ";
			link.l1.go = "PZ_ElitaShluha_Final4";
		break;
		
		case "PZ_ElitaShluha_Final4":
			dialog.text = "Ya veo... Bueno, ven a visitarnos de nuevo algún día, monsieur.";
			link.l1 = "Jamás. Adiós, damas.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_ToTortugaStreets");
		break;
		
		case "PZ_TortugaSoldier1":
			dialog.text = "¡Alto! Se reportaron gritos y peleas provenientes del lugar de Mademoiselle Etoile. La guardia cree que usted tiene algo que ver con eso. Entregue sus armas y síganos, monsieur.";
			if (!CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				link.l1 = "Es cierto, pero no empezamos la pelea, la terminamos. Los matones contratados se rebelaron por pagos atrasados y atacaron a Madame Estrella para robarla. ¿Confiar en los mercenarios, eh? Ganamos el día, pero desafortunadamente, ella no sobrevivió.";
				link.l1.go = "PZ_TortugaSoldier2";
			}
			else
			{
				link.l1 = "He perdido al amor de mi vida hoy, así que déjame pasar, oficial.";
				link.l1.go = "PZ_TortugaSoldierGirlDied1";
			}
		break;
		
		case "PZ_TortugaSoldier2":
			dialog.text = "Te das cuenta de que no podemos simplemente tomar tu palabra, ¿verdad? Tenemos que detenerte. Y necesitarás testigos entre las empleadas. Veamos qué tienen que decir.";
			link.l1 = "Mi amado está gravemente herido. Yo también estoy exhausta. ¿No podrías simplemente dejarnos ir, por favor?";
			link.l1.go = "PZ_TortugaSoldier3";
		break;
		
		case "PZ_TortugaSoldier3":
			dialog.text = "Intentaremos resolver esto lo antes posible. Ahora, síguenos.";
			link.l1 = "Vete al infierno...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaSoldiersFight");
		break;
		
		case "PZ_TortugaSoldierGirlDied1":
			dialog.text = "Mis condolencias, monsieur. Y aún no soy oficial, pero... de todos modos, no importa. ¿Podrías venir con nosotros y contarnos qué sucedió allí?";
			link.l1 = "Te lo contaré. El burdel estaba perdiendo dinero y no quedaba efectivo para pagar a los mercenarios que lo custodiaban. Decidieron tomar lo que quedaba, justo cuando yo estaba allí. Madame Etoile y yo los enfrentamos, pero ella murió de sus heridas. Ahora, déjame pasar al fin.";
			link.l1.go = "PZ_TortugaSoldierGirlDied2";
		break;
		
		case "PZ_TortugaSoldierGirlDied2":
			dialog.text = "Me encantaría, pero hay mucho papeleo que completar. Y necesito entrevistar a las damas que trabajan allí. Me temo que tendrás que quedarte en la ciudad al menos un día, incluso si estás diciendo la verdad, monsieur.";
			link.l1 = "Vete al infierno...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaSoldiersFight");
		break;
		
		case "PZ_Longway_101":
			dialog.text = "Longway tiene algo para usted, Mi Señor Capitán.";
			link.l1 = "Qué hermoso y caprichoso. Nunca he visto algo así. ¿Qué es?";
			link.l1.go = "PZ_Longway_102";
			GiveItem2Character(PChar, "talisman14");
			PlaySound("interface\important_item.wav");
		break;
		
		case "PZ_Longway_102":
			dialog.text = "Es el amuleto de Capitán de mi Tierra Natal. Y, como Longway ya no es Capitán, te lo doy a ti.";
			link.l1 = "Gracias, Longway. Con la muerte de van der Vink, obtuviste tu venganza sobre todos los que querías. Me alegra que todo haya salido así.";
			link.l1.go = "PZ_Longway_103";
		break;
		
		case "PZ_Longway_103":
			dialog.text = "Si tan solo pudiera convencer a Xing de ser una buena persona otra vez...";
			link.l1 = "Ya no quería escuchar a nadie más, ni siquiera a su hermano. Hiciste lo mejor que pudiste. Todos lo hicimos.";
			link.l1.go = "PZ_Longway_104";
		break;
		
		case "PZ_Longway_104":
			dialog.text = "Sí... Muchas gracias, Mi Señor Capitán. Longway será libre, y tendrá un hogar y amigos nuevamente.";
			link.l1 = "Eres bienvenido, mi amigo. Ahora, ¿por qué no vienes conmigo a visitar a mi hermano? ¡Oh, la ironía!";
			link.l1.go = "PZ_Longway_105";
		break;
		
		case "PZ_Longway_105":
			DialogExit();
			DeleteAttribute(npchar, "CompanionDisable");//теперь можем и в компаньоны
			chrDisableReloadToLocation = false;
			Return_LongwayOfficer();
		break;
		
		case "PZ_PuansieDialogWithLevasser_1":
			dialog.text = "Aquí estamos de nuevo, François. Veo que la vida te ha pasado factura, jeje.";
			link.l1 = " ";
			link.l1.go = "PZ_PuansieDialogWithLevasser_1_1";
			LAi_SetHuberType(npchar);
		break;
		case "PZ_PuansieDialogWithLevasser_1_1":
			StartInstantDialog("Levasser", "PZ_PuansieDialogWithLevasser_2", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_2":
			dialog.text = "Poincy, maldito avaricioso... Casi te ahogas con el oro que llenan tus cofres, ¿y aún no tienes suficiente?";
			link.l1 = " ";
			link.l1.go = "PZ_PuansieDialogWithLevasser_2_1";
			CharacterTurnByChr(npchar, CharacterFromID("Puancie"));
		break;
		case "PZ_PuansieDialogWithLevasser_2_1":
			StartInstantDialogNoType("Puancie", "PZ_PuansieDialogWithLevasser_3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_3":
			//LAi_SetActorType(npchar);
			//LAi_ActorSetHuberMode(npchar);
			dialog.text = "Compartiré un poco contigo, François. Tendrás suficiente, créeme.";
			link.l1 = " ";
			link.l1.go = "PZ_PuansieDialogWithLevasser_3_1";
			//LAi_tmpl_SetDialog(npchar, pchar, -1.0);
		break;
		case "PZ_PuansieDialogWithLevasser_3_1":
			StartInstantDialog("Levasser", "PZ_PuansieDialogWithLevasser_4", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_4":
			dialog.text = "¿Qué... qué quieres decir?";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_4_1";
			CharacterTurnByChr(npchar, CharacterFromID("Puancie"));
		break;
		case "PZ_PuansieDialogWithLevasser_4_1":
			StartInstantDialogNoType("Puancie", "PZ_PuansieDialogWithLevasser_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_5":
			dialog.text = "";
			link.l1 = "Gobernador General, ¿va usted a...";
			link.l1.go = "PZ_PuansieDialogWithLevasser_6";
		break;
		
		case "PZ_PuansieDialogWithLevasser_6":
			dialog.text = "Charles, mi amigo, ¡has hecho tu trabajo y lo has hecho brillantemente! Lo que le suceda a este hombre no debería preocuparte... Sin embargo, te será útil saberlo, Capitán, por si a tu brillante cabeza se le ocurren ideas tontas algún día. A nuestro amigo común le espera un mal caso de indigestión, por así decirlo. El oro no es bueno para el estómago, he oído... Espero no necesitar explicarme más.";
			link.l1 = "No, Gobernador General.";
			link.l1.go = "PZ_PuansieDialogWithLevasser_7";
		break;
		
		case "PZ_PuansieDialogWithLevasser_7":
			dialog.text = "A diferencia de Monsieur François, tienes un gran futuro por delante, Charles. ¡Chicos, lleven a ese cerdo a la cárcel!";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_7_1";
		break;
		case "PZ_PuansieDialogWithLevasser_7_1":
			StartInstantDialog("Levasser", "PZ_PuansieDialogWithLevasser_8", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_8":
			dialog.text = "¡Manos fuera, cabrones! ¿Estás satisfecho, de Maure? ¡Que te jodan! ¡Arderéis los dos en el Infierno, en la misma sartén conmigo!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LevasserVGostyahUPuansie3");
			CharacterTurnByChr(npchar, CharacterFromID("Puancie"));
			sld = characterFromID("PZ_SoldFra_1");
			CharacterTurnByChr(sld, CharacterFromID("Levasser"));
			sld = characterFromID("PZ_SoldFra_2");
			CharacterTurnByChr(sld, CharacterFromID("Levasser"));
		break;
		
		case "PZ_Baker_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Kasper";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Sharp";
			dialog.text = "Bueno, señor. He inspeccionado a la señorita "+sStr+"...";
			link.l1 = "¿Qué tan grave es, Raymond?";
			link.l1.go = "PZ_Baker_2";
		break;
		
		case "PZ_Baker_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					dialog.text = "No hay de qué preocuparse, Capitán. Mary fue gravemente herida, por supuesto, pero, en general, todo estará bien. Debería permanecer en cama unos días, y espero que esté de vuelta en acción en quince días.";
					link.l1 = "Ya veo. Gracias, Raymond. Retírate.";
					link.l1.go = "PZ_Baker_4";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "Mary recibió una buena paliza, Capitán. Moretones, cortes... y el shock de todo, por supuesto, aunque intenta no mostrarlo.";
					link.l1 = "Está poniendo cara dura, como siempre. Pero creo que se da cuenta de que ahora está mejor descansando en cama. ¿Por cuánto tiempo, sin embargo?";
					link.l1.go = "PZ_Baker_3";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "Incluso un soldado profesional tendría dificultades para sobrevivir a lo que ella pasó, Capitán. Esguinces, tensiones, contusiones - tenemos suerte de que esos bastardos no le rompieran los huesos. Sin embargo, sus tendones están dañados, así que no podrá empuñar una espada durante al menos un mes.";
					link.l1 = "Al diablo con la hoja. ¿Cuándo podrá ponerse de pie?";
					link.l1.go = "PZ_Baker_3";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					dialog.text = "No te preocupes, Capitán. Hellen está herida, pero no gravemente. Tendrá que permanecer en cama por ahora, pero creo que se recuperará completamente en un par de semanas.";
					link.l1 = "Entiendo. Gracias, Raymond. Despedido.";
					link.l1.go = "PZ_Baker_4";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "Recibió una buena paliza, capitán. Y las lesiones físicas son solo una parte del diagnóstico... Estar en ese lugar terrible le recordó la pesadilla que vivió en el Arbutus.";
					link.l1 = "Por supuesto... ¡maldición! ¿Cuándo volverá a estar de pie?";
					link.l1.go = "PZ_Baker_3";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "Helen caminó por el filo de una navaja, Capitán. Me sorprende que haya sobrevivido después de todo lo que ha pasado. No hay laceraciones internas ni fracturas, pero sí muchos esguinces y torceduras.";
					link.l1 = "Pobrecilla. ¿Cuánto tiempo tardará en recuperarse?";
					link.l1.go = "PZ_Baker_3";
				}
			}
		break;
		
		case "PZ_Baker_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "Al menos una semana, señor. Si sigue mis recomendaciones, debería estar de vuelta en acción en aproximadamente un mes.";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "No antes de quince días, señor. Después de eso, le permitiré paseos cortos por el alcázar. La recuperación completa tomará al menos dos meses.";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "No la molestes durante al menos una semana, te lo digo, señor. La recuperación completa tomará alrededor de un mes.";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "Deberá permanecer en cama durante quince días; después, podrá caminar por la cubierta. Pero no esperes verla de nuevo en acción hasta dentro de dos meses.";
				}
			}
			link.l1 = "Entiendo. Gracias, Raymond. Despedido.";
			link.l1.go = "PZ_Baker_4";
		break;
		
		case "PZ_Baker_4":
			DialogExit();
			sld = CharacterFromID("Baker");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "PZ_RazgovorSVrachom_4", -1);
		break;
		
		case "PZ_DevushkaVstalaSKrovati_Dialog1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "¡Es más difícil de lo que pensé mantenerme en pie después de estar tumbada tanto tiempo, sí, ¿eh?!";
				link.l1 = "Quizás no deberías dejar el reposo en cama tan abruptamente, amor.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Oh-h, mi cabeza...";
				link.l1 = "¡Helen! ¿No te has levantado un poco temprano? ¡Apenas puedes mantenerte en pie!";
			}
			link.l1.go = "PZ_DevushkaVstalaSKrovati_Dialog2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_DevushkaVstalaSKrovati_Dialog2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Preferiría quemar esta maldita cama antes que volver a acostarme en ella, ¡al menos hasta que haya caminado desde la proa hasta la popa y de regreso!";
				link.l1 = "Es una cama agradable y cómoda. Y tampoco es un mal barco. Así que no voy a detenerte. Pero estaré allí para asegurarme de que no hagas ninguna tontería.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Estoy bien, Capitán, aunque no completamente. No estoy listo para blandir una espada todavía, pero odio esta cama con toda mi alma.";
				link.l1 = "Bueno, un corto paseo por la cubierta probablemente no te hará daño. ¡Pero ni pienses en acercarte a los cables!";
			}
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DevushkaStoitVosstanovlenie");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Sex1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Charles, ¿no crees que te has olvidado de mí por completo? Recuérdame cuándo fue la última vez que compartimos lecho, sí, ¿eh?";
				link.l1 = "Antes... No hablemos de eso, ¿vale, Mary?";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Mi capitán, ¿he dejado de interesarte como mujer?";
				link.l1 = "Eso es inesperado, Helen. Normalmente, soy yo quien menciona eso... pero no estaba seguro de que estuvieras lista después de...";
			}
			link.l1.go = "PZ_DevushkaSnovaOfficer_Sex2";
			DelLandQuestMark(npchar);
			pchar.questTemp.PZ_DevushkaSnovaOfficer = true;
			DeleteQuestCondition("PZ_DevushkaSnovaOfficer2");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Sex2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Entonces habla de mí al menos, sí, ¿eh? ¿O me he vuelto desagradable para ti después de que esos dos bastardos me dieran una paliza?";
				link.l1 = "Eso es lo más estúpido que he escuchado. Simplemente no quería molestarte hasta que estuvieras listo. Y ya que lo estás...";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Sex3";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Está bien, Charles, de verdad. Solo trato de no pensar en ello. Y además, me salvaste de lo peor. Así que dejemos de hablar y simplemente... pongámonos al día.";
				link.l1 = "Esa es una maldita buena idea, Helen.";
				link.l1.go = "exit";
				pchar.quest.sex_partner = Npchar.id;
				AddDialogExitQuest("cabin_sex_go");
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Sex3":
				dialog.text = "Charles, no lo quiero, lo exijo, sí, ¿eh?";
				link.l1 = "No me atrevería a rechazarle...";
				link.l1.go = "exit";
				pchar.quest.sex_partner = Npchar.id;
				AddDialogExitQuest("cabin_sex_go");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Charles, necesitamos hablar, sí, ¿eh?";
				link.l1 = "¿Pasa algo, Mary? Pareces bastante ansiosa, y eso generalmente no augura nada bueno.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Mi capitán, hay algo que necesito decirte.";
				link.l1 = "¿Es así, Helen? Estoy escuchando.";
			}
			link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "¡Eso es justo! ¿No es una buena cosa que esté listo para volver a mis deberes como oficial?";
				link.l1 = "Así que eso es todo. Bueno, si te sientes lo suficientemente fuerte, no sólo es bueno, es maravilloso.";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog3";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Estoy cansada de que la tripulación me mire como si fuera una anciana frágil. Quiero volver al timón y estirar los brazos practicando con una espada...";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					link.l1 = "Si te sientes con ánimos, no me opondré, querido. Iré a buscar tu equipo. Y con gusto te dejaré tomar el timón. Pero ten cuidado en una pelea, sí, ¿eh?";
					link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog2_1";
				}
				else
				{
					link.l1 = "Te hemos echado de menos en el puente, Helen. En cuanto a la hoja, creo que es hora de que la recuperes.";
					link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog3";
				}
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog2_1":
			dialog.text = "Por supuesto, Mi Capitán, lo que usted diga.";
			link.l1 = "Bien.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "¡Maravilloso, sí, ¿eh?! No puedo esperar para practicar con la espada...";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					link.l1 = "Me alegra oírlo, Mary. Pero no te metas de lleno en las cosas todavía... Pero ¿a quién le estoy diciendo?";
					link.l1.go = "exit";
					AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
				}
				else
				{
					link.l1 = "Supongo que estarás feliz de ver ese palash de vuelta en su vaina...";
					link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog4";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "No sé qué decir, Charles. Acabo de darme cuenta de lo mucho que significa este alfanje para mí...";
				link.l1 = "Lo supe hace mucho tiempo, por eso te ha estado esperando sano y salvo.";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog4";
				notification("Diste el Cutlass de Blaze", "None");
				PlaySound("interface\important_item.wav");
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "¡Mi narval, sí, ¿eh?! ¡Charles, lo has salvado! ¡No solo estoy feliz, estoy emocionada! ¡Gracias, gracias! Tenía tanto miedo de que se quedara en el barco de Martin...";
				link.l1 = "Esta hoja pertenece a tu mano, mi Talismán Rojo. Confío en que no la perderás de nuevo... Bueno, no me interpondré en tu reunión, ¡ja, ja!";
				notification("Gave Narwhal", "None");
				PlaySound("interface\important_item.wav");
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Gracias, Charles. Sabes, probablemente por eso te amo...";
				link.l1 = "¿Por devolver cosas perdidas? Ja ja ja ja...";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog5";
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog5":
			dialog.text = "Te ríes, pero hablo en serio.";
			link.l1 = "Lo sé, Helen. Yo también te amo, aunque todavía no estoy seguro de por qué.";
			link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog6";
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog6":
			dialog.text = "Tal vez porque aún no he usado este alfanje contigo.";
			link.l1 = "Me salvaré de eso dirigiéndome a los botes. Te esperaré allí, Helen.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
		break;
	}
} 