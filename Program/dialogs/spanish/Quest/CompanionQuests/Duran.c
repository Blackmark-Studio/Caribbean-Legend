void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;
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
			dialog.text = "¿Qué necesita?";
			link.l1 = "Nada.";
			link.l1.go = "exit";
		break;
		
		case "SKD_DomAnri":
			dialog.text = "Saludos en mi hogar, caballeros. ¿Qué puedo hacer por ustedes?";
			link.l1 = "Levasseur envía sus saludos, monsieur.";
			link.l1.go = "SKD_DomAnri_2";
			StartQuestMovie(true, false, true);
		break;
		
		case "SKD_DomAnri_2":
			dialog.text = "Así que así es... ¡Alicia! Déjanos, por favor. Estos caballeros tienen asuntos conmigo.";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_2_1";
			CharacterTurnToLoc(npchar, "goto", "goto1");
		break;
		case "SKD_DomAnri_2_1":
			StartInstantDialog("SKD_Alisia", "SKD_DomAnri_3", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_3":
			dialog.text = "Pero...";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_3_1";
			CharacterTurnToLoc(npchar, "barmen", "stay");
		break;
		case "SKD_DomAnri_3_1":
			StartInstantDialog("SKD_Anri", "SKD_DomAnri_4", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_4":
			dialog.text = "Te amo, querida. ¡Adelante entonces!";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_5";
			CharacterTurnToLoc(npchar, "goto", "goto1");
		break;
		
		case "SKD_DomAnri_5":
			DialogExit();
			locCameraFromToPos(3.47, 2.41, 0.10, false, -1.05, 0.20, -0.07);
			
			sld = CharacterFromID("SKD_Anri");
			CharacterTurnByLoc(sld, "barmen", "stay");
			
			sld = CharacterFromID("SKD_Alisia");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "", "", "", "", -1);
			sld.location = "None";
			sld.lifeday = 0;
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("SKD_DomAnri_2", 4.0);
		break;
		
		case "SKD_DomAnri_6":
			dialog.text = "¡Maravillosas obras, oh Señor! ¡Valió la pena perderlo todo para encontrar el amor de tu vida al fin del mundo! Caballeros, soy todo vuestro. ¿No supongo que podremos llegar a un acuerdo?";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_6_1";
		break;
		case "SKD_DomAnri_6_1":
			StartInstantDialog("Duran", "SKD_DomAnri_7", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_7":
			dialog.text = "No, y tampoco intentes pedir clemencia.";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_7_1";
			CharacterTurnToLoc(npchar, "barmen", "stay");
			locCameraFromToPos(-0.52, 1.47, 0.76, false, -2.52, 0.20, 0.99);
		break;
		case "SKD_DomAnri_7_1":
			StartInstantDialog("SKD_Anri", "SKD_DomAnri_8", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_8":
			dialog.text = "No es propio de un Caballero de la Orden pedir clemencia.";
			link.l1 = "Un antiguo caballero, sin embargo.";
			link.l1.go = "SKD_DomAnri_9";
		break;
		
		case "SKD_DomAnri_9":
			dialog.text = "Los burócratas no tendrían toda la tinta del mundo para quitarme ese título.";
			link.l1 = "En ese caso, demuéstralo. Pero, primero, satisface mi curiosidad: ¿Eres un traidor a la Corona? De lo contrario, no entiendo por qué Levasseur quería tu vida con tanta desesperación.";
			link.l1.go = "SKD_DomAnri_10";
		break;
		
		case "SKD_DomAnri_10":
			dialog.text = "Soy fiel a mi juramento, monsieur, así que no me lo reproche. Solo diré que un traidor a la Corona me ha enviado a eliminar a otro traidor. Y lo hará una y otra vez hasta que un Hermano más capaz que yo tenga éxito. Basta de charla. ¡Caballeros, a la batalla!";
			link.l1 = "...";
			link.l1.go = "SKD_DomAnri_11";
		break;
		
		case "SKD_DomAnri_11":
			DialogExit();
			EndQuestMovie();
			
			sld = CharacterFromID("Duran");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "SKD_DomAnri_6");
		break;
		
		case "SKD_DomAnri_12":
			dialog.text = "¡Ah-ah! Oh, gracias, Capitán. Era un diablo duro. No había manera de que pudiera haberlo vencido yo solo.";
			link.l1 = "De alguna manera no me siento muy feliz por esta victoria. ¿Supongo que hemos terminado aquí?";
			link.l1.go = "SKD_DomAnri_13";
		break;
		
		case "SKD_DomAnri_13":
			dialog.text = "Aún no del todo, primero tenemos que limpiar y eliminar a la chica que se escapó tan rápido al segundo piso.";
			link.l1 = "¿Qué?! ¡Baja las armas! ¿Has perdido la cabeza, Claude? ¡No soy un carnicero!";
			link.l1.go = "SKD_DomAnri_14";
		break;
		
		case "SKD_DomAnri_14":
			dialog.text = "No tienes que hacer nada, Cap. Además, todo es tu culpa: no deberías haberle mencionado a Levasseur.";
			link.l1 = "Eso es una tontería y lo sabes. Y si te atreves a darme otra reprimenda inarticulada, no te saldrás con la tuya.";
			link.l1.go = "SKD_DomAnri_15";
		break;
		
		case "SKD_DomAnri_15":
			dialog.text = "¡Je! Mi error, Capitán. Es cierto, las órdenes de Levasseur decían claramente eliminar no solo al caballero, sino a todos sus compañeros. A todos, ¿entiendes? Con esta gente no se juega y sus demandas deben tomarse en serio. No me impidas hacer mi trabajo, Cap. Un último trabajo sucio y luego estaré contigo hasta el final, lo juro.";
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) > 70)
			{
				notification("Reputation Check Passed", "None");
				notification("Trustworthy", "Trustworthy");
				link.l1 = "(Confiable) (Honor) Una vez dijiste que estaba destinado a volar alto, y estabas feliz de contribuir a eso.";
				link.l1.go = "SKD_DomAnri_VD";
			}
			else
			{
				notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(71))+")", "None");
				notification("Perk Check Failed", "Trustworthy");
			}
			link.l2 = "¡Al diablo contigo! Haz tu trabajo sucio. Acepto tu juramento, y será mejor que lo tomes mortalmente en serio. ¿Nos entendemos?";
			link.l2.go = "SKD_DomAnri_DuranDruzhba";
			link.l3 = "No a este precio, Claude. No dejaré que mates a esa chica.";
			link.l3.go = "SKD_DomAnri_DuranDraka";
		break;
		
		case "SKD_DomAnri_DuranDraka":
			dialog.text = "¡Je! Supongo que estábamos destinados a matarnos el uno al otro, ¿eh, Capitán?";
			link.l1 = "Supongo que sí. Continuemos donde lo dejamos en Tortuga, ¿de acuerdo?";
			link.l1.go = "SKD_DomAnri_DuranDraka_2";
		break;
		
		case "SKD_DomAnri_DuranDraka_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			
			RemovePassenger(pchar, npchar);
			npchar.SaveItemsForDead = true;
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "SKD_DomAnri_DuranDraka");
		break;
		
		case "SKD_DomAnri_DuranDruzhba":
			dialog.text = "¡Sí sí, Capitán!";
			link.l1 = "...";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_2";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_2":
			DialogExit();
			
			LocatorReloadEnterDisable("PortRoyal_houseSp1", "reload2", true);
			sld = CharacterFromID("Duran");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen("PortRoyal_town", true);
			
			PChar.quest.SKD_DomAnri_DuranDruzhba.win_condition.l1 = "location";
			PChar.quest.SKD_DomAnri_DuranDruzhba.win_condition.l1.location = "PortRoyal_town";
			PChar.quest.SKD_DomAnri_DuranDruzhba.win_condition = "SKD_DomAnri_DuranDruzhba";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_3":
			dialog.text = "Está hecho, Capitán. Ella me sorprendió...";
			link.l1 = "No quiero oír hablar de eso. Yo cumplí mi palabra. Ahora es tu turno.";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_4";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_4":
			dialog.text = "El oro es una cosa, pero arriesgar tu propia piel por un simple mercenario vale mucho más. Estoy contigo hasta el final, Capitán.";
			link.l1 = "En ese caso, hemos terminado aquí.";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_5";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_5":
			dialog.text = "Sí, sí.";
			link.l1 = "...";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_6";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_6":
			DialogExit();
			
			EndQuestMovie();
			locCameraTarget(PChar);
			locCameraFollow();
			LAi_LocationDisableOfficersGen("PortRoyal_town", false);
			chrDisableReloadToLocation = false;
			AddQuestRecord("TheFormerKnight", "3");
			CloseQuestHeader("TheFormerKnight");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			
			sld = CharacterFromID("Duran");	//Клод Дюран становится постоянным офицером
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.Dialog.CurrentNode = "hired";
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0;
			sld.Health.maxHP    = 60.0;
			SetCharacterPerk(sld, "ShipEscape");
			
			pchar.questTemp.SKD_DuranDruzhba = true;
			pchar.questTemp.SKD_DevushkaUbita = true;
			sld.reputation = sti(sld.reputation) - 15;
			OfficersFollow();
		break;
		
		case "SKD_DomAnri_VD":
			dialog.text = "Lo hice. ¿Cuál es tu punto, Cap?";
			link.l1 = "Demuéstrame que esas palabras no fueron charlatanería vacía. ¿Quieres ganarte un lugar en mi equipo? ¿Una parte del botín futuro? Sigue mis órdenes. No toques a la chica. ¿Por qué? Porque si no lo haces, serás un carnicero para siempre, y no tengo espacio para personas así.";
			link.l1.go = "SKD_DomAnri_VD_2";
		break;
		
		case "SKD_DomAnri_VD_2":
			dialog.text = "Esta es la segunda vez que tú y yo estamos a punto de luchar a muerte, Cap\n¡Y una vez más, tú ganas gracias a tu don para rascarte la lengua! ¡Ja ja! ¡Lo dijiste! Bueno, al diablo con la chica. Después de todo, soy un animal. ¿Permiso para unirme a la tripulación?";
			link.l1 = "Bienvenido, Claude. Esta vez de verdad.";
			link.l1.go = "SKD_DomAnri_VD_3";
		break;
		
		case "SKD_DomAnri_VD_3":
			dialog.text = "¡Aye, aye, Capitán!";
			link.l1 = "...";
			link.l1.go = "SKD_DomAnri_VD_4";
		break;
		
		case "SKD_DomAnri_VD_4":
			DialogExit();
			AddQuestRecord("TheFormerKnight", "2");
			CloseQuestHeader("TheFormerKnight");
			chrDisableReloadToLocation = false;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			
			sld = CharacterFromID("Duran");	//Клод Дюран становится постоянным офицером
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.Dialog.CurrentNode = "hired";
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0;
			sld.Health.maxHP    = 60.0;
			SetCharacterPerk(sld, "ShipEscape");
			
			pchar.questTemp.SKD_DuranDruzhba = true;
			sld.reputation = 60;
			OfficersFollow();
		break;
		
		case "SKD_KlodDuran":
			dialog.text = "Algo ha surgido, Capitán.";
			Link.l1 = "Déjame adivinar: ¿vas a amenazar con renunciar y exigir un aumento otra vez?";
			Link.l1.go = "SKD_KlodDuran_1";
		break;
		
		case "SKD_KlodDuran_1":
			dialog.text = "¡Je! No esta vez... No se preocupe, Capitán, mientras pague, soy todo suyo... dentro de lo razonable, por supuesto. Es la única manera en que nuestros hermanos mercenarios sobreviven. Y hasta los mejores de nosotros apenas reciben un mísero pago.";
			link.l1 = "¿Por qué no vamos directamente al grano?";
			link.l1.go = "SKD_KlodDuran_2";
		break;
		
		case "SKD_KlodDuran_2":
			dialog.text = "¿Recuerdas a esa perra de Tortuga?";
			link.l1 = "¿Marceline? ¿La esposa del gobernador? No se olvida a una mujer así.";
			link.l1.go = "SKD_KlodDuran_3";
		break;
		
		case "SKD_KlodDuran_3":
			dialog.text = "No llegué a la casa de Levasseur por accidente. Tuve tratos con ese bribón y hereje.";
			link.l1 = "Es bastante extraño que hables tan despectivamente de los poderosos, Claude.";
			link.l1.go = "SKD_KlodDuran_4";
		break;
		
		case "SKD_KlodDuran_4":
			dialog.text = "¿Eh? ¡Je! ¡Levasseur es el diablo! ¡Es mucho peor que incluso los piratas que se alimentan de él!";
			link.l1 = "Usted mismo acaba de decir que hizo negocios con él. ¿No es un poco hipócrita de su parte?";
			link.l1.go = "SKD_KlodDuran_5";
		break;
		
		case "SKD_KlodDuran_5":
			dialog.text = "Yo no soy un ángel, Capitán, y me gano la vida matando a quien me dicen. Por eso me valoras tanto, ¿no es así? ¡Pero incluso a tipos como yo se nos pone la piel de gallina al escuchar rumores sobre lo que hacen a las mujeres en Tortuga en las guaridas de Levasseur!";
			link.l1 = "Los rumores no me interesan. Este hombre es un noble y un servidor del Rey, y merece respeto.";
			link.l1.go = "SKD_KlodDuran_6";
		break;
		
		case "SKD_KlodDuran_6":
			dialog.text = "¿Así que robaste al sirviente de este rey y te acostaste con su esposa? ¡Je! Tú mismo, Capitán. Vamos al grano. Su Excelencia me ordenó encontrar y matar a un hombre. Una tarea bastante rutinaria, aunque no suele venir de alguien tan importante, y menos en persona.";
			link.l1 = "¿Y qué quieres? ¿Que te libere para que puedas cumplir tu palabra y matar a este hombre?";
			link.l1.go = "SKD_KlodDuran_7";
		break;
		
		case "SKD_KlodDuran_7":
			dialog.text = "Quiero que me ayudes a hacerlo, Cap. Cuando las cosas se pusieron mal para mí en Tortuga, accedí a unirme a tu servicio, pero no descansaré hasta que el trabajo esté hecho. Levasseur me mataría si se enterara. Además, es poco profesional dejar un trabajo sin terminar.";
			link.l1 = "¿Es profesional tener asuntos con la esposa de un cliente? Es muy extraño escuchar tal solicitud de ti, especialmente si recordamos el comienzo de nuestra conversación, donde describiste con bastante precisión la esencia de nuestra relación. Sangre por oro, ¿eh?";
			link.l1.go = "SKD_KlodDuran_8";
		break;
		
		case "SKD_KlodDuran_8":
			dialog.text = "Si me ayudas, no solo obtendrás mi espada, también obtendrás mi lealtad. Puedo ver de inmediato que estás destinado a volar alto, Capitán. Estaría encantado de ayudar a que eso suceda.";
			link.l1 = "Admito que preferiría tener a un hombre de tus habilidades cubriéndome las espaldas. ¿Dónde podemos encontrar a este objetivo tuyo?";
			link.l1.go = "SKD_KlodDuran_10";
			link.l2 = "Tu sable será suficiente por ahora. No soy un asesino. ¡A tus órdenes, oficial!";
			link.l2.go = "SKD_KlodDuran_9";
		break;
		
		case "SKD_KlodDuran_9":
			dialog.text = "Sí, sí, Capitán. De todos modos valía la pena preguntar.";
			link.l1 = "...";
			link.l1.go = "SKD_KlodDuran_9_1";
		break;
		
		case "SKD_KlodDuran_9_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.loyality = makeint(npchar.loyality) + 10;
			Return_DurandOfficer();
		break;
		
		case "SKD_KlodDuran_10":
			dialog.text = "¡Je! Ese es el problema, Capitán. Todo lo que sé es que es un antiguo caballero de la Orden de Malta que se está escondiendo en algún lugar del territorio inglés. Un hombre de noble cuna, así que no estará viviendo en una choza.";
			link.l1 = "¿Caballero de la Orden?";
			link.l1.go = "SKD_KlodDuran_11";
		break;
		
		case "SKD_KlodDuran_11":
			dialog.text = "Un antiguo caballero. Sí, y ya he lamentado haber aceptado este trabajo mil veces. Los caballeros pelean como demonios, así que te garantizo una prueba seria de tus habilidades con la espada.";
			link.l1 = "No me gusta, pero vamos a intentarlo. Entonces: ¿no es un hombre pobre, un noble y escondiéndose con los ingleses? ¿Levasseur no dijo por qué debería ser tratado?";
			link.l1.go = "SKD_KlodDuran_12";
		break;
		
		case "SKD_KlodDuran_12":
			dialog.text = "¡Por supuesto que no lo hará! Pero es obviamente político, de lo contrario habría enviado soldados.";
			link.l1 = "Lo intentaré, pero no puedo prometer nada.";
			link.l1.go = "SKD_KlodDuran_13";
		break;
		
		case "SKD_KlodDuran_13":
			dialog.text = "Gracias, Capitán.";
			link.l1 = "...";
			link.l1.go = "SKD_KlodDuran_14";
		break;
		
		case "SKD_KlodDuran_14":
			DialogExit();
			SetQuestHeader("TheFormerKnight");
			AddQuestRecord("TheFormerKnight", "1");
			chrDisableReloadToLocation = false;
			npchar.loyality = makeint(npchar.loyality) + 15;
			Return_DurandOfficer();
			PChar.quest.SKD_DomAnri.win_condition.l1 = "location";
			PChar.quest.SKD_DomAnri.win_condition.l1.location = "PortRoyal_houseSp1";
			PChar.quest.SKD_DomAnri.win_condition = "SKD_DomAnri";
			pchar.GenQuestBox.PortRoyal_houseSp1.box1.items.chest = 1;
		break;
		
	}
} 
