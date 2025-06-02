void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Error. Háznoslo saber.";
			link.l1 = "¡Claro!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "FalseTrace":
			DelMapQuestMarkCity(pchar.questTemp.FalseTrace.StartCity);
			dialog.text = "Buenas tardes, capitán... ehm... ¡kha-hahrm! Malditas minas... Permítame presentarme. Adam Rayner. Soy un hombre sencillo y no me gustan los prólogos largos, así que lo soltaré de una vez. ¿Quiere ganar buen dinero? Le ofrezco un pequeño negocio que ninguno de los dos podrá manejar por sí solo.";
			link.l1 = "¡Je! ¿Buen dinero? Interesante. Te escucho, Adam.";
			link.l1.go = "FalseTrace_1";
			link.l2 = "Sabes, lo siento, pero no pareces de fiar. Así que no haré ningún negocio contigo.";
			link.l2.go = "FalseTrace_exit";
		break;
		
		case "FalseTrace_exit":
			dialog.text = "¿Confiable? ¡Ja-ja! Uno no debería juzgar a un hombre por su cara. Bueno, no importa. Acabas de perder una buena oportunidad de ganar dinero fácil y rápidamente. Encontraré a alguien más cooperativo...";
			link.l1 = "¡Nuestra conversación ha terminado, señor. ¡Adiós!";
			link.l1.go = "FalseTrace_exit_1";
		break;
		
		case "FalseTrace_exit_1":
			DialogExit();
			DelLandQuestMark(npchar);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			DeleteAttribute(pchar, "questTemp.FalseTrace");
		break;
		
		case "FalseTrace_1":
			//выбираем целевой пункт
			switch (hrand(2))
			{
				case 0: 
					pchar.questTemp.FalseTrace.DayQty = 18;
					pchar.questTemp.FalseTrace.TargetCity = "Beliz";
					pchar.questTemp.FalseTrace.TargetShore = "Shore8";
				break;
				case 1: 
					pchar.questTemp.FalseTrace.DayQty = 22;
					pchar.questTemp.FalseTrace.TargetCity = "Marigo";
					pchar.questTemp.FalseTrace.TargetShore = "Shore41";
				break;
				case 2: 
					pchar.questTemp.FalseTrace.DayQty = 20;
					pchar.questTemp.FalseTrace.TargetCity = "Santodomingo";
					pchar.questTemp.FalseTrace.TargetShore = "Mayak8";
				break;
			}
			pchar.questTemp.FalseTrace.ShipName = GenerateRandomNameToShip(sti(npchar.nation));
			pchar.questTemp.FalseTrace.Mation = sti(npchar.nation);
			dialog.text = "¡Kha! Un placer hacer negocios con alguien tan ingenioso como usted, Capitán. Entonces, el trabajo es sencillo: hay un filibote cargado con una buena cantidad de plata y pronto zarpará de uno de los puertos locales. Un solo navío, sin escolta. ¿Tonto, verdad? K-kha\n Fácil como un pastel. Le digo dónde y cuándo, usted toma el botín y yo obtengo mi parte.";
			link.l1 = "¿Y por supuesto, quieres recibirlo en efectivo ahora mismo?";
			link.l1.go = "FalseTrace_2";
		break;
		
		case "FalseTrace_2":
			dialog.text = "¿Parezco un miserable bribón, capitán? De ninguna manera. Me uniré a ti en esta incursión y lo haremos juntos. No me quedaré en la bodega durante la pelea, todo lo contrario: te pido que me pongas en el grupo de abordaje como tu oficial, temporalmente, por supuesto.\nConozco mi trabajo, sé cómo apuñalar y disparar a la gente. Así que arriesgaré mi trasero igual que tú... khe... ¡kha! Me pagarás mi parte después de que capturemos el filibote.";
			link.l1 = "¿Qué parte del botín reclamas para ti mismo?";
			link.l1.go = "FalseTrace_3";
		break;
		
		case "FalseTrace_3":
			dialog.text = "No soy un hombre codicioso, capitán. Mi parte es tanta como pueda cargarse en la bodega de mi viejo bote largo, y eso es alrededor de 200 paquetes de plata. Según mi información, no habrá menos de 2000 paquetes de plata en el filibote, así que obtendré la décima parte. Es justo, ¿no lo crees?";
			link.l1 = "¿Una décima parte del botín solo por información? Compro esa información a los borrachos por un vaso de ron en una taberna. ¡No, no vamos por el mismo camino, amigo!";
			link.l1.go = "FalseTrace_4";
			link.l2 = "Hm. Supongo que estoy de acuerdo. Acepto tu oferta, Adam. Bienvenido a bordo. Ahora sobre tu información: ¿de dónde, hacia dónde, hora, nombre del barco?";
			link.l2.go = "FalseTrace_5";
		break;
		
		case "FalseTrace_4":
			dialog.text = "¡Qué tacaño eres, Capitán! ¡En ese caso no recibirás más que mierda! ¡Nos vemos!";
			link.l1 = "¡Buena suerte! ¡Encuentra otro simplón para tu turbio emprendimiento!";
			link.l1.go = "FalseTrace_exit_1";
		break;
		
		case "FalseTrace_5":
			dialog.text = "El nombre del filibote es el "+pchar.questTemp.FalseTrace.ShipName+", ella parte de Cartagena y navega "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+". No tenemos mucho tiempo, sin embargo. Dos semanas, tres como máximo. Si no la encontramos en tres semanas, se acabó.";
			link.l1 = "¡No perdamos el tiempo, entonces! ¡La aventura nos llama!";
			link.l1.go = "FalseTrace_6";
		break;
		
		case "FalseTrace_6":
			DialogExit();
			NextDiag.CurrentNode = "FalseTrace_officer";
			DelLandQuestMark(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto1");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			AddPassenger(pchar, npchar, false);
			AddQuestRecord("FalseTrace", "1");
			AddQuestUserData("FalseTrace", "sCity1", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.StartCity+"Gen"));
			AddQuestUserData("FalseTrace", "sCity2", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity));
			AddQuestUserData("FalseTrace", "sShip", pchar.questTemp.FalseTrace.ShipName);
			//установим таймер на генерацию энкаунтера
			pchar.quest.False_Trace_2.win_condition.l1 = "Timer";
			pchar.quest.False_Trace_2.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.False_Trace_2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2);
			pchar.quest.False_Trace_2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.False_Trace_2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2);
			pchar.quest.False_Trace_2.function = "CreateFalseTraceGaleonOnMap";
			SetFunctionTimerCondition("FalseTraceGaleonOver", 0, 0, sti(pchar.questTemp.FalseTrace.DayQty)+2, false);//таймер
		break;
		
		case "FalseTrace_officer":
			dialog.text = "¿Querías algo, capitán?";
			link.l1 = "Nada, no importa.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FalseTrace_officer";
		break;
		
		case "FalseTrace_7":
			chrDisableReloadToLocation = true;
			dialog.text = "¿Querías verme, capitán?";
			link.l1 = "Creo que viste esto venir... ¿Dónde está la plata, maldita sea? ¿Dónde está? ¡Estoy hablando contigo! ¡El capitán del filibote me dijo que era un barco de abastecimiento! ¡Me mentiste!";
			link.l1.go = "FalseTrace_8";
		break;
		
		case "FalseTrace_8":
			dialog.text = "Tranquilízate, Capitán. Intentaré explicarlo todo.";
			link.l1 = "¡Por supuesto, lo harás! ¡Ya me he calmado! No estás colgado de una verga en este momento solo porque aún no puedo entender tus motivos. Perseguiste este filibote conmigo, sabiendo de antemano que no había plata. Así que, por favor, explícateme.";
			link.l1.go = "FalseTrace_9";
		break;
		
		case "FalseTrace_9":
			dialog.text = "Sí, realmente te engañé, Capitán. Pero esa era la única manera de persuadirte para que hicieras lo que necesito, capturar... khe kha! Capturar este maldito filibote\nPero te prometo que saldaré mi deuda contigo. Ahora déjame decirte por qué lo hice. ¿Has encontrado una mujer en el galeón? Vi a los tripulantes llevándola a tu embarcación...";
			link.l1 = "¿Hm... Entonces, necesitabas a la chica? ¡¿Y por eso me obligaste a comenzar una batalla naval y matar a un montón de gente!?";
			link.l1.go = "FalseTrace_10";
		break;
		
		case "FalseTrace_10":
			dialog.text = "Es mi esposa. Katerine Rayner. Se escapó de mí hace tres meses con ese patético capitán. Hice todos los esfuerzos para encontrarlos y lo logré. Ambos iban a "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+". No podría imaginar una mejor manera de devolver a Katerine y de lidiar incluso con ese roba-esposas\nSi te dijera la verdad, te marcharías. Así que tuve que contarte una historia jugosa sobre un filibote lleno de plata.";
			link.l1 = "Hmpf... Tu esposa te dejó, ¿verdad? ¡Muy interesante!";
			link.l1.go = "FalseTrace_11";
		break;
		
		case "FalseTrace_11":
			dialog.text = "Esta es mi legítima esposa, ¡la amo y nadie más tiene derecho a estar con ella! Ese sinvergüenza le contó hermosas mentiras sobre romance y toda esa porquería cuando yo estaba... lejos. ¿No conoces a las mujeres? Ella creyó en esas tonterías, tonta chica, y se escapó con él.";
			link.l1 = "Está bien, escucha, a mí no me importa mucho tu vida familiar, así que arréglalo con tu esposa. Pero me hablaste de compensar mis gastos, ¿verdad? ¿Te escuché bien?";
			link.l1.go = "FalseTrace_12";
		break;
		
		case "FalseTrace_12":
			if (pchar.basenation == SPAIN || pchar.basenation == HOLLAND)
			{
				pchar.questTemp.FalseTrace.QuestCity = "Portobello";
				pchar.questTemp.FalseTrace.QuestShore = "Shore48";
			}
			else
			{
				pchar.questTemp.FalseTrace.QuestCity = "SantaCatalina";
				pchar.questTemp.FalseTrace.QuestShore = "Shore54";
			}
			dialog.text = "Sí, me has oído bien, capitán. Un favor por un favor. No tengo dinero ahora mismo, pero si traes a Katerine y a mí a "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+", te diré información totalmente fiable sobre dónde puedes conseguir algo de oro sin ningún esfuerzo.";
			link.l1 = "Muy interesante. ¿Y por qué no puedes contarme esta información totalmente fiable ahora mismo?";
			link.l1.go = "FalseTrace_13";
		break;
		
		case "FalseTrace_13":
			link.l1 = "Tu historia suena bastante parecida a tu anterior fábula sobre un filibote cargado de plata. Ya me has engañado una vez. ¿Cómo puedes garantizar que no estás mintiendo esta vez?";
			dialog.text = "Porque, aún no tengo esta información. Déjame explicarte en detalle. Un caballero de fortuna llamado Solly el Bizco, ¿alguna vez has oído hablar de él? - va a saquear unas minas de oro no lejos de Blueweld\nDebido a ciertos eventos, tendrá que dejar todo su oro en algún lugar escondido y poner algunos guardias para protegerlo. El mismo hombre irá a pie a Belice o a Blueweld para conseguir un barco\nTengo un agente entre la tripulación de Solly, él me estará esperando en "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+"Una vez que echemos el ancla allí, él me dirá dónde esconde Solly sus tesoros.\nIrás allí, eliminarás a los guardias y te llevarás todo el oro. Iba a hacerlo yo mismo, pero considerando la situación actual, te lo dejaré todo a ti. Sin cargo.";
			link.l1.go = "FalseTrace_14";
		break;
		
		case "FalseTrace_14":
			dialog.text = "Te doy mi palabra. No tengo otras garantías. Pero es cierto, lo juro khe... kha... ¡malditas minas!";
			link.l1 = "Está bien. Ahora vete, y pensaré en lo que has dicho.";
			link.l1.go = "FalseTrace_15";
		break;
		
		case "FalseTrace_15":
			dialog.text = "No pienses demasiado. Solly el Bizco volverá por sus tesoros, como deberías darte cuenta. Según mis cálculos, sólo tienes dos semanas para llegar a "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+".";
			link.l1 = "Tendré eso en cuenta. Y ahora ve a los camarotes de la tripulación y únete a los marineros. Creo que será mejor que estés separado de tu esposa hasta nuestra llegada. Puedes irte ahora.";
			link.l1.go = "FalseTrace_16";
		break;
		
		case "FalseTrace_16":
			DialogExit();
			LAi_SetActorType(npchar);
			pchar.questTemp.FalseTrace = "TalkCabinWoman";
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "TalkSelf_Quest", 3.0);
			SetFunctionTimerCondition("FalseTraceSollyOver", 0, 0, 15, false);//таймер
			AddQuestRecord("FalseTrace", "5");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
		break;
		
		case "FalseTrace_17":
			dialog.text = "¿Me llamaste, capitán?";
			link.l1 = "Sí. Adam Rayner, te arrestaré y te encerraré. Me has engañado, y no tengo otra opción que aislarte y entregarte a las autoridades.";
			link.l1.go = "FalseTrace_18";
		break;
		
		case "FalseTrace_18":
			dialog.text = "¿De veras? Esperaba que lo hicieras, Capitán. Especialmente después de que viniste a la bodega y compartiste una charla con ese sucio raptor de esposas ajenas. Decidiste que estás de su lado, ¿no es así, Capitán?";
			link.l1 = "Nada de tu incumbencia. Me usaste, me traicionaste, ¡y ahora intentas engañarme de nuevo con absurdas historias de tesoros! Contramaestre, ¡llévenselo!";
			link.l1.go = "FalseTrace_19";
		break;
		
		case "FalseTrace_19":
			dialog.text = "¡Kha, no tan rápido, capitán... El contramaestre y el resto de tu gente no podrán entrar aquí en cualquier momento. ¿No te has dado cuenta de que he cerrado la puerta? Ahora estamos solos aquí, solo tú y yo. Así que muéstrame, capitán, de qué estás hecho!";
			link.l1 = "¿De verdad? ¿De verdad crees que tienes una oportunidad? ¡Te arrepentirás de esto, cabrón!";
			link.l1.go = "FalseTrace_20";
		break;
		
		case "FalseTrace_20":
			DialogExit();
			NextDiag.currentnode = "FalseTrace_21";
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetHP(npchar, 100+MOD_SKILL_ENEMY_RATE*35, 100+MOD_SKILL_ENEMY_RATE*35); // belamour с 40 хп боец из него никудышный
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "FalseTrace_capture");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_21":
			dialog.text = "";
			link.l1 = "Eso es mejor... ¡Depón las armas, canalla! ¡Contramaestre! ¡Pon a este bribón en grilletes y arrójalo a la bodega!";
			link.l1.go = "FalseTrace_22";
		break;
		
		case "FalseTrace_22":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			bQuestDisableMapEnter = false;
			RemovePassenger(Pchar, npchar);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			Pchar.questTemp.FalseTrace.PrisonerAdamIDX = sti(pchar.GenQuest.LastQuestPrisonerIdx);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			LAi_SetPlayerType(pchar);
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(npchar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(npchar, CIRASS_ITEM_TYPE);
			sld = &Characters[sti(Pchar.questTemp.FalseTrace.PrisonerIDX)];
			ReleasePrisoner(sld); //освободили пленника
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			DeleteAttribute(sld, "LifeDay") //постоянный персонаж
			GiveItem2Character(sld, "blade_10");
			EquipCharacterbyItem(sld, "blade_10");
			GiveItem2Character(sld, "pistol1");
			EquipCharacterbyItem(sld, "pistol1");//патроны не даю - все одно для антуражу
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			AddComplexSelfExpToScill(40, 40, 40, 40);
			AddQuestRecord("FalseTrace", "11");
			AddQuestUserData("FalseTrace", "sShore", XI_ConvertString(pchar.questTemp.FalseTrace.TargetShore+"Gen"));
			pchar.questTemp.FalseTrace = "AdamPrisoner";
		break;
		
		case "FalseTrace_23":
			pchar.quest.FalseTraceSollyOver.over = "yes"; //снять таймер
			dialog.text = "¡Gracias, capitán, por ayudarme a devolver a mi esposa! Adam Rayner está en deuda contigo, no lo olvidará, ja-ja, ¡lo juro por... kha! ¡Malditas minas! Ahora sobre Solly el Bizco. Mi hombre ya me ha dado todos los detalles. Solly ha dejado todas sus cosas en una gruta de la bahía de San Juan del Norte. El mismo está en Blueweld ahora\nDeberías apresurarte, tienes solo cinco días, según mi amigo. Lleva a tus hombres contigo, los bandidos de Solly son duros, te darán pelea\nEs hora de despedirse. Gracias de nuevo, Capitán, ¡que Dios te acompañe!";
			link.l1 = "Buena suerte, Adam. ¡No ofendas a tu esposa!";
			link.l1.go = "FalseTrace_Remove_exit";
			SetFunctionTimerCondition("FalseTraceBonanzaOver", 0, 0, 5, false);//таймер
			pchar.quest.False_Trace_4.win_condition.l1 = "location";
			pchar.quest.False_Trace_4.win_condition.l1.location = "Shore55";
			pchar.quest.False_Trace_4.function = "FalseTrace_SollyBonanza";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddQuestRecord("FalseTrace", "14");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
		break;
		
		case "FalseTrace_24":
			pchar.quest.FalseTraceSollyOver.over = "yes"; //снять таймер
			dialog.text = "¡Ja! ¿Por qué demonios, Capitán, hemos desembarcado en esta bahía? Te dije que mi hombre me estaba esperando en el puerto de "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+"¡Piensas ir allí a pie a través de las selvas?";
			link.l1 = "Mal suposición, Adam. ¿De verdad pensaste que volvería a creer tus tonterías una vez más? ¿Crees que soy un completo idiota? Esta vez he hecho un trato con tu esposa.";
			link.l1.go = "FalseTrace_25";
		break;
		
		case "FalseTrace_25":
			dialog.text = "¿Qué?! ¡Ja! ¿Qué clase de trato con mi esposa? ¿De qué estás hablando, pez podrido?";
			link.l1 = "Por tu información falsa capturé un filibote vacío y maté a su capitán. Lamento haber hecho eso, aunque ya es tarde para lamentaciones. Tu esposa estaba enamorada de ese marinero, según entendí. Por eso me pidió que te matara. Por eso estamos aquí en esta bahía ahora.";
			link.l1.go = "FalseTrace_26";
		break;
		
		case "FalseTrace_26":
			dialog.text = "¡No puedo creerlo! ¡Katerine... qué perra! Bueno, aún recibirás lo que mereces... Entonces, ¿cómo prometió pagarte, tonto? ¡No tiene un centavo, incluso vendió todas sus joyas para huir con ese capitán!";
			link.l1 = "Eso no es asunto tuyo, canalla. Pero es hora de terminar nuestra conversación. ¡Te enviaré al infierno, donde deberías haber estado desde hace bastante tiempo ya!";
			link.l1.go = "FalseTrace_27";
		break;
		
		case "FalseTrace_27":
			dialog.text = "¡Veamos qué puedes hacer, arenque podrido!";
			link.l1 = "...";
			link.l1.go = "FalseTrace_28";
		break;
		
		case "FalseTrace_28":
			DialogExit();
			npchar.SaveItemsForDead = true;
			npchar.DontClearDead = true;
			LAi_SetWarriorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FalseTrace_AdamDead");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_abordage":
			dialog.text = "¡Ah! ¿Por qué demonios has atacado mi barco, canalla? No puedo entender...";
			link.l1 = "No pretendas ser un cordero, capitán. Sé qué tipo de carga estás transportando. La necesito.";
			link.l1.go = "FalseTrace_abordage_1";
		break;
		
		case "FalseTrace_abordage_1":
			dialog.text = "¿Carga? ¡Ja-ja! ¿Qué clase de carga esperabas ver aquí? ¡Mis bodegas están vacías!";
			link.l1 = "¡Qué dijiste, bribón! ¡Repítelo!";
			link.l1.go = "FalseTrace_abordage_2";
		break;
		
		case "FalseTrace_abordage_2":
			dialog.text = "Repito - no tengo carga a bordo. Este filibote es un navío de abastecimiento que se dirige a "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+" llevar un cargamento de balas de cañón y provisiones para las tropas.";
			link.l1 = "Me estás tomando el pelo. Tus bodegas deben estar llenas de plata. Y voy a comprobarlo, después de que terminemos esta conversación...";
			link.l1.go = "FalseTrace_abordage_3";
		break;
		
		case "FalseTrace_abordage_3":
			dialog.text = "No sé quién te habló de la plata. Pero esto es un completo disparate... Perdí ante ti, así que me rindo. Aquí tienes mi espada. Ahora puedes ir y revisar las bodegas. Están vacías.";
			link.l1 = "¿Rindiéndote? ¡No! No necesito testigos. Toma tu espada y pelea, o te destriparé como a una oveja.";
			link.l1.go = "FalseTrace_abordage_4";
			link.l2 = "Bien por ti que has mostrado razón. Creo que podré conseguir un rescate por ti... ¡Eh, muchachos - lancen al capitán al calabozo!";
			link.l2.go = "FalseTrace_abordage_5";
		break;
		
		case "FalseTrace_abordage_4":
			DialogExit();
			pchar.questTemp.FalseTrace.KillCaptain = "true";//атрибут квеста
			Lai_SetPlayerType(pchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "FalseTrace_AfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.FalseTrace.CapName = GetFullName(npchar);
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
		break;
		
		case "FalseTrace_abordage_5":
			DialogExit();
			pchar.questTemp.FalseTrace.CapPrisoner = "true";//атрибут квеста
			Lai_SetPlayerType(pchar);
			DeleteAttribute(npchar, "DontRansackCaptain");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "FalseTrace_AfterFight", 3.0);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			pchar.questTemp.FalseTrace.CapName = GetFullName(npchar);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "FalseTrace_wife":
			dialog.text = "¡Lo mataste, canalla! ¡Granuja! ¡Pobre "+pchar.questTemp.FalseTrace.CapName+"!";
			link.l1 = "¿Qué es esto? ¿De dónde vienes, querida?";
			link.l1.go = "FalseTrace_wife_1";
		break;
		
		case "FalseTrace_wife_1":
			dialog.text = "Arderás en el infierno por todo lo que has hecho. ¡Que te den!";
			link.l1 = "¡Cálmate, jovencita! No tientes a la suerte maldiciéndome, o ¡te enviaré directamente tras tu capitán!";
			link.l1.go = "FalseTrace_wife_2";
		break;
		
		case "FalseTrace_wife_2":
			dialog.text = "¡Tú ... tú no te atreverás a levantar la mano contra una mujer!";
			link.l1 = "No lo necesitaré siquiera. Puedo dispararte. O simplemente te arrojaré por la borda, y los tiburones harán el resto... Ahora, ¿qué estás esperando? Ve a mi barco. No temas, no dejaré que nadie te haga daño y no te tocaré yo mismo si te mantienes callado...";
			link.l1.go = "FalseTrace_wife_3";
		break;
		
		case "FalseTrace_wife_3":
			DialogExit();
			pchar.quest.False_Trace_AfterBattle.over = "yes";
			pchar.quest.FalseTraceGaleonOver.over = "yes";
			if (CheckAttribute(pchar, "questTemp.FalseTrace.CapPrisoner")) AddQuestRecord("FalseTrace", "");
			else AddQuestRecord("FalseTrace", "");
			sld = characterFromId("Mugger");
			DeleteAttribute(sld, "HalfImmortal");
			RemovePassenger(Pchar, sld);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			DoQuestCheckDelay("LAi_EnableReload", 4.0);
			bQuestDisableMapEnter = true;
			pchar.questTemp.FalseTrace = "TalkCabin";
			AddQuestRecord("FalseTrace", "4");
		break;
		
		case "FalseTrace_wife_4":
			dialog.text = "¿Qué... qué le vas a hacer?";
			link.l1 = "¿Qué es esto? ¿De dónde vienes, querida?";
			link.l1.go = "FalseTrace_wife_5";
		break;
		
		case "FalseTrace_wife_5":
			dialog.text = "Pobre "+pchar.questTemp.FalseTrace.CapName+". Dime, ¿vas a matarlo? No...";
			link.l1 = "Escuchame, dama, si quisiera matarlo, ya lo habría hecho. Él se quedará en la bodega, y luego lo soltaré o probablemente pediré un rescate por él... lo último es más probable. Y ahora, por favor, sé una buena chica y sube a bordo de mi barco. No temas - no dejaré que nadie te haga daño y no te tocaré yo mismo si te mantienes callada...";
			link.l1.go = "FalseTrace_wife_3";
		break;
		
		case "FalseTrace_wife_6":
			if (CheckAttribute(pchar, "questTemp.FalseTrace.KillCaptain"))
			{
				dialog.text = "¿Qué quieres de mí? ¿Echarme a los tiburones, como dijiste que harías? Arruinaste mi vida y yo...";
				link.l1 = "Vamos, querida. Nadie te va a lanzar a ningún lado. Solo quiero aclarar la situación, ya que ataqué este filibote por tu culpa y no por ninguna otra razón.";
				link.l1.go = "FalseTrace_wife_7";
			}
			else
			{
				dialog.text = "¿Qué quieres de mí? ¿Dónde está "+pchar.questTemp.FalseTrace.CapName+"¿Rescate? ¿Necesitas un rescate?";
				link.l1 = "Está bien, dama, detengamos este flujo de preguntas sin sentido. No te llamé aquí para esto. Un hecho ha sido aclarado, y será interesante para ti escucharlo.";
				link.l1.go = "FalseTrace_wife_20";
			}
		break;
		
		case "FalseTrace_wife_7":
			dialog.text = "¿Por mi culpa? ¿Estás diciendo que es mi culpa que atacasteis nuestro barco y matasteis a mi amado? Pobre "+pchar.questTemp.FalseTrace.CapName+", ¿qué te hizo? Responderás ante el Señor por todo lo que has hecho...";
			link.l1 = "¡El mismo guiso de siempre! ¿Deberíamos volver a nuestra charla de tiburones?";
			link.l1.go = "FalseTrace_wife_8";
		break;
		
		case "FalseTrace_wife_8"://ноды пересечения - старт
			dialog.text = "";
			link.l1 = "¿Tranquilo ahora? Estupendo. ¡Ahora escúchame! Ataqué el barco porque tenía información de que llevaba una carga decente de plata. Y obtuve esta información de Adam Rayner.";
			link.l1.go = "FalseTrace_wife_9";
		break;
		
		case "FalseTrace_wife_9":
			dialog.text = "¡Ah! ¿Qué?! ¿Adam? ¿Dónde está él? ¿Está aquí?";
			link.l1 = "Veo que conoces el nombre... Katerine. Y, como puedes ver, ya sé todo sobre ti. Supongo que Adam Rayner es tu esposo, ¿no es así?";
			link.l1.go = "FalseTrace_wife_10";
		break;
		
		case "FalseTrace_wife_10":
			dialog.text = "Sí. Soy la esposa de este monstruo. Estaba bajo la ilusión de que esta pesadilla finalmente había terminado... ¿Te contrató para atraparme?";
			link.l1 = "En general resultó ser así. Adam me mintió sobre la astilla, para que capturara el filibote '"+pchar.questTemp.FalseTrace.ShipName+"'. Definitivamente, estaba decidido a traerte de vuelta. Hace un cuarto de hora me explicó todas sus acciones.";
			link.l1.go = "FalseTrace_wife_11";
		break;
		
		case "FalseTrace_wife_11":
			dialog.text = "¿Y... qué quiere él? ¿Qué te dijo?";
			link.l1 = "Él quiere que su legítima esposa regrese a él. Me proporcionará información sobre el oro de Solly el Bizco como compensación por engañarme. Y voy a llevarlos a ambos a "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+".";
			link.l1.go = "FalseTrace_wife_12";
		break;
		
		case "FalseTrace_wife_12":
			dialog.text = "No... (llora) ¡No quiero volver con ese granuja! Hice un gran esfuerzo para huir de él y cubrir mis huellas, pero me ha encontrado de todos modos... ¡Canalla! ¡Bandido! ¡Maldito ladrón!";
			link.l1 = "Calma, Katerine... Cuida tu lenguaje. Después de todo, él es tu esposo. Y dijo que te amaba.";
			link.l1.go = "FalseTrace_wife_13";
		break;
		
		case "FalseTrace_wife_13":
			dialog.text = "(llora) ¿Mi marido? ¿Sabes quién es mi marido? Es un ex-prisionero, un convicto y ahora el bandido más cruel de "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.StartCity+"Gen")+"¡Es un vil y sucio bastardo, y para él solo soy un agujero entre las piernas para follar!";
			link.l1 = "¿No lo habías visto todo antes de casarte con él?";
			link.l1.go = "FalseTrace_wife_14";
		break;
		
		case "FalseTrace_wife_14":
			dialog.text = "Al principio, él era diferente... Y su pasado me parecía tan romántico... Pero con el tiempo todo ha cambiado. Y ni siquiera quiero verlo, ni hablar de vivir con él, ¿no puedes entenderlo? ¡No quiero! ¡Especialmente después de este ataque al filibote, que él ha organizado!";
			link.l1 = "Hum... ¿Qué debería hacer contigo, entonces, dulce dama?";
			link.l1.go = "FalseTrace_wife_15";
		break;
		
		case "FalseTrace_wife_15"://ноды пересечения - конец
			if (CheckAttribute(pchar, "questTemp.FalseTrace.KillCaptain"))
			{
				dialog.text = "¿Qué hacer? Sé qué hacer. Eres una herramienta del pecado, gracias a las acciones de mi marido. Has matado a un hombre inocente, el único hombre que me trató bien. Expiad tus pecados, capitán. Mata a Adam. Justo frente a mis ojos. Quiero ver morir a esta escoria, quiero escupir sobre su cadáver. Cuando esté muerto, te diré dónde esconde sus tesoros. El idiota borracho me habló de su escondite una vez, ¡ja-ja, ni siquiera lo recuerda!";
				link.l1 = "¡Eh! ¡Eres una mujer cruel, Katerine, como puedo ver!";
				link.l1.go = "FalseTrace_wife_16";
			}
			else
			{
				dialog.text = ""+pchar.questTemp.FalseTrace.CapName+"... El capitán del filibote. Lo encerraste. ¡Háblale, te lo ruego! ¡Te ofrecerá algo por nuestras vidas y libertad! ¡Él tendrá una idea! Yo... No quiero volver a Adam, de ahora en adelante "+pchar.questTemp.FalseTrace.CapName+"¡es mi esposo! Te lo suplico, no me lleves de vuelta con Adam, ¡a ese monstruo!";
				link.l1 = "Mm. Interesante. ¿Y qué puede ofrecerme mi prisionero? Puedo obtener un rescate por él de las autoridades, y también obtendré el oro de Solly el Bizco...";
				link.l1.go = "FalseTrace_wife_21";
			}
		break;
		
		case "FalseTrace_wife_16":
			dialog.text = "Mira quién habla de crueldad. Navega a "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+", haz lo que te dijo Adam, solo desembarca no en el puerto sino en la bahía más cercana. Tres de nosotros iremos allí y tú matarás al bastardo\nUna vez hecho, te contaré sobre el escondite. Te juro que no miento. Creo que confías más en mis palabras que en las de Adam, te engañó una vez, ¿verdad? ¿Qué dices, capitán?";
			link.l1 = "Sí... Dicen por algo que marido y mujer son de la misma calaña. Te miro, Katerine, y veo que eres el mejor partido para Adam... Si tanto deseas su muerte, bien podrías apuñalarlo mientras duerme borracho... ¡Contramaestre! ¡Llévatela!";
			link.l1.go = "FalseTrace_wife_17";
			link.l2 = "Odio a los canallas que intentan engañarme y usarme para sus propios fines. Está bien, Katherine, acepto tu oferta, ya que me queda claro que no se puede confiar en Adam. Pero si tú también me engañas, te encontraré incluso en Europa, lo juro, y te meteré una bala en la cabeza. Ahora lárgate. ¡Contramaestre! ¡Llévala!";
			link.l2.go = "FalseTrace_wife_19";
		break;
		
		case "FalseTrace_wife_17":
			dialog.text = "Te arrepentirás de esto... Lo juro, yo ...";
			link.l1 = "¡Contramaestre! Cuídala y vigílala todo el tiempo hasta que lleguemos a "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+".";
			link.l1.go = "FalseTrace_wife_18";
		break;
		
		case "FalseTrace_wife_18":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("FalseTrace", "6");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
			AddDialogExitQuestFunction("SetCheckForSolly");
			chrDisableReloadToLocation = false;
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		break;
		
		case "FalseTrace_wife_19":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("FalseTrace", "7");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
			AddDialogExitQuestFunction("SetCheckForKillAdam");
			chrDisableReloadToLocation = false;
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		break;
		
		case "FalseTrace_wife_20":
			dialog.text = "¿Qué hecho? ¿Qué vas a hacer con nosotros? ¿Por qué has capturado nuestro barco?";
			link.l1 = "¿Me dejarás decir una palabra o debo ordenar a mi contramaestre que te calle con un mordaza?!";
			link.l1.go = "FalseTrace_wife_8";
		break;
		
		case "FalseTrace_wife_21":
			dialog.text = "¿El oro de Solly? ¿Realmente confías en este sinvergüenza? ¡Te engañará de nuevo, es su estilo! ¡Habla con tu prisionero!\n"+pchar.questTemp.FalseTrace.CapName+" es un verdadero caballero, no romperá su palabra y no te mentirá.";
			link.l1 = "No me persuadiste, señora. No tengo nada de qué hablar con tu capitán. Conseguiré un rescate por él y obtendré el oro de Solly de Adam. Si Adam me engaña de nuevo, lo encontraré incluso al final del mundo, y maldecirá el día en que nació... ¡Contramaestre! ¡Llévatela!";
			link.l1.go = "FalseTrace_wife_23";
			link.l2 = "Para decirte la verdad, no confío en Adam... Odio que me manipulen. Está bien, hablaré con tu capitán y veré qué puede decirme. Ahora puedes irte... ¡Contramaestre! ¡Llévatela!";
			link.l2.go = "FalseTrace_wife_24";
		break;
		
		case "FalseTrace_wife_23":
			dialog.text = "¡Eres un hombre cruel y despiadado! Juro que yo...";
			link.l1 = "¡Contramaestre! Vigílala y mantén un ojo en ella todo el tiempo hasta que lleguemos a "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+".";
			link.l1.go = "FalseTrace_wife_18";
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], true);
		break;
		
		case "FalseTrace_wife_24":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("FalseTrace", "8");
			chrDisableReloadToLocation = false;
			pchar.questTemp.FalseTrace.Prisoner = "true";
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], true);
		break;
		
		case "FalseTrace_wife_25":
			dialog.text = "Ya se acabó... Pobre "+pchar.questTemp.FalseTrace.CapName+" está vengado, y ahora puedo respirar libremente y llamarme viuda...";
			link.l1 = "He cumplido mi parte del trato, Katerine. Ahora es tu turno.";
			link.l1.go = "FalseTrace_wife_26";
		break;
		
		case "FalseTrace_wife_26":
			dialog.text = "Por supuesto, capitán. Mi marido - gracias a Dios, ahora ex-marido - era un bandido, como ya sabes. Temiendo posibles registros, no guardaba el botín saqueado en casa. Organizó un escondite - pero una vez se le escapó la lengua sobre ello. Aun así, lo ocultó de manera muy astuta - no hay acceso a ese lugar desde la costa.";
			link.l1 = "Muy interesante... ¿Y dónde está?";
			link.l1.go = "FalseTrace_wife_27";
		break;
		
		case "FalseTrace_wife_27":
			dialog.text = "En una pequeña isla cerca de La Española. En el faro.";
			link.l1 = "¡Faro de Port-au-Prince! ¡Está ubicado en la isla!";
			link.l1.go = "FalseTrace_wife_28";
		break;
		
		case "FalseTrace_wife_28":
			dialog.text = "Probablemente sí. Podrás encontrar el botín allí. Ya verás. Eso es todo. Adiós, Capitán.";
			link.l1 = "Espera... Perdóname, Katerine, si puedes. Espero que la muerte del culpable de todas tus desgracias sea un alivio, de todos modos. Lo siento mucho...";
			link.l1.go = "FalseTrace_wife_29";
		break;
		
		case "FalseTrace_wife_29":
			dialog.text = "No necesito tus lamentos, Capitán. Hiciste lo que te pedí y te conté todo lo que querías saber. Adiós ahora, y déjame solo con mi pena...";
			link.l1 = "Adiós, Katerine.";
			link.l1.go = "FalseTrace_wife_30";
		break;
		
		case "FalseTrace_wife_30":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 15);
			LAi_LocationDisableOfficersGen(pchar.questTemp.FalseTrace.QuestShore, false);//офицеров пускать
			//LAi_LocationDisableOfficersGen("Mayak7", true);//офицеров не пускать
			locations[FindLocation("Mayak7")].DisableEncounters = true;//энкаунтеры закрыть
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			pchar.quest.False_Trace_7.win_condition.l1 = "location";
			pchar.quest.False_Trace_7.win_condition.l1.location = "Mayak7";
			pchar.quest.False_Trace_7.function = "FalseTrace_AdamTreasure";
			AddQuestRecord("FalseTrace", "23");
		break;
		
		case "FalseTrace_wife_31":
			dialog.text = "¡Asqueroso sinvergüenza! ¡Logró matar a los cuatro! ¡Increíble!";
			link.l1 = "¿No esperabas tal giro, Katerine? Soy difícil de matar. ¡Juegas a dobles juegos bastante bien, debo decir!";
			link.l1.go = "FalseTrace_wife_32";
		break;
		
		case "FalseTrace_wife_32":
			dialog.text = "Has asesinado a mi hombre. ¿Realmente crees que podría dejarte seguir respirando? ¿Pensaste que la muerte de Adam me satisfizo? ¡No! No saldrás de este lugar. Hay un barco no muy lejos de esta isla, ¡hundirá tu viejo cascarón contigo!\nAhora, haz lo que quieras conmigo.";
			link.l1 = "¿No te dije, querida, que perderías la cabeza si me engañabas? ¡Un diablo astuto! Serás mucho menos peligroso muerto. Esta bonita cabeza va a recibir una bala ahora mismo...";
			link.l1.go = "FalseTrace_wife_33";
			link.l2 = "Siento lástima por ti, Katerine. Tu ansia de venganza no te trajo nada bueno al final. Voy a dejarte a tu suerte - te quedarás en esta isla. Creo que los pescadores locales te encontrarán pronto y te llevarán a La Española. Y que el Señor nos juzgue por todos nuestros actos...";
			link.l2.go = "FalseTrace_wife_35";
		break;
		
		case "FalseTrace_wife_33":
			dialog.text = "¡Eres tú quien debería rezar, monstruo! ¡Asesino! ¡Ayuda! ¡Maldit...";
			link.l1 = "He oído suficiente.";
			link.l1.go = "FalseTrace_wife_34";
		break;
		
		case "FalseTrace_wife_34":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetImmortal(npchar, false);
			//  belamour legendary edition если не надет пистоль или мушкет, то выдадим строевой -->
			if(!CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE) || !CheckAttribute(pchar,"equip."+MUSKET_ITEM_TYPE))
			{
				GiveItem2Character(pchar, "pistol1");
				EquipCharacterbyItem(pchar, "pistol1");
			}
			// <-- legendary edition
			LAi_ActorAnimation(pchar, "shot", "FalseTrace_CaterinaKilled", 1.0);
		break;
		
		case "FalseTrace_wife_35":
			dialog.text = "¡Que te ahogues! ¡Que tu barco se estrelle contra las rocas! ¡Que tú...";
			link.l1 = "Adiós, Katerine.";
			link.l1.go = "FalseTrace_wife_36";
		break;
		
		case "FalseTrace_wife_36":
			DialogExit();
			sld = characterFromID("FalseTraceWife"); 
			sld.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "goto", "goto33", "none", "", "", "", -1);
			LAi_SetPlayerType(pchar);
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen("Mayak7", false);//офицеров пускать
			locations[FindLocation("Mayak7")].DisableEncounters = false;//энкаунтеры открыть
			AddQuestRecord("FalseTrace", "25");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			OfficersReaction("good");
		break;
		
		case "FalseTrace_Bandits":
			dialog.text = "¡A-ah, aquí está el asesino de Adam! ¡Katerine tenía razón, este bastardo vino a robar el escondite!";
			link.l1 = "¿Qué? ¿Katerine? ¿Quién eres tú?";
			link.l1.go = "FalseTrace_Bandits_1";
		break;
		
		case "FalseTrace_Bandits_1":
			dialog.text = "¿Quiénes somos? Somos amigos de Adam Rayner, quien fue asesinado por ti. Él era la cabeza de nuestra hermandad. Ahora soy yo la cabeza, mi nombre es "+GetFullName(npchar)+", y te castigaré por matar a mi jefe y por la violencia que cometiste contra su esposa.";
			link.l1 = "¿Violencia? ¿De qué diablos estás hablando?";
			link.l1.go = "FalseTrace_Bandits_2";
		break;
		
		case "FalseTrace_Bandits_2":
			dialog.text = "Apuñalaste a Adam por la espalda, maldito traidor, forzaste a su esposa a decirte dónde Adam guardaba su oro y luego dejaste a la pobre mujer morir en una costa desierta\nPero ella sobrevivió, nos pidió que la ayudáramos, para corregir un error. Hemos estado esperando varios días por ti. ¡Y aquí́ estás, bastardo!";
			link.l1 = "¡Ja, ja! Definitivamente el estilo de Katerine... Ahora escucha, he matado a Adam, eso es cierto, pero lo hice porque su esposa realmente me pidió que lo matara. Eso fue una venganza por la muerte de su amante. Ella me dijo dónde encontrar el alijo para poder pagarme...";
			link.l1.go = "FalseTrace_Bandits_3";
		break;
		
		case "FalseTrace_Bandits_3":
			dialog.text = "¡No calumnies a la pobre viuda, escoria! ¿Por qué habría de venir a nosotros entonces? Nos ofreció quedarnos con todo el oro a cambio de tu vida. ¡No quiere monedas, quiere tu muerte! ¡Una muerte sagrada por la muerte de su esposo!\nPero te juro, no morirá en la pobreza, esto es tan cierto como que mi nombre es "+GetFullName(npchar)+", ¡y que este es el momento para que mueras, cobarde!";
			link.l1 = "¡Santo cielo, qué discurso tan glorioso! Ah, ahí está ella, ansiosa por ver esta comedia en persona... ¿Caballeros?";
			link.l1.go = "FalseTrace_Bandits_4";
		break;
		
		case "FalseTrace_Bandits_4":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			DialogExit();
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Adam_bandit_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FalseTrace_BanditsAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_Remove1":
			dialog.text = "¡Eres un desastre, capitán! Perder un filibote lleno de plata... Cometí un error al contar contigo. ¡Adiós!";
			link.l1 = "Adiós, Adam.";
			link.l1.go = "FalseTrace_Remove2";
		break;
		
		case "FalseTrace_Remove2":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 15);
		break;
		
		case "FalseTrace_Remove_exit":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "FalseTraceWife_Remove", 15);
		break;
		
		case "FalseTrace_Remove2":
			dialog.text = "Te he advertido, capitán, ¡solo teníamos dos semanas! A estas alturas, Solly el Bizco ya debe haber robado todo el botín. No es mi culpa que seas tan desordenado. ¡Adiós!";
			link.l1 = "Sí, mi culpa. Adiós, espero que no nos volvamos a encontrar, eres solo una mala suerte para mí.";
			link.l1.go = "FalseTrace_Remove_exit";
		break;
		
		case "FalseTrace_Solly":
			dialog.text = "¡Je! ¡Finalmente! Estamos cansados de esperar, y estos malditos mosquitos... Espera... ¿Y dónde está Solly? No lo entiendo...";
			link.l1 = "Solly no vendrá aquí. Actúo en su nombre... Así que o me das el oro o estás tan bueno como muerto.";
			link.l1.go = "FalseTrace_Solly_1";
		break;
		
		case "FalseTrace_Solly_1":
			dialog.text = "¡Argh! ¡Ya veremos! ¡A mí, muchachos! ¡A las armas!";
			link.l1 = "¡Qué manera tan tonta de morir, venid entonces, carroñeros!";
			link.l1.go = "FalseTrace_Solly_2";
			AddDialogExitQuestFunction("FalseTrace_SollyBonanzaAdd");
		break;
		
		case "FalseTrace_Solly_2":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			DialogExit();
			for (i=1; i<=6; i++)
			{
				sld = characterFromId("FTEnemy_crew_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FalseTrace_SollyAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_GoldShip":
			dialog.text = "Has cumplido con tu parte del trato, capitán. Gracias por confiar en mí. No te preocupes por Adam, lo llevaré al lugar adecuado. Recibirá lo que merece.";
			link.l1 = "No me importa Adam. ¿Qué hay de tu promesa sobre algún barco?";
			link.l1.go = "FalseTrace_GoldShip_1";
		break;
		
		case "FalseTrace_GoldShip_1":
			if (sti(pchar.basenation == HOLLAND) || sti(pchar.basenation == SPAIN))
			{
				pchar.questTemp.FalseTrace.ShipNation = ENGLAND;
				pchar.questTemp.FalseTrace.ShipCity = "PortRoyal";
			}
			else
			{
				pchar.questTemp.FalseTrace.ShipNation = SPAIN;
				pchar.questTemp.FalseTrace.ShipCity = "Maracaibo";
			}
			dialog.text = "Sí, sí, claro. A ver, contando desde hoy... Sí... En 12-14 días desde "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.ShipCity+"Gen")+" un pesado galeón cargado con mineral de oro zarpará hacia Europa. Estará protegido por una sola fragata o corbeta\nAsí que prepárate, es un botín rico, pero tiene dientes. Sin embargo, estoy seguro de que tendrás éxito, aplastaste mi resistencia con bastante facilidad... Debes llegar "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.ShipCity+"Gen")+"en dos semanas y prepara una emboscada\nRecuerda que tu objetivo es un galeón pesado con un solo barco de escolta. Esto es todo, supongo. El resto está en tus manos.";
			link.l1 = "Ya veo... Bueno, "+pchar.questTemp.FalseTrace.CapName+", adiós. ¿Quizás debería desearte suerte y una vida feliz con Katerine? Espero que ustedes dos estén bien. Es una lástima que nos hayamos encontrado bajo circunstancias tan tristes.";
			link.l1.go = "FalseTrace_GoldShip_2";
		break;
		
		case "FalseTrace_GoldShip_2":
			dialog.text = "Gracias, capitán. Como he dicho antes, tiene algo de nobleza. Espero que saque la conclusión correcta de que las acciones honestas le dan más beneficio que las deshonrosas. Dedíquese a servir a su nación, y se convertirá en un gran marinero naval.";
			link.l1 = "Pensaré en tus palabras. ¡Bueno, adiós por ahora!";
			link.l1.go = "FalseTrace_GoldShip_3";
		break;
		
		case "FalseTrace_GoldShip_3":
			DialogExit();
			locations[FindLocation(pchar.questTemp.FalseTrace.TargetShore)].DisableEncounters = false; //энкаутеры открыть
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "FalseTraceDouble_Remove", -1);
			pchar.quest.False_Trace_6.win_condition.l1 = "Timer";
			pchar.quest.False_Trace_6.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.False_Trace_6.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 14);
			pchar.quest.False_Trace_6.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 14);
			pchar.quest.False_Trace_6.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 14);
			pchar.quest.False_Trace_6.function = "CreateFalseTraceGoldShipOnMap";
			AddQuestRecord("FalseTrace", "19");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.ShipCity+"Gen"));
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
