// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué quieres? Pregunta lo que desees.","Te escucho, ¿cuál es la pregunta?"),"Esta es la segunda vez que intentas preguntar...","Esta es la tercera vez que intentas preguntar...","¿Cuándo va a terminar esto?! ¡Soy un hombre ocupado, trabajando en asuntos de la colonia y tú todavía me molestas!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Cambié de opinión...","Ahora no. Lugar y momento equivocados."),"Verdad... Pero más tarde, no ahora...","Preguntaré... Pero un poco más tarde...","Lamento, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_8")
			{
				link.l1 = "Su Excelencia, me gustaría informar sobre una actividad de comercio ilegal en esta isla.";
                link.l1.go = "Mtraxx";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_12")
			{
				link.l1 = "Me gustaría escuchar un informe sobre tu misión respecto al contrabando de velas de seda.";
                link.l1.go = "Mtraxx_4";
			}
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_10_continue" && !CheckAttribute(npchar, "quest.slaveships"))
			{
				link.l1 = "He llegado en nombre del Gobernador General Phillipe de Poincy. Mi tarea es traeros los esclavos capturados de los holandeses, ¿es correcto?";
                link.l1.go = "patria_Sl";
			}
			if (CheckAttribute(npchar, "quest.slaveships.wait") && GetSquadronGoods(pchar, GOOD_SLAVES) >= 3000)
			{
				link.l1 = "Te he traído los esclavos, como acordamos.";
                link.l1.go = "patria_Sl_2";
			}
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_11_start" && CheckAttribute(pchar, "questTemp.Patria.Curacao.DoilyReady"))
			{
				link.l1 = "Llegué por instrucciones del Gobernador General Phillipe de Poincy para participar en una expedición conjunta a Curazao contra los holandeses.";
                link.l1.go = "patria_Sl_4";
			}
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_11_wait" && GetCompanionQuantity(pchar) < 3)
			{
				link.l1 = "Mi escuadrón fue disminuido, podemos partir ahora.";
                link.l1.go = "patria_Sl_6";
			}
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "Mtraxx":
            dialog.text = "Interesante. Soy todo oídos.";
			link.l1 = "Tengo buenas fuentes que aseguran que un bergantín holandés, el 'Utrecht', bajo bandera inglesa, ha estado descargando grandes cantidades de tela de seda para velas en la Bahía de Portland durante mucho tiempo. Han estado operando durante más de un año, por las noches, entre el 10 y el 15 de cada mes.";
			link.l1.go = "Mtraxx_1";
		break;
		
		case "Mtraxx_1":
            dialog.text = "¿Estás seguro de que se puede confiar en tu fuente?";
			link.l1 = "A veces ni siquiera confío en mí mismo, sin embargo, un hombre que reveló esta información es de fiar. Además, no tenía razón para mentir.";
			link.l1.go = "Mtraxx_2";
		break;
		
		case "Mtraxx_2":
			string sTemp = "this";
			if (sti(pchar.questTemp.Mtraxx.month == 1)) sTemp = "next";
            dialog.text = "Muy bien, capitán. Este es un asunto serio y debo actuar según la información presentada, incluso si su informante mintió o simplemente estaba equivocado. Enviaré una patrulla costera a la hora especificada, y si su información se confirma, será generosamente recompensado, tales actividades ilegales deben ser severamente reprimidas.";
			link.l1 = "Te veré "+sTemp+" mes el día 16. La situación seguramente se resolverá para entonces.";
			link.l1.go = "Mtraxx_3";
		break;
		
		case "Mtraxx_3":
            DialogExit();
			pchar.questTemp.Mtraxx = "silk_11";
			int month = sti(pchar.questTemp.Mtraxx.month);
			pchar.quest.mtr_silk_smuggler.over = "yes";
			pchar.quest.mtr_silk_smuggler_over.over = "yes";
			DeleteQuestCondition("Mtraxx_SilkCreateSmuggler");
			DeleteQuestCondition("Mtraxx_SilkSmugglerFail");
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1 = "Timer";
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.hour  = 6;
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.day   = 16;
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.month = GetAddingDataMonth(0, month, 0);
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.year  = GetAddingDataYear(0, month, 0);
			pchar.quest.mtr_silk_smuggler_patrol.function = "Mtraxx_SilkSmugglerPatrol";
			sTemp = "this";
			if (sti(pchar.questTemp.Mtraxx.month == 1)) sTemp = "next";
			AddQuestRecord("Roger_2", "19");
			AddQuestUserData("Roger_2", "sDate", sTemp);
			if (CharacterIsAlive("Mtr_Utreht"))
			{
				sld = CharacterFromID("Mtr_Utreht");
				sld.lifeday = 0;
			}
		break;
		
		case "Mtraxx_4":
            dialog.text = "Tu información resultó ser correcta, capitán. Emboscamos a los criminales durante la transacción. El 'Utrecht' intentó escapar y luchar, pero fue hundido por nuestro corbeta de patrulla. Cuatro compradores resistieron el arresto. Uno fue abatido de un disparo, y los otros tres huyeron a la selva. La carga completa de 80 rollos de seda ha sido transferida al tesoro de Port Royal. Aunque no logramos identificar al cabecilla de esta red, el hombre muerto está sin identificar, y los otros han huido, declaro que esta operación ha sido un éxito completo. Dudo que estos canallas se atrevan a regresar aquí alguna vez.\nNos has prestado un gran servicio, capitán, al ser diligente y señalar a los estafadores. Aquí tienes 10.000 pesos como recompensa.";
			link.l1 = "Muchas gracias, su Excelencia. Me alegra ver que todo salió según lo planeado y que los contrabandistas obtuvieron lo que se merecían. Con eso, me despido, que tenga un buen día.";
			link.l1.go = "Mtraxx_5";
		break;
		
		case "Mtraxx_5":
            DialogExit();
			pchar.questTemp.Mtraxx = "silk_13";
			AddQuestRecord("Roger_2", "20");
			AddMoneyToCharacter(pchar, 10000);
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterNationReputation(pchar, ENGLAND, 5);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		// Jason НСО
		case "patria_Sl":
			if (GetSquadronGoods(pchar, GOOD_SLAVES) < 500)
			{
				dialog.text = "Eso es preciso. ¿Cuántos esclavos trajiste?";
				link.l1 = "Todavía estoy trabajando en ello. Pronto regresaré con los resultados.";
				link.l1.go = "patria_Sl_wait";
				break;
			}
			dialog.text = "Eso es preciso. ¿Cuántos esclavos trajiste?";
			link.l1 = ""+FindRussianQtyString(GetSquadronGoods(pchar,GOOD_SLAVES))+".";
			if (GetSquadronGoods(pchar, GOOD_SLAVES) >= 3000) link.l1.go = "patria_Sl_2";
			else link.l1.go = "patria_Sl_1";
		break;
		
		case "patria_Sl_wait":
			DialogExit();
			npchar.quest.slaveships.wait = "true";
		break;
		
		case "patria_Sl_1":
			dialog.text = "Hmm, el Caballero prometió que no habría menos de 3000 esclavos";
			link.l1 = "Así es. Esto es mi culpa: algunos de los esclavos murieron bajo el fuego de cañones de un barco enemigo, algunos murieron en el camino. Corregiré mi error y regresaré a usted. Todo se hará de acuerdo con el contrato.";
			link.l1.go = "patria_Sl_wait";
		break;
		
		case "patria_Sl_2":
			DeleteAttribute(npchar, "quest.slaveships.wait");
			dialog.text = "¡Excelente! Con el Caballero de Poincy uno realmente puede hacer negocios. Dígale al Gobernador General que mi escuadrón para el ataque a Curazao estará listo en un mes. Estoy seguro de que él lo enviará a esta campaña conmigo, así que lo veré pronto, Monsieur de Maure.";
			link.l1 = "Me alegraría volver a encontrarme con usted, Coronel. Y ahora permítame despedirme.";
			link.l1.go = "patria_Sl_3";
		break;
		
		case "patria_Sl_3":
			DialogExit();
			npchar.quest.slaveships = "true";
			RemoveCharacterGoods(pchar, GOOD_SLAVES, GetSquadronGoods(pchar, GOOD_SLAVES));
			AddQuestRecord("Patria", "57");
			pchar.questTemp.Patria = "epizode_10_return";
			pchar.quest.Patria_SlaveShipsJamaicaTimeOver.over = "yes"; //снять таймер на доставку рабов
			SetFunctionTimerCondition("Patria_CuracaoDoilyReady", 0, 0, 30, false); // таймер на 1 месяц на готовность эскадры д'Ойли
			SetFunctionTimerCondition("Patria_CuracaoTimeOver", 0, 0, 62, false); // таймер на 2 месяца на туда-обратно к Пуанси
			SaveCurrentQuestDateParam("questTemp.Patria.Curacao.Date"); // запоминаем дату
			// меняем отношение наций
			pchar.questTemp.Patria.Friend = "true";
			LaunchNationLegend();
			DeleteAttribute(pchar, "questTemp.Patria.Friend");
			DoQuestCheckDelay("sea_victory", 0.2);
		break;
		
		case "patria_Sl_4":
			dialog.text = "No dudaba que serías tú. ¡Aún mejor! Nuestra escuadra está lista. Un navío de línea de 1er rango y dos barcos de 4to rango. El tamaño máximo de toda la escuadra no debe exceder cinco barcos.";
			if (GetCompanionQuantity(pchar) > 2)
			{
				link.l1 = "Entonces dejaré los barcos extra en los muelles y me quedaré solo con dos. Obtendremos cinco barcos como resultado.";
				link.l1.go = "patria_Sl_5";
			}
			else
			{
				link.l1 = "Sí, exactamente cinco, y no más. Deberíamos partir.";
				link.l1.go = "patria_Sl_6";
			}
		break;
		
		case "patria_Sl_5":
			DialogExit();
			pchar.questTemp.Patria = "epizode_11_wait";
		break;
		
		case "patria_Sl_6":
			dialog.text = "Perfecto. Ahora te explicaré el plan por el cual actuaremos: quizás quieras cambiar algo o añadir algo, entonces lo discutiremos.";
			link.l1 = "Soy todo oídos, coronel.";
			link.l1.go = "patria_Sl_7";
		break;
		
		case "patria_Sl_7":
			dialog.text = "No tiene sentido capturar Curazao: es la principal colonia holandesa en el archipiélago, e incluso si capturamos su bandera en el fuerte de Willemstad y izamos una inglesa o francesa, será muy difícil mantener la isla. Los holandeses harán todo lo posible para recuperarla y la apuntarán con escuadrones militares. En general, no tiene sentido capturarla ya que no es obligatorio. Más importante para nosotros es obligar a Steivesant a firmar el tratado en términos que sean beneficiosos para nosotros, y para hacer esto será suficiente destruir las principales defensas del enemigo y poner a los holandeses bajo la amenaza de la destrucción completa de la colonia de Willemstad.";
			link.l1 = "¿De qué tratará el tratado?";
			link.l1.go = "patria_Sl_8";
		break;
		
		case "patria_Sl_8":
			dialog.text = "El tratado fue redactado por mí y el Caballero de Poincy. Está relacionado con varios aspectos del comercio, el fin de la 'guerra comercial' entre la Compañía e Inglaterra, la negación de las pretensiones de Stuyvesant sobre la isla de San Martín y otros puntos políticos que son de poco interés para ti.";
			link.l1 = "Entendido.";
			link.l1.go = "patria_Sl_9";
		break;
		
		case "patria_Sl_9":
			dialog.text = "Este es el plan: primero, con todas las fuerzas atacaremos el fuerte y lo destruiremos. Los holandeses esperarán un desembarco de tropas, pero no lo haremos, las mayores bajas suelen sufrirse al tomar un bastión desde el mar. En cambio, desembarcaremos equipos de asalto en dos puntos de la isla: en el Cabo Santa María y en la laguna de Blanca, y nos moveremos por tierra hasta la puerta de la ciudad de Willemstad. Ordené llevar artillería de campaña con nosotros en los barcos, no hay vegetación densa antes de alcanzar Curazao, y podremos rodar los cañones sobre ruedas por el suelo sin dificultad.\nMientras los holandeses se preguntan qué está ocurriendo, tomaremos el pueblo bajo la mira desde la jungla y bloquearemos cualquier oportunidad de enviar refuerzos desde el fuerte por tierra. Después de eso, pondremos el pueblo bajo fuego de cañones. Seguramente la guarnición del fuerte intentará atacar, pero no podrán hacer nada contra los cañones de campaña y nuestros mosqueteros, y si sus cañones en el fuerte aún son funcionales, no podrán llevarlos a la jungla.\nAdemás, nuestros barcos simularán preparativos para desembarcar tropas desde el mar para infundir miedo a los enemigos y bajar su moral. Después de un tiempo, cuando los holandeses sean plenamente conscientes de su situación desesperada, llamaremos a los parlamentarios para negociar. ¿Qué opinas, capitán?";
			link.l1 = "¡Plan brillante! Y lo mejor de todo es que no perderemos a ningún soldado junto a las murallas del fuerte.";
			link.l1.go = "patria_Sl_10";
		break;
		
		case "patria_Sl_10":
			dialog.text = "Me alegra que te hayan gustado mis ideas. ¡Vayamos entonces!";
			link.l1 = "¡Vamos!";
			link.l1.go = "patria_Sl_11";
		break;
		
		case "patria_Sl_11":
			DialogExit();
			chrDisableReloadToLocation = true;
			pchar.questTemp.Patria = "epizode_11_continue";
			AddQuestRecord("Patria", "60");
			pchar.quest.Patria_CuracaoTimeOver.over = "yes"; // снять таймер 2 месяца
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "PortRoyal_townhall", "goto", "goto4");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 7.0);
			Patria_CuracaoSail();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
