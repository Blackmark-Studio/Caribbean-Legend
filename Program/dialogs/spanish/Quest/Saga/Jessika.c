// Джессика Роуз - нежить и супербосс
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;
	float locx, locy, locz;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		dialog.text = "¿Deseas algo?";
		link.l1 = "No, no es nada.";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	// бой на рифе
	case "reef":
		PlaySound("Voice\Spanish\saga\Jessica Rose-06.wav");
		dialog.text = "¡Tú! ¡Tú la has traído aquí! ¡Ella es su carne y sangre! ¡Ella es su carne y sangre! ¡La hija de la ramera ha venido a la tumba de su madre! ¡Morirá! ¡Y no podrás detenerlo! ¡No te interpongas en el camino de Jessica! ¡Voy a obtener mi venganza! ¡Lo juro!";
		link.l1 = "...";
		link.l1.go = "reef_1";
		break;

	case "reef_1":
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		DialogExit();
		LAi_SetWarriorType(npchar);
		LAi_group_MoveCharacter(npchar, "EnemyFight");
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "stage_1":
		PlaySound("Voice\Spanish\saga\Jessica Rose-07.wav");
		dialog.text = "¡Ja, ja, ja! ¡Soy imparable! ¡No puedes herirme!\n El aire, el agua, la tierra, el fuego, ¡os ordeno que me asistáis!\n ¡Que los muertos se levanten, que el fuego arda, que el agua custodie el puente y que el viento te lleve en sus alas y te arroje al suelo!\n ¡Diviértete!!!";
		link.l1 = "...";
		link.l1.go = "stage_1_exit";
		break;

	case "stage_1_exit":
		DialogExit();
		LAi_SetActorType(pchar);
		CreateLocationParticles("blast_inv", "quest", "top", 1.6, 0, 0, "");
		PlaySound("Sea Battles_01\Bomb_Explosion_03.wav");
		PlaySound("People Fight\Death_NPC_08.wav");
		GetCharacterPos(pchar, &locx, &locy, &locz);
		ChangeCharacterAddressGroup(pchar, "shore67", "goto", LAi_FindFarFreeLocator("goto", locx, locy, locz));
		LAi_ActorAnimation(Pchar, "Ground_sitting", "", 3.5);
		DoQuestCheckDelay("Saga_JessikaFirstKick_2", 3.5);
		break;

	case "stage_2":
		PlaySound("Voice\Spanish\saga\Jessica Rose-07.wav");
		dialog.text = "¡Ja, ja,ja! ¡Soy imparable! ¡No puedes herirme!\n¡Deja que más muertos se levanten y ataquen, deja que el fuego queme la piedra, deja que el viento te levante y te arroje al suelo y deja que la tierra absorba tus fuerzas!\n¡Disfruta!!!";
		link.l1 = "... ";
		link.l1.go = "stage_2_exit";
		break;

	case "stage_2_exit":
		DialogExit();
		LAi_SetActorType(pchar);
		CreateLocationParticles("blast_inv", "quest", "rock", 1.6, 0, 0, "");
		PlaySound("Sea Battles_01\Bomb_Explosion_03.wav");
		PlaySound("People Fight\Death_NPC_08.wav");
		pchar.GenQuest.BladePenalty = 30;
		GetCharacterPos(pchar, &locx, &locy, &locz);
		ChangeCharacterAddressGroup(pchar, "shore67", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
		LAi_ActorAnimation(Pchar, "Ground_sitting", "", 3.5);
		DoQuestCheckDelay("Saga_JessikaSecondKick_2", 3.5);
		break;

	case "stage_3":
		PlaySound("Voice\Spanish\saga\Jessica Rose-07.wav");
		dialog.text = "¡Ja, ja, ja! ¡Soy imparable! ¡No puedes herirme!\n¡Deja que el veneno cubra mi espada de hoja ardiente, deja que el viento te envuelva en sus abrazos, deja que el agua se beba tu agilidad!\n¡Muere! ¡Ja-ja-ja!";
		link.l1 = "...";
		link.l1.go = "stage_3_exit";
		break;

	case "stage_3_exit":
		DialogExit();
		npchar.viper = true;
		TakeNItems(npchar, "potion2", 3);
		LAi_SetActorType(pchar);
		PlaySound("Sea Battles_01\Bomb_Explosion_03.wav");
		PlaySound("People Fight\Death_NPC_08.wav");
		pchar.GenQuest.EnergyPenalty = 2;
		GetCharacterPos(pchar, &locx, &locy, &locz);
		ChangeCharacterAddressGroup(pchar, "shore67", "quest", "bridge2");
		LAi_ActorTurnToLocator(pchar, "quest", "bridge1");
		LAi_ActorAnimation(Pchar, "Ground_sitting", "", 3.5);
		DoQuestCheckDelay("Saga_JessikaThirdKick_2", 3.5);
		break;

	case "stage_4":
		PlayStereoOGG("music_shore");
		sld = characterFromId("Svenson");
		dialog.text = "Suficiente... Estoy cansado. Estoy derrotado... ¡Ten piedad del destino de la desafortunada Jessica!";
		link.l1 = "Claro... ¡Ahorraré a tu pobre alma el peso de este cadáver!";
		link.l1.go = "exit_battle";
		if (CheckAttribute(sld, "quest.jessika_peace")) // выслушал историю Джессики
		{
			link.l2 = "Conozco tu historia, Jessica. Y lamento que tu vida haya sido tan triste y haya terminado de esa manera. ¿Quieres hablar conmigo, verdad? Bueno, intentaré olvidar que recientemente intentaste matarme y te escucharé, aunque no será fácil para mí...";
			link.l2.go = "exit_talk";
		}
		break;

	case "exit_battle":
		DialogExit();
		SetMusic("music_teleport");
		DeleteAttribute(npchar, "viper");
		LAi_SetImmortal(npchar, false);
		npchar.chr_ai.hp = stf(npchar.chr_ai.hp) + 100;
		LAi_SetWarriorType(npchar);
		LAi_group_MoveCharacter(npchar, "EnemyFight");
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "Saga_JessikaDie");
		AddDialogExitQuest("MainHeroFightModeOn");
		pchar.questTemp.Saga.JessSeekTreatment = 0;
		LAi_LocationDisableOfficersGen(pchar.location, false); // офицеров пускать
		break;

	case "exit_talk":
		dialog.text = "Gracias... Ya sabes sobre Beatrice Sharp y Lawrence... mi Lawrence. La he matado sin titubear, pero no pude matarlo a él. No pude hacerlo, pero él sí pudo. Jessica murió...";
		link.l1 = "... ";
		link.l1.go = "exit";
		AddDialogExitQuest("Video_Reef");
		NextDiag.TempNode = "exit_talk_0";
		break;

	case "exit_talk_0":
		dialog.text = "... pero el juramento de sangre, sellado por un terrible voto, aún no se ha cumplido. El poder de este juramento proviene de la magia india. Levantó el cadáver de su tumba.\nEl odio convirtió mi alma en un desierto. Todos los que llegaron a este arrecife fueron asesinados por mi mano y sus cadáveres se convirtieron en mis marionetas. No puedo pedir ayuda a nadie más que a aquel que me ha vencido...";
		link.l1 = "¿Y qué puedo hacer por ti? Lo único que puedo hacer es librarte del sufrimiento...";
		link.l1.go = "exit_talk_1";
		break;

	case "exit_talk_1":
		PlaySound("Voice\Spanish\saga\Jessica Rose-08.wav");
		dialog.text = "Ayúdame... Ahora, llévame con él.";
		link.l1 = "¿A Lawrence Beltrope? ¿Y cómo se supone que haga eso? Mi tripulación o huirá en cuanto te vean o te quemarán sin remordimientos. Por cierto, todavía eres capaz de masacrar a mis hombres y 'controlarlos'...";
		link.l1.go = "exit_talk_2";
		break;

	case "exit_talk_2":
		dialog.text = "No me verán. Pero tú sí. Debes haber entendido ya que poseo poderes que no están disponibles para los vivos. Pero no puedo abordar tu barco sin tu permiso. Llévame a él. \nNo me quedaré contigo por mucho tiempo. Y no haré daño a tu gente. Déjame en la bahía de Portland en Jamaica a medianoche, la noche siguiente nos volveremos a encontrar y recibirás lo que querías encontrar aquí.";
		link.l1 = "¿Cómo sabes por qué estoy aquí?";
		link.l1.go = "exit_talk_3";
		break;

	case "exit_talk_3":
		PlaySound("Voice\Spanish\saga\Jessica Rose-09.wav");
		dialog.text = "Tengo lo que estás buscando, ¿porqué no me ayudas? Yo sé mucho. Más que los vivos. La vi... Necesitas un documento para ella y lo obtendrás. Obtendrás aún más, te daré algo adicional. Llévame a él...";
		link.l1 = "Hum. No me gustan tus intenciones sedientas de sangre hacia Helen. Ni se te ocurra tocarla. Después de todo, ella no es responsable de las acciones de su madre.";
		link.l1.go = "exit_talk_4";
		break;

	case "exit_talk_4":
		dialog.text = "Me has derrotado. No la haré daño... Lo prometo.";
		link.l1 = "Aún no ha terminado. ¿Vas a liberarme de tus numerosas maldiciones? Lo admito, no me gusta la idea de vivir con ellas para siempre...";
		link.l1.go = "exit_talk_5";
		break;

	case "exit_talk_5":
		dialog.text = "No es tan simple... Cuando nos encontremos en la Cala de Portland después de que yo... Te diré cómo curarte.";
		link.l1 = "¿Después de qué tú qué?.. ¿Qué quieres decir?";
		link.l1.go = "exit_talk_6";
		break;

	case "exit_talk_6":
		dialog.text = "Después de mi encuentro con él.";
		link.l1 = "Oh, no estará feliz. Puedo imaginarlo. Bien, resumamos: primero, prometes que nadie te verá, segundo, no harás daño a mi tripulación, tercero, ni siquiera pensarás en Helen, cuarto, me darás lo que estoy buscando, y quinto, me curarás de tus maldiciones. ¿Estoy en lo correcto?";
		link.l1.go = "exit_talk_7";
		break;

	case "exit_talk_7":
		dialog.text = "Casi. No te sanaré, pero te diré cómo hacerlo. Tendrás que hacerlo tú mismo.";
		link.l1 = "Está bien. Trato hecho. Te permito embarcar en mi barco.";
		link.l1.go = "exit";
		AddDialogExitQuest("Video_Reef2");
		NextDiag.TempNode = "exit_talk_8";
		break;

	case "exit_talk_8":
		PlaySound("Ambient\Teno_inside\teleporter.wav");
		ChangeCharacterAddressGroup(npchar, "none", "", "");
		dialog.text = "";
		link.l1 = "¡Oye! ¿Dónde estás? Simplemente desapareciste...";
		link.l1.go = "exit_talk_9";
		break;

	case "exit_talk_9":
		DialogExit();
		LAi_group_Delete("EnemyFight");
		pchar.quest.Saga_JessFire.over = "yes";
		pchar.quest.Saga_JessFire1.over = "yes";
		pchar.quest.Saga_JessFire2.over = "yes";
		ref chr = &Locations[FindLocation(pchar.location)];
		DeleteAttribute(chr, "hell_fire_1");
		DeleteAttribute(chr, "hell_fire_2");
		DeleteAttribute(chr, "hell_fire_3");
		chrDisableReloadToLocation = false;			   // открыть локацию
		DeleteAttribute(pchar, "GenQuest.CannotWait"); // можно мотать время
		AddQuestRecord("Shadows", "9");
		AddPassenger(pchar, npchar, false);
		SetCharacterRemovable(npchar, false);
		pchar.questTemp.Saga.JessOnShip = "true"; // атрибут на отрицательные последствия
		pchar.quest.Saga_Jessika_Travel.win_condition.l1 = "Hour";
		pchar.quest.Saga_Jessika_Travel.win_condition.l1.start.hour = 0.00;
		pchar.quest.Saga_Jessika_Travel.win_condition.l1.finish.hour = 2.00;
		pchar.quest.Saga_Jessika_Travel.win_condition.l2 = "location";
		pchar.quest.Saga_Jessika_Travel.win_condition.l2.location = "shore36";
		pchar.quest.Saga_Jessika_Travel.function = "Saga_JessikaOnJamaica";
		NextDiag.CurrentNode = "shore";
		npchar.greeting = "jessika_2";
		LAi_LocationDisableOfficersGen(pchar.location, false); // офицеров пускать
		LAi_LocationDisableOfficersGen("shore36", true);	   // офицеров не пускать в бухту Портленд
		break;

	case "shore":
		dialog.text = "Has cumplido tu palabra, estamos en Jamaica. Ven aquí mañana por la noche y cumpliré mi promesa. Adiós.";
		link.l1 = "Adiós...";
		link.l1.go = "shore_1";
		break;

	case "shore_1":
		DialogExit();
		DeleteAttribute(pchar, "questTemp.Saga.JessOnShip");
		DeleteAttribute(npchar, "SaveItemsForDead");
		DeleteAttribute(npchar, "DontClearDead");
		LAi_SetActorType(npchar);
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // разрешить драться
		LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
		AddQuestRecord("Shadows", "10");
		SetFunctionTimerCondition("Saga_JessikaShoreWait", 0, 0, 1, false);
		NextDiag.CurrentNode = "shore_2";
		npchar.greeting = "jessika_3";
		break;

	case "shore_2":
		dialog.text = "Se acabó, " + pchar.name + "...";
		link.l1 = "¿Qué quieres decir?";
		link.l1.go = "shore_3";
		break;

	case "shore_3":
		dialog.text = "Se acabó... Aquí, tómalo, esto es lo que buscabas. Esta es la carta de mi rival, fue enterrada con ella. Está bien conservada. La he perdonado y ya no hay odio en mi alma.";
		link.l1 = "¿Te... encontraste con él? ¿Con Lawrence?";
		link.l1.go = "shore_4";
		break;

	case "shore_4":
		GiveItem2Character(pchar, "letter_beatriss"); // дать письмо
		AddQuestRecordInfo("Letter_beatriss", "1");
		dialog.text = "Sí. Lo último que sintió en su vida fue horror. No lo lamento por él.";
		link.l1 = "Que Dios perdone su alma pecadora... Parece que nunca lo conoceré.";
		link.l1.go = "shore_5";
		break;

	case "shore_5":
		dialog.text = "No has perdido nada de valor. Era un hombre muy malo. Ahora, deberíamos despedirnos, ya no hay nada más que pueda hacer aquí. Mi juramento se ha cumplido y la magia ha perdido su poder. Te he prometido un regalo. Aquí. Este es mi Flamberge. Ya no lo necesito. Esta espada es única, no encontrarás una mejor en ningún lugar del mundo.";
		link.l1 = "Gracias...";
		link.l1.go = "shore_6";
		break;

	case "shore_6":
		RemoveAllCharacterItems(npchar, true);
		GiveItem2Character(pchar, "blade_25");
		PlaySound("interface\important_item.wav");
		dialog.text = "Ahora, sobre ti. Ve a Bridgetown, a la iglesia, para levantar mis maldiciones. Encontrarás a un sacerdote allí. Me conocía personalmente. Habla con él y te dirá qué hacer. Prepara veinte velas, las necesitarás.";
		link.l1 = "¿Estás seguro de que él me curará?";
		link.l1.go = "shore_7";
		break;

	case "shore_7":
		dialog.text = "Tú lo harás tú mismo. Dios te guiará. Estate seguro. Todo irá bien.";
		link.l1 = "Está bien, zarparé a Barbados de inmediato. ¿Y ahora qué?";
		link.l1.go = "shore_8";
		break;

	case "shore_8":
		PlaySound("Voice\Spanish\saga\Jessica Rose-04.wav");
		dialog.text = "Y ahora deseo una última cosa. Entierra mi cuerpo aquí en esta bahía cerca del mar. Quiero eso. Tal vez algún día visites la tumba de la pobre Jessica. Adiós, " + pchar.name + ", y reza por mí...";
		link.l1 = "¿Jess?..";
		link.l1.go = "shore_9";
		break;

	case "shore_9":
		DialogExit();
		LAi_KillCharacter(npchar);
		bQuestDisableMapEnter = false;
		DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		chrDisableReloadToLocation = false;
		LAi_LocationDisableOfficersGen("shore36", false);
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		AddQuestRecord("Shadows", "11");
		pchar.questTemp.Saga.JessTreatment = "true";
		// вытираем Белтропа
		sld = characterFromId("Beltrop");
		sld.lifeday = 0;
		pchar.questTemp.Saga.Beltrop_die = "true"; // Белтроп убит
		sld = ItemsFromID("letter_jess");
		sld.price = 1; // страницу можно выкладывать 270912
		break;

	case "soul":
		dialog.text = "¿Me reconoces, Capitán?";
		link.l1 = "¿Eres tú...? ¿Pero cómo?";
		link.l1.go = "soul_1";
		break;

	case "soul_1":
		dialog.text = "Sí, " + pchar.name + ", soy yo, ¡es Jessica! Al menos cuando me veía así hace veinte años.";
		link.l1 = "Entonces... ¿morí? ¿Pero cuándo? ¿Cómo?";
		link.l1.go = "soul_2";
		break;

	case "soul_2":
		dialog.text = "No estás muerto, " + pchar.name + ". Estás en la iglesia de Bridgetown ahora. Solo estás... durmiendo.";
		link.l1 = "¿Es esto solo un sueño? Las cosas parecen demasiado reales...";
		link.l1.go = "soul_3";
		break;

	case "soul_3":
		dialog.text = "A veces sucede, " + pchar.name + ". Dios te ha escuchado. Tus oraciones no solo te han sanado, sino que también han purificado mi alma. Muchas gracias, " + pchar.name + "¡Y quiero pedirte que me perdones por lo que ha pasado en el arrecife. Es... bueno, solo perdóname. No podía irme sin pedirte perdón.";
		link.l1 = "Te perdono, Jessica. ¿Estoy realmente vivo?";
		link.l1.go = "soul_4";
		break;

	case "soul_4":
		dialog.text = "Eres... No te preocupes. Pronto despertarás. Solo quería despedirme.";
		link.l1 = "¡Eres tan... hermosa!";
		link.l1.go = "soul_5";
		break;

	case "soul_5":
		dialog.text = "¿Te gusto? Sí, hubo un tiempo en que los mejores pretendientes de las Antillas Menores me cortejaban y cada tercer pirata de Isla Tesoro estaba listo para batirse en duelo por mí.";
		link.l1 = "Pero siempre has necesitado solo uno... ¡Eh, talismán de jengibre! Solo dime, ¿por qué terminaste así?";
		link.l1.go = "soul_6";
		break;

	case "soul_6":
		dialog.text = "Por mi ira. Por mi odio. Por la incapacidad de entender, perdonar y olvidar. Podría haber empezado una nueva vida, pero preferí dedicarme a una venganza estúpida e inútil. Me has liberado. Gracias, " + pchar.name + "... ";
		link.l1 = "Siento mucha pena por tu vida...";
		link.l1.go = "soul_7";
		break;

	// здесь проверяем Мэри
	case "soul_7":
		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
		{ // Мэри-офицер
			dialog.text = "No... Todavía tienes tu talismán de jengibre...";
			link.l1 = "¿Mi qué?";
			link.l1.go = "mary_1";
			break;
		}
		if (!CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && CheckAttribute(pchar, "questTemp.LSC.marywait"))
		{ // Мэри осталась на острове
			dialog.text = "No... Todavía tienes tu talismán de jengibre...";
			link.l1 = "¿Mi qué?";
			link.l1.go = "mary_3";
			break;
		}
		dialog.text = "No... Considera mi triste experiencia y no repitas mis errores. Y no dejes que las personas que amas los cometan tampoco.";
		link.l1 = "Lo consideraré y no cometeré los mismos errores, seguro...";
		link.l1.go = "soul_8";
		break;

	case "mary_1":
		dialog.text = "Piensa un poco. Ella está en tu barco.";
		link.l1 = "¿Mary?!";
		link.l1.go = "mary_2";
		break;

	case "mary_2":
		dialog.text = "Sí. Ella es la mejor que tendrás en tu vida. Recuerda eso. Su amor es puro, su devoción es infinita. Es valiente, joven, pero desesperada e inexperta. No entiende mucho. Cuida de ella, protégela y no dejes que nadie se interponga entre ustedes. Ella es tu talismán...";
		link.l1 = "Yo... nunca la dejaré y la protegeré de cualquier peligro.";
		link.l1.go = "soul_8";
		break;

	case "mary_3":
		dialog.text = "Está en la extraña isla hecha de barcos muertos... No está sola allí, pero sí se siente sola. Cada mañana suya comienza con un pensamiento sobre ti, cada día reza por ti, cada noche hay una luz en su cabaña y su almohada está mojada por sus lágrimas...";
		link.l1 = "Mary...";
		link.l1.go = "mary_4";
		break;

	case "mary_4":
		dialog.text = "Hay una hija entre vosotros. La hija de la mujer que una vez se interpuso entre Lawrence y yo. El destino de tu talismán está en tus manos. No pueden coexistir juntos, al igual que Beatrice y yo no pudimos.";
		link.l1 = "¿Cómo sabes eso?";
		link.l1.go = "mary_5";
		break;

	case "mary_5":
		dialog.text = "El otro lado... Muestra mucho... Es tu elección, pero recuerda: Mary es lo mejor que tendrás en tu vida. Su amor es puro, su devoción es infinita. Es valiente, joven, pero desesperada e inexperta. No entiende mucho. Necesita tu protección, tu cuidado y tu amor. Es tu talismán.";
		link.l1 = "Lo consideraré. Lo haré seguro...";
		link.l1.go = "soul_8";
		break;

	case "soul_8":
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_friend"))
			sTemp = "";
		else
			sTemp = "Y sobre la hija de Beatrice, sepa que sus nobles acciones en su nombre no serán valoradas. Pronto lo verás por ti mismo. Ten cuidado con ella. Bueno...\n";
		dialog.text = "" + sTemp + "Tengo que irme. Es hora de decir adiós... De verdad esta vez. No te olvides de Jessica y trata de visitar su tumba de vez en cuando... Solo tú sabes dónde está.";
		link.l1 = "Claro, Jess. Lo visitaré y rezaré por ti.";
		link.l1.go = "soul_9";
		break;

	case "soul_9":
		dialog.text = "Gracias. Adiós, " + pchar.name + "¡Adiós!";
		link.l1 = "Adiós, Jessica...";
		link.l1.go = "soul_10";
		break;

	case "soul_10":
		DialogExit();
		LAi_SetActorType(pchar);
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Saga_JessikaSoul_4", -1);
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}
