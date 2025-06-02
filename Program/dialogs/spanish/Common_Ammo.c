// диалог коменданта форта
void ProcessDialogEvent()
{
	int amount, iGunQty, iGunGoods, iGunPrice, iTemp;
	int iTest;
	ref NPChar, sld, location;
	ref arItem;
	ref rColony;
	aref Link, NextDiag;
	string sTemp;
	float locx, locy, locz;
	bool ok;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// вызов диалога по городам -->
	/*NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Prison\" + NPChar.City + "_Prison.c";
	 if (LoadSegment(NPChar.FileDialog2))
	 {
		 ProcessCommonDialog(NPChar, Link, NextDiag);
		 UnloadSegment(NPChar.FileDialog2);
	 }*/
	// вызов диалога по городам <--

	switch (Dialog.CurrentNode)
	{
	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "fight":
		DialogExit();
		NextDiag.CurrentNode = NextDiag.TempNode;
		LAi_group_Attack(NPChar, Pchar);
		if (rand(3) != 1)
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "NoMoreTalkExit":
		LAi_CharacterDisableDialog(npchar);
		DialogExit();
		break;

	case "First time":
		location = &Locations[FindLocation(pchar.location)];
		if (rand(4) == 4 && GetNpcQuestPastDayParam(location, "gun_date") > 365 && !CheckAttribute(pchar, "questTemp.PrisonGun"))
		{
			dialog.text = RandPhraseSimple(RandPhraseSimple("Escucha, tengo un negocio importante contigo. Espero que puedas ayudar.", "Capitán, ¿puedo interesarle con una oferta bastante rentable?"), RandPhraseSimple("Creo que podrías ayudarnos en un asunto importante.", "Capitán, tengo una oferta delicada para ti, que podría ser bastante rentable para ambos."));
			link.l1 = "Bueno, habla lo que piensas, y veremos...";
			link.l1.go = "GiveTaskGun";
			location.quest.PrisonGun = "Target";
			SaveCurrentNpcQuestDateParam(location, "gun_date");
			break;
		}

		dialog.text = RandPhraseSimple("Soy el comandante del fuerte. ¿Qué necesitas aquí?", "¿Qué necesitas? ¿Por qué has venido aquí?");
		link.l1 = "Oh, nada, solo miro alrededor del pueblo y sus alrededores. Llegué aquí solo por una casualidad.";
		// belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
		//  Офицер с патентом
		if (IsOfficerFullEquip())
		{
			dialog.text = "Bienvenido al fuerte, capitán. ¿Necesitas algo?";
			link.l1 = "No, nada, solo pasé por aquí al azar.";
		}
		// вице-адмирал
		if (isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
		{
			dialog.text = "¡Saludos Vicealmirante! ¿Tiene alguna orden?";
			link.l1 = "No, oficial, no hay órdenes. Solo vine a ver el fuerte.";
		}
		// генерал-губернатор
		if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
		{
			dialog.text = "Gobernador General, ¡Su Gracia! Tengo orden completo en el fuerte. ¿Habrá alguna orden?";
			link.l1 = "Me alegro de que estés bien, oficial. No hay órdenes, solamente pasé a revisar el fuerte.";
		}
		// <-- legendary edition
		link.l1.go = "exit";
		// Jason --> мини-квест Дефицитный товар
		if (CheckAttribute(pchar, "questTemp.Wine.bottle") && NPChar.location == pchar.questTemp.Wine.City + "_ammo" && GetQuestPastDayParam("questTemp.Wine_bottle") < 5)
		{
			link.l11 = "Tengo una información interesante para ti, oficial. Uno de tus soldados, " + pchar.questTemp.Wine.SName + " me pidió que comprara vino en la ciudad a través de mi mediación. Considerando tus órdenes...";
			link.l11.go = "Wine_prison";
		}
		// <-- мини-квест Дефицитный товар
		// Карибские нравы
		if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "fraht" && NPChar.location == "portpax_ammo")
		{
			link.l11 = "Hola, oficial. Vengo de la colonia de Basse-Terre, por orden de un hombre llamado Gerard LeCroix. Hay un cargamento de pólvora y bombas para ti en mi bodega...";
			link.l11.go = "trial";
		}
		// Опасный груз -->
		if (pchar.location == "Cumana_Ammo")
		{
			if (pchar.questTemp.zpq != "begin" && pchar.questTemp.zpq != "failed" && pchar.questTemp.zpq != "completed")
			{
				link.l2 = "Pareces preocupado, oficial. ¿Cómo puedo ayudarte?";
				link.l2.go = "zpq_prs1";
			}
			if (pchar.questTemp.zpq == "begin" && GetSquadronGoods(pchar, GOOD_POWDER) >= 15000 && GetQuestPastDayParam("pchar.questTemp.zpq") >= 7)
			{
				link.l3 = "Estoy listo para informar que toda la carga de pólvora ha sido entregada. Mi barco está listo para ser descargado.";
				link.l3.go = "zpq_ex";
			}
			if (pchar.questTemp.zpq == "begin")
			{
				link.l4 = "Quiero rechazar nuestro trato de pólvora. Esto es demasiado problemático.";
				link.l4.go = "zpq_fld2";
			}
		}
		// <-- Опасный груз
		NextDiag.TempNode = "First time";
		break;

	// --> Орудия для форта
	case "GiveTaskGun":
		dialog.Text = LinkRandPhrase("Verás, los cañones del fuerte están bastante desgastados. La tesorería asignó fondos para reemplazarlos, pero simplemente no tengo idea de dónde comprar los nuevos: simplemente no hay manera de encontrarlos en nuestra colonia en la cantidad requerida. Entonces, pensé que los cañones de los barcos que abordaste podrían ser bastante útiles para nosotros aquí.", "Necesito reemplazar la batería de cañones del fuerte. Los fondos ya han sido asignados, pero, ya sabes... Es simplemente imposible comprar la cantidad necesaria en nuestra colonia.", "Me encargaron reemplazar los cañones desgastados del fuerte, pero parece que no puedo encontrar suficientes en ningún lugar.");
		Link.l1 = "Hmm... ¿Puedes entrar un poco más en detalle? Calibre, cantidad, precio?";
		Link.l1.go = "GiveTaskGun_1";
		pchar.questTemp.PrisonGun = true;
		SaveCurrentQuestDateParam("pchar.questTemp.PrisonGun");
		break;

	case "GiveTaskGun_1":
		GetGunType();
		pchar.questTemp.PrisonGun.Sum = makeint(sti(pchar.questTemp.PrisonGun.Price) * sti(pchar.questTemp.PrisonGun.Qty));
		pchar.questTemp.PrisonGun.Luck = rand(4);
		pchar.questTemp.PrisonGun.Id = npchar.location;
		dialog.Text = "Necesito " + pchar.questTemp.PrisonGun.Text + ", en la cantidad de " + sti(pchar.questTemp.PrisonGun.Qty) + "  unidades exactamente. Pagaré en doblones de oro, " + sti(pchar.questTemp.PrisonGun.Price) + " por pieza. Eso sumará a " + FindRussianDublonString(sti(pchar.questTemp.PrisonGun.Sum)) + " en total. ¿Qué dirás? Ah, y una cosa más. Aceptaré todo el lote, pero no antes de un mes el dinero aún no ha llegado.";
		Link.l1 = RandPhraseSimple("No, oficial, su oferta no me interesó en absoluto... Lo siento.", "Es tentador, pero creo que paso. Permíteme guardar mis razones para mí mismo.");
		Link.l1.go = "exit_gun";
		Link.l2 = RandPhraseSimple("Bueno, esa oferta es ciertamente interesante. Considéralo un trato.", "Supongo que lo tomaré. No es tan difícil y es claramente lucrativo.");
		Link.l2.go = "GiveTaskGun_2";
		break;

	case "exit_gun":
		dialog.Text = "Qué lástima, capitán, contaba contigo. Y... ¿puedo esperar que esta conversación se quede dentro del fuerte?";
		Link.l1 = "No tienes que recordarme eso. Mis mejores saludos.";
		Link.l1.go = "exit";
		DeleteAttribute(pchar, "questTemp.PrisonGun");
		NextDiag.TempNode = "First time";
		break;

	case "GiveTaskGun_2":
		dialog.Text = "Bueno, entonces eso es un trato! No te estoy restringiendo a ciertos términos, pero por favor, intenta no prolongarlo más de medio año. ¿Y espero que entiendas que esto es estrictamente confidencial?";
		Link.l1 = "Por supuesto que sí. Hasta luego, comandante.";
		Link.l1.go = "exit";
		ReOpenQuestHeader("PrisonGun");
		AddQuestRecord("PrisonGun", "1");
		AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("", ""));
		AddQuestUserData("PrisonGun", "sName", GetFullName(npchar));
		AddQuestUserData("PrisonGun", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
		AddQuestUserData("PrisonGun", "sQty", makeint(pchar.questTemp.PrisonGun.Qty));
		AddQuestUserData("PrisonGun", "sSum", makeint(pchar.questTemp.PrisonGun.Sum));
		AddQuestUserData("PrisonGun", "sText", pchar.questTemp.PrisonGun.Text);
		NextDiag.TempNode = "First time";
		break;

	case "CheckGun":
		if (GetQuestPastDayParam("pchar.questTemp.PrisonGun") < 30)
		{
			dialog.Text = "¡Te dije que no vinieras antes de un mes!";
			Link.l1 = "¡Maldita sea! Estaba tan ocupado" + GetSexPhrase("", "") + ", que perdí un" + GetSexPhrase("", "") + " pierdo la noción del tiempo ... Lo siento, vendré más tarde, como acordamos.";
			Link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			break;
		}
		if (GetQuestPastDayParam("pchar.questTemp.PrisonGun") > 180)
		{
			dialog.Text = "Hmm... Sabes, ha pasado más de medio año desde el día que hemos cerrado nuestro 'trato'. Ya he comprado los cañones. ¿Realmente pensaste que te estaría esperando para siempre?";
			Link.l1 = "¡Maldita sea! ¿Y qué se supone que debo hacer con ellos ahora?";
			Link.l1.go = "TakeGun_late";
			break;
		}
		iGunGoods = pchar.questTemp.PrisonGun.Goods;
		amount = GetSquadronGoods(Pchar, iGunGoods) - sti(pchar.questTemp.PrisonGun.Qty);
		sTemp = sti(pchar.questTemp.PrisonGun.Qty);
		iTest = FindColony(NPChar.City); // город

		if (iTest != -1)
		{
			rColony = GetColonyByIndex(iTest);
		}
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
		{
			dialog.Text = "Sí, ¿estás listo para ayudarme?";
			if (amount < 0)
			{
				Link.l1 = "No, aún en progreso. Solo quería asegurarme de que nuestro trato sigue en pie.";
				Link.l1.go = "exit";
			}
			else
			{
				Link.l1 = "Sí lo estoy. Todo el lote está en la bodega, " + sTemp + " unidades, como se acordó.";
				Link.l1.go = "TakeGun";
			}
		}
		else
		{
			dialog.text = "No veo tu barco en el puerto. ¿Estás sugiriendo arrastrar esos cañones por la selva? Apresúrate a nuestro puerto y vuelve.";
			link.l1 = "Mi barco está al otro lado de la isla. Lo llevaré al puerto.";
			link.l1.go = "exit";
		}
		break;

	case "TakeGun":
		if (pchar.questTemp.PrisonGun.Luck == 4)
		{
			dialog.Text = RandPhraseSimple("Sabes, es realmente incómodo, pero tengo que denunciar nuestro trato. Acabamos de tener una inspección financiera, y sabes lo escrupulosos que son en tales cosas. Simplemente no puedo hacer nada. Lo siento.", "Capitán, ya sabes... Bueno, nos han enviado cañones desde la metrópoli, y me vi obligado a comprarlos, por supuesto. Precios exorbitantes, pero... Lamento mucho haberte fallado... Tampoco me siento bien al respecto.");
			Link.l1 = "¡Maldita sea! ¿Y qué se supone que haga con ellos ahora?";
			Link.l1.go = "TakeGun_no";
		}
		else
		{
			dialog.Text = RandPhraseSimple("Excelente. Enviaré un escuadrón de la guarnición para descargarlos.", "Excelente. Mis soldados te ayudarán a descargar los cañones.");
			Link.l1 = "¿Has preparado el pago?";
			Link.l1.go = "TakeGun_1";
		}
		break;

	case "TakeGun_no":
		dialog.Text = "No lo sé. Véndelos en el astillero, equipa un barco mercante, húndelos... Realmente no tengo idea. Y por favor, no le cuentes a nadie sobre este trato.";
		Link.l1 = "¡Oh, lo dices tú! ¡Simplemente no tengo palabras!";
		Link.l1.go = "exit";
		AddQuestRecord("PrisonGun", "3");
		CloseQuestHeader("PrisonGun");
		DeleteAttribute(pchar, "questTemp.PrisonGun");
		NextDiag.TempNode = "First time";
		break;

	case "TakeGun_late":
		dialog.Text = "No tengo ni idea. Es tu problema. Véndelos, deshazte de ellos o húndelos realmente no me importa.";
		Link.l1 = "Oh, eso fue simplemente una pérdida de tiempo...";
		Link.l1.go = "exit";
		AddQuestRecord("PrisonGun", "4");
		AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("", ""));
		AddQuestUserData("PrisonGun", "sName", GetFullName(npchar));
		CloseQuestHeader("PrisonGun");
		DeleteAttribute(pchar, "questTemp.PrisonGun");
		NextDiag.TempNode = "First time";
		break;

	case "TakeGun_1":
		iGunGoods = pchar.questTemp.PrisonGun.Goods;
		amount = sti(pchar.questTemp.PrisonGun.Qty);
		iTemp = sti(pchar.questTemp.PrisonGun.Sum);
		dialog.Text = "Por supuesto. Aquí tienes tu oro, haz lo que quieras.";
		Link.l1 = "¡Gracias! ¡Fue un placer hacer negocios contigo!";
		Link.l1.go = "TakeGun_2";
		TakeNItems(pchar, "gold_dublon", iTemp);
		Log_Info("Has recibido " + FindRussianDublonString(sti(pchar.questTemp.WPU.Escort.Money)) + "");
		PlaySound("interface\important_item.wav");
		RemoveCharacterGoods(Pchar, iGunGoods, amount);
		break;

	case "TakeGun_2":
		dialog.Text = "El sentimiento es mutuo. Has sido de gran ayuda. Y, te suplico, mantén ese trato en esta habitación.";
		Link.l1 = "Por supuesto. Mis mejores deseos para ti.";
		Link.l1.go = "exit";
		AddQuestRecord("PrisonGun", "2");
		AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("", ""));
		CloseQuestHeader("PrisonGun");
		DeleteAttribute(pchar, "questTemp.PrisonGun");
		NextDiag.TempNode = "First time";
		break;
	// <-- орудия для форта

	// Jason --> мини-квест Дефицитный товар
	case "Wine_prison":
		dialog.text = "¿¡Qué?! ¡He prohibido estrictamente cualquier bebida en el territorio del fuerte! Bueno, él tendrá que pagar por esto. Descontaré 1000 pesos de su pago y te los entregaré como recompensa por tu vigilancia. Y este tipo estará en detención durante tres días.";
		link.l1 = "Gracias, " + GetAddress_FormToNPC(NPChar) + ". Detener tales violaciones es nuestro deber común.";
		link.l1.go = "exit";
		AddMoneyToCharacter(pchar, 1000);
		ChangeCharacterComplexReputation(pchar, "nobility", -1);
		DeleteAttribute(pchar, "questTemp.Wine.bottle");
		pchar.quest.Wine_Exchange.over = "yes"; // снять прерывание
		pchar.quest.WineTraderQM.over = "yes";	// снять прерывание
		WineTraderQMDel();
		sld = characterFromId(pchar.questTemp.Wine.id);
		sld.lifeday = 0;
		CloseQuestHeader("Wine");
		NextDiag.TempNode = "First time";
		break;
	// <-- мини-квест Дефицитный товар

	// Карибские нравы
	case "trial":
		iTest = FindColony(NPChar.City); // город
		QuestPointerDelLoc("portpax_town", "reload", "gate_back");
		QuestPointerDelLoc("portpax_exittown", "reload", "reload2_back");
		QuestPointerDelLoc("portpax_fort", "reload", "reload2");
		if (iTest != -1)
		{
			rColony = GetColonyByIndex(iTest);
		}
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
		{
			if (GetSquadronGoods(pchar, GOOD_BOMBS) < 2500 || GetSquadronGoods(pchar, GOOD_POWDER) < 2500)
			{
				dialog.text = "¿Hmm. Pero esta partida no está completa! ¿Cómo ha ocurrido esto?";
				link.l1 = "¡Maldita sea! Por favor, perdóname, es mi culpa. Compraré inmediatamente la cantidad que falta y te entregaré el lote completo, como acordamos.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "¿Así que tú eres nuestro mensajero? Bien. Vamos a arreglar las cosas con la carga, y luego recibirás instrucciones adicionales.";
				link.l1 = "Bien.";
				link.l1.go = "trial_1";
			}
		}
		else
		{
			dialog.text = "No veo tu barco en el puerto. ¿Estás sugiriendo arrastrar la carga a través de la selva? Date prisa a nuestro puerto y regresa.";
			link.l1 = "Mi barco está al otro lado de la isla. Lo llevaré al puerto.";
			link.l1.go = "exit";
		}
		break;

	case "trial_1":
		if (!bImCasual)
			pchar.quest.Trial_FrahtFail.over = "yes"; // belamour legendary edition если был - снять таймер
		dialog.text = "Bien, bombas y pólvora, 2500 unidades cada una... Bueno. Los soldados descargarán la carga, tus hombres pueden tomar un descanso. Aquí está tu pago por el flete, cinco mil pesos.";
		link.l1 = "¡Gracias! ¿Qué debería hacer a continuación? Monsieur LeCroix dijo...";
		link.l1.go = "trial_2";
		DelLandQuestMark(npchar);
		break;

	case "trial_2":
		AddMoneyToCharacter(pchar, 5000);
		RemoveCharacterGoods(pchar, GOOD_BOMBS, 2500);
		RemoveCharacterGoods(pchar, GOOD_POWDER, 2500);
		dialog.text = "Sí, sí, recibirás tus instrucciones ahora. ¿Estás listo para prestar atención?";
		link.l1 = "Claro, oficial.";
		link.l1.go = "trial_3";
		break;

	case "trial_3":
		dialog.text = "Así pues, nuestro buque militar el 'Warlike' está navegando cerca de la colonia española de Portobello, en la parte sur de Tierra Firme. Esta nave está bajo el mando de Florian Shoke, que prepara una emboscada a un galeón pesado español que zarpará de Portobello dentro de dos semanas.\nEl problema es que los cañones de nuestra fragata adolecen de un defecto de fundición, necesitamos reemplazar quince cañones para salvar la misión; de lo contrario, el galeón superará a 'Warlike' tanto en cañones como en hombres.\nSin el reemplazo, Florian Shoke se verá obligado a navegar sin sentido. Tal secuencia de acontecimientos es altamente indeseable. Tu tarea es salvar la misión entregando quince cañones en un plazo de catorce días.";
		link.l1 = "Entonces, ¿necesito llevar a bordo quince cañones, dirigirme a Portobello, buscar la fragata 'Militante' y entregar los cañones al capitán Florian Shoke?";
		link.l1.go = "trial_4";
		break;

	case "trial_4":
		dialog.text = "Exactamente. Lo has entendido bien. ¿Estás listo para emprender esta misión?";
		link.l1 = "¿Qué hay del pago?";
		link.l1.go = "trial_5";
		link.l2 = "Lo siento, oficial, pero simplemente no quiero involucrarme. Por favor, discúlpame.";
		link.l2.go = "trial_exit";
		break;

	case "trial_exit":
		dialog.text = "Estás en tu derecho, pero contaba con tu acuerdo. Ahora tendré que buscar otro mensajero, aunque no me queda mucho tiempo... Bueno, no te retengo más, capitán.";
		link.l1 = "Los mejores deseos.";
		link.l1.go = "trial_exit_1";
		break;

	case "trial_exit_1":
		DialogExit();
		AddQuestRecord("Trial", "6");
		CloseQuestHeader("Trial");
		DeleteAttribute(pchar, "questTemp.Trial");
		pchar.questTemp.TrialEnd = true;
		break;

	case "trial_5":
		dialog.text = "No te preocupes por eso. Florian Shoke te pagará doscientos doblones de oro del tesoro del barco. Además, estoy seguro de que querrá usar a ti y a tu barco para sus propios objetivos, con tu consentimiento, por supuesto.";
		link.l1 = "¡Está bien, estoy en esta misión! ¿Dónde están los cañones?";
		link.l1.go = "trial_6";
		break;

	case "trial_6":
		dialog.text = "Daré una orden a los soldados para que los carguen en su barco de inmediato. ¡Zarpe tan pronto como pueda, señor! ¡Buena suerte!";
		link.l1 = "Gracias. Seguramente la suerte no hará daño, y tampoco lo hará el viento de cola...";
		link.l1.go = "trial_7";
		break;

	case "trial_7":
		DialogExit();
		AddQuestRecord("Trial", "7");
		pchar.questTemp.Trial = "cannon";
		// belamour legendary edition
		if (!bImCasual)
			SetFunctionTimerCondition("Trial_CannonFail", 0, 0, 21, false);
		else
			NewGameTip("Exploration mode: el temporizador está desactivado.");
		SetCharacterGoods(pchar, GOOD_CANNON_24, GetCargoGoods(pchar, GOOD_CANNON_24) + 15);
		if (MOD_SKILL_ENEMY_RATE >= 6)
		{
			EnemyNationHunterOnMap(true); // запуск перехватчиков
		}
		pchar.quest.Trial_cannon.win_condition.l1 = "location";
		pchar.quest.Trial_cannon.win_condition.l1.location = "Portobello";
		pchar.quest.Trial_cannon.function = "Trial_CreateFlorianFrigate";
		// Sinistra - квест "Встреча с Диего"
		bDisableFastReload = true;
		PChar.quest.VsD_GiumDyubua.win_condition.l1 = "location";
		PChar.quest.VsD_GiumDyubua.win_condition.l1.location = "PortPax_Fort";
		PChar.quest.VsD_GiumDyubua.win_condition = "VsD_GiumDyubua";
		AddMapQuestMarkShore("Shore47", false);
		break;

	// Опасный груз -->
	case "zpq_prs1":
		if (!isBadReputation(pchar, 70))
		{
			dialog.text = "Hm, quizás. Bueno, debido a tu buena reputación, tomaré el riesgo de confiar en ti. En otro caso, ni siquiera hablaría de eso contigo. El caso es que necesitamos un lote bastante grande de carga especial, por lo que necesitarás un barco de carga grande y voluntad para arriesgar. Además, debes darme tu palabra de no decirle a nadie sobre eso.\nSi te resulta embarazoso, entonces dímelo ahora mismo. Creo que he dejado claro mi punto...";
			link.l1 = "Suena intrigante. Estoy dentro si el pago está bien, aunque no tengo idea de qué carga estás hablando. De todas formas, tienes mi palabra.";
			link.l1.go = "zpq_prs2";
			link.l2 = "Diría que no, supongo... si te diera mi palabra tendría que hacer un trabajo que parece bastante problemático. No lo haré.";
			link.l2.go = "zpq_fld";
			notification("Reputation Check Passed", "None");
		}
		else
		{
			dialog.text = "Tu reputación es inaceptable para mí. Te pido que abandones la sala. Somos capaces de resolver nuestros problemas por nosotros mismos.";
			link.l1 = "Lo que sea, resuélvelos entonces...";
			link.l1.go = "exit";
			notification("Reputation Too Low! (" + XI_ConvertString(GetReputationName(71)) + ")", "None");
		}
		break;

	case "zpq_fld":
		dialog.text = "Bueno, al menos me has rechazado de manera honesta... Ya no te retengo más.";
		link.l1 = "Adiós.";
		link.l1.go = "exit";
		pchar.questTemp.zpq = "failed";
		DelLandQuestMark(npchar);
		DelMapQuestMarkCity("Cumana");
		break;

	case "zpq_fld2":
		dialog.text = "Eh, en realidad no esperaba eso de ti. Tengo que pedirte que te vayas... Y recuerda tu promesa de no divulgar ninguna información.";
		link.l1 = "Lo siento...";
		link.l1.go = "exit";
		ChangeCharacterComplexReputation(pchar, "nobility", -3);
		if (pchar.questTemp.zpq == "begin")
		{
			AddQuestRecord("zpq", "6");
			AddQuestUserData("zpq", "sSex", GetSexPhrase("", ""));
			CloseQuestHeader("zpq");
		}
		pchar.questTemp.zpq = "failed";
		break;

	case "zpq_prs2":
		dialog.text = "Espléndido. Espléndido. El problema es que la reciente tormenta ha dañado nuestro suministro de pólvora en el arsenal del fuerte. Espero que no necesite explicarte que tenemos un problema delicado aquí. En caso de un asedio prolongado, el fuerte no podrá hacer nada. No duraremos mucho.";
		link.l1 = "Ahora veo. ¿Qué carga necesitas y qué cantidad?";
		link.l1.go = "zpq_prs3";
		DelLandQuestMark(npchar);
		DelMapQuestMarkCity("Cumana");
		break;

	case "zpq_prs3":
		dialog.text = "Necesitamos 15 000 barriles de pólvora. Te pagaré 100 000 pesos... Debes entender que es un muy buen precio. Nuestra situación actual me obliga a asumir tales costos aunque fue problemático convencer al tesorero del gobernador de ello... La temporada de tormentas no nos permitirá usar nuestras propias líneas de suministro y no queremos que todos sepan sobre este problema...";
		link.l1 = "Ya veo... el precio es realmente atractivo. Has mencionado riesgos...";
		link.l1.go = "zpq_prs4";
		break;

	case "zpq_prs4":
		dialog.text = "Quise decir que una cantidad tan grande de pólvora puede ser muy peligrosa durante el transporte. He visto unas cuantas explosiones con mis propios ojos, a veces una sola chispa puede hacer el trabajo. Pero si te enfrentas a la tormenta... Los convoyes enteros suelen mantenerse a distancia del potencial barco incendiario. Si explota, entonces todos están muertos!";
		link.l1 = "Entiendo... Pero siempre cumplo mi palabra, considera que está hecho.";
		link.l1.go = "zpq_prs5";
		link.l2 = "Bueno, señor... Me has contado cosas tan terribles, que he perdido cualquier deseo de hacer ese trabajo.";
		link.l2.go = "zpq_fld2";
		break;

	case "zpq_prs5":
		dialog.text = "Bien, estoy muy contento de que hayamos hecho un trato. Te pagaré tan pronto como me traigas la carga.\nTendré dinero en una semana, no antes, así que tómate tu tiempo pero te pediría que intentes no demorar demasiado.";
		link.l1 = "Lo entiendo, señor. Estoy en ello.";
		link.l1.go = "zpq_prs5_ok";
		break;

	case "zpq_prs5_ok":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		pchar.questTemp.zpq = "begin";
		pchar.questTemp.zpq.time = 20;
		AddQuestRecord("zpq", "1");
		AddQuestUserData("zpq", "sSex", GetSexPhrase("", ""));
		SaveCurrentQuestDateParam("pchar.questTemp.zpq");
		break;

	case "zpq_ex":
		dialog.text = "¡Al fin! Pensé que ya te habías olvidado de nuestro trato. Ordenaré inmediatamente a mis soldados que comiencen a descargar tu barco. Trabajar con pólvora es un negocio muy delicado, ¡ja-ja!";
		link.l1 = "Es grandioso, señor, pero debo recordarle el pago.";
		link.l1.go = "zpq_ex2";
		RemoveCharacterGoods(pchar, GOOD_POWDER, 15000);
		AddCharacterExpToSkill(pchar, "Sailing", 500);
		AddCharacterExpToSkill(pchar, "Fortune", 500);

		pchar.quest.zpq_sld1_fc.win_condition.l1 = "location";
		pchar.quest.zpq_sld1_fc.win_condition.l1.location = "Cumana_ExitTown";
		pchar.quest.zpq_sld1_fc.function = "zpq_sld1_fc";
		break;

	case "zpq_ex2":
		dialog.text = "Sí, por supuesto. Se te pagará 50 000 pesos como acordamos.";
		link.l1 = "¿Probablemente me estás tomando el pelo, señor?! ¡Tuvimos un trato por 100 000 pesos!";
		link.l1.go = "zpq_ex3";
		if (CheckCharacterPerk(pchar, "Trustworthy"))
		{
			notification("Trustworthy", "Trustworthy");
			link.l2 = "(Confiable) ¡Estoy empezando a pensar que vas a engañarme para que no me vaya de aquí sin mis 125 000 pesos!";
			link.l2.go = "zpq_ex4";
		}
		link.l3 = "Hm.. Veo que las circunstancias han cambiado. Bueno, será mejor que tome el dinero y me vaya...";
		link.l3.go = "zpq_ex5";
		break;

	case "zpq_ex3":
		if (GetSummonSkillFromName(pchar, "Leadership") > 35)
		{
			notification("Skill Check Passed", "Leadership");
			dialog.text = "Ah, sí... ¡Exactamente! 100 000 pesos. Lo había olvidado, perdóname. Es culpa de mi edad, esclerosis ya sabes... Claro, aquí están tus monedas. Fue un placer hacer negocios contigo, capitán. Ahora lo siento, pero tengo mucho trabajo que hacer...";
			link.l1 = "Lo mismo para ti, señor. Nos vemos.";
			link.l1.go = "exit";
			pchar.questTemp.zpq = "completed";
			AddQuestRecord("zpq", "2");
			AddQuestUserData("zpq", "sSex", GetSexPhrase("", ""));
			CloseQuestHeader("zpq");
			pchar.questTemp.zpq.sum = 100000;
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
		}
		else
		{
			notification("Skill Check Failed (36)", "Leadership");
			dialog.text = "¿¡Qué?! ¡Toma tu dinero y lárgate, o te pudrirás en este casamato!";
			link.l1 = "¡Eres un mentiroso, señor! Te aconsejo que me des mi dinero de buena manera, ¡o quitaré la carga!";
			link.l1.go = "zpq_ex_agry";
			link.l2 = "Perdóneme... Bien, tomaré la suma que ofreces y estamos a mano.";
			link.l2.go = "zpq_ex5";
			Log_info("¡Tu capacidad de liderazgo no es suficiente!");
		}
		break;

	case "zpq_ex4":
		dialog.text = "¡Qué grosería! No estoy loco y recuerdo perfectamente que ofrecí 100 000 pesos.\n ¡Maldita sea! ¡No voy a jugar a tus juegos!";
		link.l1 = "Cálmate. Piensa en el brander listo lleno de pólvora justo frente a tu fuerte. Si digo solo una palabra, tu fuerte se convertirá en ruinas.";
		link.l1.go = "zpq_ex6";
		break;

	case "zpq_ex6":
		dialog.text = "Hm-Hm... argumento fuerte. ¿Dices 125 000 pesos? Toma, y perdóname ahora pero tengo trabajo que hacer...";
		link.l1 = "Adiós, señor. Nos vemos.";
		link.l1.go = "exit";
		pchar.questTemp.zpq = "completed";
		AddQuestRecord("zpq", "5");
		CloseQuestHeader("zpq");
		pchar.questTemp.zpq.sum = 125000;
		AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
		/*else
		{
			dialog.text = "¡¿Qué?! ¡Soy un oficial militar! ¿Crees que puedes asustarme, niño? ¡Guardias, arrésten"+GetSexPhrase("lo","la")+"!";
			link.l1 = "Buena suerte en intentarlo, ratas de casamates...";
			link.l1.go = "zpq_ex_war";
		}*/
		break;

	case "zpq_ex5":
		dialog.text = "¡Espléndido! Has tomado la decisión correcta. Toma tus monedas y adiós. ¡Fue un placer!";
		link.l1 = "Adiós...";
		link.l1.go = "exit";
		pchar.questTemp.zpq = "completed";
		AddQuestRecord("zpq", "3");
		AddQuestUserData("zpq", "sSex", GetSexPhrase("", ""));
		CloseQuestHeader("zpq");
		pchar.questTemp.zpq.sum = 50000;
		AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
		break;

	case "zpq_ex_agry":
		dialog.text = "¡Ah, bastardo! ¡Guardias, arrésten" + GetSexPhrase("lo", "la") + "!";
		link.l1 = "¡Argh! Parece que tendré que quitar mi dinero de tu cuerpo sin aliento...";
		link.l1.go = "zpq_ex_war";
		break;

	case "zpq_ex_war":
		DialogExit();
		NextDiag.CurrentNode = NextDiag.TempNode;
		LAi_SetFightMode(PChar, true);
		pchar.questTemp.zpq = "failed";
		AddQuestRecord("zpq", "4");
		CloseQuestHeader("zpq");
		pchar.questTemp.zpq.sum = 100000;
		AddMoneyToCharacter(npchar, makeint(sti(pchar.questTemp.zpq.sum) * 2 + rand(5000)));
		GiveItem2Character(npchar, "blade_21");
		EquipCharacterbyItem(npchar, "blade_21");
		npchar.SaveItemsForDead = true;
		npchar.DontClearDead = true;
		npchar.cirassId = Items_FindItemIdx("cirass3");
		chrDisableReloadToLocation = true;
		string slai_group = GetNationNameByType(sti(npchar.nation)) + "_citizens";
		LAi_group_AttackGroup(slai_group, LAI_GROUP_PLAYER);
		LAi_group_SetCheck(slai_group, "OpenTheDoors");
		AddSimpleRumour("¡Qué cosas tan terribles ocurren aquí! ¡Dicen que algún prisionero ha escapado de las casamatas! ¡Mató a todos los guardias, robó el tesoro y se largó! ¡Caramba!", SPAIN, 5, 1);
		break;
		// <-- Опасный груз
	}
}

