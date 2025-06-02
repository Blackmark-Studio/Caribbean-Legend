// диалог прочих НПС по квесту Саги
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

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

		//---------------------------------------------Джимми в доме в Марун-Тауне------------------------------------
	case "Jimmy":
		dialog.text = "¿Qué quieres? ¡No ves que estoy de luto! ¡Lárgate antes de que te eche escaleras abajo!";
		link.l1 = "Bueno, cómprate una casa más grande con escaleras para eso. Entonces hablaremos de lanzar gente por las escaleras, héroe...";
		link.l1.go = "Jimmy_1_1";
		link.l2 = "¿Por qué estás tan disgustado, Jimmy? ¡No probaré más ron en toda mi maldita vida si no tiene que ver con alguna mujer hermosa! Sólo una mujer podría hacer que un viejo lobo de mar como tú amenace a sus viejos amigos...";
		link.l2.go = "Jimmy_1_2";
		break;

	case "Jimmy_1_1":
		dialog.text = "¡Odio a la gente quisquillosa como tú! Siempre se quedan con los mejores pedazos del pastel. No me dejaron matar a un advenedizo, así que desahogaré mi ira contigo!";
		link.l1 = "... ";
		link.l1.go = "Jimmy_fight";
		break;

	case "Jimmy_fight":
		chrDisableReloadToLocation = true; // закрыть локацию
		DialogExit();
		LAi_SetImmortal(npchar, false);
		LAi_SetWarriorType(npchar);
		LAi_group_MoveCharacter(npchar, "EnemyFight");
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "Saga_KillJimmy");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "Jimmy_1_2":
		dialog.text = "¿¡Sí?! ¿Te conozco? No te recuerdo, maldita sea...";
		link.l1 = "Soy yo, " + pchar.name + "¡Tuvimos un buen rato en Blueweld después de que casi destriparas a ese insolente en un abrigo! ¿Cómo se llamaba? Lo he olvidado... De todos modos, no me importarán un comino los cañones de su corbeta si alguna vez me lo encuentro en el mar.";
		link.l1.go = "Jimmy_2";
		break;

	case "Jimmy_2":
		dialog.text = "¡Su nombre era Arthur! ¡Arthur Donovan, capitán de la corbeta 'Arbutus'! ¡Maldito bastardo! ¿Estás de acuerdo en que estuve cerca de enviarlo al diablo?";
		link.l1 = "¡Por supuesto! No tenía absolutamente ninguna oportunidad, pero tus compañeros interfirieron. Perdónalos, no querían que te ahorcaran por el asesinato de un oficial naval.";
		link.l1.go = "Jimmy_3";
		break;

	case "Jimmy_3":
		dialog.text = "¡Argh! ¡Si tan solo tuviera un barco! Este bastardo se puede rastrear fácilmente cerca de Antigua... ¡ja! Te debo una si lo envías al fondo del mar.";
		link.l1 = "¡Trato hecho, ja-ja! Por cierto, ¿realmente vale la pena tu sufrimiento por Rumba?";
		link.l1.go = "Jimmy_4";
		break;

	case "Jimmy_4":
		dialog.text = "¡Por supuesto! Nunca he conocido a nadie mejor que ella. Pero ella solo se ríe de mí. Todos quieren a esa sirena. Algunos marineros me contaron en secreto que nuestro Jacob está buscando a una chica que se parece a mi Rumba. ¡Él también la quiere! ¿Cómo puedo seguir sus órdenes ahora?";
		link.l1 = "¡Mantén la boca cerrada, compañero! Las paredes tienen oídos... ¿Y por qué crees que Jackman está buscando a Rumba?";
		link.l1.go = "Jimmy_5";
		break;

	case "Jimmy_5":
		dialog.text = "¡Lo es, sin duda! Está buscando a un tal Henry el Verdugo y a una muchacha de veinte años con cabello rubio y ojos azules. Alguna Gladys Chandler de Belice debe ser su cuidadora.";
		link.l1 = "¡Espera! Gladys tiene un apellido diferente. ¡Y ella es su madre!";
		link.l1.go = "Jimmy_6";
		break;

	case "Jimmy_6":
		dialog.text = "¡Jackman es astuto! ¡No puedes atraparlo desprevenido! He estado cortejando a Rumba por un tiempo y descubrí que Gladys se casó con Sean McArthur exactamente hace veinte años. Y antes de eso vivía en Belice. Su primer esposo se llamaba Pete Chandler.\nEl pobre Pete fue asesinado en una pelea de borrachos. Dicen que el propio McArthur fue el responsable ya que tenía sentimientos por la rolliza Gladys en ese entonces. Ella quedó viuda con un bebé en sus brazos. El niño no sobrevivió mucho a su padre y murió de fiebre poco después.\nY solo un par de meses después Gladys y Sean aparecieron con una niña, que afirmaron ser hija de McArthur, en Blueweld. Entonces, ¿cómo pudo Gladys dar a luz a otro bebé tan pronto? ¿Lo entiendes?";
		link.l1 = "¿Le has contado a alguien más sobre esto?";
		link.l1.go = "Jimmy_7";
		break;

	case "Jimmy_7":
		dialog.text = "Aún no. ¡Cierra la boca o... bueno, ya me conoces!";
		link.l1 = "Sí, tengo. Tienes una lengua podrida que revela secretos a cualquiera. Rumba hizo bien en alejarte, bocazas...";
		link.l1.go = "Jimmy_8_1";
		link.l2 = "¡Seguro! ¡Seré discreto! Y ahora tengo que irme. Adiós, Jimmy.";
		link.l2.go = "Jimmy_8_2";
		break;

	case "Jimmy_8_1":
		dialog.text = "¿Qué... qué dijiste?!";
		link.l1 = "No podrás contárselo a nadie más...";
		link.l1.go = "Jimmy_fight";
		pchar.questTemp.Saga.Jimmysecret = "true";
		break;

	case "Jimmy_8_2":
		DialogExit();
		pchar.questTemp.Saga = "jackman";
		LAi_CharacterDisableDialog(npchar);
		npchar.lifeday = 0;
		AddQuestRecord("Saga", "4_1");
		break;
		// <-- Джимми

		//-------------------------------------------корвет Донована, абордаж-----------------------------------------
		// Донован
	case "Donovan_abordage":
		PlaySound("Voice\Spanish\saga\Artur Donovan.wav");
		dialog.text = "¡Cómo te atreves, convicto!";
		link.l1 = "¿Estás hablando contigo mismo, señor?! ¿Dónde está Rumba?";
		link.l1.go = "Donovan_abordage_1";
		break;

	case "Donovan_abordage_1":
		dialog.text = "¿Qué Rumba? No tengo escoria con apodos en mi barco. ¡Este es un navío de la marina inglesa!";
		link.l1 = "No te hagas el tonto conmigo, Donovan. Sabes perfectamente de quién hablo. ¿Dónde está la chica? ¿Dónde está Helen? Respóndeme, bastardo inmundo...";
		link.l1.go = "Donovan_abordage_2";
		break;

	case "Donovan_abordage_2":
		dialog.text = "¿Helen? ¡No hay putas de tierra en mi barco, pedazo de mierda!";
		link.l1 = "¿No hay putas en tierra? Difícil de creer, ya que una de ellas está justo frente a mí en este mismo momento... Supongo que no tiene sentido continuar nuestra conversación. ¡Muere, gusano patético!";
		link.l1.go = "Donovan_abordage_3";
		break;

	case "Donovan_abordage_3":
		chrDisableReloadToLocation = true; // закрыть локацию
		DialogExit();
		LAi_SetCurHPMax(npchar);
		QuestAboardCabinDialogFree();
		LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Saga_AfterDonovanBoarding");
		AddDialogExitQuest("MainHeroFightModeOn");
		pchar.questTemp.Saga.Takehelen = "true"; // признак, что абордировали судно
		break;

	// наш матрос
	case "Tempsailor":
		dialog.text = "Capitán, hemos registrado todas las cabinas y la bodega de carga como nos dijo. Encontramos a una muchacha encadenada en la bodega...";
		link.l1 = "¡Qué bastardo! Tal como pensaba... ¿Ya has liberado a la chica?";
		link.l1.go = "Tempsailor_1";
		break;

	case "Tempsailor_1":
		dialog.text = "Claro, Capitán. Ella ha sido llevada a salvo a su barco.";
		link.l1 = "¡Bien hecho! Llévala a mi camarote, quiero hablar con ella una vez que hayamos terminado aquí.";
		link.l1.go = "Tempsailor_2";
		break;

	case "Tempsailor_2":
		dialog.text = "¡Sí, sí, Capitán!";
		link.l1 = "...";
		link.l1.go = "Tempsailor_3";
		break;

	case "Tempsailor_3":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
		break;
		//<-- абордаж корвета Донована

		//----------------------------------------поиск Энрике Гонсалеса, Картахена----------------------------------
		// фальшивый Гонсалес №1, дом
	case "GonsalesA":
		dialog.text = "¿Quieres algo?";
		link.l1 = "¡Hola, Verdugo! El Capitán Butcher te envía saludos.";
		link.l1.go = "GonsalesA_1_1";
		link.l2 = "Me llamo Charles de Maure. Busco a Enrique, el hijo de la señora Gonzales, en nombre de su viejo amigo. Creo que tú eres él...";
		link.l2.go = "GonsalesA_2_1";
		break;

	case "GonsalesA_1_1":
		dialog.text = "¡Qué demonios! ¡No conozco a ningún Butcher!";
		link.l1 = "Vamos, Henry. Dime por qué los piratas de Jackman te están buscando y no te haré daño.";
		link.l1.go = "GonsalesA_1_2";
		break;

	case "GonsalesA_1_2":
		dialog.text = "¡Ayuda! ¡Piratas! ¡Asesinato!";
		link.l1 = "¡Cállate, idiota! Media ciudad vendrá aquí por tus gritos. ¡Ah!, ¿eso es lo que quieres?";
		link.l1.go = "GonsalesA_1_fight";
		break;

	case "GonsalesA_1_fight":
		DialogExit();
		SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		LAi_group_MoveCharacter(NPChar, "EnemyFight");
		LAi_group_Attack(NPChar, Pchar);
		LAi_group_SetCheck("EnemyFight", "Saga_KillGonsalesA");
		AddDialogExitQuest("MainHeroFightModeOn");
		pchar.questTemp.Saga.Trap = "true";
		break;

	case "GonsalesA_2_1":
		dialog.text = "Mm... Señor, debe estar equivocado. Crecí en una familia extranjera, no recuerdo a mi madre biológica. He adoptado el apellido de mi tutor. No sé el nombre de mi madre, pero dudo que fuera Gonzales. Puede hacer averiguaciones sobre mí y cualquier residente antiguo confirmará mis palabras. Mi padrastro era un hombre famoso, no tenía hijos propios, así que heredé esta casa y...";
		link.l1 = "Lo siento. Parece que me equivoqué. Adiós.";
		if (CheckAttribute(pchar, "questTemp.Mtraxx.Cartahena.Gold"))
			link.l1.go = "GonsalesA_3_1";
		else
			link.l1.go = "GonsalesA_2_2";
		break;

	case "GonsalesA_2_2":
		DialogExit();
		LAi_CharacterDisableDialog(npchar);
		chrDisableReloadToLocation = false; // открыть локацию
		AddQuestRecord("Saga", "17");
		break;

	// belamour участвовал в событиях Картахены -->
	case "GonsalesA_3_1":
		dialog.text = "No lo creo.";
		link.l1 = "¿Disculpa?";
		link.l1.go = "GonsalesA_3_2";
		break;

	case "GonsalesA_3_2":
		dialog.text = "Sabes, recientemente nuestra colonia fue atacada ferozmente por piratas. ¿Creo que has oído sobre eso? Como resultado de este ataque, innumerables personas sufrieron. Yo salí ileso, pero mi negocio heredado está pasando por momentos difíciles ahora. Y el culpable de toda esta calamidad es el líder de estos piratas, un canalla llamado Charlie Prince.";
		link.l1 = "Lamento mucho, pero ¿qué tiene eso que ver conmigo?";
		link.l1.go = "GonsalesA_3_3";
		break;

	case "GonsalesA_3_3":
		dialog.text = "¡Ja, ja, solo mira a este corderito inocente! Te sugiero que cubras mis pérdidas, ya que tú eres el culpable de ellas. Me conformaré con una suma de quince mil pesos. Y fingiré que nunca has estado en mi casa.";
		if (sti(pchar.money) >= 15000)
		{
			link.l1 = "Qué vengativos sois todos... Aquí está vuestro dinero. Y recordad, si alguien descubre que estuve en esta ciudad, volveré por vosotros.";
			link.l1.go = "GonsalesA_3_4";
		}
		link.l2 = "¿Quince mil? Hm... No creo que tu vida valga tanto. Así que supongo que es más barato simplemente cortarte para que no chismorrees.";
		link.l2.go = "GonsalesA_3_5";
		break;

	case "GonsalesA_3_4":
		DialogExit();
		LAi_CharacterDisableDialog(npchar);
		chrDisableReloadToLocation = false; // открыть локацию
		AddQuestRecord("Saga", "171");
		break;

	case "GonsalesA_3_5":
		dialog.text = "¡Guardias! ¡Piratas! ¡Asesinato!";
		link.l1 = "¡Cállate, idiota!";
		link.l1.go = "GonsalesA_3_6";
		break;

	case "GonsalesA_3_6":
		DialogExit();
		iTemp = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE - 2;
		for (i = 1; i <= 2; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("SpSold" + i, "sold_" + NationShortName(SPAIN) + "_" + (rand(1) + 1), "man", "man", iTemp, SPAIN, 0, true, "soldier"));
			SetFantomParamFromRank(sld, iTemp, true);
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, false);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
		}
		sld = GetCharacter(NPC_GenerateCharacter("SpOfficer", "off_" + NationShortName(SPAIN) + "_" + (rand(1) + 1), "man", "man", iTemp, SPAIN, 0, true, "quest"));
		FantomMakeCoolFighter(sld, 25, 100, 100, "blade_13", "pistol6", "bullet", 150);
		ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		LAi_group_MoveCharacter(NPChar, "EnemyFight");
		LAi_group_Attack(NPChar, Pchar);
		LAi_group_SetCheck("EnemyFight", "Saga_KillGonsalesAK");
		AddDialogExitQuest("MainHeroFightModeOn");
		pchar.questTemp.Saga.Trap = "true";
		break;
	// <-- участвовал в событиях Картахены

	// фальшивый Гонсалес №2, улицы
	case "GonsalesB":
		PlaySound("Voice\Spanish\citizen\Pirati v Gorode-19.wav");
		dialog.text = "Veo que te gusta mi alfanje. Puedo vendértelo si quieres. No pediré mucho, me muero por beber un poco de ron y mis bolsillos están vacíos.";
		link.l1 = "¿Y para qué diablos lo necesitaría? Forest Devil me ha pedido que te dé sus mejores saludos.";
		link.l1.go = "GonsalesB_1_1";
		if (sti(pchar.money) >= 1000)
		{
			link.l2 = "Bueno, sí. Tienes un buen sable, de hecho. ¿Cuánto?";
			link.l2.go = "GonsalesB_2_1";
		}
		break;

	case "GonsalesB_1_1":
		dialog.text = "¡Me habría dado mejor un par de cientos de pesos en su lugar!";
		link.l1 = "¿Conoces a Svenson?";
		link.l1.go = "GonsalesB_1_2";
		break;

	case "GonsalesB_1_2":
		dialog.text = "Que te jodan a ti y a tu Svenson, mándalo al diablo. Al diablo del bosque o al diablo del mar, me importa un bledo. Si no estás dispuesto a ayudar a un hombre enfermo comprando su alfanje, entonces te lo meteré por el culo gratis.";
		link.l1 = "¿De veras? ¡Veamos cómo piensas hacer eso, cara de mierda!";
		link.l1.go = "GonsalesB_1_fight";
		break;

	case "GonsalesB_1_fight":
		chrDisableReloadToLocation = true;
		DialogExit();
		LAi_group_MoveCharacter(NPChar, "EnemyFight");
		LAi_group_Attack(NPChar, Pchar);
		LAi_group_SetCheck("EnemyFight", "Saga_KillGonsalesB");
		AddDialogExitQuest("MainHeroFightModeOn");
		pchar.questTemp.Saga.Trap = "true";
		break;

	case "GonsalesB_2_1":
		dialog.text = "¡Veo que eres un hombre con experiencia! Mil pesos y es tuyo.";
		link.l1 = "¡Trato hecho!";
		link.l1.go = "GonsalesB_2_2";
		break;

	case "GonsalesB_2_2":
		AddMoneyToCharacter(pchar, -1000);
		GiveItem2Character(pchar, "blade_10");
		RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
		dialog.text = "Solo hay dos sables como este en Cartagena: el mío y el del viejo Alvares del faro. Pero él no venderá el suyo. Es un hipócrita, puedo oler a un ex-pirata a una milla de distancia. La hoja es una especie de talismán para él.\nParece que el pobre alma lamenta cosas que quiere olvidar. Esta debe ser la razón por la que va a la iglesia todos los meses, por pecados que no le dejan dormir.";
		link.l1 = "Y veo que también tienes algo de historia. Debes ser tú de quien Svenson hablaba. Dijo que te diera sus mejores saludos en caso de encontrarte en Cartagena.";
		link.l1.go = "GonsalesB_2_3";
		break;

	case "GonsalesB_2_3":
		dialog.text = "¿Svenson? Nunca he oído hablar de él. Mi nombre es Enrique Gallardo. Pero si tu Svenson tiene una botella de ron para mí, estoy dispuesto a ser Henry para él. Llámame como quieras, solo no me llames tarde a la cena. Entonces, ¿vamos?";
		link.l1 = "Hoy no. Svenson está lejos, pero la taberna está cerca. Tus bolsillos ya no están vacíos, así que cuídate, Enrique.";
		if (CheckAttribute(pchar, "questTemp.Mtraxx.Cartahena.Gold"))
			link.l1.go = "GonsalesB_3_1";
		else
			link.l1.go = "GonsalesB_2_4";
		break;

	case "GonsalesB_2_4":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
		npchar.lifeday = 0;
		AddQuestRecord("Saga", "19");
		pchar.questTemp.Saga = "ortega";
		Saga_SetOrtega();
		break;

	// belamour участвовал в событиях Картахены -->
	case "GonsalesB_3_1":
		dialog.text = "No están completamente llenas, sin embargo. Quiero más. Y tú me pagarás.";
		link.l1 = "Estoy desconcertado... ¿No valoras tu vida? ¿Planeas robarme en medio de la ciudad? ¿Y esto después de que tú mismo me vendiste tu arma?";
		link.l1.go = "GonsalesB_3_2";
		break;

	case "GonsalesB_3_2":
		dialog.text = "No, me pagarás por tu cuenta. ¿Y sabes por qué?";
		link.l1 = "Curioso por escuchar.";
		link.l1.go = "GonsalesB_3_3";
		break;

	case "GonsalesB_3_3":
		dialog.text = "Te reconocí. Estaba en los calabozos por una pelea de borrachos en la taberna cuando tus hombres irrumpieron en la prisión y acabaron con todos los guardias. Logré alcanzar el cadáver del guardia con las llaves y salí a las calles. La ciudad estaba en llamas, cadáveres, sangre y humo de pólvora por todas partes... ¡Como en un abordaje! Y a través de ese humo, te vi salir de la residencia del gobernador. Poético, ¿no es así? ¡Jo-ho-ho, hola, Charlie Príncipe!";
		link.l1 = "¡Deja de gritar así! Sabiendo lo que sabes, especialmente no deberías intentar sacarme dinero. ¿Te das cuenta siquiera de lo que puedo hacerte?";
		link.l1.go = "GonsalesB_3_4";
		break;

	case "GonsalesB_3_4":
		dialog.text = "¿En medio de la ciudad que una vez robaste? No puedes hacer nada. Así que, para concluir... lo haremos de esta manera: me das... digamos, diez mil pesos ahora mismo. Creo que será suficiente para un mes. ¡Y te vas por tu camino! Ya sea con tu amado Henry, a Svenson, o a cualquier otro diablo de tu elección... Y si no lo haces, solo necesito gritar, y te arrastrarán a una cámara personal especialmente preparada llena de herramientas de tortura.";
		if (sti(pchar.money) >= 10000)
		{
			link.l1 = "¡Maldita sea, toma tus diez mil y sal de mi vista! Y, Dios no lo quiera, que te vuelva a ver.";
			link.l1.go = "GonsalesB_3_5";
		}
		link.l2 = "Eso es todo, ya he tenido suficiente de esto. Tu arma es mía, así que no tienes oportunidad, escoria.";
		link.l2.go = "GonsalesB_3_7";
		link.l3 = "¡Ja, ja, eres bueno! ¿Sabes qué? A cualquier otro ya le habría abierto desde el vientre hasta la garganta. Pero gente como tú me hace falta. ¿Qué te parece esto?: te doy diez mil pesos, te devuelvo tu 'Hombre Ahorcado', y te doy tres mil más cada mes - Debería ser suficiente para el licor - Y te conviertes en un pasajero en mi barco.";
		link.l3.go = "GonsalesB_3_9";
		break;

	case "GonsalesB_3_5":
		dialog.text = "¡Está bien, está bien, ya me voy! ¡Buena suerte con tu búsqueda, Príncipe Charlie!";
		link.l1 = "...";
		link.l1.go = "GonsalesB_3_6";
		break;

	case "GonsalesB_3_6":
		AddMoneyToCharacter(pchar, -10000);
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
		npchar.lifeday = 0;
		AddQuestRecord("Saga", "191");
		pchar.questTemp.Saga = "ortega";
		Saga_SetOrtega();
		break;

	case "GonsalesB_3_7":
		dialog.text = "¡Guardias! ¡Guardias!!! ¡Es Charlie Prince!!!";
		link.l1 = "¡Maldito seas, bastardo!";
		link.l1.go = "GonsalesB_3_8";
		break;

	case "GonsalesB_3_8":
		DialogExit();
		LAi_SetActorTypeNoGroup(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
		LAi_group_AttackGroup("Spain_citizens", LAI_GROUP_PLAYER);
		npchar.lifeday = 0;
		AddQuestRecord("Saga", "192");
		pchar.questTemp.Saga = "ortega";
		Saga_SetOrtega();
		break;

	case "GonsalesB_3_9":
		dialog.text = "¿Sugieres que me una a tu tripulación?";
		link.l1 = "Exactamente. Pero esta es una oferta única. Entonces, ¿qué dices? ¿Aceptas, o te destripo aquí mismo? No creerás que puedes chantajear al príncipe Charlie tan fácilmente, ¿verdad?";
		link.l1.go = "GonsalesB_3_10";
		break;

	case "GonsalesB_3_10":
		if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34 && makeint(pchar.reputation.nobility) < 48)
		{
			dialog.text = "¡Demonios! ¡El mismísimo Charlie Prince me está ofreciendo unirme a su tripulación! ¡Maldita sea, acepto! Devuélveme mi espada y diez mil pesos. ¡Nunca pensé que resultaría así!";
			link.l1 = "Aquí. Y mantén la boca cerrada: nadie en esta ciudad necesita saber quién soy, ¿entendido?";
			link.l1.go = "GonsalesB_3_11";
			break;
		}
		if (makeint(pchar.reputation.nobility) > 47)
		{
			dialog.text = "No. Puede que seas un capitán decente, pero me parece que eres un poco demasiado estirado. Sí, enseñaste a los españoles a temer una vez, llevando a cabo una atrevida incursión en Cartagena, pero todo eso fue solo con la ayuda de Marcus Tyrex. No tienes agallas para saquear honestamente por tu cuenta. ¡Así que, suelta la pasta!";
		}
		if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 35)
		{
			dialog.text = "No. Ciertamente eres un pirata notorio, pero como capitán, no pareces tan impresionante. Sólo lograste saquear la colonia con la ayuda de Marcus Tyrex - ni siquiera te atreverías a abordar un balandro destartalado por tu cuenta. ¡Así que afloja el dinero!";
		}
		if (sti(pchar.money) >= 10000)
		{
			link.l1 = "¡Maldita sea, toma tus diez mil y desaparece de mi vista! Y, Dios no lo quiera, que te vuelva a ver.";
			link.l1.go = "GonsalesB_3_5";
		}
		link.l2 = "Eso es todo, ya he tenido suficiente de esto. Tu arma es mía, así que no tienes ninguna oportunidad, escoria.";
		link.l2.go = "GonsalesB_3_7";
		break;

	case "GonsalesB_3_11":
		dialog.text = "Entendido, no soy un tonto.";
		link.l1 = "Bien.";
		link.l1.go = "GonsalesB_3_12";
		break;

	case "GonsalesB_3_12":
		DialogExit();
		AddMoneyToCharacter(pchar, -10000);
		LAi_RemoveLoginTime(npchar);
		npchar.quest.OfficerPrice = 3000;
		npchar.reputation.nobility = 30;
		npchar.dialog.FileName = "Enc_Officer_dialog.c";
		npchar.loyality = MAX_LOYALITY;
		GiveItem2Character(npchar, "blade_10");
		EquipCharacterByItem(npchar, "blade_10");
		TakeItemFromCharacter(pchar, "blade_10");
		Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
		AddQuestRecord("Saga", "193");
		pchar.questTemp.Saga = "ortega";
		Saga_SetOrtega();
		AddDialogExitQuestFunction("LandEnc_OfficerHired");
		break;
	// <-- участвовал в событиях Картахены

	// настоящий Гонсалес - Ортега, маяк
	case "Ortega":
		dialog.text = "No espero invitados, ni hoy ni nunca. ¿Qué quieres?";
		link.l1 = "Hola, Verdugo. Forest Devil me ha enviado. Es bueno que te haya encontrado antes que los muchachos de Jackman. Sus hombres te están buscando por todo el Caribe. Por suerte para ti, Henry, solo Svenson sabe dónde naciste. Me pidió que te advirtiera.";
		link.l1.go = "Ortega_1";
		break;

	case "Ortega_1":
		dialog.text = "Ahora entiendo... Entonces, parece que Svenson todavía está vivo y no se ha olvidado de su viejo amigo. Mucha sangre ha corrido desde que lo vi por primera vez como un novato a bordo de un bergantín dañado... La vida ha pasado demasiado rápido y no me queda mucho tiempo\nQuería morir por causas naturales en este páramo, lejos de la humanidad y cerca del mar. Pero si Jackman ha vuelto al Caribe, no me dejará en paz. No fue mi culpa, pero le debo a su maestro. De todos modos, ¿quién me creerá ahora?\nNo temo a la muerte, sino al dolor. Y Jackman sabe mucho sobre el dolor. El solo pensarlo hace que mi corazón se detenga y todo se oscurezca.";
		link.l1 = "El Butcher fue colgado hace veinte años, así que no tienes que pagar deudas a nadie. Puedes entregarme tu deuda si tienes miedo de Jackman. Creo que lo encontrarás de todos modos.";
		link.l1.go = "Ortega_2";
		break;

	case "Ortega_2":
		dialog.text = "No es fácil colgar a personas como Butcher. El antiguo verdugo de San Juan podría contarte muchas historias interesantes sobre los muertos que regresaron del infierno. Y Jacob fue bien enseñado por su capitán, así que no estoy seguro de a quién temo más.";
		link.l1 = "¿Por qué te necesita Jackman?";
		link.l1.go = "Ortega_3";
		break;

	case "Ortega_3":
		dialog.text = "Tuve que entregar oro a una viuda como pago por mantener a salvo a la hija de Butcher. ¿Por qué me miras así? Sí, ella nació poco antes de que el 'Neptune' se hundiera. No podía regresar por ella a tiempo, así que me envió a cuidar al bebé y a su cuidadora.";
		link.l1 = "¿Era Gladys Chandler el nombre de la cuidadora?";
		link.l1.go = "Ortega_4";
		break;

	case "Ortega_4":
		dialog.text = "No te hagas el idiota. Si Jackman me busca, es porque necesita a la hija de Butcher. Ya debes saber que está buscando a una mujer de Belice llamada Gladys y a su hija adoptiva. Sé honesto conmigo y podría confiar en ti.";
		link.l1 = "¿Qué se suponía que debías decirle a Gladys?";
		link.l1.go = "Ortega_5";
		break;

	case "Ortega_5":
		dialog.text = "Nada. Se suponía que debía mostrarle el anillo de Butcher, así es como ella sabría que era un mensajero enviado por el capitán. También tenía que darle un cofre de doblones para las necesidades del bebé. Tuve que matar a un bastardo para quitarle el anillo. Eso me hizo prolongar mi estancia en Antigua por un mes adicional.\nY cuando finalmente llegué a Belice, Gladys ya se había ido y la ciudad fue quemada y saqueada por los españoles. Logró vender su casa y escapar con su nuevo novio y la bebé Helen. Espero que ella haya cuidado de ella y no haya vendido a la niña a los gitanos o al burdel.";
		link.l1 = "El nombre de la hija de Butcher era Helena, ¿verdad?";
		link.l1.go = "Ortega_6";
		break;

	case "Ortega_6":
		dialog.text = "Exactamente. En honor a la madre de Butcher. Si no te asustan los muertos vivientes y los piratas que te miran con ojos muertos, entonces puedo darte el anillo y el oro. Nunca lo toqué. Me moría de hambre pero no lo toqué. Haz con ellos lo que quieras. Y a cambio te pido q...";
		link.l1 = "¿Qué está pasando, Henry?!";
		link.l1.go = "Ortega_7";
		break;

	case "Ortega_7":
		dialog.text = "Tu...u... yo pre...g... oh!";
		link.l1 = "¡No!";
		link.l1.go = "Ortega_8";
		break;

	case "Ortega_8":
		DialogExit();
		LAi_SetImmortal(npchar, false);
		LAi_KillCharacter(npchar);
		AddQuestRecord("Saga", "20");
		pchar.questTemp.Saga = "svenson1";
		PlaySound("interface\important_item.wav");
		GiveItem2Character(pchar, "chest");
		GiveItem2Character(pchar, "bucher_ring"); // перстень Бучера
		// таймер на возврат смотрителя
		SetFunctionTimerCondition("Saga_LightmanReturn", 0, 0, 10, false);
		// ставим прерывания, если ГГ наследил в городе
		if (CheckAttribute(pchar, "questTemp.Saga.Trap"))
		{
			pchar.quest.Saga_Trap.win_condition.l1 = "location";
			pchar.quest.Saga_Trap.win_condition.l1.location = "Mayak11";
			pchar.quest.Saga_Trap.function = "Saga_CreateTrapBandos";
			CoolTraderHunterOnMap();
		}
		AddCharacterExpToSkill(pchar, "Sneak", 50); // скрытность

		DeleteAttribute(pchar, "questTemp.HelenDrinking.Dialogs");
		// pchar.questTemp.HelenDrinking = "end_henry";
		break;

	// бандиты в поисках Гонсалеса, маяк
	case "saga_trap":
		dialog.text = "¡A-ah, allí está nuestro curioso amigo! ¿Has encontrado a Gonzales por fin? Bien hecho, nos has llevado hasta él... ya no te necesitamos. ¡Chicos, maten a este bufón!";
		link.l1 = "¡Es hora de morir, despojos de cangrejo!";
		link.l1.go = "saga_trap_1";
		break;

	case "saga_trap_1":
		DialogExit();
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // разрешить драться
		int n = makeint(MOD_SKILL_ENEMY_RATE / 3);
		for (i = 1; i <= 3 + n; i++)
		{
			sld = characterFromId("sagatrap_sold_" + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//<-- поиск Гонсалеса, Картахена

		//--------------------------------------------НПС по квесту Возвращение барона---------------------------------

	// доминиканский вождь
	case "DominicaHead":
		dialog.text = "¡U-ah! ¡U-ah! ¡El gran Kukulcán exige una nueva víctima! ¡O-eh! ¡El espíritu del poderoso guerrero del pasado vino a nuestro poblado para ser sacrificado al gran Kukulcán! ¡O-eh! ¡Todos inclínense ante el poderoso espíritu guerrero!";
		link.l1 = "(débilmente) ¿Qué demonios, dónde estoy?";
		link.l1.go = "DominicaHead_1";
		NextDiag.TempNode = "DominicaHead";
		if (CheckCharacterItem(pchar, "Ultimate_potion"))
		{
			pchar.systeminfo.NoNotifications = true;
			RemoveItems(pchar, "Ultimate_potion", 1);
			DeleteAttribute(pchar, "systeminfo.NoNotifications");
			notification("Has usado una poción comanche", "None");
			LAi_SetCurHPMax(PChar);
			AddCharacterHealth(pchar, 50);
			DeleteAttribute(pchar, "chr_ai.poison");
			notification("Siente que recuperas la salud.", "None");
			// Log_Info("A Comanche potion is used");
			// Log_Info("You are feeling that your health is restored!");
			// PlaySound("Ambient\Tavern\glotok_001.wav");
			PlaySound("Ambient\Horror\Fear_breath_01.wav");
		}
		break;

	case "DominicaHead_1":
		dialog.text = "¡Oh-eh! ¡El gran guerrero quiere ser devorado por el gran Kukulcán! ¡El sol está saliendo, las sombras se acortan! ¡El gran Kukulcán pronto estará vivo! ¡Te llevamos a él, oh poderoso guerrero, y continúas pasando por la tierra de los ancestros!";
		link.l1 = "(débilmente) Tonterías... ¿Kukulcán otra vez? ¡Oye, jefe, vine en son de paz! Estoy aquí para...";
		link.l1.go = "DominicaHead_2";
		break;

	case "DominicaHead_2":
		dialog.text = "¡O-eh! El gran guerrero dice que quiere ser sacrificado a Kukulcán inmediatamente. ¡Oh, gran guerrero! ¡Vamos a Kukulcán ahora y esperaremos su visita! ¡Guerreros! ¡Tenemos el gran honor de llevar el espíritu del ancestro a Kukulcán!";
		link.l1 = "(débilmente) Idiota... Está bien, tengo que ir con ellos. Es bueno que aún no me hayan atacado, no podría defenderme con esta cosa...";
		link.l1.go = "DominicaHead_3";
		break;

	case "DominicaHead_3":
		DialogExit();
		LAi_SetActorType(pchar);
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocator(npchar, "reload", "reload1_back", "Saga_DominicaDollyReload", -1);
		LAi_ActorFollow(pchar, npchar, "", -1);
		for (i = 2; i <= 10; i++)
		{
			sld = characterFromId("Dominica_ind_" + i);
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, npchar, "", -1);
		}
		break;

	case "DominicaHead_4":
		dialog.text = "Venimos a Kukulcán, gran espíritu ancestro. Pronto el sol se pondrá, las sombras crecerán y Kukulcán nos visitará. Espera, gran guerrero...";
		link.l1 = "(débilmente) Ahora veo, jefe de guerra indio...";
		link.l1.go = "DominicaHead_5";
		break;

	case "DominicaHead_5":
		DialogExit();
		bDisableCharacterMenu = true; // лочим Ф2
		AddQuestRecord("BaronReturn", "7");
		LAi_SetActorType(pchar);
		DoQuestCheckDelay("Saga_DominicaDollyWait", 5.0);
		pchar.questTemp.Saga.BaronReturn = "third_teleport";
		break;

	case "DominicaHead_6":
		dialog.text = "¡Kukulcán vive! ¡Kukulcán con nosotros! ¡El gran guerrero puede ser sacrificado a Kukulcán! ¡Guerreros, inclinaos ante el gran espíritu ancestral!";
		link.l1 = "(débilmente) Aléjate, Jefe. Lo haré yo mismo. No es mi primera vez...";
		link.l1.go = "DominicaHead_7";
		break;

	case "DominicaHead_7":
		DialogExit();
		bDisableCharacterMenu = false; // разлочим Ф2
		AddQuestRecord("BaronReturn", "8");
		for (i = 2; i <= 10; i++)
		{
			sld = characterFromId("Dominica_ind_" + i);
			LAi_SetActorType(sld);
		}
		break;

		//----------------------------------------НПС по квесту Искушение Барбазона----------------------------------
		// капитан рыболовного баркаса, стыривший шелк, море
	case "BarbCapBarkas":
		dialog.text = "¿Cómo puedo ayudarle, señor?";
		link.l1 = "Bueno, bueno..  dime, amigo, ¿qué haces aquí?";
		link.l1.go = "BarbCapBarkas_1";
		break;

	case "BarbCapBarkas_1":
		dialog.text = "¿Qué hago aquí? Soy un pescador y estoy pescando aquí. ¿Y por qué demonios me estás interrogando en ese tono de voz?";
		link.l1 = "No me mientas, amigo. Quizás seas un pescador de verdad, pero no has estado pescando peces aquí. Seda de barco valiosa fue arrojada al mar, aquí en este lugar. Y tu sola presencia me resulta bastante sospechosa.";
		link.l1.go = "BarbCapBarkas_2";
		break;

	case "BarbCapBarkas_2":
		dialog.text = "¿Qué tonterías? ¿De qué seda estás hablando siquiera?";
		link.l1 = "¿Qué seda? La china... ¡No te hagas el idiota! Escúchame bien: o sacas inmediatamente la seda de tu bodega y me la das, o la tomaré yo mismo. Pero, primero, mi grupo de abordaje se encargará de ti y de tu gente. ¿Entonces? ¿Debería llamar a mis hombres?";
		link.l1.go = "BarbCapBarkas_3";
		break;

	case "BarbCapBarkas_3":
		dialog.text = "¡No! Mynheer, yo no sabía... Esos fardos solo estaban flotando por ahí, así que decidí...";
		link.l1 = "Trae la seda a mi barco. ¡Date prisa!";
		link.l1.go = "BarbCapBarkas_4";
		break;

	case "BarbCapBarkas_4":
		dialog.text = "Sí, sí, claro. Lo haremos de inmediato, ¡solo no te lleves mi barco!";
		link.l1 = "¡Mueve el culo! No tengo mucho tiempo...";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Saga_BarbBarkasSilk");
		break;

	case "BarbCapBarkas_5":
		dialog.text = "Aquí, hemos traído todo lo que hemos encontrado - los nueve fardos. Esto es todo, lo juro...";
		link.l1 = "Está bien. Puedes continuar con tu pesca, pero no pongas el ojo en las pertenencias ajenas en el futuro.";
		link.l1.go = "BarbCapBarkas_6";
		break;

	case "BarbCapBarkas_6":
		DialogExit();
		npchar.DontDeskTalk = true;
		npchar.lifeday = 0;
		LAi_SetStayType(npchar);
		pchar.quest.BarbBarkas_Sink.over = "yes";	  // снять прерывание
		pchar.quest.BarbBarkas_Abordage.over = "yes"; // снять прерывание
		NextDiag.CurrentNode = "BarbCapBarkas_7";
		AddQuestRecord("BarbTemptation", "6");
		pchar.questTemp.Saga.BarbTemptation = "give_silk";
		AddCharacterExpToSkill(pchar, "Fortune", 100); // везение
		AddCharacterExpToSkill(pchar, "Sneak", 50);	   // скрытность
		break;

	case "BarbCapBarkas_7":
		dialog.text = "Ya has conseguido lo que querías. ¡No me queda nada! ¿Qué más necesitas?";
		link.l1 = "Relájate, amigo. Me voy.";
		link.l1.go = "exit";
		NextDiag.TempNode = "BarbCapBarkas_7";
		break;

	// Моррель, капитан потопленного судна, тюрьма
	case "Morelle":
		dialog.text = "Si te envía Barbazon, entonces dile que no quiero salir de la prisión por mi cuenta. Prefiero esperar al juicio. Incluso el cáñamo holandés en mi cuello es mejor que su amabilidad.";
		link.l1 = "No te tires un pedo todavía. Tu navegante le dijo a Jacques que estás muerto. Me envió a buscar la seda que arrojaste al mar. ¿Cuánta había en tu bergantín?";
		link.l1.go = "Morelle_1";
		break;

	case "Morelle_1":
		dialog.text = "Fue mi culpa, maldita sea. El mensajero trajo nueve fardos de seda para Barbazon. Ordené seguirlo. Se puso ruidoso, así que tuvimos que cortarle el cuello. Tenía tres fardos extra en su escondite, que tomé para mí y escondí en mi propio escondite. Pero parece que hemos llamado la atención no deseada.\nNos encontraron rápido y una patrulla holandesa esperó al 'Perro Salado' en mar abierto. No logramos escapar. Puedes quedarte con la seda si no le dices a Barbazon sobre mí. El escondite está ubicado en la Playa Grand Case entre las piedras cerca del callejón sin salida. Es poco probable que lo necesite de nuevo.";
		link.l1 = "Está bien. No le diré a Barbazon que todavía estás vivo. Si lo que dicen de él es cierto, entonces es mejor que te ahorquen los holandeses. O, tal vez tengas suerte y te condenen a trabajos forzados.";
		link.l1.go = "Morelle_2";
		break;

	case "Morelle_2":
		DialogExit();
		LAi_CharacterDisableDialog(npchar);
		// тайник - модель
		// int m = Findlocation("Shore40");
		// locations[m].models.always.Roll = "Roll_of_rolls";
		// Locations[m].models.always.Roll.locator.group = "quest";
		// Locations[m].models.always.Roll.locator.name = "quest1";
		pchar.quest.Saga_MorelGoods.win_condition.l1 = "locator";
		pchar.quest.Saga_MorelGoods.win_condition.l1.location = "Shore40";
		pchar.quest.Saga_MorelGoods.win_condition.l1.locator_group = "quest";
		pchar.quest.Saga_MorelGoods.win_condition.l1.locator = "quest1";
		pchar.quest.Saga_MorelGoods.function = "Saga_SetMorelGoods";
		AddCharacterExpToSkill(pchar, "Fortune", 200); // везение
		AddCharacterExpToSkill(pchar, "Sneak", 200);   // скрытность
		break;

	// Валет, брат Джекмана в Капстервиле
	case "valet":
		dialog.text = "Estoy esperando al hombre que sabe cuándo comenzará la caza del tiburón blanco.";
		link.l1 = "La caza ha comenzado.";
		link.l1.go = "valet_1";
		break;

	case "valet_1":
		dialog.text = "¡Finalmente! Ahora escucha con atención. Tendrás que visitar a Marcus Tyrex en La Vega y decirle que el bergantín 'Separador' fue atacado cerca de la isla de los Turcos y ahora se esconde en la Bahía del Sur. Su capitán está gravemente herido y la tripulación está esperando ayuda. Has recogido a un marinero del 'Separador' y te contó todo. Ahora está muerto. Eso es todo lo que sabes. ¿Entendido?";
		link.l1 = "¿Y por qué me necesitas para eso? He estado esperando demasiado solo para eso...";
		link.l1.go = "valet_2";
		break;

	case "valet_2":
		dialog.text = "Te pagan por hacer tu trabajo y no para hacer preguntas. Sin embargo, tienes razón. Debo advertirte que Tyrex no te dejará ir hasta que esté seguro de que estás diciendo la verdad. Pero una vez que lo descubra todo, te pagará bien. Si es que puede hacerlo...";
		link.l1 = "Me engañas, señor... ¿Por qué no quieres recibir su agradecimiento tú mismo?";
		link.l1.go = "valet_3";
		break;

	case "valet_3":
		dialog.text = "¡Caramba! ¡No me gusta tu curiosidad! Tu cháchara te llevará directo a la tumba algún día.";
		link.l1 = "Sí, a veces soy insoportable. Especialmente cuando veo que alguien va a intentar tomarme el pelo. No, amigo, ahora jugaremos con mis reglas. ¿Quién es tu amo, maldita sea? ¡Responde o te haré hablar!";
		link.l1.go = "valet_4";
		break;

	case "valet_4":
		dialog.text = "¡Tú... bastardo! ¡Barbazon pagará por esto y tu vida va a terminar, come-mierda!";
		link.l1 = "¡Ja! Esperaba esto. ¡Prepárate, canalla!";
		link.l1.go = "valet_5";
		break;

	case "valet_5":
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // разрешить драться
		chrDisableReloadToLocation = true;										   // закрыть локацию
		DialogExit();
		LAi_SetWarriorType(npchar);
		LAi_group_MoveCharacter(npchar, "EnemyFight");
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "Saga_ValetDie");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "vensan":
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
		{
			dialog.text = "¿Charlie Prince? ¿Qué haces aquí? ¡A-arg, maldita sea, fuiste tú! ¡Todo esto es obra tuya!";
			link.l1 = "Relájate Bernie. Estoy de tu lado. La emboscada ha sido eliminada, tú y tu embarcación estáis a salvo.";
			link.l1.go = "vensan_8";
		}
		else
		{
			dialog.text = "¿Quién eres, maldita sea? ¿Cómo llegaste aquí? Márchate ahora, mi barco está minado y los bastardos en la costa pueden volarlo de un solo tiro.";
			link.l1 = "No se preocupe, señor. La emboscada en la costa fue eliminada. Su barco está a salvo ahora, siempre y cuando no vaya a encender una pipa en cubierta, por supuesto. ¿Cuál es su nombre?";
			link.l1.go = "vensan_1";
		}
		break;

	case "vensan_1":
		dialog.text = "Vincent. Bernard Vincent. ¿Y cómo te llamas tú?";
		link.l1 = "Capitán " + GetFullName(pchar) + ". Cortaré esas sogas y te liberar é...";
		link.l1.go = "vensan_2";
		break;

	case "vensan_2":
		LAi_SetStayType(npchar);
		dialog.text = "Oh... mi gratitud. ¿Cómo puedo agradecerte?";
		link.l1 = "Esto aún no ha terminado, señor. ¿Alguno de su tripulación sigue con vida?";
		link.l1.go = "vensan_3";
		break;

	case "vensan_3":
		dialog.text = "Tres docenas de mis hombres están encerrados en la bodega...";
		link.l1 = "Libéralos y aléjate de aquí inmediatamente. ";
		link.l1.go = "vensan_4";
		break;

	case "vensan_4":
		dialog.text = "Pero...";
		link.l1 = "No pierdas tiempo, Bernard. Puedes agradecerme más tarde en La Vega... Tyrex también podría agradecerme.";
		link.l1.go = "vensan_5";
		break;

	case "vensan_5":
		dialog.text = "¿Entonces, no estás aquí por accidente? ¿Sabías todo?";
		link.l1 = "Sí, lo sabía. Logré descubrir la maquinación de Jackman y sus planes para matar a Marcus. Oh, pídele a Tyrex que se quede quieto, su intromisión puede asustar a Jackman.";
		link.l1.go = "vensan_6";
		break;

	case "vensan_6":
		dialog.text = "¡Se lo diré con certeza! ¿Te vas ahora?";
		link.l1 = "Sí. Y tú también deberías darte prisa.";
		link.l1.go = "vensan_7";
		break;

	case "vensan_7":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "goto", "goto2", "none", "", "", "", 5.0);
		Ship_SetTaskRunaway(SECONDARY_TASK, GetCharacterIndex("Cap_Vensan"), GetMainCharacterIndex());
		pchar.questTemp.Saga.BarbTemptation.Vensan_free = "true";
		if (!CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.vensan_attack"))
		{
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				sld = characterFromId("Mary");
			else
				sld = characterFromId("Helena");
			sld.dialog.currentnode = "sea_bomb";
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto6");
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
		AddCharacterExpToSkill(pchar, "Leadership", 100); // авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 100);	  // везение
		AddCharacterExpToSkill(pchar, "Sneak", 50);		  // скрытность
		sld = characterFromId("Cap_Vensan");
		sld.lifeday = 1;
		sld.DontDeskTalk = true;
		break;

	// Addon 2016-1 Jason пиратская линейка патч 17/1
	case "vensan_8":
		dialog.text = "¿De veras? Mira, lo siento, hermano...";
		link.l1 = "Olvídalo. Déjame cortar las cuerdas y liberarte.";
		link.l1.go = "vensan_9";
		break;

	case "vensan_9":
		LAi_SetStayType(npchar);
		dialog.text = "Joder... No siento mis manos...";
		link.l1 = "Bernie, ¿hay más sobrevivientes en el barco?";
		link.l1.go = "vensan_10";
		break;

	case "vensan_10":
		dialog.text = "Treinta hombres están encerrados en la bodega...";
		link.l1 = "¡Libérales y lárgate de aquí. Ahora!";
		link.l1.go = "vensan_11";
		break;

	case "vensan_11":
		dialog.text = "Pero...";
		link.l1 = "Navega a La Vega de inmediato. Cuéntale a Marcus todo sobre este lío con todos los detalles.";
		link.l1.go = "vensan_12";
		break;

	case "vensan_12":
		dialog.text = "¿Te envió Marcus?";
		link.l1 = "No lo hizo. Logré descubrir el complot de un bastardo. Planeaba eliminar a Marcus a través de esta intriga. Pídele que se quede quieto y no se entrometa por ahora... Le explicaré todo yo mismo, más tarde. Y por favor, dile que deje de estar enfadado conmigo.";
		link.l1.go = "vensan_7";
		break;

		//--------------------------------------НПС по Завещанию Шарпа--------------------------------------------------
		// Устрица, Поль Моллиган
	case "molligan":
		dialog.text = "¿Qué queréis en mi barco, señor?";
		link.l1 = "Buen día, Paul. Tu nombre es Paul Molligan, ¿verdad?";
		link.l1.go = "molligan_0";
		break;

	case "molligan_0":
		dialog.text = "Sí, soy yo. ¿En qué puedo ayudarle?";
		link.l1 = "Mi nombre es " + GetFullName(pchar) + " y Jan Svenson me ha enviado.";
		link.l1.go = "molligan_1";
		break;

	case "molligan_1":
		dialog.text = "¿Jan? A-ah, te recuerdo. ¡Claro! Has estado visitando su casa constantemente últimamente. Entonces, ¿qué quiere Jan de mí?";
		link.l1 = "Tenías tanta prisa por zarpar de Blueweld. Jan quería cargar tu barco con doscientas arrobas adicionales de caoba para entregarlas al lord Willoughby en Bridgetown. Prepara tu navío, mis hombres pondrán la caoba en tu bodega.";
		link.l1.go = "molligan_2";
		break;

	case "molligan_2":
		dialog.text = "¿Caoba? ¿Jan dijo eso? Hm. ¿Y por qué no lo llevas tú mismo a Barbados? ¿Por qué yo?";
		link.l1 = "Porque tú estás navegando allí y yo no. He recibido una misión inmediata de Svenson, así que no puedo perder el tiempo navegando a Bridgetown también. Además, Jan no confía en que yo haga negocios con lord Willoughby y quiere que lo hagas tú. Lo siento. Ahora vamos a cargar, tengo que irme.";
		link.l1.go = "molligan_3";
		break;

	case "molligan_3":
		dialog.text = "Escucha, no tengo espacio libre en mi bodega. No podré hacer lo que Jan me pide, aunque me gustaría hacerlo.";
		link.l1 = "¿No hay espacio? Extraño... Jan me dijo que tenías algo de espacio libre.";
		link.l1.go = "molligan_4";
		break;

	case "molligan_4":
		dialog.text = "Es cierto, pero Jan no sabía que he equipado la 'Ostra' con cañones más pesados. No puedo cargar más mercancía de la que ya tengo. Así que entrega la madera a Barbados tú mismo, ¿eh colega? Dile a Jan que no pude hacerlo. Tratar con Willoughby es fácil: solo ve a verlo, dale la carga y toma tu recibo. Bastante fácil.";
		link.l1 = "Hum. Esto no era mi plan... Revisemos tu bodega de carga, ¿te parece? Mi intendente es muy talentoso para empacar cosas, podrá meter las mercancías en tu bodega y hasta dejarte algo de espacio libre...";
		link.l1.go = "molligan_5";
		break;

	case "molligan_5":
		dialog.text = "Amigo, no puedo cargar más mercancías. ¿Quieres que tire mis cañones y deje al 'Ostras' desprotegido?";
		link.l1 = "Bueno, si estás tan seguro... ¡Pero a Jan no le gustará, tenlo en cuenta!";
		link.l1.go = "molligan_6";
		break;

	case "molligan_6":
		dialog.text = "Lo explicaré a Svenson, no te preocupes. Después de todo, es su culpa, no me preguntó sobre el tonelaje de mi barco.";
		link.l1 = "Eh, y ahora tendré que navegar con esos troncos hasta Barbados, maldición... Adiós, camarada.";
		link.l1.go = "molligan_7";
		break;

	case "molligan_7":
		DialogExit();
		// ставим проверку скрытности
		if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > (10 + hrand(50)))
		{
			pchar.questTemp.Saga.Molligan.friend = "true"; // будет шанс критического залпа картечью
			sTemp = "El canalla sigue sin sospechar nada. Debería acercarme y dispararle con metralla. Un golpe repentino siempre ganará cualquier batalla. ";
			log_Testinfo("Friends");
			AddCharacterExpToSkill(pchar, "Fortune", 200); // везение
			AddCharacterExpToSkill(pchar, "Sneak", 300);   // скрытность
		}
		else
		{
			pchar.questTemp.Saga.Molligan.enemy = "true"; // нападет
			sTemp = "";
			log_Testinfo("Enemies");
			AddCharacterExpToSkill(pchar, "Sneak", 150); // скрытность
		}
		AddQuestRecord("Testament", "7");
		AddQuestUserData("Saga", "sText", sTemp);
		NextDiag.CurrentNode = "molligan_8";
		npchar.DontDeskTalk = true; // patch-5
		break;

	case "molligan_8":
		dialog.text = "Estamos claros, ¿verdad?";
		link.l1 = "Sí, sí. Me voy a mi barco.";
		link.l1.go = "exit";
		NextDiag.TempNode = "molligan_8";
		break;

		//-----------------------------------------НПС по Теням прошлого--------------------------------------------
		// Джим Бенсон, плешивая мэгги
	case "benson":
		dialog.text = "¿Qué quieres de mí? No me gustan los chismes ni el juego. Y bebo mi ron solo. Además, estoy de mal humor después de mi último crucero.";
		link.l1 = "¿Y qué cosa especial ha sucedido durante tu último crucero?";
		link.l1.go = "benson_1";
		break;

	case "benson_1":
		dialog.text = "Un buen hombre confió en mí y lo arrojé por la borda porque mi tripulación lo exigió.";
		link.l1 = "¿Y cuál fue su culpa?";
		link.l1.go = "benson_2";
		break;

	case "benson_2":
		dialog.text = "Soy un recién llegado y no conozco a muchas personas aquí. Por eso contraté a ese bonachón gordo como cirujano sin saber sobre su pasado. Los piratas nos perseguían desde que salimos de Barbados. ¿Por qué necesitarían mi cáscara de huevo?\nApenas logramos escapar, gracias a un fuerte vendaval. Bebimos por tal ocasión. Y el gordo tonto no pensó en nada mejor que contarle a todos que los piratas probablemente lo estaban persiguiendo porque es el antiguo verdugo y sabe cosas que no debería saber.\nPor supuesto, mis tripulantes se enfadaron mucho. ¿¡En serio?! ¡Un verdugo a bordo, sirviendo como cirujano! Y nadie quería meterse con los piratas tampoco... Así que tuve que desembarcar al pobre alma. Todo es culpa suya, solo tenía que abrir la boca. Pero me siento mal por el pueblerino, era un excelente médico. Solo le llevó un minuto curar mi resaca.";
		link.l1 = "¡Maldita sea! El nombre de tu médico era Raymond Baker, ¿verdad?";
		link.l1.go = "benson_3";
		break;

	case "benson_3":
		dialog.text = "Sí. Exactamente. ¿Y cómo lo sabes? ¿Me estabas persiguiendo?";
		link.l1 = "No, ese no fui yo. Solo necesito a ese hombre, es un gran médico. ¿Dónde lo desembarcaste?";
		link.l1.go = "benson_4";
		break;

	case "benson_4":
		dialog.text = "Latitud 15 grados 28' norte, longitud 63 grados 28' oeste. ¡Apresúrate, señor! Debe estar aún vivo y te quitarás la culpa de mí si lo salvas.";
		link.l1 = "¡Ya estoy izando mis anclas!";
		link.l1.go = "benson_5";
		break;

	case "benson_5":
		DialogExit();
		NextDiag.CurrentNode = "benson_6";
		AddQuestRecord("Shadows", "3");
		npchar.lifeday = 0;
		bQuestDisableMapEnter = false;
		pchar.quest.Saga_Shadows_Baker.win_condition.l1 = "location";
		pchar.quest.Saga_Shadows_Baker.win_condition.l1.location = "Dominica";
		pchar.quest.Saga_Shadows_Baker.function = "Saga_SetBakerBoat";
		DeleteAttribute(pchar, "Cheats.SeaTeleport");
		break;

	case "benson_6":
		dialog.text = "¡Capitán, date prisa! ¡Debe estar todavía vivo!";
		link.l1 = "Sí, sí, estoy en camino...";
		link.l1.go = "exit";
		NextDiag.TempNode = "benson_6";
		break;

		//---------------------------------------бандиты у джекмановского рудника-------------------------------
	case "mine_bandit":
		locCameraFromToPos(6.21, 2.31, 8.46, true, -2.26, -1.10, 4.99);
		if (CheckAttribute(pchar, "questTemp.Saga.MineAttack"))
		{
			dialog.text = "¡Oye! ¡Quédate ahí! No te muevas. ¡Este territorio está asegurado!";
			link.l1 = "¡No seas demasiado duro, amigo! ¡Amigos! Jackman nos envió. Necesitamos llegar a la mina. Orden del maestro...";
			link.l1.go = "mine_attack";
			break;
		}
		if (npchar.quest.meeting == "0")
		{
			dialog.text = "¡Eh! ¡Quédate ahí! No te muevas. ¡Este territorio está asegurado!";
			link.l1 = "Mm. Pero quiero pasar... ¿Por qué demonios me estás deteniendo?";
			link.l1.go = "mine_bandit_1";
			npchar.quest.meeting = "1";
		}
		else
		{
			dialog.text = "¿A-ah, tú otra vez? Veo que no lo entiendes... ¡Muchachos, fuego!!";
			link.l1 = "...";
			link.l1.go = "mine_bandit_fire";
		}
		break;

	case "mine_bandit_0":
		dialog.text = "¡Vamos, muévanse!";
		link.l1 = "Bien...";
		link.l1.go = "exit";
		NextDiag.TempNode = "mine_bandit_0";
		break;

	case "mine_bandit_1":
		dialog.text = "Porque la mina detrás de mí es propiedad privada y estoy aquí para detener a cualquier extraño como tú de pasar. Será mejor que te des la vuelta y te largues de este lugar, forastero. Nuestros cañones están cargados con metralla, solo un paso más y te convertirás en un charco húmedo.";
		link.l1 = "Heh, ya veo. Tu mina tiene una guardia seria. Bien, me voy.";
		link.l1.go = "mine_bandit_exit";
		link.l2 = "¡Tú, bastardo! ¡Pues veremos quién se convierte en un charco!";
		link.l2.go = "mine_bandit_2";
		break;

	case "mine_bandit_exit":
		DialogExit();
		LAi_SetGuardianType(npchar);
		LAi_group_MoveCharacter(npchar, "PIRATE_CITIZENS");
		chrDisableReloadToLocation = false; // открыть локацию
		DoQuestReloadToLocation("Mine_02", "reload", "reload3", "");
		break;

	case "mine_bandit_2":
		dialog.text = "Te di una oportunidad... ¡Muchachos, fuego!!";
		link.l1 = "...";
		link.l1.go = "mine_bandit_fire";
		break;

	case "mine_bandit_fire":
		DialogExit();
		DoQuestCheckDelay("Saga_MineBanditsFire", 1.5);
		break;

	case "mine_banditx":
		locCameraFromToPos(6.21, 2.31, 8.46, true, -2.26, -1.10, 4.99);
		if (CheckAttribute(pchar, "questTemp.Saga.MineAttack"))
		{
			dialog.text = "¡Oye! ¡Fuera de aquí! ¡Este territorio está asegurado!";
			link.l1 = "¡Eh, relájate, amigo! Jackman nos envió. Necesitamos llegar a la mina. Orden del maestro...";
			link.l1.go = "mine_attackx";
			break;
		}
		if (npchar.quest.meeting == "0")
		{
			dialog.text = "¡Oye! ¡Vete! ¡Este territorio está asegurado!";
			link.l1 = "Mm. ¿Y qué hay allí?";
			link.l1.go = "mine_banditx_1";
			npchar.quest.meeting = "1";
		}
		else
		{
			dialog.text = "¿A-ah, tú otra vez? Veo que no lo entiendes... ¡Muchachos, fuego!";
			link.l1 = "... ";
			link.l1.go = "mine_banditx_fire";
		}
		break;

	case "mine_banditx_1":
		dialog.text = "¡No es asunto tuyo! ¡Lárgate o te dispararemos, lo juro!";
		link.l1 = "Tranquilo. Me voy.";
		link.l1.go = "mine_banditx_exit";
		link.l2 = "¡Tú, bastardo! Bueno, veremos quién disparará a quién.";
		link.l2.go = "mine_banditx_2";
		break;

	case "mine_banditx_exit":
		DialogExit();
		LAi_SetGuardianType(npchar);
		LAi_group_MoveCharacter(npchar, "PIRATE_CITIZENS");
		DoQuestReloadToLocation("Mine_04", "reload", "reload3", "");
		break;

	case "mine_banditx_2":
		dialog.text = "Te di una oportunidad... ¡Mosquetes listos! ¡Fuego!!";
		link.l1 = "...";
		link.l1.go = "mine_banditx_fire";
		break;

	case "mine_banditx_fire":
		DialogExit();
		DoQuestCheckDelay("Saga_MineBanditsxFire", 0.6);
		break;

	case "mine_attackx":
		dialog.text = "¿En serio? Entonces debes saber la contraseña. Habla, pero lo lamentarás si estás mintiendo...";
		link.l1.edit = 5;
		link.l1 = "";
		link.l1.go = "mine_attackx_1";
		break;

	case "mine_attackx_1":
		sTemp = GetStrSmallRegister(dialogEditStrings[5]);
		if (sTemp == "neptune")
		{
			dialog.text = "Correcto. Pero tú, amigo, has llegado aquí desde el lado equivocado. ¿No te advirtieron? Regresa y toma el camino de la izquierda desde el pozo seco. Luego rodea la colina y allí verás la puerta principal.";
			link.l1 = "¿No puedo entrar aquí?";
			link.l1.go = "mine_attackx_2";
		}
		else
		{
			dialog.text = "¡Chicos, tenemos un sabueso! ¡Mosquetes listos! ¡Fuego!!";
			link.l1 = "...";
			link.l1.go = "mine_banditx_fire";
		}
		break;

	case "mine_attackx_2":
		dialog.text = "No. Solo por la entrada central.";
		link.l1 = "Está bien, amigo... ¡Oye! ¡Mira! ¿Qué diablos es eso en la cima de la empalizada?";
		link.l1.go = "mine_attackx_3";
		break;

	case "mine_attackx_3":
		DialogExit();
		for (i = 1; i <= 4; i++)
		{
			sld = characterFromId("Mine_banditx_" + i);
			LAi_RemoveCheckMinHP(sld);
		}
		sld = characterFromId("Svensons_sold_12");
		LAi_SetActorType(sld);
		LAi_ActorTurnToLocator(sld, "soldiers", "soldier1");
		LAi_ActorAnimation(sld, "shot", "Saga_MineBanditxDie", 1.0);
		break;

	case "mine_attack":
		dialog.text = "¿De verdad? Entonces deberías saber la contraseña. Habla y dila para que pueda oírla. Y si intentas engañarme, esa será la última broma que le harás a alguien en tu vida.";
		link.l1.edit = 5;
		link.l1 = "";
		link.l1.go = "mine_attack_1";
		break;

	case "mine_attack_1":
		sTemp = GetStrSmallRegister(dialogEditStrings[5]);
		if (sTemp == "neptune")
		{
			dialog.text = "Correcto. Sigue adelante. El jefe del campamento está en la casa a la izquierda de la entrada de la mina. Ve a verlo.";
			link.l1 = "Está bien, colega...";
			link.l1.go = "mine_attack_2";
		}
		else
		{
			dialog.text = "¡Chicos, tenemos un sabueso! ¡Cañones, abran fuego!!";
			link.l1 = "...";
			link.l1.go = "mine_bandit_fire";
		}
		break;

	case "mine_attack_2":
		DialogExit();
		NextDiag.CurrentNode = "mine_attack_3";
		LAi_SetActorType(pchar);
		LAi_ActorFollow(pchar, npchar, "ActorDialog_Any2Pchar", -1);
		LAi_ActorTurnToCharacter(npchar, pchar);
		SetActorDialogAny2Pchar(npchar.id, "", 0.0, 0.0);
		break;

	case "mine_attack_3":
		dialog.text = "¿Qué más? ¿Olvidaste algo?";
		link.l1 = "Sí. Me pidieron que te diera los mejores saludos.";
		link.l1.go = "mine_attack_4";
		break;

	case "mine_attack_4":
		dialog.text = "¿A mí? ¡Ja, ja! ¿De quién?";
		link.l1 = "¡Jan Svenson, maldito seas!";
		link.l1.go = "mine_attack_5";
		break;

	case "mine_attack_5":
		DialogExit();
		LAi_SetPlayerType(pchar);
		for (i = 1; i <= 6; i++)
		{
			sld = characterFromId("Mine_bandit_" + i);
			LAi_RemoveCheckMinHP(sld);
		}
		if (pchar.questTemp.Saga.MineAttack == "soldiers")
		{
			sld = characterFromId("Svensons_sold_12");
			LAi_SetActorType(sld);
			LAi_ActorTurnToLocator(sld, "soldiers", "soldier1");
			LAi_ActorAnimation(sld, "shot", "Saga_MineBanditDie", 1.0);
		}
		else
		{
			for (i = 1; i <= 6; i++)
			{
				sld = characterFromId("Mine_bandit_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_BanditsDestroyed");
			AddDialogExitQuest("MainHeroFightModeOn");
		}
		pchar.quest.Saga_MineAttack_07.win_condition.l1 = "NPC_Death";
		pchar.quest.Saga_MineAttack_07.win_condition.l1.character = "Mine_bandit_1";
		pchar.quest.Saga_MineAttack_07.win_condition.l2 = "NPC_Death";
		pchar.quest.Saga_MineAttack_07.win_condition.l2.character = "Mine_bandit_2";
		pchar.quest.Saga_MineAttack_07.function = "Saga_SvensonMineexitAttack";
		break;

		// ----------------------------- диалоги НПС при штурме бандитского рудника -------------------------------
	case "Svensons_off":
		dialog.text = LinkRandPhrase("¡Despedazaremos a esos bastardos!", "¡Estoy ansioso por darles una paliza a esos canallas!", "¡Los secuaces de Jackman no tienen derecho a estar en el Mar Occidental! ¡Los ahuyentaremos de aquí!");
		link.l1 = "...";
		link.l1.go = "exit";
		NextDiag.TempNode = "Svensons_off";
		break;

	case "Svensons_sold":
		dialog.text = LinkRandPhrase("¡Estamos listos para luchar!", "¡Les mostraremos!", "¡Ni siquiera saben con quién se están metiendo!");
		link.l1 = "...";
		link.l1.go = "exit";
		NextDiag.TempNode = "Svensons_sold";
		break;

	case "gunner":
		PlaySound("Voice\Spanish\Evilpirates02.wav");
		dialog.text = "Comandante, el cañón está listo. Fue cargado con una bomba tal como ordenaste.";
		link.l1 = "Tengo entendido que aquí nadie nos espera... Es hora de presentarnos. Jan me dijo que su campamento está detrás de esta colina. ¿Podrás llegar hasta allí?";
		link.l1.go = "gunner_0_1";
		break;

	case "gunner_0_1":
		dialog.text = "Fácil, comandante. Levantemos un poco el barril, eso debería bastar... hecho.\n¡Prepárense!.. ¡Fuego!!";
		link.l1 = "...";
		link.l1.go = "gunner_0_2";
		npchar.quest.canonada = "1";
		break;

	case "gunner_0_2":
		DialogExit();
		LAi_SetActorType(pchar);
		DoQuestCheckDelay("Saga_Gunfire", 3.0);
		LAi_ActorTurnToLocator(npchar, "goto", "goto14");
		break;

	case "gunner_1":
		dialog.text = "";
		link.l1 = "Hum. Randolf, ¿crees que hemos chocado con algo? Me gustaría escuchar tu opinión.";
		link.l1.go = "gunner_1_1";
		break;

	case "gunner_1_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");
			dialog.text = "Comandante, hemos golpeado algo o a alguien, pero no puedo ser más específico... esta maldita colina está bloqueando la vista. Cambiaré el ángulo.\n¡Listo! ¡Fuego!";
			link.l1 = "...";
			link.l1.go = "gunner_0_2";
			npchar.quest.canonada = "2";
		break;
		
		case "gunner_2":
			PlaySound("interface\abordage_wining.wav");
			PlaySound("Types\Spanish\warrior07.wav");
			dialog.text = "¡Ja! ¡Mira, comandante! ¡Hay humo! ¡Maldita sea, debemos haber dado en el granero de algún bandido! ¡Hurra-ah!";
			link.l1 = "Sí, veo el humo... Una victoria épica ya, sin duda. Recarguen el cañón y apúntenlo al camino, parece que nuestros invitados están llegando. ¡Los saludaremos apropiadamente!";
			link.l1.go = "gunner_2_1";
		break;
		
		case "gunner_2_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");
			dialog.text = "¡Aye-aye, Comandante! ¡Cargad una bomba! ¡Tripulación de artillería a sus puestos! ¡Mecha lista! ¡Fuego a mi orden!";
			link.l1 = "...";
			link.l1.go = "gunner_2_2";
			npchar.quest.canonada = "3";
		break;
		
		case "gunner_2_2":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_LoginBandos_01", 6.0);
			LAi_ActorTurnToLocator(pchar, "goto", "goto14");
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
		break;
		
		case "gunner_3":
			PlaySound("interface\abordage_wining.wav");
			PlaySound("Types\Spanish\warrior07.wav");
			PlaySound("Voice\Spanish\Evilpirates05.wav");
			dialog.text = "¡Ja-ja, eso debe doler!";
			link.l1 = "¡No te relajes todavía! ¡Carga el cañón! No creo que hayan tenido suficiente. ¡Vienen más!";
			link.l1.go = "gunner_3_1";
		break;
		
		case "gunner_3_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");//
			dialog.text = "¡Sí, sí, comandante! ¡Carguen una bomba! ¡Listo! ¡Fuego a mi orden!";
			link.l1 = "...";
			link.l1.go = "gunner_3_2";
			npchar.quest.canonada = "4";
		break;
		
		case "gunner_3_2":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_LoginBandos_02", 5.0);
			LAi_ActorTurnToLocator(pchar, "goto", "goto14");
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
		break;
		
		case "gunner_5":
			PlaySound("Types\Spanish\warrior08.wav");
			PlaySound("Voice\Spanish\Evilpirates06.wav");
			dialog.text = "¡Ja-ja-ja, esos bastardos nos han dado la espalda! ¡Carne de perro! ¡La metralla los está destrozando a esta distancia! ¡Parece que no tienen el valor para atacarnos de nuevo!";
			link.l1 = "Ahora es nuestro turno. Randolph, te quedarás aquí cerca del cañón. Dispara al camino un par de veces y luego apunta al humo, ¡quema su guarida! Solo no nos dispares a nosotros.";
			link.l1.go = "gunner_5_1";
		break;
		
		case "gunner_5_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");
			dialog.text = "¡A la orden, Comandante! ¡Preparen el cañón! ¡Carguen una bomba!";
			link.l1 = "¡Hombres! ¡A las armas! ¡Síganme, ataque! ¡Hurra!!";
			link.l1.go = "attack";
		break;
		
		case "attack":
			DialogExit();
			n = Findlocation("mine");
			Locations[n].hidden_fire = true;
			PlaySound("interface\abordage_wining.wav");
			PlaySound("interface\abordage_wining.wav");
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
			if (GetCharacterIndex("Svensons_sold_12") != -1 && pchar.questTemp.Saga.MineAttack == "soldiers")
			{
			sld = characterFromId("Svensons_sold_12");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i=1; i<=8; i++)
			{
			if (GetCharacterIndex("Ourmine_sold_" + i) != -1)
			{
				sld = characterFromId("Ourmine_sold_" + i);
				if (i == 1)
					sld.MusketerDistance = 10;
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			}
			LAi_group_SetRelation("EnemyFight", "TMP_FRIEND", LAI_GROUP_NEITRAL);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_MineBandos_05Die");
			AddDialogExitQuest("MainHeroFightModeOn");	
			DoQuestCheckDelay("Saga_MineSetMusic", 0.3);
			// запускаем автобабахалку на 10 выстрелов
			iTotalTemp = 0;
			DoQuestCheckDelay("Saga_GunAutoFire", 7.0);
			bDisableCharacterMenu = false;//разлочим интерфейсы
			InterfaceStates.Buttons.Save.enable = true;//разрешим сохраняться
		break;
		
		case "convict":
			if (LAi_grp_playeralarm > 0)
			{
			dialog.text = LinkRandPhrase("¡No me hagas daño, no soy uno de ellos! ¡Mata a los bandidos!", "¡Libéranos, compañero! ¡Y mátalos a todos!", "¡Córtalos, amigo, córtalos! ¡Hazlos muertos!");
			link.l1 = "¡Ja! No te preocupes, eso es exactamente lo que estamos haciendo ahora mismo.";
			link.l1.go = "exit";
			}
			else
			{
			dialog.text = LinkRandPhrase("¿Ha terminado nuestra esclavitud? ¿Nos liberarás?", "Je, ¿realmente he logrado sobrevivir para ver este día?", "¡Malditos bastardos nos han drenado toda la sangre....!");
			link.l1 = "Creo que pronto podrás disfrutar de tu libertad, compañero...";
			link.l1.go = "exit";
			}
			NextDiag.TempNode = "convict";
		break;
		
		// жена Яна Свенсона
		case "js_girl":
			if (LAi_grp_playeralarm > 0)
			{
			dialog.text = "Será mejor que abandone este lugar, señor. No encubrimos criminales y no necesitamos conflictos con las autoridades de la colonia.";
			link.l1 = "Está bien, me voy...";
			link.l1.go = "exit";
			NextDiag.TempNode = "js_girl";
			break;
			}
			if(NPChar.quest.meeting == "0")
			{
			// Первый диалог с Элен
			if (startHeroType == 4)
			{
				dialog.text = "Ah, Helen. Podrías haberte vestido un poco más decentemente antes de venir a ver a Jan, en lugar de mostrarle cómo eres realmente. Es una pena que él no me crea.";
				link.l1 = "¿Y cómo soy exactamente? Me ha ayudado a criarme desde la infancia y me conoce mejor que nadie. No tengo secretos para él. He estado sufriendo este calor desde que era niño, así que tuve que lidiar con ello a mi manera, eso es todo.";
				link.l1.go = "js_helen_ft";
				NextDiag.TempNode = "js_girl";
				NPChar.quest.meeting = "1";
				break;
			}
			dialog.text = TimeGreeting() + ", señor. ¿Quiere ver a Jan?";
			link.l1 = "Buen día. Fue un placer conocerte, ¿señorita?..";
			link.l1.go = "js_girl_1";
			}
			else
			{
			// заглушка элен
			if (startHeroType == 4)
			{
				dialog.text = "Jan está adentro. Adelante, nada que ver aquí, y me estás poniendo de los nervios.";
				link.l1 = "No estaba realmente de humor de todos modos.";
				link.l1.go = "exit";
				NextDiag.TempNode = "js_girl";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Joan"))
			{
				dialog.text = "¡Grr!";
				link.l1 = "Y buena salud para usted también, Sra. Svensson.";
				link.l1.go = "exit";
				break;
			}

			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "blueveld")
			{
				dialog.text = TimeGreeting() + ", Capitán " + GetFullName(pchar) + ". Si estás aquí por Jan, entonces tengo que decepcionarte - no está aquí. Está ocupado con algunos asuntos importantes.";
				link.l1 = "¡Maldita sea! ¡Y lo necesito! Dígame, señora Svenson, ¿le dijo cuándo va a regresar?";
				link.l1.go = "js_girl_3";
				break;
			}
			dialog.text = "Ah-ah, tú de nuevo, Capitán " + GetFullName(pchar) + "... sigue adelante, Jan está arriba, como de costumbre.";
			link.l1 = "Gracias, señora Svenson...";
			link.l1.go = "exit";
			}
			NextDiag.TempNode = "js_girl";
		break;
		
		case "js_girl_1":
			dialog.text = "Señora, Señora Johanna Svenson.";
			link.l1 = "Capitán "+GetFullName(pchar)+".";
			link.l1.go = "js_girl_2";
		break;
		
		case "js_girl_2":
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "blueveld")
			{
			dialog.text = "¿Capitán? Pues, me alegra darle la bienvenida a mi casa. Pero si está aquí por Jan, entonces tengo que decepcionarle - no está aquí. Está ocupado llevando a cabo algunos asuntos importantes.";
			link.l1 = "¡Maldita sea! ¡Y lo necesito! Dígame, señora Svenson, ¿le dijo cuándo va a volver?";
			link.l1.go = "js_girl_3";
			break;
			}
			dialog.text = "¿Capitán? Bueno, me alegra darle la bienvenida a mi casa. Mi esposo está en el segundo piso en su oficina. Suba las escaleras.";
			link.l1 = "Lo tengo, señora Svenson...";
			link.l1.go = "exit";
			NPChar.quest.meeting = "1";
			NextDiag.TempNode = "js_girl";
		break;
		
		case "js_girl_3":
			dialog.text = "No. Ni siquiera me dijo la fecha exacta de su regreso, porque él mismo no sabe cuánto durará la búsqueda.";
			link.l1 = "Lamento interferir, pero realmente lo necesito... ¿Qué búsqueda está realizando?";
			link.l1.go = "js_girl_4";
		break;
		
		case "js_girl_4":
			dialog.text = "Te lo diré. La encantadora Helena, también conocida como Rumba, hija de su difunto amigo Sean McArthur, ha desaparecido. Jan trata a la joven diablilla como si fuera su propia hija. Ella le recuerda a su viejo amor, que tenía el mismo temperamento temerario. Al menos, creo que esa es la razón de la atracción.\nDe todos modos, la chica desapareció hace una semana junto con su goleta 'Arcoíris' y toda su tripulación. Sean McArthur le enseñó navegación y el 'Arcoíris' le fue legado en su testamento. Y ahora juega a ser capitana...";
			link.l1 = "¿Qué le podría haber sucedido?";
			link.l1.go = "js_girl_5";
		break;
		
		case "js_girl_5":
			dialog.text = "Quién sabe... Una semana no es tanto tiempo, pero la viuda de McArthur está segura de que algo le ha pasado a su hija y logró convencer a Jan de eso también. Reunió a sus hombres y empezó a buscarla él mismo, sin resultado aún. Personalmente, creo que Helen está bien y Jan solo se está torturando por nada.\nEscuchó demasiado las tonterías de esa vieja y gorda mujer y se asustó. Lo más probable es que la chica esté divirtiéndose con otro novio en este momento, lejos de los ojos de la gente en un lugar seguro. Regresará tan pronto como su hambre esté saciada.";
			link.l1 = "Johanna, ¿dónde puedo encontrar a Gladys? Quiero hablar con ella...";
			link.l1.go = "js_girl_6";
		break;
		
		case "js_girl_6":
			dialog.text = "Su casa está cerca del muelle, a la izquierda. Pero probablemente no esté allí. Pasa todos los días en los muros del fuerte, buscando a su preciosa hija.";
			link.l1 = "Ya veo. ¡Muchas gracias por tu información!";
			link.l1.go = "js_girl_7";
		break;
		
		case "js_girl_7":
			DialogExit();
			NextDiag.CurrentNode = "js_girl_8";
			sld = characterFromId("Gladis"); //устанавливаем Глэдис на форт
			ChangeCharacterAddressGroup(sld, "SantaCatalina_fort", "goto", "goto53");
			LAi_SetStayType(sld);
			sld.dialog.currentnode = "FindHelena";
			pchar.questTemp.Saga = "gladis";
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("SantaCatalina_tavernkeeper"));
			DelMapQuestMarkCity("SantaCatalina");
		break;
		
		case "js_girl_8":
			dialog.text = "Aún no está aquí Jan, Capitán, así que regrese más tarde.";
			link.l1 = "Ya veo...";
			link.l1.go = "exit";
			NextDiag.TempNode = "js_girl_8";
		break;
		
		case "js_helen_ft":
			dialog.text = "Yo diría que siempre estás en celo. Deberías ir a la iglesia; apenas te he visto allí.";
			link.l1 = "Mi conciencia está limpia - no tengo nada de qué pedir perdón. ¿Todavía amarga porque ayudó a abastecer mi barco en lugar de comprar otro vestido para ti, Joanna?";
			link.l1.go = "js_helen_ft_1";
		break;
		
		case "js_helen_ft_1":
			dialog.text = "¿Yo? ¿Amargado? No vales la pena. Es sólo que todo te viene demasiado fácil, y no lo mereces.";
			link.l1 = "Pero en cuanto conseguí ese barco, comencé a ganarme la vida por mi cuenta. Y desde que te recogió como a un gato callejero, no has trabajado ni un solo día. Entonces, ¿quién realmente vive a su costa?";
			link.l1.go = "js_helen_ft_2";
		break;
		
		case "js_helen_ft_2":
			dialog.text = "Sigues hablando así, y un día recibirás lo que te mereces. Jan y Gladys deberían haberte enseñado modales. Está bien, sigue, di lo que venías a decir y sal de mi vista, Helen. Él está adentro.";
			link.l1 = "Estúpida gallina. Claro, lo haré.";
			link.l1.go = "exit";
		break;
		
		// хронометр Алекса
		case "Alexs_bandos":
			dialog.text = "¡Oye! ¿Qué haces aquí?";
			link.l1 = "Me gustaría preguntarte lo mismo, ¿qué hacen tú y tus compinches aquí, en mi mazmorra?";
			link.l1.go = "Alexs_bandos_1";
		break;
		
		case "Alexs_bandos_1":
			dialog.text = "¡Ja! ¿Tu mazmorra? ¿Y cuándo se convirtió en tuya, maricón?";
			link.l1 = "El día que tu padre cometió el error de joder a tu madre.";
			link.l1.go = "Alexs_bandos_2";
		break;
		
		case "Alexs_bandos_2":
			dialog.text = "¿Buscas problemas?";
			link.l1 = "Escucha, amigo, te doy una última oportunidad para que te largues de aquí. Esta es mi mazmorra y no dejaré que nadie entre aquí como Pedro por su casa, ¿entendido? Solo necesito silbar una vez, y la mitad de los piratas de Isla Tesoro estarán aquí en un minuto.";
			link.l1.go = "Alexs_bandos_3";
		break;
		
		case "Alexs_bandos_3":
			dialog.text = "¡Bueno, entonces intentaremos cerrarte la boca!";
			link.l1 = "¡Ja, ja! ¡Eres patético, escoria!";
			link.l1.go = "Alexs_bandos_4";
		break;
		
		case "Alexs_bandos_4":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Bermudes_Dungeon")], false);
			for (i=1; i<=4; i++)
			{
			sld = characterFromId("Alexs_bandos_" + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+5;
			int iScl = 25+2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("Alexs_bandos_5", "mush_ctz_8", "man", "mushketer", iRank, PIRATE, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "cartridge", iScl*2+50);
			ChangeCharacterAddressGroup(sld, "Bermudes_Dungeon", "monsters", "monster8");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "AlexClock_BandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "helendrinking_gypsy":
			dialog.text = "¡Espera un momento, halcón!";
			link.l1 = "No es el mejor momento, cariño.";
			link.l1.go = "helendrinking_gypsy_1";
		break;
		
		case "helendrinking_gypsy_1":
			dialog.text = "Oh, estás equivocado, guapo. A esta chica le gustas, y ese sentimiento es mutuo, puedo verlo.";
			link.l1 = "No es la mejor recomendación... Está bien, ¿qué es lo que quieres? ¿Una limosna?";
			link.l1.go = "helendrinking_gypsy_2";
		break;
		
		case "helendrinking_gypsy_2":
			dialog.text = "Quiero ofrecerte apoyo en tu desafiante empresa. ¡Mira aquí! Una jarra mágica y un ungüento prohibido. La jarra te ayudará en asuntos de bebida, y el ungüento, en asuntos de amor. ¿Qué elegirás? ¡Solo dos mil!";
			link.l1 = "No necesito nada - ya he dado un montón de plata a los de tu calaña.";
			link.l1.go = "helendrinking_gypsy_refuse";
			if (sti(pchar.money) >= 2000) {
			link.l2 = "¿Ungüento prohibido, dices? Bueno, no soy un santo, lo admito. Dame eso.";
			link.l2.go = "helendrinking_gypsy_fuck";
			link.l3 = "¿Una jarra? ¿Acaso parezco un borracho? Bueno, ¿a quién engaño...? ¡La tomaré!";
			link.l3.go = "helendrinking_gypsy_drink";
			}
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_gypsy_refuse":
			dialog.text = "Guapo pero tonto. Vuela entonces, halcón.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_gypsy_drink":
			dialog.text = "¡Oh, no lo escondas en tus bolsillos sin fondo! ¡Vuela, halcón, y no peques!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddMoneyToCharacter(pchar, -2000);
			GiveItem2Character(pchar, "totem_01");
			Log_Info("¡Has conseguido el talismán 'Garganta de hierro fundido'!");
			PlaySound("interface\important_item.wav");
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_gypsy_fuck":
			dialog.text = "¡Oh, no lo escondas en tus bolsillos sin fondo! ¡Vuela, halcón, y no peques!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddMoneyToCharacter(pchar, -2000);
			GiveItem2Character(pchar, "totem_03");
			Log_Info("Has conseguido el talismán 'Bálsamo de Cupido'.");
			PlaySound("interface\important_item.wav");
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
			notification("Helen disapproves", "Helena");
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_joan":
			dialog.text = "¡Ah! ¡Fuera de aquí, canalla! ¿Cuántas veces te he dicho que no te subas a mi casa? ¿Y quién es este?";
			link.l1 = "Señora, ya nos conocemos.";
			link.l1.go = "helendrinking_joan_1";
		break;
		
		case "helendrinking_joan_1":
			dialog.text = "Monsieur de Maure? ¡Pues esto es simplemente encantador! ¿Así es como haces negocios con mi esposo? ¡Lo sabía! Le advertí a Jan: ¡algún día esta buscona comenzará a desviar a sus hombres! ¿Y qué tienes en tus manos?";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JoanDialog1");
		break;
		
		case "helendrinking_joan_2":
			dialog.text = "¡¿Qué?! ¡¿Cómo te atreves, desgraciado?! No irás a ninguna parte; ¡mi marido llegará en cualquier momento y te enseñará a hablar con los mayores!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JoanDialog3");
		break;
		
		case "helendrinking_fort_officer":
			dialog.text = "¿Qué está pasando aquí? ¡Señorita MacArthur! Tenía un gran respeto por su padre, y el señor Svensson es nuestro amigo... Pero, ¿no recuerda cómo terminó todo la última vez?\n¡Es decepcionante, palabra de oficial, decepcionante! ¡Podrías habernos invitado!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog");
		break;
		
		case "helendrinking_fort_officer_1":
			dialog.text = "Gracias por su hospitalidad, señorita MacArthur. Permítame decirle que todos estamos muy contentos de verla de vuelta. Lo que sucedió es un gran misterio, pero no es sorprendente que la ciudad lo sepa. Aun así, puedo prometerle que nadie chismorreará. Le ofrezco mis más sinceras disculpas por el comportamiento reciente de uno de nuestros capitanes. Y quiero agradecerle específicamente a usted, señor de Mor.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog3");
		break;
		
		case "helendrinking_fort_officer_2":
			dialog.text = "Todo estará bien, señorita. Sr. de Maure, seré franco: a pesar de que Donovan se comporta como un verdadero granuja y bandido, la flota nunca lo condenará abiertamente. Más bien, es probable que incluso lo defiendan. Su pequeña expedición llegó a los informes y complicó significativamente las relaciones entre nuestros países. No obstante, considerando la influencia del Sr. Svensson, así como las notables concesiones hechas a usted por Capsterville, no tiene nada que temer.";
			link.l1 = "Eso es espléndido. ¡Digo que bebamos por eso!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog1");
		break;
		
		case "helendrinking_poorman":
			dialog.text = "Disculpa amablemente, ¿qué hay del trabajo?";
			link.l1 = "¿Todavía estás aquí?";
			link.l1.go = "helendrinking_poorman_1";
		break;
		
		case "helendrinking_poorman_1":
			dialog.text = "Querido señor, ¿adónde más puedo ir? Solo fui a aliviarme, escuché su conversación sentimental y me calenté un poco. ¡Emocionalmente, quiero decir!";
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.BoughtRainbow")) {
			link.l1 = "¡Santo cielo! Bueno, ya que te di mi palabra, no hay más remedio. Ve, toma el mando.";
			link.l1.go = "helendrinking_poorman_bought";
			} else {
			link.l1 = "No tengo trabajo para usted, señor.";
			link.l1.go = "helendrinking_poorman_notbought";
			}
		break;
		
		case "helendrinking_poorman_bought":
			dialog.text = "¡Sí, sí, Capitán!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AddRainbow");
			AddDialogExitQuestFunction("HelenDrinking_LightsOut1NoArg");
		break;
		
		case "helendrinking_poorman_notbought":
			dialog.text = "¡Qué lástima! De todos modos, gracias por la invitación, ¡Capitán!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AddRainbow");
			AddDialogExitQuestFunction("HelenDrinking_LightsOut1NoArg");
		break;
		
		case "helensleep_amelia_mary":
			dialog.text = "En el nombre del Padre, del Hijo y del Espíritu Santo... entra, hijo mío.";
			if (HelenSleep_TalkedToAmelia()) {
			link.l1 = "Hola, Madre Amelia. ¿Vas a gritarme también?";
			link.l1.go = "helensleep_amelia_mary_know";
			} else {
			link.l1 = "¡Desaparece! ¿Qué clase de pesadilla es esta? ¿Qué está sucediendo? ¿Estoy soñando?";
			link.l1.go = "helensleep_amelia_mary_notknow";
			}
		break;
		
		case "helensleep_amelia_mary_know":
			dialog.text = "No, mi pequeño halcón. Y perdona a Jan, el pobre hombre se alteró. Pero sí, quiero regañarte. ¿Por qué viniste a la iglesia? ¿A arrepentirte de tus pecados? ¿O ibas tras la pelirroja?";
			link.l1 = "No me conozco a mí mismo...";
			link.l1.go = "helensleep_amelia";
			link.l2 = "¿La viste también? Me llamó la atención.";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia_mary_notknow":
			dialog.text = "Desaparece tú mismo. Ya deberíamos habernos encontrado, pero estás demorando todo. ¿Por qué viniste a la iglesia? ¿Para arrepentirte de tus pecados? ¿O estabas tras la pelirroja?";
			link.l1 = "No me conozco a mí mismo...";
			link.l1.go = "helensleep_amelia";
			link.l2 = "¿La viste también? Me llamó la atención.";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia_helen":
			dialog.text = "Buenos días, mi halcón. La recepción aún no ha comenzado, espera en la fila, por favor.";
			if (HelenSleep_TalkedToAmelia()) {
			link.l1 = "Hola, Su Excelencia. ¿Me va a gritar también?";
			link.l1.go = "helensleep_amelia_helen_know";
			} else {
			link.l1 = "¡Desaparece! ¿Qué clase de pesadilla es esta? ¿Qué está pasando? ¿Estoy soñando?";
			link.l1.go = "helensleep_amelia_helen_notknow";
			}
		break;
		
		case "helensleep_amelia_helen_know":
			dialog.text = "No, mi halcón. Y perdona a Jan, el pobre se puso nervioso. No hace falta que le regañe; lo hizo todo bien: no fue tras la pelirroja a la iglesia. ¡Buen chico!";
			link.l1 = "Recibir elogios es agradable. Especialmente si está claro por qué.";
			link.l1.go = "helensleep_amelia";
			link.l2 = "¿La viste también? Me llamó la atención.";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia_helen_notknow":
			dialog.text = "Desaparece tú mismo. Ya deberíamos habernos encontrado, pero lo estás retrasando todo. Ven aquí, te alabaré - no fuiste tras la pelirroja a la iglesia. ¡Buen chico!";
			link.l1 = "Recibir alabanzas es agradable. Especialmente si está claro por qué.";
			link.l1.go = "helensleep_amelia";
			link.l2 = "¿La viste tú también? Ella llamó mi atención.";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia":
			dialog.text = "No te molestaré con los detalles, tonto, pero te diré esto: estás destinado a ser una gran persona. Traerás mucho mal, pero mucho más bien. Pero la felicidad no está garantizada para ti. La felicidad, mi halcón, se da solo a aquellos que caminan su camino y no se desvían. Y una mujer fiel te ayudará a no desviarte.\nTendrás dos de ellas, y ambas te traerán felicidad, pero necesitas elegir a la de cabello rubio.";
			link.l1 = "¿Por qué habría de ser así? ¡Lo decidiré por mí mismo!";
			link.l1.go = "helensleep_amelia_1";
		break;
		
		case "helensleep_amelia_1":
			dialog.text = "Por supuesto, elige por ti mismo, pero la rubia es mejor. Lo decidimos así.";
			link.l1 = "¿Quiénes somos?";
			link.l1.go = "helensleep_amelia_2";
		break;
		
		case "helensleep_amelia_2":
			dialog.text = "La desafortunada ni siquiera sabe su verdadero nombre. Llámala, y será tuya. Así se dice.";
			link.l1 = "Ya no entiendo nada.";
			link.l1.go = "helensleep_amelia_3";
		break;
		
		case "helensleep_amelia_3":
			dialog.text = "¿Oyes esos golpes? Abre, y no te equivoques.";
			link.l1 = "De hecho, alguien está llamando... ¡Adelante!";
			link.l1.go = "exit";
			
			PlaySound("interface\knock.wav");
			
			AddDialogExitQuestFunction("HelenSleep_WakeUp");
		break;
		
		case "helendrinking_notifier":
			dialog.text = "Monsieur, el señor Svensson solicitó que le dedique un poco de su tiempo.";
			link.l1 = "Maldita sea, esto no augura nada bueno. Lo intentaré, pero no prometo nada.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_End");
		break;
		
		case "islatesoro_pirate1":
			dialog.text = "¡Día de suerte, muchachos! Les dije que tarde o temprano vendría aquí, ¿no? Muy bien, querida, entrega las armas y ven con nosotros.";
			link.l1 = "Os habéis equivocado, muchachos. Está conmigo.";
			link.l1.go = "islatesoro_pirate1_1";
		break;
		
		case "islatesoro_pirate1_1":
			dialog.text = "Mantente fuera de esto, o te dispararé como a un perro. Hay una buena suma ofrecida por la chica, y somos tipos hambrientos, carentes de principios.";
			link.l1 = "Sigue hablándome en ese tono, y resolveré tu problema de hambre de forma permanente.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroSpawnSecond");
		break;
		
		case "islatesoro_pirate1_2":
			dialog.text = "¿Te has vuelto completamente loco, Lucky? ¡La encontramos primero nosotros! ¡Será mejor que tengas una buena razón para ladrar tu estúpida boca hacia mí!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog1");
		break;
		
		case "islatesoro_pirate1_3":
			dialog.text = "¡Tú eres la rata aquí! Acabamos de destrozar a un gordo español; ¡podemos quedarnos sentados un año!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog3");
		break;
		
		case "islatesoro_pirate2":
			dialog.text = "Bueno, miren a quién tenemos aquí. Muy bien, todos los demás, váyanse, y usted, señora, venga con nosotros.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog");
		break;
		
		case "islatesoro_pirate2_1":
			dialog.text = "Te superamos en número, y somos más duros, danés. ¿Qué otra razón necesitas, rata de sentina? ¡Hace seis meses que no ves un botín decente, y has estado comiendo migajas de pan de la mesa de Vuazie!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog2");
		break;
		
		case "islatesoro_pirate2_2":
			dialog.text = "";
			link.l1 = "Parece que no habrá una resolución pacífica aquí.";
			link.l1.go = "islatesoro_pirate_a";
			if (!CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedB")) {
			link.l2 = "¿Qué dijiste? ¿Suerte? Escuché un rumor de que él y Vuazie conspiraron para darte consejos dudosos. Eso explica tu racha de mala suerte en el mar.";
			link.l2.go = "islatesoro_pirate_b";
			}
			bOk = (!CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Choice")) || (pchar.questTemp.Mtraxx.Retribution.Choice == "bad");
			if (!CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedC") && CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold") && bOk) {
			link.l3 = "Estoy cansado de esta farsa. ¡Isla Tesoro, escúchame! ¿Quién estuvo conmigo en Cartagena?! ¿Quién quemó Mérida conmigo?! ¡Estas ratas se atreven a enfrentarse al mismísimo Charlie Prince! ¡Mostrémosles, muchachos!";
			link.l3.go = "islatesoro_pirate_c";
			}
		break;
		
		case "islatesoro_pirate_a":
			dialog.text = "¿Todavía estás aquí, medusa? Muy bien, muchachos, vamos: amarren al capitán, y nos ocuparemos de la chica después, ¿entendido?";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog4");
		break;
		
		case "islatesoro_pirate_a_1":
			dialog.text = "Claro, al menos derramemos un poco de sangre. Jeje.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroA");
		break;
		
		case "islatesoro_pirate_b":
			pchar.questTemp.HelenDrinking.IslaTesoroAmbush.TriedB = true;
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 60) {
			dialog.text = "¿Qué?! ¡Diablo, sabía que estabas coludido con ese canalla de gafas! ¡Córtenlos a todos, muchachos, y recogeremos a la chica más tarde!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroB");
			} else {
			dialog.text = "¿De qué estás parloteando, Capitán? Piérdete mientras la gente respetable discute negocios.";
			link.l1 = "";
			link.l1.go = "islatesoro_pirate2_2";
			}
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "islatesoro_pirate_c":
			pchar.questTemp.HelenDrinking.IslaTesoroAmbush.TriedC = true;
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 50) {
			DialogExit();
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroC");
			} else {
			dialog.text = "¿De qué estás parloteando, capitán? He visto a Charlie Prince, y tú no le llegas ni a los talones. Piérdete mientras la gente respetable discute asuntos.";
			link.l1 = "";
			link.l1.go = "islatesoro_pirate2_2";
			}
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "francois":
			dialog.text = "¿Charles de Maure? ¿Hijo de Henri de Monpe?";
			link.l1 = "Eso es correcto, monsieur. ¿Y quién sois vos?";
			link.l1.go = "francois_1";
		break;
		
		case "francois_1":
			dialog.text = "Coronel Francois de Tavanne. Puede considerar esto un desafío directo, monsieur; el guante para el duelo ha sido lanzado. Ni siquiera deseo ensuciarme las manos con usted, ¡pero le juro que mi espada saboreará su sangre!";
			link.l1 = "¿Un duelo? En ese caso, tendrá que esforzarse mucho más, Coronel. ¡Ahora mismo, sólo podría confundirle con un bandido, y por aquí la conversación con su clase es breve! ¡Explíquese!";
			link.l1.go = "francois_2";
		break;
		
		case "francois_2":
			dialog.text = "¡Seduciste a mi esposa, monsieur! Mientras yo derramaba sangre por el rey y el país, tú... ¡tú te divertías con mi esposa!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog");
		break;
		
		case "francois_3":
			dialog.text = "Silencio, señora. ¡Su atrevido atuendo deshonra el honor de cualquier mujer, aunque parece bastante apropiado al lado de este indigno seductor de una dama noble!";
			link.l1 = "Todavía no es suficiente razón para un duelo, Coronel. Y permítame señalar que usted se comporta aquí igual de indignamente.";
			link.l1.go = "francois_4";
		break;
		
		case "francois_4":
			dialog.text = "¿No es eso suficiente? He preguntado - en mi lugar ahora podrían estar una docena de maridos nobles, señor. Pero si deseas los detalles, entonces para mi vergüenza, confieso que una de tus pasiones fue Lulu de Tavann, ¡la más hermosa y honesta de las mujeres!";
			link.l1 = "Lulú, dices... ¿Y cómo está ella?";
			link.l1.go = "francois_5";
		break;
		
		case "francois_5":
			dialog.text = "¡Silencio! ¡Mi esposa, incapaz de soportar el tormento que infligiste, falleció recientemente! ¡He pasado casi un año y una fortuna para encontrarte, canalla! ¡Basta de palabras! Acepta el desafío, o te mataré como a un perro. ¡Richard! ¡Sé mi testigo!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog2");
		break;
		
		case "francois_6":
			dialog.text = "¡Silencio, señor! ¡Acepta el desafío o pierde cualquier vestigio de honor que aún puedas tener!";
			if (pchar.HeroParam.HeroType == "HeroType_1") {
			link.l1 = "Un duelo es un duelo. No voy a mentir, disfruto de ellos. Capitán, dígale al Coronel que es hora de que ordene un ataúd adecuado.";
			} else {
			link.l1 = "¿Quieres pelea? ¡La tendrás! Capitán, dígale al Coronel que es hora de que ordene un ataúd adecuado.";
			}
			link.l1.go = "francois_duel";
			link.l2 = "Esto no es Europa, Coronel. El honor en el Caribe es más difícil de ganar, pero tampoco tan fácil de perder. Rechazo su duelo porque simplemente no lo deseo.";
			link.l2.go = "francois_refuse";
		break;
		
		case "francois_7":
			dialog.text = "¡Tu padre ya está a un paso de la tumba, escoria! ¡Y me aseguraré de que sepa de tu cobardía!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog7");
		break;
		
		case "richard":
			dialog.text = "Coronel, confirmo su derecho a un duelo, ¡pero no permitiré simple bandidaje! Monsieur de Maure, soy el Capitán Richard Small. ¿Está dispuesto a darle satisfacción al Coronel de Tavann?";
			link.l1 = "Un momento, Capitán. Conocía bien a Lulu... y ella... tenía la inclinación de cambiar de admiradores con frecuencia, y su salud era mejor que la mía... ¿Cómo murió, Coronel? ¿Antes o después de su regreso a casa?";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog3");
		break;
		
		case "richard_1":
			dialog.text = "Por favor, François, permíteme. Monsieur de Maure, has sido desafiado. La sociedad de oficiales de Blueweld ha reconocido que la demanda de satisfacción del Coronel de Tavann está justificada. Acepta el desafío o pierde tu honor.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog5");
		break;
		
		case "richard_2":
			dialog.text = "Charles, por favor, somos nobles aquí. No es apropiado. ¡El Coronel viajó hasta aquí para encontrarse contigo! ¡Es un escándalo!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog8");
		break;
		
		case "richard_3":
			dialog.text = "Sí, sí, por supuesto, señorita. Pero yo...";
			link.l1 = "";
			link.l1.go = "exit";
			CharacterTurnToLoc(npchar, "quest", "helen");
			
			AddDialogExitQuestFunction("HelenDrinking_AfterFrancoisDeath1");
		break;
		
		case "richard_4":
			dialog.text = "¡Capitán de Maure, el día es suyo! No fue la pelea más adecuada, pero hoy defendiste tu honor.";
			link.l1 = "¿Dijiste algo, Capitán? Podría ser que pueda encajar otro duelo en el horario de hoy.";
			link.l1.go = "richard_5";
		break;
		
		case "richard_5":
			dialog.text = "Mis disculpas, capitán. ¡Son solo los nervios!";
			link.l1 = "Creo que tu presencia aquí ya no es necesaria.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_DuelVictory");
		break;
		
		case "richard_duel":
			dialog.text = "¡Una decisión justa! Aunque no se presentó de la manera más digna... ¡Caballeros! ¡Comencemos!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SetupDuel");
		break;
		
		case "alonso":
			dialog.text = "Capitán, puede que no entienda todas esas palabras elegantes que estos dignatarios sueltan, pero mire, si a alguien le llaman cobarde, usualmente no lo dejas escapar. ¡Dale un golpe al tipo, Capitán, o nuestra tripulación se preocupará!";
			link.l1 = "¿Queréis sangre? ¿La vida es demasiado aburrida, sin emoción? ¡Tendréis vuestra sangre, animales!";
			link.l1.go = "francois_duel";
			link.l2 = "¡Bú, bú, estoy tan asustado! ¿Han terminado aquí, caballeros? Tengo lugares a donde ir.";
			link.l2.go = "alonso_refuse";
		break;
		
		case "alonso_1":
			dialog.text = "No quedará bien que nuestro capitán se eche atrás ante un desafío público. Dale un buen golpe a ese noble; ¡sabemos que eres bueno con la espada!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog9");
		break;
		
		case "alonso_refuse":
			DialogExit();
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog6");
		break;
		
		case "francois_refuse":
			dialog.text = "¡Cobarde! ¡Libertino! ¡Rata! ¿Tienes miedo, canalla? ¿Lo habéis presenciado todos?! ¡Richard, lo mataré de todos modos!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog4");
		break;
		
		case "francois_duel":
			DialogExit();
			
			AddDialogExitQuestFunction("HelenDrinking_SetupDuelDialog");
		break;
		
		case "francois_sit":
			dialog.text = "¡M-miserable! Está bien, estoy acostumbrado a las heridas. Me recuperaré, y...";
			link.l1 = "Suena como una amenaza, coronel. Y no tomo las amenazas a la ligera.";
			link.l1.go = "francois_sit_kill";
			link.l2 = "Una vez que te hayas recuperado, no olvides alardear sobre las circunstancias de tu herida ante la comunidad de oficiales.";
			link.l2.go = "francois_sit_taunt";
		break;
		
		case "francois_sit_kill":
			DialogExit();
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
			notification("Helen disapproves", "Helena");
			
			AddDialogExitQuestFunction("HelenDrinking_FinishFrancois");
		break;
		
		case "francois_sit_taunt":
			DialogExit();
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
			notification("Helen approves", "Helena");
			AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 300);
			AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 300);
			
			AddDialogExitQuestFunction("HelenDrinking_SpareFrancois");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

bool HelenSleep_TalkedToAmelia()
{
	if (GetCharacterIndex("Amelia") < 0)
	{
		return false;
	}

	sld = CharacterFromID("Amelia");
	if (sld.dialog.currentnode == "amelia")
	{
		return false;
	}

	return true;
}
