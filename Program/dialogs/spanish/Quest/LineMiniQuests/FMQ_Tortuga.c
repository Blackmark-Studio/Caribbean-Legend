// Addon-2016 Jason, французские миниквесты (ФМК) Тортуга
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		dialog.text = "Un error obvio. Dile a los desarrolladores al respecto.";
		link.l1 = "Oh, lo haré.";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	case "girl":
		DelMapQuestMarkCity("Tortuga");
		LAi_SetImmortal(npchar, false);
		DelLandQuestMark(npchar);
		LAi_RemoveLoginTime(npchar);
		FMQT_FillChest();
		PlaySound("Voice\Spanish\Girls_1.wav");
		dialog.text = "¡Oh, hola monsieur! ¡Bienvenido a Tortuga! Capitanes tan nobles como usted son huéspedes raros aquí...";
		link.l1 = "Saludos, señorita. Gracias por la cálida bienvenida. ¿Pero cómo es eso? Pensé que un puerto tan importante siempre era un lugar de interés para caballeros de fortuna mucho más nobles que yo.";
		link.l1.go = "girl_1";
		break;

	case "girl_1":
		dialog.text = "Ah monsieur... Claramente sois un recién llegado, ¿verdad? Ya lo veréis. No tenéis idea de lo difícil que es encontrar hombres dignos para una fiesta de baile en el palacio del gobernador. ¿Quizás podríais acompañarme...?";
		link.l1 = "¿Cómo puedo servir a una mujer tan hermosa?";
		link.l1.go = "girl_2";
		break;

	case "girl_2":
		dialog.text = "¡Vaya, vaya, qué galantería! (risitas) Quizás podrías visitarnos a las seis de la tarde esta noche. La esposa de nuestro gobernador organiza regularmente fiestas informales en las dependencias del palacio. Es una oportunidad rara para nosotros de tener compañía intrigante en tales eventos. ¿Nos harás una visita? Por favor, ven, estaríamos encantadísimos.";
		link.l1 = "Sería un honor, señorita. Te haré una visita esta noche.";
		link.l1.go = "girl_3";
		link.l2 = "Perdóname, mademoiselle, pero tengo asuntos urgentes que atender. ¿Quizás en otro momento?";
		link.l2.go = "girl_exit";
		break;

	case "girl_exit":
		dialog.text = "Lástima. Tendré que encontrar a alguien más que me haga compañía a mí y a mis amigas... Adiós.";
		link.l1 = "Adiós.";
		link.l1.go = "girl_exit_1";
		break;

	case "girl_exit_1":
		DialogExit();
		chrDisableReloadToLocation = false;
		LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 40.0);
		npchar.lifeday = 0;
		FMQT_ClearChest();
		break;

	case "girl_3":
		dialog.text = "¡Gracias! Te prometo que esta será una noche que nunca olvidarás, monsieur. ¡Au revoir!";
		link.l1 = "Nos vemos...";
		link.l1.go = "girl_4";
		break;

	case "girl_4":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 40.0);
		npchar.lifeday = 0;
		pchar.questTemp.FMQT = "begin_serveroom";
		FMQT_Begin();
		AddQuestRecord("FMQ_Tortuga", "1");
		break;

	case "girl_5":
		DelMapQuestMarkCity("Tortuga");
		LAi_SetImmortal(npchar, false);
		DelLandQuestMark(npchar);
		LAi_RemoveLoginTime(npchar);
		FMQT_FillChest();
		PlaySound("Voice\Spanish\Girls_1.wav");
		dialog.text = "¡Hola, marinero! ¿Qué viento afortunado te trajo aquí hoy? Rara vez vemos hombres tan finos en Tortuga.";
		link.l1 = "Hola a ti también, mademoiselle, eres capaz de hacerme sonrojar con tus cumplidos. Soy capitán de mi propio barco y un hombre ocupado, pero estoy seguro de que esta isla puede ofrecer suficiente para que un aventurero como yo se mantenga entretenido.";
		link.l1.go = "girl_6";
		break;

	case "girl_6":
		dialog.text = "(risita) Oh sí señor, ¡estoy segura de que podemos ayudar con eso! Tortuga siempre tiene algo que ofrecer. Como yo... Bueno, soy capaz de hacer casi *cualquier cosa* después de escuchar una buena historia de mar. ¡Me encantan tanto! Un capitán una vez me contó una historia fantástica sobre cómo logró escapar de ser abandonado en una isla desierta haciendo una balsa con tortugas marinas. ¡Qué valiente! ¿Podrías tú?";
		link.l1 = "¿Podría qué?";
		link.l1.go = "girl_7";
		break;

	case "girl_7":
		dialog.text = "(risita) ¿Podrías hacer una balsa con tortugas marinas?";
		link.l1 = "Haré algo mejor. Una vez, siendo un aprendiz fugitivo, capturé el barco más rápido de la Armada Inglesa usando solo un hacha. También puedo contener la respiración durante diez minutos. ¿Quieres verlo?";
		link.l1.go = "girl_8";
		break;

	case "girl_8":
		dialog.text = "Tal vez más tarde. Trabajo como sirviente en el palacio de nuestro gobernador. Ven allí a las seis en punto esta noche y encuéntrame a mí y a mi amigo en el cenador. Entonces podrás contarnos todas tus aventuras...";
		link.l1 = "Parece una invitación a mostrar y contar que no puedo rechazar. Te veo a las seis esta noche.";
		link.l1.go = "girl_9";
		link.l2 = "¿Colarse en el palacio del gobernador? Suena un poco arriesgado para mi gusto. Paso, querida. Encuéntrame en la taberna si quieres la compañía de un verdadero hombre. ¡Yo ho ho!";
		link.l2.go = "girl_exit_2";
		break;

	case "girl_exit_2":
		dialog.text = "Ph-f. Lo que sea, encontraré a un hombre mejor y más grande que tú entonces. Tu bragueta se ve demasiado pequeña después de todo. Buen viaje.";
		link.l1 = "Incluso un acorazado parecería pequeño al navegar por tu Paso de Barlovento.";
		link.l1.go = "girl_exit_1";
		break;

	case "girl_9":
		dialog.text = "¡Lo espero con ansias!";
		link.l1 = "...";
		link.l1.go = "girl_10";
		break;

	case "girl_10":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 40.0);
		npchar.lifeday = 0;
		pchar.questTemp.FMQT = "begin_bedroom";
		FMQT_Begin();
		AddQuestRecord("FMQ_Tortuga", "2");
		break;

	case "wife":
		DelLandQuestMark(npchar);
		PlaySound("Voice\Spanish\LE\Marselina\Marselina_Levasser_01.wav");
		dialog.text = "¡Ah, ahí estás! Capitán " + GetFullName(pchar) + "¡Me alegra tanto conocerte, ha pasado un tiempo desde que he sido honrado por un visitante de tal nobleza y estatura!";
		link.l1 = "Es un gran honor y placer para mí estar aquí en su compañía, señora. Pero, ¿qué hay de los demás invitados? ¿He llegado demasiado pronto?";
		link.l1.go = "wife_1";
		break;

	case "wife_1":
		dialog.text = "¡Oh, están indispuestos y no pueden venir! Pero no pensemos en ellos, bebamos vino y hablemos... ¡Ah, si supieras cuán aburrida y sola me siento aquí! ¡Tortuga es un antro sórdido lleno de escoria, villanos y piratas! ¡Piratas! Y, por fin, ¡un caballero digno en mi casa! ¡Ojalá mi esposo hiciera más negocios con hombres de tu clase y talento! Pero no, nada más que piratas, ¡piratas por todas partes! ¿Has oído hablar de esa nueva moda que se está haciendo popular en París en la Corte Real de Su Majestad? ¿Cuál es tu opinión al respecto?";
		link.l1 = "Lo siento, ¿mi opinión sobre qué exactamente? ¿Piratas? ¿O moda?";
		link.l1.go = "wife_2";
		break;

	case "wife_2":
		dialog.text = "¡Oh señor, me entiende tan bien! Ni siquiera puedo creer esto. ¡Mi marido me da centavos mientras él hace MILLONES con sus piratas, imagínese eso! ¡Piratas! Tengo que pedir que me traigan vestidos a este agujero sucio, pero cuando llegan aquí ya están seis meses pasados de moda. ¿Cómo puede una mujer de mi estatus vestir tales harapos? ¡Oh, cuánto deseo ver y llevar esas modas de París! ¿Cree usted que me vería encantadora con ellas?";
		link.l1 = "Madame, usted luce bastante encantadora. No necesita modas de París para esto, ya es obvio para todos los hombres de esta hermosa isla.";
		link.l1.go = "wife_3";
		break;

	case "wife_3":
		dialog.text = "Eres demasiado amable conmigo... Capitán, debo confesar, estoy en un gran apuro. Pero ayudarás a una pobre mujer, ¿verdad?";
		link.l1 = "Claro, señora. Lo que desee.";
		link.l1.go = "wife_4";
		break;

	case "wife_4":
		dialog.text = "Con cuidado, monsieur capitán, ¡o perderé la cabeza! (risita coqueta) Mi esposo no me da ni un solo céntimo últimamente. ¡Ese bruto trae rameras comunes a nuestra casa y no me presta atención en absoluto!\nSé dónde guarda parte de su tesoro mal habido, está en un cofre en su oficina. Este es mi dinero por derecho de esposa y mujer. Ayúdame a conseguir lo que me debe y serás recompensado... Con oro y... otras cosas deliciosas.";
		link.l1 = "Esa es una oferta intrigante. Muy bien, señora, la ayudaré. ¿Dónde está este cofre y cómo lo abro?";
		link.l1.go = "wife_5";
		link.l2 = "Muy bien, señora, le conseguiré el contenido del cofre. Obtendremos el dinero y tendremos una 'conversación' muy agradable después. ¿Qué hombre puede rechazar tal oferta? ¿Dónde está este cofre y cómo abrirlo?";
		link.l2.go = "wife_6";
		link.l3 = "Señora, está tratando de seducirme. Lo siento, pero mi honor exige que rechace su oferta. Tiene mis simpatías, merece algo mejor, pero tendrá que encontrar otro actor para su obra.";
		link.l3.go = "wife_exit";
		break;

	case "wife_exit":
		dialog.text = "Lástima. No tenemos nada más de qué hablar entonces, monsieur. ¡Vete y recuerda: si le dices una palabra de esto a mi esposo, lo lamentarás!";
		link.l1 = "Adiós.";
		link.l1.go = "wife_exit_1";
		break;

	case "wife_exit_1":
		DialogExit();
		chrDisableReloadToLocation = false;
		DeleteAttribute(pchar, "questTemp.FMQT.Common");
		LAi_CharacterDisableDialog(npchar);
		npchar.lifeday = 0;
		pchar.questTemp.FMQT = "huber";
		pchar.quest.FMQT_late1.win_condition.l1 = "Timer";
		pchar.quest.FMQT_late1.win_condition.l1.date.hour = 18.0;
		pchar.quest.FMQT_late1.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
		pchar.quest.FMQT_late1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
		pchar.quest.FMQT_late1.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
		pchar.quest.FMQT_late1.function = "FMQT_HuberTime";
		AddQuestRecord("FMQ_Tortuga", "4");
		break;

	case "wife_5":
		pchar.questTemp.FMQT.Honour = "true"; // вар 1
		dialog.text = "No esperaba esto de ti... El cofre... Déjalo para después, primero, debemos encontrar una llave duplicada que fue robada por un sucio pirata. Ahora mismo está de juerga en la taberna, bebiendo como un cerdo. Date prisa y tráeme la llave duplicada. Estaré esperándote.";
		link.l1 = "¡No perdamos tiempo entonces!";
		link.l1.go = "wife_7";
		break;

	case "wife_6":
		pchar.questTemp.FMQT.Bed = "true"; // вар 2
		dialog.text = "No te arrepentirás de esto, capitán. Primero, debemos encontrar una llave duplicada que fue robada por un sucio pirata. Ahora mismo está de parranda en la taberna, bebiendo como un cerdo. Date prisa y tráeme la llave duplicada. Te estaré esperando.";
		link.l1 = "¡No perdamos tiempo entonces!";
		link.l1.go = "wife_7";
		break;

	case "wife_7":
		DialogExit();
		LAi_CharacterDisableDialog(npchar);
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "FMQT_PirateInTavern", 10.0);
		pchar.quest.FMQT_late2.win_condition.l1 = "Timer";
		pchar.quest.FMQT_late2.win_condition.l1.date.hour = 0.0;
		pchar.quest.FMQT_late2.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
		pchar.quest.FMQT_late2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
		pchar.quest.FMQT_late2.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
		pchar.quest.FMQT_late2.function = "FMQT_TavernTime";
		AddQuestRecord("FMQ_Tortuga", "6");
		break;

	case "wife_8":
		DelLandQuestMark(npchar);
		PlaySound("Voice\Spanish\LE\Marselina\Marselina_Levasser_01.wav");
		dialog.text = "Capitán " + GetFullName(pchar) + "¡Vaya, vaya! ¡Qué hombre en mis aposentos privados! ¿Estás sorprendido? Eres el único invitado aquí esta noche. (risita)";
		link.l1 = "Me sorprende, señora. Pero no me importa en absoluto. ¿Se trata de negocios o de placer?";
		link.l1.go = "wife_9";
		break;

	case "wife_9":
		dialog.text = "¡Qué enfoque tan directo! Me gustan los hombres como tú. Tengo una propuesta de negocio para ti, capitán. Encontraré la manera de compensar tus esfuerzos si tienes éxito.";
		link.l1 = "Sigue.";
		link.l1.go = "wife_10";
		break;

	case "wife_10":
		dialog.text = "Ah... Mi esposo tiene un cofre lleno de dinero y joyas. Lo odio y quiero una asignación mayor por mis sufrimientos.";
		link.l1 = "Madame, os veis encantadora. No necesitáis más joyas ni modas de París para esto, ya es obvio para todos los hombres en La Española.";
		link.l1.go = "wife_11";
		break;

	case "wife_11":
		dialog.text = "Eres demasiado amable conmigo... Capitán, debo confesar que estoy en un gran apuro. ¿Ayudarás a una mujer en apuros?";
		link.l1 = "Por supuesto, madame. El honor lo exige. Todo lo que desees.";
		link.l1.go = "wife_12";
		break;

	case "wife_12":
		dialog.text = "¡Cuidado, monsieur capitán, o perderé la cabeza! (risita coqueta) Mi esposo no me da ni un centavo últimamente. ¡Ese bruto trae a casa a rameras comunes y no me presta atención en absoluto!\nSé dónde guarda parte de su tesoro mal habido, está en un cofre en su oficina. Este es mi dinero por derecho de esposa y mujer. Ayúdame a obtener lo que me debe y serás recompensado... Con oro y... otras cosas deliciosas.";
		link.l1 = "Está bien. Lo haré. ¿Dónde está este cofre y cómo lo abro?";
		link.l1.go = "wife_13";
		link.l2 = "¡Ja! No hay dudas, puedo hacer eso por una mujer como tú. No te arrepentirás, querida. Conseguiremos el dinero y pasaremos un tiempo muy agradable juntos. ¿Dónde está este cofre y cómo lo abro?";
		link.l2.go = "wife_14";
		link.l3 = "No yo, madame. No soy un caballero para tanto cornudo como robar a un hombre en una noche. No de esta manera, de todos modos. Encuentra otro intérprete para esta obra.";
		link.l3.go = "wife_exit_2";
		break;

	case "wife_13":
		pchar.questTemp.FMQT.Honour = "true"; // вар 1
		dialog.text = "Oh... Me gustas cada vez más... Primero, deberíamos devolver una llave duplicada que fue robada por un pirata inmundo. Él está de juerga en su guarida, bebiendo como un cerdo. Apresúrate y tráeme el duplicado. Estaré esperando.";
		link.l1 = "¡No perdamos el tiempo entonces!";
		link.l1.go = "wife_7";
		break;

	case "wife_14":
		pchar.questTemp.FMQT.Bed = "true"; // вар 2
		dialog.text = "Mantén la calma, monsieur, habrá tiempo para eso más tarde. (risita) Primero, debemos devolver una llave duplicada que fue robada por un sucio pirata. Está de juerga en su guarida, bebiendo como un cerdo. Date prisa y tráeme el duplicado. Estaré esperándote. ¿Seguro que puedes manejar eso?";
		link.l1 = "No me dudes, ya estoy en camino.";
		link.l1.go = "wife_7";
		break;

	case "wife_exit_2":
		dialog.text = "¡Bastardo mojigato! ¡Fuera de mi vista! Y ni se te ocurra contarle a mi marido sobre esto o lo lamentarás.";
		link.l1 = "Adiós, cariño.";
		link.l1.go = "wife_exit_1";
		break;

	case "wife_15":
		DelLandQuestMark(npchar);
		pchar.quest.FMQT_late3.over = "yes";
		dialog.text = "¡Capitán! ¿Conseguiste la llave?";
		link.l1 = "Sí, lo tengo. ¿Dónde está el cofre?";
		link.l1.go = "wife_16";
		break;

	case "wife_16":
		dialog.text = "¡Oh! ¿Mi vil esposo realmente va a recibir lo que merece? ¡Eres un hombre increíble, capitán! Tienes un gran futuro por delante, ¿lo sabes? Olvídate del cofre. Lo haré yo misma. Ven a verme mañana para recibir tu recompensa. No te arrepentirás, capitán...";
		link.l1 = "Bien. Como quieras. Espero verte mañana.";
		link.l1.go = "wife_17";
		link.l2 = "No, soy un hombre ocupado y no quiero perder tiempo esperando. ¿Por qué esperar? Dime lo que hay que hacer y lo haré. No puedo permitir que una mujer tan hermosa estropee sus delicadas manos trasteando con una cerradura y llave.";
		link.l2.go = "wife_18";
		break;

	case "wife_17":
		RemoveItems(pchar, "kaleuche_key", 1);
		ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key");
		dialog.text = "Ven a verme antes de las seis, mi valiente caballero...";
		link.l1 = "...";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("FMQT_Deceive");
		break;

	case "wife_18":
		dialog.text = "¿Estás seguro? Podría ser peligroso para ti. ¿Por qué quieres arriesgar tu vida, capitán?";
		link.l1 = "Está bien. Como quieras. Espero verte mañana.";
		link.l1.go = "wife_17";
		link.l2 = "Ya he tomado mi decisión. ¿Qué debo hacer exactamente?";
		link.l2.go = "wife_19";
		break;

	case "wife_19":
		dialog.text = "¡Un corazón de león!... Ve a la oficina de mi esposo, encontrarás el cofre allí. Usa la llave duplicada. No hay nadie allí a esta hora de la noche, así que tómate tu tiempo. Hay... diamantes dentro de ese cofre. Un gran número de ellos. Llévalos todos y regresa a mí. Estaré esperando. No traiciones mi confianza... por favor.";
		link.l1 = "Regresaré pronto.";
		link.l1.go = "wife_20";
		break;

	case "wife_20":
		DialogExit();
		LAi_CharacterDisableDialog(npchar);
		AddQuestRecord("FMQ_Tortuga", "11");
		sld = &Locations[FindLocation("Tortuga_townhallRoom")];
		sld.private2.key = "kaleuche_key"; // допуск к сундуку
		pchar.questTemp.FMQT = "chest";
		break;

	case "wife_21":
		DelLandQuestMark(npchar);
		pchar.quest.FMQT_GemsTimeOver.over = "yes";
		PlaySound("Voice\Spanish\LE\Marselina\Marselina_Levasser_02.wav");
		dialog.text = "¡Oh, capitán! Yo... Tú... ¿Está hecho? ¡Oh, ¿y quién es éste?! ¡A-ah!";
		link.l1 = "...";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("FMQT_MercenAttackRoom");
		break;

	case "wife_22":
		dialog.text = "¡Oh, cielos! ¡Capitán, me has salvado! Tú... ¡tú eres mi héroe! Era el matón de mi esposo, ¡quería matarte! ¡Le rogué que no lo hiciera! ¿Estás herido? ¿Trajiste los diamantes?";
		link.l1 = "Ja. ¿De veras? Tu marido es un hombre celoso... Lo que sea. Al diablo con él, tengo agallas.";
		link.l1.go = "wife_23";
		break;

	case "wife_21x":
		DelLandQuestMark(npchar);
		pchar.quest.FMQT_GemsTimeOver.over = "yes";
		PlaySound("Voice\Spanish\LE\Marselina\Marselina_Levasser_02.wav");
		dialog.text = "¡Oh capitán! Yo... Tú... ¿Está hecho?";
		link.l1 = "Hubo una pequeña complicación, pero ya está resuelta. ¿Por qué estás pálida, señora? ¿Estás bien? Tengo las joyas, eso debería alegrarte, ¿no es cierto?";
		link.l1.go = "wife_23";
		break;

	case "wife_23":
		dialog.text = "¡Gracias a Dios! ¡Estoy vengado! ¡Mi caballero! ¿Cuántos diamantes había?";
		if (GetCharacterItem(pchar, "jewelry2") >= 100)
		{
			link.l1 = "Tu caballero ha regresado de su aventura con un saco lleno de botín. Dejará la mitad a su dama para que pueda comprar las mejores modas de París. He cumplido mi promesa contigo.";
			if (CheckAttribute(pchar, "questTemp.FMQT.Honour"))
				link.l1.go = "wife_25";
			else
				link.l1.go = "wife_26";
		}
		else
		{
			link.l1 = "¡Oh, había un montón de diamantes, pero no obtendrás nada! Contrataste a un asesino para matarme, ¡puta! ¿Realmente crees que compartiría contigo después de todo esto? Abre la boca sobre esto y tu esposo se enterará de tu plan para robarlo y burlarte de él. Así que cállate.";
			link.l1.go = "wife_24";
		}
		break;

	case "wife_24":
		PlaySound("Voice\Spanish\LE\Marselina\Marselina_Levasser_03.wav");
		dialog.text = "¡Canalla! ¡Bastardo! ¡No te saldrás con la tuya!";
		link.l1 = "Sí, he oído eso antes.";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("FMQT_FinalNoJewelry");
		break;

	case "wife_25":
		RemoveItems(pchar, "jewelry2", 100);
		Log_Info("Has entregado diamantes");
		PlaySound("interface\important_item.wav");
		dialog.text = "No eres como... el resto de ellos. Consigues lo que quieres. Tienes un futuro brillante por delante. Sé que eres un hombre ocupado pero... ¿Te quedarás conmigo un rato? Nadie nos molestará, lo prometo.";
		link.l1 = "Siempre tengo tiempo para una mujer hermosa como tú. ¿Debería abrir una botella del vino de tu esposo?";
		link.l1.go = "wife_sex";
		break;

	case "wife_sex":
		DialogExit();
		LAi_SetActorType(npchar);
		pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1;
		DoQuestCheckDelay("PlaySex_1", 1.0);

		// Rebbebion, для "Путеводной звезды"
		pchar.questTemp.FMQT.GiveDiamonds = true;
		pchar.questTemp.FMQT.Marceline = "Fuck";
		break;

	case "wife_26":
		RemoveItems(pchar, "jewelry2", 100);
		Log_Info("Has entregado diamantes");
		PlaySound("interface\important_item.wav");
		dialog.text = "Creo que puedo vivir sin ellos. Hay muchas opciones para gastar dinero aquí. Tantos hombres apuestos y dignos en Tortuga... Gracias por todo, capitán. Sólo para que sepas, por favor mantén en secreto este asunto o mi marido te verá colgado de una horca. No es un buen hombre. Adiós.";
		link.l1 = "¿Así sin más? Fue una experiencia instructiva. Adiós, señora, le sugiero que también guarde silencio sobre esto, yo tampoco soy un buen hombre. Pero ya lo sabe, ¿verdad?";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("FMQT_FinalNoSex");

		// Rebbebion, для "Путеводной звезды"
		pchar.questTemp.FMQT.GiveDiamonds = true;
		pchar.questTemp.FMQT.Marceline = "NoFuck";
		break;

	case "wife_27":
		PlaySound("Voice\Spanish\Girls_2.wav");
		dialog.text = "¿Quién eres y qué haces aquí?";
		link.l1 = "¿A qué estás jugando? Teníamos un trato...";
		link.l1.go = "wife_28";
		break;

	case "wife_28":
		dialog.text = "¿Qué trato, monsieur? ¡Soy una mujer casada, no hago negocios con otros hombres! ¡Sal de mis aposentos ahora o llamaré a mi esposo y a sus guardias!";
		link.l1 = "¿Así nomás, eh? Muy bien, creo que iluminaré a tu buen esposo en ese caso.";
		link.l1.go = "wife_29";
		break;

	case "wife_29":
		dialog.text = "¡Sal ahora, insolente, o mis hombres te arrojarán al calabozo del Fuerte La Roche! ¡No me importan tus amenazas! ¡Fuera!";
		link.l1 = "...";
		link.l1.go = "wife_30";
		break;

	case "wife_30":
		DialogExit();
		DoQuestReloadToLocation("Tortuga_town", "reload", "reload3", "FMQT_FinalFail");
		pchar.questTemp.FMQT.Marceline = "Deception"; // Rebbebion, для "Путеводной звезды"
		break;

	case "pirate":
		DelLandQuestMark(npchar);
		PlaySound("Voice\Spanish\EvilPirates07.wav");
		pchar.quest.FMQT_late2.over = "yes";
		FreeSitLocator("Tortuga_tavern", "sit_base2");
		dialog.text = "¿Quién eres tú? Ah, lo que sea. No confíes en las mujeres, amigo. Es como dice la Biblia... incluso la más tonta de las busconas puede arrastrarte al fondo del Infierno con sus mani-mani-ipulaciones. ¡Toma asiento, compañero, y tómate una copa!";
		link.l1 = "¡Con mucho gusto!";
		link.l1.go = "pirate_1x";
		break;

	case "pirate_1x":
		DialogExit();
		LAi_Fade("", "");
		ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "sit", "sit_base2");
		LAi_SetSitType(pchar);
		npchar.Dialog.currentnode = "pirate_1";
		LAi_SetActorType(npchar);
		LAi_ActorSetSitMode(npchar);
		LAi_ActorDialogDelay(npchar, pchar, "", 2.0);
		break;

	case "pirate_1":
		PlaySound("Voice\Spanish\EvilPirates08.wav");
		dialog.text = "¿Qué estás mirando? ¡Sírveme ya!";
		link.l1 = "¡Por ti!.. Oye amigo, no voy a perder el tiempo aquí. Necesito esa llave duplicada que tienes, sabes de qué hablo. Dámela y nos separaremos: tú seguirás bebiendo y yo seguiré ayudando a damiselas en apuros.";
		link.l1.go = "pirate_2";
		break;

	case "pirate_2":
		dialog.text = "¡Ahh, camarada! ¡No escuchaste nada de lo que acabo de decir! Debes parecer más listo de lo que realmente eres... trabajando para esa ramera. ¿Sabes quién es su esposo? Hace poco, el Gobernador Levasseur envió a su negro leal Kampacho a 'hablar' con un comerciante muy respetado. ¡El negro golpeó al pobre desgraciado hasta matarlo en su propia tienda! Este comerciante había mostrado algún tipo de falta de respeto menor a la esposa del gobernador durante un baile o algo así. Y esta misma perra me sedujo con su aspecto y sus doblones. \nLa llave duplicada existe. Solía ser un decente cerrajero en Francia, así que fue un juego de niños. Si no fuera por la hija del comandante de Lyons... nunca me habría hecho pirata. ¡Bah! ¡Al diablo con todo!";
		link.l1 = "Todo esto es muy triste, pero hablemos de negocios. ¿Dónde está la llave?";
		link.l1.go = "pirate_3";
		break;

	case "pirate_3":
		dialog.text = "¿Estás escuchando? ¡Estoy fuera del juego, camarada! ¡Fui lo suficientemente astuto para ver lo que se avecina! Me iré de este lugar para siempre tan pronto como mi barco esté listo para zarpar. Si quieres la llave, págala. No seas avaricioso aquí, creo que no necesitarás dinero muy pronto.";
		link.l1 = "Sabes, tienes razón. No quiero ser el juguete de una mujer. ¡Gracias por el consejo y que estés a salvo en el mar!";
		link.l1.go = "pirate_4";
		link.l2 = "¿Pagar por ello? ¿A ti? Eres un ladrón patético y un cobarde. Deberías haberte quedado en ese agujero de mierda de Lyon. Quién sabe, tal vez el comandante se hubiera compadecido de ti y dejado que un ladrón degenerado fuera su yerno. No voy a compadecerme de ti, eso es seguro. Puedes darme la llave por las buenas o por las malas, la elección es tuya.";
		link.l2.go = "pirate_5";
		link.l3 = "(suspiro) ¿Cuánto?";
		link.l3.go = "pirate_6";
		break;

	case "pirate_4":
		dialog.text = "Listo, muchacho astuto, esa es la decisión correcta, camarada. Buena suerte. Espero que encuentres una mujer verdadera y amorosa algún día. Preferiblemente una pelirroja o una rubia, ¿verdad?";
		link.l1 = "Adiós, camarada...";
		link.l1.go = "pirate_exit";
		break;

	case "pirate_exit":
		DialogExit();
		LAi_CharacterDisableDialog(npchar);
		LAi_Fade("", "");
		ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "tables", "stay8");
		LAi_SetPlayerType(pchar);
		pchar.questTemp.FMQT = "huber";
		pchar.quest.FMQT_late1.win_condition.l1 = "Timer";
		pchar.quest.FMQT_late1.win_condition.l1.date.hour = 18.0;
		pchar.quest.FMQT_late1.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
		pchar.quest.FMQT_late1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
		pchar.quest.FMQT_late1.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
		pchar.quest.FMQT_late1.function = "FMQT_HuberTime";
		AddQuestRecord("FMQ_Tortuga", "9");
		break;

	case "pirate_5":
		dialog.text = "¡Me insultas! ¡Saca el acero, bastardo!";
		link.l1 = "¡Veamos qué tan bien puedes abrir cajas fuertes sin brazos!";
		link.l1.go = "pirate_duel";
		break;

	case "pirate_duel":
		DialogExit();
		LAi_SetSitType(npchar);
		// ключ квестовый от Калеуче - вернуть назад
		GiveItem2Character(npchar, "kaleuche_key");
		ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key_FMQT");
		i = makeint(MOD_SKILL_ENEMY_RATE / 4);
		pchar.questTemp.FMQT = "duel";
		PChar.questTemp.duel.enemy = NPChar.id;
		if (MOD_SKILL_ENEMY_RATE > 2)
			PChar.questTemp.duel.enemyQty = i;
		AddDialogExitQuestFunction("Duel_Prepare_Fight");
		break;

	case "pirate_6":
		dialog.text = "Eres un hombre de negocios, te concedo eso. Podrías lograrlo. Cincuenta doblones. Sobre la mesa.";
		link.l1 = "Cincuenta piezas de oro? ¿Por un pedazo de hojalata? Que me arrastren por la quilla. Pon la llave en la mesa. Ahora.";
		link.l1.go = "pirate_7";
		if (PCharDublonsTotal() >= 50)
		{
			link.l2 = "Vaya precio... Está bien. Llévalos.";
			link.l2.go = "pirate_8";
		}
		else
		{
			link.l2 = "Vaya precio... Está bien.  Los traeré pronto. Quédate aquí.";
			link.l2.go = "pirate_wait";
		}
		break;

	case "pirate_wait":
		DialogExit();
		AddLandQuestMark(npchar, "questmarkmain");
		LAi_SetSitType(npchar);
		npchar.Dialog.currentnode = "pirate_dublon";
		LAi_Fade("", "");
		ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "tables", "stay8");
		LAi_SetPlayerType(pchar);
		break;

	case "pirate_dublon":
		NextDiag.TempNode = "pirate_dublon"; // mitrokosta правка явного бага
		dialog.text = "¿Trajiste cincuenta doblones?";
		link.l1 = "Sabes, creo que puedes vivir sin ellos. La llave. En la mesa.";
		link.l1.go = "pirate_7";
		if (PCharDublonsTotal() >= 50)
		{
			link.l2 = "Sí. Llévalos.";
			link.l2.go = "pirate_8";
		}
		else
		{
			link.l2 = "Todavía los estoy consiguiendo.";
			link.l2.go = "exit";
		}
		break;

	case "pirate_7":
		dialog.text = "¿Bailamos?";
		link.l1 = "Yo lideraré.";
		link.l1.go = "pirate_duel";
		break;

	case "pirate_8":
		DelLandQuestMark(npchar);
		RemoveDublonsFromPCharTotal(50);
		Log_Info("Has entregado 50 doblones");
		PlaySound("interface\important_item.wav");
		dialog.text = "Bien. Usa tu cerebro y tal vez salgas de esto con algunos reales de a ocho y tu cabeza. Toma la llave y escucha mi consejo. Gratis. La mujer de Levasseur es tan tonta como un pez, pero se cree astuta. No confíes en ella. Mantén tu gallo en los pantalones y vigila tus bolsillos. No es gran oponente, solo ten cuidado y evita involucrar a su esposo en esto\nUna última cosa: hay un cofre en su aposento donde guarda sus baratijas, fácil de forzar. Ella pondrá su parte allí. Me escuchaste. Que los mares te sean seguros, hermano. Recuerda, los hermanos antes que las fulanas.";
		link.l1 = "Buen viento, camarada...";
		link.l1.go = "pirate_9";
		break;

	case "pirate_9":
		DialogExit();
		LAi_CharacterDisableDialog(npchar);
		LAi_Fade("", "");
		ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "tables", "stay8");
		LAi_SetPlayerType(pchar);
		pchar.questTemp.FMQT = "key";
		pchar.questTemp.FMQT.Caution = "true";
		FMQT_KeyNextDay();
		pchar.quest.FMQT_late3.win_condition.l1 = "Timer";
		pchar.quest.FMQT_late3.win_condition.l1.date.hour = sti(GetTime());
		pchar.quest.FMQT_late3.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
		pchar.quest.FMQT_late3.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
		pchar.quest.FMQT_late3.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
		pchar.quest.FMQT_late3.function = "FMQT_KeyTime";
		AddQuestRecord("FMQ_Tortuga", "10");
		// ключ квестовый от Калеуче - вернуть назад
		GiveItem2Character(pchar, "kaleuche_key");
		ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key_FMQT");
		break;

	case "mercen":
		PlaySound("Voice\Spanish\EvilPirates09.wav");
		dialog.text = "¡Maldita sea! No esperaba... ¡al diablo con esa mujer! Mi maestro me dijo que evitara su tipo. Pero un trabajo es un trabajo. Te atraparé después de todo.";
		link.l1 = "Bueno bueno, camarada... Parece que ella quería engañarnos a ambos, no puedo decir que me sorprenda. ¿Por qué deberíamos seguir peleando? ¿Quieres un trabajo? Tengo uno. Tienes habilidad, necesito hombres como tú en mi tripulación. Comida, litera, salario regular, ron y una parte justa de cualquier botín. Te daré mi palabra de honor sobre ello. ¿Qué dirás?";
		// if(CheckCharacterPerk(pchar, "IronWill") || CheckCharacterPerk(pchar, "HT2") || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34 || GetSummonSkillFromName(pchar, SKILL_FORTUNE) > 20) link.l1.go = "mercen_1";
		if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34)
			link.l1.go = "mercen_1";
		else
			link.l1.go = "mercen_4";
		break;

	case "mercen_1":
		// if(CheckCharacterPerk(pchar, "IronWill")) notification("Iron Will", "IronWill");
		// if(CheckCharacterPerk(pchar, "HT2")) notification("Mimicry", "Mimicry");
		if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34)
			notification("Skill Check Passed", SKILL_LEADERSHIP);
		// if(GetSummonSkillFromName(pchar, SKILL_FORTUNE) > 20) notification("Skill Check Passed", SKILL_FORTUNE);
		dialog.text = "Tienes una lengua de plata y tu fama te precede, capitán, te lo concedo. Aye, estoy dentro. ¿Cómo se llama tu barco?";
		link.l1 = "'" + pchar.ship.name + "'. Habla con el contramaestre, él te encontrará un camarote. ¡Bienvenido a bordo!";
		link.l1.go = "mercen_2";
		break;

	case "mercen_2":
		dialog.text = "¡Ja! Estoy ascendiendo en el mundo. Dale una patada a esa perra de mi parte.";
		link.l1 = "...";
		link.l1.go = "mercen_3";
		break;

	case "mercen_3":
		DialogExit();
		LAi_group_Delete("EnemyFight");
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "FMQT_MercenHire", 10.0);
		AddQuestRecord("FMQ_Tortuga", "17");
		break;

	case "mercen_4":
		// if(!CheckCharacterPerk(pchar, "IronWill")) notification("Perk check failed", "IronWill");
		if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 35)
			notification("Skill Check Failed (35)", SKILL_LEADERSHIP);
		// if(GetSummonSkillFromName(pchar, SKILL_FORTUNE) < 21) notification("Skill Check Failed (21)", SKILL_FORTUNE);
		dialog.text = "Hablas bonito. Pero no lo suficiente si quieres que verdaderos profesionales se unan a tus filas. Tenlo en cuenta en el futuro. Si es que lo tienes.";
		link.l1 = "Inténtalo. Sé rápido, tengo un compromiso con una dama.";
		link.l1.go = "mercen_5";
		link.l2 = "Hoy no hay segundas oportunidades. Soy un hombre ocupado, así que no arruinemos la alfombra. No te pagan lo suficiente como para morir por alguna puta de poca monta. Si es que te pagan algo en absoluto.";
		link.l2.go = "mercen_6";
		break;

	case "mercen_5":
		DialogExit();
		LAi_SetCurHPMax(npchar);
		LAi_GetCharacterMaxEnergy(npchar);
		LAi_SetImmortal(npchar, false);
		LAi_SetWarriorType(npchar);
		LAi_group_MoveCharacter(npchar, "EnemyFight");
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "FMQT_MercenDie");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "mercen_6":
		dialog.text = "Tienes razón. Nadie me ha pagado... todavía. Arreglaré esto ahora mismo. Haz lo que quieras...";
		link.l1 = "...";
		link.l1.go = "mercen_7";
		break;

	case "mercen_7":
		DialogExit();
		LAi_SetCurHPMax(npchar);
		LAi_GetCharacterMaxEnergy(npchar);
		LAi_group_Delete("EnemyFight");
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
		AddQuestRecord("FMQ_Tortuga", "18");
		pchar.questTemp.FMQT.Roomfight = "true";
		FMQT_WifeFinalTalk();
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}
