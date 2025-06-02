// гид
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "¿Quieres algo?";
			link.l1 = "No, nada.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "guide_0":
			SetAchievement("Test_Ach");
			PlaySound("Voice\Spanish\LE\Greguar\Greguar_01.wav");
			dialog.text = "¡Placer darle la bienvenida a las colonias, señor! Permítame presentarme: "+GetFullName(pchar)+". ¿Viene usted de Europa? ¿Es su primera vez aquí?";
			link.l1 = "Buenos días, monsieur. Mi nombre es "+GetFullName(pchar)+". Sí, acabo de bajar del barco.";
			link.l1.go = "guide_1";
		break;
		
		case "guide_1":
			DelLandQuestMark(npchar);
			dialog.text = "Al ver a un noble caballero, consideré mi deber ofrecerle ayuda. Aquí, en el Nuevo Mundo, hay sus propias reglas — y no conocerlas puede costar caro. La gente de rango debe ayudarse mutuamente. No creerían cuánta chusma se ha reunido aquí, dispuesta a traicionar al prójimo por un puñado de monedas.\n"+
			"¿Me permite mostrarle la ciudad y ponerle al corriente brevemente?";
			link.l1 = "¡Muy noble de su parte, monsieur! Aceptaré gustoso su oferta.";
			link.l1.go = "guide_2";
			link.l2 = "Gracias por su preocupación, señor, realmente se lo agradezco, pero creo que sin dificultad me las arreglaré solo.";
			link.l2.go = "guide_exit";
		break;
		
		case "guide_exit":
			dialog.text = "Como guste, monsieur. En cualquier caso, me alegró conocerle. La gente noble es tan rara en esta región apartada. ¡Le deseo todo lo mejor y buena suerte!";
			link.l1 = "¡Y a usted también, "+GetFullName(npchar)+"!";
			link.l1.go = "guide_exit_1";			
		break;
		
		case "guide_exit_1":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DoQuestCheckDelay("NgtF3", 1.0);
			QuestPointerToLoc("FortFrance_town", "reload", "reload3_back");
		break;
		
		case "guide_2":
			dialog.text = "¡Excelente! La vida en el Caribe es sencilla, y cada asentamiento está construido según las mismas reglas. Si se familiariza con Saint-Pierre, se familiarizará con cualquier otra ciudad.";
			link.l1 = "";
			link.l1.go = "guide_tavern";			
		break;
		
		case "guide_tavern":
			dialog.text = "Taberna: el corazón del puerto. Aquí encontrará alojamiento, ron, rumores y podrá contratar marineros y oficiales. También puede jugar a las cartas, encontrar trabajo o usar los servicios de contrabandistas y vendedores de mapas del tesoro.";
			link.l1 = "";
			link.l1.go = "guide_market";
			locCameraFromToPos(-2.08, 5.32, 68.88, true, -15.00, 0.90, 55.00);
		break;
		
		case "guide_market":
			dialog.text = "Mercado. Los artículos para uso personal siempre se pueden comprar en el mercado. En el armero: armas, armaduras y municiones; en la herbolaria: pociones curativas. Las gitanas y monjes comercian con amuletos, y el chatarrero vende toda clase de cachivaches útiles para quienes no desdeñan hacer manualidades.";
			link.l1 = "";
			link.l1.go = "guide_brothel";
			locCameraFromToPos(-13.58, 4.11, 69.06, true, -45.00, -6.00, 52.00);
		break;
		
		case "guide_brothel":
			dialog.text = "Burdel. No hay mejor medicina para el cuerpo que los placeres amorosos en brazos de una mujer hábil. Si la salud se tambalea, pase por aquí, diviértase, reciba una dosis de caricias y se sentirá como una nueva persona.";
			link.l1 = "";
			link.l1.go = "guide_bank";
			locCameraFromToPos(-2.75, 7.07, 61.10, true, 60.00, -6.60, 42.65);
		break;
		
		case "guide_bank":
			dialog.text = "Banco. Casa del usurero. Se puede pedir prestado o invertir dinero, cambiar pesos por doblones. Y además, es el mejor lugar para vender joyas.";
			link.l1 = "";
			link.l1.go = "guide_prison";
			locCameraFromToPos(3.07, 7.64, 51.99, true, 45.00, -8.30, 4.50);
		break;
		
		case "guide_prison":
			dialog.text = "Prisión. Hay pocos criminales verdaderos aquí, principalmente toda clase de gentuza. Si quiere encontrar trabajo entre la escoria de la sociedad, hable con el comandante. Por un pequeño soborno puede dejarle pasar a las celdas.";
			link.l1 = "";
			link.l1.go = "guide_townhall";
			locCameraFromToPos(-50.52, 5.79, 38.60, true, -47.65, 3.95, 33.52);
		break;
		
		case "guide_townhall":
			dialog.text = "Palacio. El palacio de la persona más importante de la colonia: el gobernador. Los hombres de negocios y capitanes vienen aquí por trabajo serio. Estar en buenas relaciones con el gobernador es muy importante, pues de él depende en gran medida cómo lo tratará toda su nación.";
			link.l1 = "";
			link.l1.go = "guide_12";
			locCameraFromToPos(3.14, 7.39, 37.55, true, 1.06, 8.45, 14.14);
		break;
		
		case "guide_12":
			dialog.text = "¿Tiene prisa por ir a algún lado y lo estoy distrayendo?";
			link.l1 = "Bueno... supongo que sí. Monsieur, he venido aquí para encontrar a mi hermano. Dicen que está en algún lugar de Saint-Pierre. Es un hombre importante y seguramente conocido por el gobernador...";
			link.l1.go = "guide_13";
			SetCameraDialogMode(npchar);
		break;
		
		case "guide_13":
			dialog.text = "Ah, entiendo. Nuestro gobernador se llama Jacques Dyel du Parquet. Estoy seguro de que le recibirá sin demora.";
			link.l1 = "¿A quién más podría preguntar sobre mi hermano? Tal vez no debería molestar a Su Excelencia ahora mismo.";
			link.l1.go = "guide_14";
		break;
		
		case "guide_14":
			dialog.text = "Si su hermano es realmente conocido en Martinica, pregunte a los transeúntes. Tal vez alguien pueda indicarle. Por cierto, ¿cómo se llama?";
			link.l1 = "Michelle de Monper.";
			link.l1.go = "guide_15";
		break;
		
		case "guide_15":
			dialog.text = "He oído ese nombre, pero, lamentablemente, no he tenido el honor de ser presentado personalmente. Intente preguntar en la ciudad — o vaya directamente al gobernador. Buena suerte, monsieur. ¡Seguro que nos volveremos a ver y charlaremos!";
			link.l1 = "¡Gracias, "+GetFullName(npchar)+"!";
			link.l1.go = "guide_16";
		break;
		
		case "guide_16":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			LAi_group_MoveCharacter(npchar, "FRANCE_CITIZENS"); // пока идем заниматься Мишелем
			chrDisableReloadToLocation = false;//открыть локацию
			DoQuestCheckDelay("NgtF3", 1.0);
			QuestPointerToLoc("FortFrance_town", "reload", "reload3_back");
		break;
		
		case "guide_21":
			dialog.text = "¡Oh, es usted de nuevo, mi amigo! Veo que le han permitido entrar en el sanctasanctórum de Saint-Pierre — la fortaleza de los Caballeros de Malta. Por todo lo que se ve, usted es un pez gordo. ¿Encontró a su hermano?";
			link.l1 = "Sí, lo encontré... de alguna manera.";
			link.l1.go = "guide_22";
		break;
		
		case "guide_22":
			dialog.text = "Perdone la insistencia, monsieur, pero me pareció que no oigo alegría en su voz...";
			link.l1 = "Es cierto, señor. Esperaba salir de aquí de vuelta a Francia en el próximo barco, pero el destino parece haberse burlado de mí: me quedo aquí por mucho tiempo... no, maldita sea, ¡por un tiempo indeterminado! Y, ¿se imagina?, ¡además debo convertirme en marinero, bah!";
			link.l1.go = "guide_23";
		break;
		
		case "guide_23":
			dialog.text = "Por alguna razón no me sorprende. Ya he oído hablar de su aventura en el pingue 'Ulysse'. No se desanime: ser propietario de su propio barco y capitán es muy honorable. Planea comprar un barco, ¿verdad?";
			link.l1 = "Sí, maldita sea, eso es exactamente lo que debo hacer... Solo queda encontrar un astillero y de alguna manera reunir dinero. ¡Pero no sé ni dónde está el astillero, ni cómo manejar un barco, ni dónde conseguir dinero, nada!";
			link.l1.go = "guide_24";
		break;
		
		case "guide_24":
			dialog.text = "Con el dinero, lamentablemente, no puedo ayudar — yo mismo estoy sin fondos. Pero en todo lo demás — estoy a su servicio. ¿Está listo para continuar el recorrido?";
			link.l1 = "Sí, probablemente, pues no en vano dicen: el conocimiento es poder.";
			link.l1.go = "guide_25";
			link.l2 = "Gracias de todo corazón, monsieur, pero a partir de aquí me las arreglaré solo.";
			link.l2.go = "guide_exit_11";
		break;
		
		case "guide_exit_11":
			dialog.text = "Me alegró conocerle. Y en cuanto al dinero para el barco, hable con la gente influyente de la ciudad. Por ejemplo, con el comerciante de la tienda.\n"+
			"Buena suerte, "+pchar.name+" — sea audaz y todo le saldrá bien.";
			link.l1 = "";
			link.l1.go = "guide_exit_12";			
		break;
		
		case "guide_exit_12":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		case "guide_25":
			dialog.text = "¡Entonces sígame! Empecemos por lo más básico: los barcos.";
			link.l1 = "";
			link.l1.go = "guide_shipyard";
		break;
		
		case "guide_shipyard":
			dialog.text = "Astillero. Aquí se compran y reparan barcos. La selección no es grande — principalmente embarcaciones pequeñas, pero a veces aparecen naves serias. También se pueden comprar cañones y decorar las velas.";
			link.l1 = "";
			link.l1.go = "guide_port";
			locCameraFromToPos(-23.25, 7.74, 77.79, true, -27.85, 5.36, 73.65);
		break;
		
		case "guide_port":
			dialog.text = "Muelle — la puerta al mar. Tan pronto como tenga un barco, un bote le estará esperando aquí. Mientras tanto, recomiendo contratar a un navegante, un tesorero y un artillero — con ellos se sentirá más seguro en el mar.";
			link.l1 = "";
			link.l1.go = "guide_portoffice";
			locCameraFromToPos(-8.55, 4.06, 91.31, true, 40.00, -8.00, 0.00);
		break;
		
		case "guide_portoffice":
			dialog.text = "Oficina portuaria. Aquí puede dejar su barco y encontrar trabajo honesto: fletes, escoltas, entrega de correo. Cuantos más encargos complete, mejores serán las recompensas.";
			link.l1 = "";
			link.l1.go = "guide_store";
			locCameraFromToPos(48.38, 9.48, 43.95, true, 43.69, 5.47, 48.13);
		break;
		
		case "guide_store":
			dialog.text = "Tienda. Los capitanes vienen aquí por provisiones, ron, medicinas, pólvora y munición. Si falta algo, busque contrabandistas en la taberna. Sin un buen tesorero, comerciar es perder tiempo y dinero.";
			link.l1 = "";
			link.l1.go = "guide_gate";
			locCameraFromToPos(-21.10, 6.60, 45.21, true, -30.00, 3.70, 45.00);
		break;
		
		case "guide_gate":
			dialog.text = "Puerta. Si el muelle es la puerta al mar, aquí está la entrada a la naturaleza salvaje. Peligroso, pero necesario para llegar a un fuerte, buscar tesoros o cruzar a otro asentamiento por tierra.";
			link.l1 = "";
			link.l1.go = "guide_45";
			locCameraFromToPos(50.58, 5.74, 23.21, true, 100.00, 0.00, 20.00);
			//AddQuestRecordInfo("Guide_OnLand", "1");
		break;
		
		case "guide_45":
			dialog.text = "No todas las colonias reciben bien a los forasteros. Si no quiere esperar a la noche, ice otra bandera en el mar y confíe en su sigilo, o compre una licencia comercial.";
			link.l1 = "";
			link.l1.go = "guide_46";
		break;
		
		case "guide_46":
			dialog.text = "Es usted buen oyente, amigo. ¿Le apetece divertirse un poco? Le propongo un duelo de práctica fuera de la puerta.";
			link.l1 = "Конечно! Это будет как нельзя кстати.";
			link.l1.go = "guide_47";
			link.l2 = "Gracias de todo corazón, monsieur, pero a partir de aquí me las arreglo solo.";
			link.l2.go = "guide_exit_11";
		break;
		
		case "guide_47": // телепортируем за городские ворота
			DialogExit();
			LAi_SetActorType(npchar);
			DoQuestReloadToLocation("FortFrance_ExitTown", "goto", "goto19", "Guide_ExitTown");
		break;
		
		case "guide_49":
			dialog.text = "Amigo mío, supongo que no es usted nuevo en esgrima, ¿verdad?";
			link.l1 = "¡Ja! Ya he sobrevivido a un abordaje y hasta...";
			link.l1.go = "guide_50";
			if (FindCharacterItemByGroupWithout_knife_03(pchar, BLADE_ITEM_TYPE) == "")
			{
				GiveItem2Character(pchar, "blade_05");
				EquipCharacterByItem(Pchar, "blade_05");
			}
		break;
		
		case "guide_50":
			dialog.text = "Excelente. ¿Empezamos?";
			link.l1 = "¡Bailemos!";
			link.l1.go = "guide_56";
			npchar.quest.guide_win = 0;
		break;
		
		case "guide_56": // махач
			LAi_SetPlayerType(pchar);
			LAi_SetCurHPMax(pchar); 
			LAi_GetCharacterMaxEnergy(pchar);
			LAi_SetCurHPMax(npchar); 
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_group_Delete("EnemyFight");
			if (MOD_SKILL_ENEMY_RATE <= 6)	// На первых трёх сложностях Валинье будет ослаблен
			{
				LAi_SetHP(npchar, LAi_GetCharacterMaxHP(npchar) * 0.7, LAi_GetCharacterMaxHP(npchar) * 0.7);
				npchar.rank = 1;
				SetSelfSkill(npchar, 1, 1, 1, 1, 1);
			}
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			// ставим проверяльщики
			LAi_SetCheckMinHP(pchar, 1, true, "Guide_HeroFail");
			LAi_SetCheckMinHP(npchar, 1, true, "Guide_HeroWin");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			//DoQuestCheckDelay("GuideFight_tutorial", 1.0);
		break;

		case "guide_57": // побил гида с первого раза
			dialog.text = "Tú... eres un hombre que sabe cómo empuñar su espada. Bien hecho, monsieur. Necesitas más práctica, pero tienes el potencial de convertirte en un verdadero maestro de la espada.";
			link.l1 = "Merci beaucoup. ¿Y ahora qué?";
			link.l1.go = "guide_62"; // нода на выход
			if (MOD_SKILL_ENEMY_RATE >= 6)
			{
				link.l2 = "¿Más práctica dices? ¿Hablas en serio? ¡Estoy cansado de este tono condescendiente desde que puse un pie en este miserable lugar!"; // Пасхалка Корсары 2 для сложности СФ и выше
				link.l2.go = "guide_64";
			}
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 80);
		break;

		case "guide_58": // побил гида со второго или третьего раза
			dialog.text = "¡Mucho mejor! Mira, todo lo que necesitas es concentrarte. Con un poco más de práctica, un día te convertirás en un espadachín decente.";
			link.l1 = "Merci beaucoup. ¿Y ahora qué?";
			link.l1.go = "guide_62"; // нода на выход
			AddComplexSelfExpToScill(20, 20, 20, 20);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
		break;

		case "guide_59": // побили первый раз
			dialog.text = "Gané, monsieur. Muévete más rápido, para mis estocadas, salta hacia atrás. ¿Una revancha?";
			link.l1 = "¡Oui! ¡Sin piedad, monsieur!";
			link.l1.go = "guide_56";
			link.l2 = "No, he tenido suficiente. Terminemos la lección. ¿Ahora qué?";
			link.l2.go = "guide_62"; // нода на выход
		break;

		case "guide_60": // побили второй раз
			dialog.text = "He ganado de nuevo, " + pchar.name + ". ¡No pierdas tu iniciativa! Atrapa mis golpes, fintéalos. Si ves que voy a golpear fuerte, salta o para, no te limites a defenderte. ¡Otra vez!";
			link.l1 = "¡Ven, monsieur, esta vez te daré una paliza!";
			link.l1.go = "guide_56";
			link.l2 = "No, he tenido suficiente. Terminemos la lección. ¿Qué hacemos ahora?";
			link.l2.go = "guide_62"; // нода на выход
		break;

		case "guide_61": // побили третий раз
			dialog.text = "Tienes mucho que aprender, " + pchar.name + ". No te preocupes, todavía tienes mucho tiempo para dominar la esgrima. Pero ten cuidado, no te arriesgues hasta que sepas cómo sostener un arma.";
			link.l1 = "Lo consideraré, monsieur, pero debo decir que tuviste demasiada suerte. Este maldito calor... la única razón por la que no te di una paliza. ¡Merde, terminemos nuestra lección de esgrima! ¿Y ahora qué?";
			link.l1.go = "guide_62"; // нода на выход
		break;

		case "guide_62":
			dialog.text = "Ahora es el momento de despedirse, monsieur. Fue un placer. Espero que mi presentación y entrenamiento hayan sido de alguna utilidad y resulten útiles en el futuro. Tal vez, nos volvamos a encontrar algún día.\nY acerca del dinero que necesitas - habla con las personas importantes de nuestra ciudad. Visita todos los lugares que te he mostrado hoy y habla con sus dueños. Pregunta por ahí. Da un paseo por la jungla y el fuerte. Encuentra un trabajo o... bueno, no soy sacerdote ni juez, echa un vistazo a las casas de la gente y observa qué baratijas puedes encontrar en sus cofres sin cerradura. Solo házlo cuando te den la espalda o los guardias te atraparán.\nBuena suerte, " + pchar.name + ". Tengo una fuerte corazonada de que tienes la chispa de la verdadera grandeza dentro de ti. ¡Haz todo lo posible por avivarla hasta convertirla en un fuego rugiente!";
			link.l1 = "Merci, monsieur. El placer fue mío. ¡Buen viento, y buena mar!";
			link.l1.go = "guide_63";
		break;

		case "guide_63":
			LAi_SetCurHPMax(pchar);
			LAi_GetCharacterMaxEnergy(pchar);
			DialogExit();
			chrDisableReloadToLocation = false; // открыть локацию
			npchar.lifeday = 0;
			DoQuestReloadToLocation("FortFrance_Town", "quest", "quest2", "");
		break;

		case "guide_64": // решили убить Валинье
			dialog.text = "¡Cierra el pico, monsieur! No toleraré tal insolencia por más tiempo. Sin embargo, entiendo tu reacción ante un nuevo entorno, por lo tanto, perdono tu arrebato esta vez. Pero cuida tus palabras de ahora en adelante. Adiós, Monsieur de Maure.";
			link.l1 = "Sin ofender, monsieur Valinnie. ¡Si estuviéramos en el Louvre en este momento, cuidarías tu tono! Es hora de enseñar una lección final a una provincia. ¡Defiéndete!";
			link.l1.go = "guide_65";
		break;

		case "guide_65":
			DialogExit();

			npchar.rank = 25;
			int iHp = MOD_SKILL_ENEMY_RATE * 10 + 300;
			LAi_SetHP(npchar, iHp, iHp);
			SetSelfSkill(npchar, 80, 80, 80, 80, 50);
			SetShipSkill(npchar, 50, 80, 35, 30, 50, 20, 30, 20, 80);
			SetSPECIAL(npchar, 9, 5, 8, 6, 5, 10, 8);
			SetCharacterPerk(npchar, "Energaiser");
			SetCharacterPerk(npchar, "BasicDefense");
			SetCharacterPerk(npchar, "AdvancedDefense");
			SetCharacterPerk(npchar, "CriticalHit");
			SetCharacterPerk(npchar, "Tireless");
			SetCharacterPerk(npchar, "HardHitter");
			SetCharacterPerk(npchar, "Sliding");
			SetCharacterPerk(npchar, "BladeDancer");
			SetCharacterPerk(npchar, "SwordplayProfessional");
			SetCharacterPerk(npchar, "Gunman");
			SetCharacterPerk(npchar, "GunProfessional");
			GiveItem2Character(npchar, "blade_30");
			EquipCharacterbyItem(npchar, "blade_30");
			GiveItem2Character(npchar, "cirass7");
			GiveItem2Character(npchar, "obereg_7");
			GiveItem2Character(npchar, "talisman11");
			AddMoneyToCharacter(npchar, 10000);
			AddItems(npchar, "gold_dublon", 25);
			AddItems(npchar, "bullet", 5);
			AddItems(npchar, "grapeshot", 5);
			AddItems(npchar, "GunPowder", 10);
			TakeItemFromCharacter(npchar, "blade_12");
			npchar.cirassId = Items_FindItemIdx("cirass4");
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_SetCurHPMax(pchar);
			LAi_GetCharacterMaxEnergy(pchar);
			LAi_SetImmortal(npchar, false);
			LAi_group_Delete("EnemyFight");
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			npchar.SaveItemsForDead = true;
			npchar.DontClearDead = true;
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "Guide_HeroKill");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string FindCharacterItemByGroupWithout_knife_03(ref chref, string groupID)
{
	ref refItm;
	string resultItemId;

	resultItemId = "";
	for (i = TOTAL_ITEMS - 1; i >= 0; i--)
	{
		refItm = &Items[i];
		if (!CheckAttribute(refItm, "groupID"))
			continue;
		if (refItm.groupID != groupID)
			continue;
		if (!CheckAttribute(chref, "items." + refItm.id))
			continue;
		if (refItm.id == "knife_03")
			continue;
		if (groupID == BLADE_ITEM_TYPE)
		{
			resultItemId = refItm.id;
		}
	}

	if (resultItemId != "")
	{
		return resultItemId;
	}

	return "";
}