// полковник Фокс - бравый командир морской пехоты 'морские лисы'.
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		if (CheckAttribute(pchar, "questTemp.Terrapin_KathyReward"))
		{
			dialog.text = "¿Qué desea, señor? Oh... por... ¡espera! ¡Eres el capitán francés que ha salvado a mi hija de las sucias manos de los servidores de Levasseur!";
			link.l1 = "Veo que Catherine ya le ha hablado de mí...";
			link.l1.go = "terrapin";
			break;
		}
		if (CheckAttribute(pchar, "questTemp.Guardoftruth.Usurer") && !CheckAttribute(npchar, "quest.utensil"))
		{
			dialog.text = "¿Qué desea, señor?";
			link.l1 = "Buen día, Coronel. He venido a usted por unos asuntos 'poco comunes'. ¿Podría dedicarme un poco de su tiempo?";
			link.l1.go = "guardoftruth";
			break;
		}
		// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
		if (CheckAttribute(pchar, "questTemp.FMQN") && pchar.questTemp.FMQN == "eng_reward")
		{
			dialog.text = "Por lo que entiendo, ¿eres el Capitán francés que ayudó a mis hombres en su misión en Sint-Maarten?" + TimeGreeting() + ".";
			link.l1 = TimeGreeting() + ", Coronel. Sí, ese sería yo.";
			link.l1.go = "FMQN";
			break;
		}
		dialog.text = "¿Qué desea, señor?";
		link.l1 = "Nada, Coronel. Me retiro.";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	case "guardoftruth":
		dialog.text = "Entonces, escúpelo de una vez, ya que has llegado hasta aquí...";
		link.l1 = "Recientemente abordaste una goleta bajo el mando de Rollie el Cap, un pirata holandés, y trajiste al capitán aquí, a Saint-John's.";
		link.l1.go = "guardoftruth_1";
		break;

	case "guardoftruth_1":
		dialog.text = "¿Capitán? ¡Oh, no me hagas reír! Este miserable criminal no tiene derecho a ser llamado por este honorable rango. He capturado a un maldito pirata, el jefe de una manada de lobos, que ha robado y asesinado a comerciantes y mercaderes ingleses. Y me aseguré de que él y sus degenerados obtuvieran lo que merecían: ¡todo Saint-John's ha visto su ahorcamiento en el muelle!";
		link.l1 = "Supongo que no podré interrogar a este canalla entonces... Coronel, ¿quizás podrías ayudarme? El pirata tenía algo en su posesión que no le pertenecía: un incensario de oro. ¿Encontraste algo en él que se parezca a eso?";
		link.l1.go = "guardoftruth_2";
		break;

	case "guardoftruth_2":
		dialog.text = "No, lo registramos y ese bribón no poseía ninguna pertenencia. Además, ¡todas ellas seguramente fueron tomadas de comerciantes honestos! Y sobre tu preocupación... hmm no, no lo hemos encontrado. ¿Y qué podría hacer un incensario en un barco pirata? ¿Realmente crees que había un sacerdote entre ellos?";
		link.l1 = "No, no es así. Rollie el Cap lo compró del usurero en Willemstad, quien lo había comprado de otro pirata. El incensario es fino y caro, y estoy intentando devolverlo a sus legítimos dueños. Supongo que Rollie le echó el ojo como una urraca.";
		link.l1.go = "guardoftruth_3";
		break;

	case "guardoftruth_3":
		dialog.text = "En verdad, Rollie tenía las bodegas vacías y unos pocos cofres con doblones cuando abordamos y capturamos su barco. Nada más que basura. Ningún objeto de valor, ningún incensario dorado. Recordaría un objeto tan inapropiado para un pirata.\nSospecho que ese maldito pirata ha escondido sus ahorros en Dominica. Incluso desembarcamos allí y registramos el área, pero no encontramos nada. Pero no nos quedamos en la isla ni exploramos sus profundidades debido a la gran cantidad de salvajes allí.";
		link.l1 = "Hm... El pirata podría haber escondido el incensario con el resto de sus cosas robadas en algún lugar de Dominica... Qué lástima. ¿Has interrogado al pirata antes de la ejecución?";
		link.l1.go = "guardoftruth_4";
		break;

	case "guardoftruth_4":
		dialog.text = "Lo hice... y él simplemente comenzó a reírse en mi cara. Pero realmente no me importaban sus escondites. Colgaron a Rollie el Cap y eso es lo más importante.";
		link.l1 = "Ya veo. Gracias por tu relato y tu tiempo, Coronel. Adiós...";
		link.l1.go = "guardoftruth_5";
		break;

	case "guardoftruth_5":
		DialogExit();
		npchar.quest.utensil = "true";
		AddQuestRecord("Guardoftruth", "24");
		Island_SetReloadEnableGlobal("Dominica", true); // patch-7
		// заполняем сундук
		pchar.GenQuestBox.Shore27 = true;
		pchar.GenQuestBox.Shore27.box1.money = 30000;
		pchar.GenQuestBox.Shore27.box1.items.gold_dublon = 100;
		pchar.GenQuestBox.Shore27.box1.items.chest = 1;
		pchar.GenQuestBox.Shore27.box1.items.icollection = 1;
		pchar.GenQuestBox.Shore27.box1.items.jewelry40 = 15;
		pchar.GenQuestBox.Shore27.box1.items.jewelry41 = 22;
		pchar.GenQuestBox.Shore27.box1.items.jewelry42 = 8;
		pchar.GenQuestBox.Shore27.box1.items.jewelry43 = 20;
		pchar.GenQuestBox.Shore27.box1.items.jewelry44 = 33;
		pchar.GenQuestBox.Shore27.box1.items.jewelry45 = 16;
		pchar.GenQuestBox.Shore27.box1.items.jewelry46 = 58;
		pchar.GenQuestBox.Shore27.box1.items.jewelry35 = 1; // кадило
		pchar.quest.GuardOT_finddominicachest.win_condition.l1 = "item";
		pchar.quest.GuardOT_finddominicachest.win_condition.l1.item = "jewelry35";
		pchar.quest.GuardOT_finddominicachest.function = "GuardOT_DominicaChest";
		break;

	case "terrapin":
		dialog.text = "¡Varias veces, capitán! Tu honorable y valiente hazaña era difícil de esperar de un francés. Te debo mi gratitud, como soldado y como padre. No hay nada más valioso para mí en este mundo entero que mi hija...";
		link.l1 = "Me alegra haber podido ayudar, y espero que con mis acciones llegues a cambiar tu opinión sobre los franceses, con el tiempo.";
		link.l1.go = "terrapin_1";
		break;

	case "terrapin_1":
		dialog.text = "La presencia de un caballero tan honorable y generoso como usted, que ha arriesgado su vida por una desconocida muchacha inglesa, provocará un esencial acercamiento en mi relación con sus compatriotas.";
		link.l1 = "Hay gente honesta entre las ratas de cualquier nación, coronel...";
		link.l1.go = "terrapin_2";
		break;

	case "terrapin_2":
		dialog.text = "¡Y lo has demostrado! Una recompensa te espera, capitán. Por supuesto, la vida de una hija no tiene precio, pero Jonathan Fox siempre paga sus deudas, ¡lo juro! Eres un verdadero soldado, por lo tanto, mi regalo para ti es un obsequio de soldado. Aquí, echa un vistazo.\nEste es un trabuco, un excelente mosquete naval, puede ser usado con una mano. Puedes cargarlo con flechas especiales que siempre atravesarán incluso la coraza más duradera. También dispara metralla y su sólida construcción te permite cargarlo con clavos. Ten, tómalo, ahora es tuyo.";
		link.l1 = "¡Un regalo tan excelente para un soldado, le agradezco, Coronel!";
		link.l1.go = "terrapin_3";
		break;

	case "terrapin_3":
		Log_Info("¡Has recibido un trabuco!");
		Log_Info("¡Has recibido 10 flechas!");
		Log_Info("¡Has recibido 10 cargas de clavos!");
		Log_Info("¡Has recibido instrucciones para crear flechas arpón!");
		Log_Info("¡Has recibido instrucciones para crear cargas de clavos!");
		GiveItem2Character(pchar, "pistol8");
		TakeNItems(pchar, "harpoon", 10);
		TakeNItems(pchar, "GunEchin", 10);
		GiveItem2Character(pchar, "recipe_harpoon");
		GiveItem2Character(pchar, "recipe_GunEchin");
		PlaySound("interface\important_item.wav");
		dialog.text = "También te entrego un pequeño lote de municiones e instrucciones para su creación. ¡Sería una pena si no usas su poder al máximo!";
		link.l1 = "Gracias, Coronel. No rechazaré tal regalo, pero quiero que sepas que no salvé a Catherine por una recompensa. Simplemente no podría haber dejado que la desprotegida chica sufriera daño alguno.";
		link.l1.go = "terrapin_4";
		break;

	case "terrapin_4":
		dialog.text = "Lo sé, capitán. Eso le honra doblemente. Catherine quedó realmente encantada por usted y no es tarea fácil causarle una buena impresión. Nuevamente, le debemos nuestra gratitud por haberla rescatado. ¡Le debo una!";
		link.l1 = "Bueno, le agradezco por el regalo, Coronel. Envíe mis mejores saludos a Catherine, y deseo que ella escuche a su padre la próxima vez.";
		link.l1.go = "terrapin_5";
		break;

	case "terrapin_5":
		dialog.text = "¡Lo haré, capitán! ¡Adiós, y buenos vientos!";
		link.l1 = "Adiós, Coronel.";
		link.l1.go = "exit";
		DeleteAttribute(pchar, "questTemp.Terrapin_KathyReward");
		ChangeCharacterComplexReputation(pchar, "nobility", 5);
		ChangeCharacterComplexReputation(pchar, "fame", 5);
		ChangeCharacterNationReputation(pchar, ENGLAND, 20);
		break;

	// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
	case "FMQN":
		DelLandQuestMark(npchar);
		dialog.text = "He leído el informe. Tus acciones son altamente valoradas, por lo tanto, debes ser recompensado. Treinta mil pesos por servicios de expedición y armas por heroísmo en la soldadesca. ¡Acepta esta espada y este arcabuz! ¡Ahora son todos tuyos!";
		link.l1 = "Gracias, señor.";
		link.l1.go = "FMQN_1";
		break;

	case "FMQN_1":
		dialog.text = "Por supuesto, capitán. También se le recompensa con el amor y respeto de las colonias británicas, las autoridades y de mí personalmente. ¡Gracias por no abandonar a mis hombres y ayudarles en su misión!";
		link.l1 = "Es un placer, coronel...";
		link.l1.go = "FMQN_2";
		break;

	case "FMQN_2":
		dialog.text = "Ahora, por favor disculpe... tengo otros asuntos que atender. Que Dios le acompañe, capitán.";
		link.l1 = "Adiós, señor.";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("FMQN_EnglandComplete");
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}