void GetGunType()
{
	int iGunType;
	if (makeint(pchar.rank) < 6)
		iGunType = rand(1); // 18&&24
	if (makeint(pchar.rank) >= 6 && makeint(pchar.rank) < 15)
		iGunType = rand(2); // 24&&32
	if (makeint(pchar.rank) >= 15 && makeint(pchar.rank) < 24)
		iGunType = rand(2) + 2; // 32&&36&&42
	if (makeint(pchar.rank) >= 24)
		iGunType = 5 - rand(1); // 36clv&&42
	int iAdd = makeint(GetSummonSkillFromName(pchar, SKILL_COMMERCE) / 20);

	switch (iGunType)
	{
	case 0:
		pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_24;
		pchar.questTemp.PrisonGun.Price = 28 + iAdd;
		pchar.questTemp.PrisonGun.Qty = sti(pchar.rank) * 5 + 25 + rand(sti(pchar.rank));
		pchar.questTemp.PrisonGun.Text = "24 calibre cannons";
		break;
	case 1:
		pchar.questTemp.PrisonGun.Goods = GOOD_CULVERINE_18;
		pchar.questTemp.PrisonGun.Price = 25 + iAdd;
		pchar.questTemp.PrisonGun.Qty = sti(pchar.rank) * 5 + 25 + rand(sti(pchar.rank));
		pchar.questTemp.PrisonGun.Text = "couleuvrines";
		break;
	case 2:
		pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_32;
		pchar.questTemp.PrisonGun.Price = 32 + iAdd;
		pchar.questTemp.PrisonGun.Qty = sti(pchar.rank) * 3 + 15 + rand(sti(pchar.rank));
		pchar.questTemp.PrisonGun.Text = "32 calibre cannons";
		break;
	case 3:
		pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_36;
		pchar.questTemp.PrisonGun.Price = 36 + iAdd;
		pchar.questTemp.PrisonGun.Qty = sti(pchar.rank) * 3 + 15 + rand(sti(pchar.rank));
		pchar.questTemp.PrisonGun.Text = "36 calibre cannons";
		break;
	case 4:
		pchar.questTemp.PrisonGun.Goods = GOOD_CULVERINE_36;
		pchar.questTemp.PrisonGun.Price = 49 + iAdd;
		pchar.questTemp.PrisonGun.Qty = sti(pchar.rank) + 15 + rand(sti(pchar.rank));
		pchar.questTemp.PrisonGun.Text = "full couleuvrines";
		break;
	case 5:
		pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_42;
		pchar.questTemp.PrisonGun.Price = 40 + iAdd;
		pchar.questTemp.PrisonGun.Qty = sti(pchar.rank) + 20 + rand(sti(pchar.rank));
		pchar.questTemp.PrisonGun.Text = "42 calibre cannons";
		break;
	}
}
