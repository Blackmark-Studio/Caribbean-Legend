// диалоги НПС по квесту НСО
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
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
			dialog.text = "¿Qué estás buscando?";
			link.l1 = "Nada.";
			link.l1.go = "exit";
		break;
		
		// инспектор Ноэль Форже
		case "noel":
			dialog.text = "¡Encantado de conocerte, capitán!";
			link.l1 = "Me alegra conocerte también, monsieur Forget. Es una ocasión rara encontrarse con un invitado de la metrópolis aquí en el desierto...";
			link.l1.go = "noel_1";
		break;
		
		case "noel_1":
			DialogExit();
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_3";
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "noel_2":
			dialog.text = "Me complace que durante este viaje estaré en su barco, capitán. Chevalier de Poincy me contó muchas historias interesantes sobre usted. Estoy seguro de que después de la cena en el comedor tendremos muchos temas de los que hablar. Una copa de vino también podría ser útil.";
			link.l1 = "Estoy completamente dispuesto a una charla acogedora, especialmente cuando estoy lleno. Me encantaría ser tu compañero, Barón. ";
			link.l1.go = "noel_3";
		break;
		
		case "noel_3":
			dialog.text = "Perfecto. Cuando vayamos a una colonia, te pediré que me guíes hasta el gobernador, y yo personalmente le explicaré lo que se debe hacer. Solo esperarás hasta que termine mis asuntos. ¿Trato?";
			link.l1 = "¡Aye, monsieur Forget. Bienvenido a bordo!";
			link.l1.go = "noel_4";
		break;
		
		case "noel_4":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 12.0);
		break;
		
		case "noel_5":
			dialog.text = "Tortuga es una pequeña colonia, capitán. Estimo que me tomará unos tres días inspeccionar todo lo que necesito en esta isla.";
			link.l1 = "Entendido, Barón. Entonces, en tres días vendré aquí a recogerle. ¡Buena suerte!";
			link.l1.go = "noel_6";
		break;
		
		case "noel_6":
			DialogExit();
			DoQuestReloadToLocation("Tortuga_town", "reload", "reload3", "Patria_VisiterTortuga");
		break;
		
		case "noel_7":
			dialog.text = "Mi trabajo en Tortuga está hecho, es hora de izar el ancla.";
			link.l1 = "Entendido, Barón. Nos pondremos en marcha de inmediato.";
			link.l1.go = "noel_8";
		break;
		
		case "noel_8":
			DialogExit();
			Patria_VisiterTortugaSail();
		break;
		
		case "noel_9":
			dialog.text = "Sí, sí, definitivamente informaremos sobre esto en Capsterville. La amenaza de que una colonia tan importante sea conquistada... impensable, ¡me aseguraré personalmente de que el Chevalier de Poincy tome medidas estrictas y despiadadas! Capitán, permaneceré una semana en esta isla, hay muchas plantaciones aquí, tomará algo de tiempo.";
			link.l1 = "Entendido, Barón. Te esperaré junto al palacio del gobernador en siete días. ¡Diviértete y no te esfuerces demasiado!";
			link.l1.go = "noel_10";
		break;
		
		case "noel_10":
			DialogExit();
			DoQuestReloadToLocation("PortPax_town", "reload", "reload3", "Patria_VisiterPortPax");
		break;
		
		case "noel_11":
			dialog.text = "Ahí estás, capitán. Mi trabajo en La Española está hecho. Es hora de levar anclas.";
			link.l1 = "Entendido, Barón. Nos pondremos en marcha de inmediato.";
			link.l1.go = "noel_12";
		break;
		
		case "noel_12":
			DialogExit();
			Patria_VisiterPortPaxSail();
		break;
		
		case "noel_13":
			dialog.text = "Capitán, esta isla me parece familiar. ¿No es San Cristóbal?";
			link.l1 = "Sí, barón, precisamente. Estamos casi allí.";
			link.l1.go = "noel_14";
		break;
		
		case "noel_14":
			dialog.text = "¿Casi llegamos?! ¿No se suponía que también íbamos a visitar Saint-Martin? También pertenece a las colonias francesas.";
			link.l1 = "¿Te refieres a Sint Maarten? Es una colonia holandesa, monsieur Forget.";
			link.l1.go = "noel_15";
		break;
		
		case "noel_15":
			dialog.text = "¿De veras? En París se consideraba francés. ¿Cómo es eso?";
			link.l1 = "No tengo idea, Barón. Desde que puse un pie en el archipiélago, Sint Maarten ha sido una colonia holandesa. Tal vez haya algo que no sepa. Debería considerar hablar con el Caballero de Poincy sobre este asunto.";
			link.l1.go = "noel_16";
		break;
		
		case "noel_16":
			dialog.text = "Está bien, capitán, que así sea. De todos modos, estamos casi en Capsterville.";
			link.l1 = "...";
			link.l1.go = "noel_17";
		break;
		
		case "noel_17":
			DialogExit();
			Island_SetReloadEnableGlobal("Nevis", true);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			pchar.quest.Patria_visiter_fin.win_condition.l1 = "location";
			pchar.quest.Patria_visiter_fin.win_condition.l1.location = "Charles_Roomtownhall";
			pchar.quest.Patria_visiter_fin.function = "Patria_VisiterFin";
			pchar.questTemp.Patria = "epizode_2_return";
		break;
		
		case "noel_18":
			dialog.text = TimeGreeting()+", capitán. Me alegra verte. He oído que te ascendieron, ¡por favor acepta mis felicitaciones! Para decirte la verdad, realmente eres uno de los oficiales más sensatos y talentosos al servicio de de Poincy.";
			link.l1 = "Gracias, monsieur.";
			link.l1.go = "noel_19";
		break;
		
		case "noel_19":
			dialog.text = "Finalmente, solo queda una colonia entonces, Saint-Martin. Para ser honesto, me he cansado de estos viajes. Me alegraré de terminar esta inspección y empezar a organizar la próxima campaña comercial de las Antillas Francesas. ¿Estamos listos para levar anclas?";
			link.l1 = "¡Aye, Barón. Súbete a bordo!";
			link.l1.go = "noel_20";
		break;
		
		case "noel_20":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_SanMartinBaron", 5.0);
		break;
		
		case "noel_21":
			dialog.text = "Capitán, ¿podría decirme qué acaba de pasar? ¿Significa esto una guerra? ¿Por qué demonios casi fuimos hundidos por los holandeses?";
			link.l1 = "Barón, ¡yo mismo no entiendo nada! Esto debe ser algún tipo de malentendido, sin duda.";
			link.l1.go = "noel_22";
		break;
		
		case "noel_22":
			dialog.text = "¡Capitán, puedo apostar que este 'malentendido' tiene nombre! ¡Peter Stuyvesant, el llamado 'arrendador' de Saint-Martin y socio de nuestro querido Chevalier de Poincy!";
			link.l1 = "Tengo   ni   idea, Barón.   Mejor   apresurémonos   a Capsterville y   informemos de este asunto al Gobernador General.";
			link.l1.go = "noel_23";
		break;
		
		case "noel_23":
			dialog.text = "¡Sin duda, eso es exactamente lo que haremos! ¡Y exigiré explicaciones! ¡Sabía que alquilar una isla a los holandeses era un gran error! ¡Salgamos de este lugar tan rápido como podamos, capitán, antes de que alguien decida perseguirnos!";
			link.l1 = "Precisamente, monsieur ...";
			link.l1.go = "noel_24";
		break;
		
		case "noel_24":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_SanMartinBack", 5.0);
		break;
		
		case "noel_25":
			dialog.text = "Monsieur, ¡primero permítame felicitarlo por su ascenso! Apoyé con entusiasmo la decisión de monseigneur de Poincy de otorgarle el rango de Vicealmirante. ¡Merece este título! Ahora, acabo de regresar de Saint-Martin. En los almacenes de Philipsburg, realizamos una revisión, todos los bienes holandeses fueron confiscados y ahora pertenecen al tesoro de Francia. A usted, como comandante de una operación de combate, se le ha otorgado una parte de los trofeos. Estoy de acuerdo con el Chevalier en que esto es justo. Sus bienes han sido transferidos al almacén de la tienda de St. Christopher, y puede recogerlos cuando quiera.";
			link.l1 = "Gracias, Barón. Deja que las mercancías permanezcan allí por un tiempo. Al regresar de Curazao, las recogeré.";
			link.l1.go = "noel_26";
		break;
		
		case "noel_26":
			dialog.text = "¡Buena suerte en tu próxima campaña, Vicealmirante! Estoy seguro de que regresarás con la victoria y castigarás justamente a ese sinvergüenza de Stuyvesant.";
			link.l1 = "...";
			link.l1.go = "noel_27";
		break;
		
		case "noel_27":
			DialogExit();
			pchar.questTemp.Patria = "epizode_11_start";
			AddQuestRecord("Patria", "58");
			pchar.questTemp.Patria.GoodsSM = "true";
		break;
		
		case "noel_28":
			dialog.text = "¡A quién tenemos aquí! ¡Vicealmirante Charles de Maure! ¡Me alegra verte! ¿Cuál es tu negocio en Puerto Príncipe?";
			link.l1 = "Me complace conocerte también, Barón. Estoy aquí por mi deber, tenía que hacerle una visita de cortesía al señor Jeremy Deschamps du Mussaca...";
			link.l1.go = "noel_29";
		break;
		
		case "noel_29":
			dialog.text = "Este encuentro es muy afortunado, de hecho, porque he estado esperando mucho tiempo para reunirme contigo personalmente. Quiero hablar contigo, pero no aquí.";
			link.l1 = "Entonces, vamos a la taberna, ¿vale?";
			link.l1.go = "noel_30";
		break;
		
		case "noel_30":
			DialogExit();
			FreeSitLocator("PortPax_tavern", "sit_base1");
			DoQuestReloadToLocation("PortPax_tavern", "sit", "sit_base1", "Patria_CondotierTavern");
		break;
		
		case "noel_31":
			LAi_SetSitType(pchar);
			dialog.text = "No hay oídos no deseados aquí, podemos hablar con seguridad...";
			link.l1 = "Soy todo oídos, Barón.";
			link.l1.go = "noel_32";
		break;
		
		case "noel_32":
			dialog.text = "Vicealmirante, parece ser un hombre de honor. Un oficial naval tan valiente debe ser así...";
			link.l1 = "Hmm... No creo que te entienda completamente, monsieur... ";
			link.l1.go = "noel_33";
		break;
		
		case "noel_33":
			dialog.text = "Monsieur de Maure, quería preguntarle: ¿qué piensa de su señor, el Gobernador General Philippe de Poincy?";
			link.l1 = "La obligación de un oficial no es pensar en su comandante, sino seguir sus órdenes.";
			link.l1.go = "noel_34";
		break;
		
		case "noel_34":
			dialog.text = "Oh, déjelo, Vicealmirante, no estamos en el cuartel, ni en el salón de de Poincy. Lo diré de esta manera: ¿no cree que monsieur de Poincy... abusa de su poder? Aún no puedo olvidar cómo casi nos fuimos al garete bajo los cañones del Fuerte de Saint-Martin. Estoy seguro de que la traición de los holandeses tuvo un motivo.";
			link.l1 = "Querían conquistar la isla.";
			link.l1.go = "noel_35";
		break;
		
		case "noel_35":
			dialog.text = "Sí, sí, pero ¿por qué exactamente en el mismo momento en que decidí inspeccionarlo? ¿Por qué no un mes antes? ¿O dos meses después? No creo que esto fuera una coincidencia, monseigneur. ¿No tienes ninguna sospecha? Ambos teníamos nuestras vidas en juego allí.";
			link.l1 = "Me juego la vida todos los días, monseigneur Forget. Creo que entiendes eso...";
			link.l1.go = "noel_36";
		break;
		
		case "noel_36":
			dialog.text = "Tu valentía está fuera de toda duda. Pero eso no es lo que quería decir. Verás... Cuando estaba haciendo mi trabajo en el Saint-Martin que fue liberado por ti, repetidamente escuché susurros de los lugareños sobre alguna mina en las profundidades de la isla. Intenté preguntar a la gente sobre ello, pero actuaban como tontos. Tenían miedo... Era obvio que no parecía muy confiable, pero esto solo fortaleció mis sospechas: ¿podría ser esta mina misteriosa la razón de todo esto, Monsieur de Maure? Las guerras se libran por el oro, ¿verdad?";
			link.l1 = "Hay numerosas minas en el archipiélago. La mayoría de ellas están agotadas y se volvieron inútiles. Conozco una importante mina de oro en funcionamiento, está en manos de los españoles en Tierra Firme del Sur. Pero nunca he oído hablar de la extracción de oro en Saint-Martin.";
			link.l1.go = "noel_37";
		break;
		
		case "noel_37":
			dialog.text = "¡Eres hábil en el arte de la elocuencia, Vicealmirante! Entiendo: no confías en mí. Soy nuevo aquí... Monsieur de Maure, pero soy una persona influyente en París. El Ministro de Finanzas es mi amigo cercano. Visito al Rey regularmente. Mi autoridad es mucho mayor que la de Philippe de Poincy, formalmente, por supuesto, porque aquí el Gobernador General es la persona más autorizada. Pero a decir verdad, aquí, en las colonias, la ley del más fuerte es la única ley.";
			link.l1 = "Estoy completamente de acuerdo contigo ahí.";
			link.l1.go = "noel_38";
		break;
		
		case "noel_38":
			dialog.text = "Pero no en París. Allí, las personas más influyentes son el Rey y el Ministro de Finanzas... mi amigo cercano. Monsieur de Maure, usted es un hombre militar brillante, pero creo que Phillip de Poincy lo está utilizando para sus propios propósitos personales. Usted es inteligente, así que debe tener sospechas. Puede confiar en mí. Le garantizo completa anonimidad y el apoyo de las autoridades de París. Lo juro por mi título.";
			link.l1 = "***PERMANECED LEALES A POINCY***";
			link.l1.go = "noel_39"; // развилка
			link.l2 = "***ALIARSE CON BARÓN OLVIDADO***";
			link.l2.go = "noel_53";
		break;
		
		case "noel_39":
			dialog.text = "";
			link.l1 = "Le entiendo, Monsieur Forger. Para un hombre no familiarizado con las mentalidades locales, las acciones de de Poincy pueden parecer realmente extrañas. Cuando llegué por primera vez al Archipiélago, quedé literalmente atónito por lo que estaba sucediendo aquí. Todavía recuerdo las primeras palabras que me dijeron: 'Si encuentras un barco español desprotegido, puedes intentar abordarlo.' Traición, perfidia, engaño - están presentes aquí a cada paso. Piratería, saqueo, robo...";
			link.l1.go = "noel_40";
		break;
		
		case "noel_40":
			dialog.text = "";
			link.l1 = "Estamos en paz con España en Europa. Pero aquí somos feroces enemigos. Los holandeses hoy parecen amistosos e inofensivos, y mañana el oficial de la Compañía confisca tus bienes solo porque de repente anunciaron que estaba prohibido importarlos, aunque no podías saberlo. El oficial inglés está abiertamente en la piratería, hundiendo los barcos de la Compañía, y la Compañía contrata a un asesino que se disfraza de barco fantasma, y aterroriza a los comerciantes británicos...";
			link.l1.go = "noel_41";
		break;
		
		case "noel_41":
			dialog.text = "";
			link.l1 = "En esta guarida de lobos, a veces tenemos que tomar decisiones extrañas que no son del todo obvias para alguien que no está familiarizado con todo esto. Y lo que te parece sospechoso es, de hecho, la única acción correcta. Es difícil sentarse en varias sillas a la vez y aún así lograr enviar beneficios al estado matriz. Chevalier de Poincy lo maneja a la perfección, es un administrador experimentado y un político visionario. Por supuesto, puede cometer errores, pero todos los cometemos en algún momento de nuestras vidas...";
			link.l1.go = "noel_42";
		break;
		
		case "noel_42":
			dialog.text = "";
			link.l1 = "Y necesitas arreglártelas con todo y con todos. Con las ambiciones de los españoles que creen que todo el Nuevo Mundo les pertenece, con la codicia de los comerciantes holandeses, con la fría prudencia y brutalidad despiadada de los ingleses. Y hasta con los piratas.";
			link.l1.go = "noel_43";
		break;
		
		case "noel_43":
			dialog.text = "¿¡Con piratas?!";
			link.l1 = "Sí, lo oíste bien. Los holandeses y los británicos están cooperando activamente con piratas... extraoficialmente, por supuesto. La Hermandad de la Costa es una fuerza seria que puede desafiar a cualquier nación en la región, están en conflicto constante con todos los que encuentran y nadie es capaz de detenerlos. La única cosa que los hace un poco menos peligrosos es el hecho de que están dispersos y actúan en su propio nombre. ¿Sabías que el antiguo gobernador de Tortuga, Levasseur, en realidad creó un estado dentro del estado, confiando completamente en los piratas?";
			link.l1.go = "noel_44";
		break;
		
		case "noel_44":
			dialog.text = "Creo que he oído algo sobre eso...";
			link.l1 = "Unos pocos poderosos barcos corsarios que protegían la isla estaban constantemente atracados en el puerto de Tortuga. Levasseur traicionó a Francia, convirtiéndose en una especie de autoridad. Y ahora, tras la destrucción del nido pirata en Tortuga junto con su amo, los piratas están terriblemente enfadados con los franceses...";
			link.l1.go = "noel_45";
		break;
		
		case "noel_45":
			dialog.text = "¡No me digas!";
			link.l1 = "Sí. Tuvimos que hacerlo, de lo contrario Tortuga se perdería para nosotros, aunque el resultado que obtuvimos no fue el mejor. Ningún barco comerciante francés puede sentirse seguro en el Caribe ahora. Los españoles, que tampoco tienen acuerdos con los barones piratas, al menos tienen flotas de fuertes galeones y poderosos barcos de guerra militares capaces de repeler a los filibusteros. Al igual que los holandeses con sus indios orientales y xebecs. Pero no podemos jactarnos de tal cosa, ay. Y los piratas franceses a menudo roban a los mercaderes franceses.";
			link.l1.go = "noel_46";
		break;
		
		case "noel_46":
			dialog.text = "¡Esto es una locura! ¿No hay manera de poner fin a esto?";
			link.l1 = "Muchos lo han intentado. Al final, en vez de luchar, compran su lealtad con oro. Emiten patentes de corsario, quiero decir.";
			link.l1.go = "noel_47";
		break;
		
		case "noel_47":
			dialog.text = "Mm...";
			link.l1 = "Así que, hablando por experiencia, una compañía comercial francesa aquí en el Archipiélago sería una muy mala idea. ¿Entiendes ahora con qué dificultades tendrás que enfrentarte? ¿Cuántos bastardos quieren obtener su parte del ingreso aquí? Y no van a soltarla fácilmente. Y los piratas, son capaces de cosas impensables, llámales locos si quieres, pero casi siempre logran sus sucios objetivos. Para proteger los barcos mercantes, tendrías que mantener una flota militar masiva, pero ¿será eso rentable desde el punto de vista financiero?";
			link.l1.go = "noel_48";
		break;
		
		case "noel_48":
			dialog.text = "¿Pero los comerciantes franceses se las arreglan aquí de alguna manera?";
			link.l1 = "Exactamente, de alguna manera. Especialmente ahora, cuando la fortaleza pirata de Levasseur en Tortuga ha sido tomada...";
			link.l1.go = "noel_49";
		break;
		
		case "noel_49":
			dialog.text = "Tus palabras coinciden con lo que dijo de Poincy.";
			link.l1 = "Es la verdad. Así es aquí en el archipiélago, siempre lo fue.";
			link.l1.go = "noel_50";
		break;
		
		case "noel_50":
			dialog.text = "Eres tan ansioso en lo que dices. Incluso yo no sabía mucho de esto y, tienes razón: todavía no lo sé. Supongo que mis sospechas sobre Poincy eran inválidas. Me has abierto los ojos. Te lo agradezco, Vicealmirante. Pero el ministro francés cuenta con la creación de la Compañía. El Rey necesita el dinero...";
			link.l1 = "Entiendo. Pero, por favor, considere lo que acabo de decir; si la creación de las Indias Occidentales Francesas es inevitable, entonces asegúrese de que tengamos una fuerte flota militar para protegerla.";
			link.l1.go = "noel_51";
		break;
		
		case "noel_51":
			dialog.text = "¡Vuestra gracia es verdaderamente admirable, Vicealmirante! ¡Qué noble temperamento! No me sorprende que hayáis estado aquí tanto tiempo y no os hayáis apresurado a volver a casa. Pero nos volveremos a ver: regresaré aquí en medio año. La Compañía Comercial Francesa se alzará. Y con los piratas, creo que estáis exagerando un poco. En resumen, tenemos buques de guerra y valientes capitanes, como vos.";
			link.l1 = "Lo siento, Barón, pero soy solo un hombre, y además de mí Francia solo tiene un barco fuerte en el archipiélago 'Eclatant', no será suficiente, perderemos mucho más de lo que ganaremos... Eh, cuando sea, es lo que es, supongo que pensaremos en algo mientras tanto... ¿Cuándo partirás hacia Francia?";
			link.l1.go = "noel_52";
		break;
		
		case "noel_52":
			dialog.text = "En dos semanas regresaré a San Cristóbal, y desde allí me dirigiré a casa. Monsieur de Poincy me dio un buen barco - un bergantín llamado 'Favory' y un capitán glorioso. El barco es rápido y el capitán es experimentado, pero, por supuesto, estaba más seguro contigo. Recuerdo nuestros viajes por el archipiélago, Vicealmirante, fue realmente una experiencia maravillosa.";
			link.l1 = "Gracias por tus amables palabras, Barón. Bueno, supongo que es hora de que nos separemos...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Patria_CondotierToPirates");
		break;
		
		case "noel_53":
			dialog.text = "";
			link.l1 = "Aquí todos se utilizan unos a otros. Chevalier me utilizó en sus asuntos mucho antes de que yo me convirtiera en oficial de la armada.";
			link.l1.go = "noel_54";
		break;
		
		case "noel_54":
			dialog.text = "¿Y es aceptable? ¿Qué piensas?";
			link.l1 = "No. Pero el Chevalier no me dejó opción: o seguía sus órdenes, o mi hermano quedaría tras las rejas hasta el fin de sus días, y el buen nombre de mi familia quedaría arruinado.";
			link.l1.go = "noel_55";
		break;
		
		case "noel_55":
			dialog.text = "¡Horrible! ¡Esto es puro terrorismo! ¿Tenía alguna razón para tales amenazas?";
			link.l1 = "Mi hermano tuvo la desgracia de ser su hombre de confianza. Igual que yo ahora.";
			link.l1.go = "noel_56";
		break;
		
		case "noel_56":
			dialog.text = "¿Dónde está tu hermano ahora?";
			link.l1 = "Conseguí liberarlo, pero lo perdí al día siguiente; eligió no servir más bajo el mando de nadie.";
			link.l1.go = "noel_57";
		break;
		
		case "noel_57":
			dialog.text = "¡Sabía que Poincy no era quien decía ser! ¡Lobo con piel de cordero! Vicealmirante, puede confiar en mí. Soy un hombre de honor. Y lo salvaré de este yugo de su 'patrón' si podemos encontrar pruebas tangibles de sus actividades criminales. ¿Sabe algo sobre esta aburrida historia con Stuyvesant? Hable abiertamente, y no se preocupe, usted es solo un hombre militar, y estaba obligado a cumplir sus órdenes.";
			link.l1 = "Lo sé. De hecho, hay una mina en Saint-Martin. Solo que allí no obtienen oro, sino sal. Es muy demandada por los españoles. Poincy no podía comerciar directamente con los españoles, por lo que Stuyvesant actuaba como intermediario.";
			link.l1.go = "noel_58";
		break;
		
		case "noel_58":
			dialog.text = "¿Así que Poincy y Stuyvesant son socios de negocios?";
			link.l1 = "Solía ser. Después de que expresaste el deseo de inspeccionar el Saint-Martin, el Stuyvesant decidió sacar a Poincy del juego, llevándose él mismo todas las ganancias de la mina de sal. Poincy no podía contárselo a nadie... Pero Stuyvesant calculó mal, como podemos ver.";
			link.l1.go = "noel_59";
		break;
		
		case "noel_59":
			dialog.text = "¿Crees que la mina sigue operando?";
			link.l1 = "Estoy seguro de ello. Parece que Poincy tiene un nuevo socio comercial ahora. No es otro que el mismo Coronel Doily.";
			link.l1.go = "noel_60";
		break;
		
		case "noel_60":
			dialog.text = "¿Podemos presentar alguna prueba al ministerio?";
			link.l1 = "Hmm. Durante el asalto a la mina, que, por cierto, fue llevado a cabo por españoles, no por los holandeses, capturamos al propietario. Todavía está en mi barco. Puedes hablar con él. Hay una posibilidad de que a cambio de su libertad cuente muchas cosas interesantes.";
			link.l1.go = "noel_61";
		break;
		
		case "noel_61":
			dialog.text = "Vayamos a tu barco inmediatamente. Ordena que entreguen a tu prisionero en tu camarote. Hablaré con él.";
			link.l1 = "Está bien, vamos.";
			link.l1.go = "exit";
			npchar.greeting = "noel_4";
			AddDialogExitQuestFunction("Patria_CondotierToCabin");
		break;
		
		case "noel_62":
			dialog.text = "Estupendo, Vicealmirante. Hablaré con él. Quédese aquí, por favor.";
			link.l1 = "Por supuesto...";
			link.l1.go = "noel_63";
		break;
		
		case "noel_63":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "rld", "aloc1", "", -1);
			DoQuestFunctionDelay("Patria_CondotierInCabinTalk", 3.0);
		break;
		
		case "noel_64":
			dialog.text = "Escribí todas las pruebas de tu cautivo, y él firmó bajo ellas. Ahora debemos cumplir lo que le prometí, siempre que haya una oportunidad conveniente, pasa por Cartagena y déjalo desembarcar. Pero tú mismo lo oíste todo.\n¡Ahora qué sinvergüenza es nuestro Poincy! Alquiló una isla a los holandeses, realizó actividades ilegales allí y permitió que los españoles fueran y gestionaran la mina. ¡Me temo imaginar cuánto dinero le falta al tesoro del Rey por su egoísmo!";
			link.l1 = "¿Será suficiente esa evidencia para acusar a Poincy?";
			link.l1.go = "noel_65";
		break;
		
		case "noel_65":
			dialog.text = "Lamentablemente, me temo que no lo hará. La evidencia es muy importante, pero no es suficiente. Pero no quiero que te involucres en todo esto por razones que ambos entendemos.";
			link.l1 = "El español accedió a testificar ante tu comisión cuando llegue aquí.";
			link.l1.go = "noel_66";
		break;
		
		case "noel_66":
			dialog.text = "Esto sucederá no antes de seis meses, y quién sabe qué será de este español, y si podremos encontrarlo más tarde en Cartagena... Necesitamos tener pruebas aún más valiosas. A saber - una prueba de que la mina continúa sus actividades secretas y todavía llena los bolsillos de nuestro querido gobernador general.";
			link.l1 = "¿Entonces estás sugiriendo que viajemos a Saint-Martin?";
			link.l1.go = "noel_67";
		break;
		
		case "noel_67":
			dialog.text = "Sí. ¿Sabes cómo llegar a la mina?";
			link.l1 = "Lo hago.";
			link.l1.go = "noel_68";
		break;
		
		case "noel_68":
			dialog.text = "Entonces, por la noche, tú y yo nos colaremos allí, en silencio, para que nadie nos vea, y veremos qué está pasando allí.";
			link.l1 = "Muy bien.";
			link.l1.go = "noel_69";
		break;
		
		case "noel_69":
			dialog.text = "¿Pero qué hay del Chevalier, eh? Ahora entiendo por qué me insinuó con tanto valor que la creación de la Compañía de Comercio Francesa en el Archipiélago sería poco rentable... ¡Por supuesto, sería muy poco rentable para él!";
			link.l1 = "Ya que ahora somos aliados, Barón, te diré toda la verdad, Poincy me pidió... que te convenciera de que no crearas la Compañía de Comercio aquí.";
			link.l1.go = "noel_70";
		break;
		
		case "noel_70":
			dialog.text = "¡Así que así es! ¿Espero que al menos no te haya pedido que me elimines con una espada o una pistola?";
			link.l1 = "No. Tenías que ser convencido de alguna otra manera.";
			link.l1.go = "noel_71";
		break;
		
		case "noel_71":
			dialog.text = "Poincy pagará por esto, pero ahora necesitamos zarpar inmediatamente hacia Saint-Martin. El español será entregado a la Metrópoli después. ¡Nos vamos, Vicealmirante!";
			link.l1 = "Parecerá un poco extraño que te vayas de la isla en mi barco, ¿no crees?";
			link.l1.go = "noel_72";
		break;
		
		case "noel_72":
			dialog.text = "No lo creo. ¿No se suponía que debías convencerme? ¡Eso es exactamente lo que hiciste, jaja! Sí, antes de zarpar hacia Europa, le diré al Caballero que estoy de acuerdo con sus puntos y que la Compañía de Comercio no será creada. Déjalo vivir en la pacífica dicha de una mentira, por ahora... ¡Vamos!";
			link.l1 = "...";
			link.l1.go = "noel_73";
		break;
		
		case "noel_73":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierToSMartin", 5.0);
		break;
		
		case "noel_74":
			dialog.text = "Guía el camino, Vicealmirante. La noche nos ocultará con su manto de oscuridad.";
			link.l1 = "Sígueme...";
			link.l1.go = "noel_75";
		break;
		
		case "noel_75":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.Patria_Condotier_inMine.win_condition.l1 = "location";
			pchar.quest.Patria_Condotier_inMine.win_condition.l1.location = "Location_reserve_03";
			pchar.quest.Patria_Condotier_inMine.function = "Patria_CondotierInMine";
		break;
		
		case "noel_76":
			dialog.text = "(susurrando) ¡Lo vi! ¡Lo vi! ¿Lo viste? ¡Casacas rojas! ¡Esos son soldados ingleses!";
			link.l1 = "Te lo dije - Poincy ahora hace negocios con el coronel Doily.";
			link.l1.go = "noel_77";
		break;
		
		case "noel_77":
			dialog.text = "Tenías razón. He visto suficiente. ¡Ahora salgamos de aquí lo más rápido que podamos antes de que nos descubran!";
			link.l1 = "De acuerdo...";
			link.l1.go = "noel_78";
		break;
		
		case "noel_78":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocator(pchar, "reload", "reload2_back", "Patria_CondotierToBeach", -1);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		break;
		
		case "noel_79":
			dialog.text = "¡Ya ves a qué llevan los 'proyectos comerciales' de nuestro querido Chevalier! ¡Los ingleses se comportan como anfitriones en una isla francesa! ¡Esto es indignante!";
			link.l1 = "Necesitamos movernos, o alguien definitivamente vendrá aquí. No podemos permitirnos ser reconocidos.";
			link.l1.go = "noel_80";
		break;
		
		case "noel_80":
			dialog.text = "Vicealmirante, he estado pensando todo el tiempo durante nuestro viaje a Saint-Martin, y he decidido algo: ¿puede arreglarme una reunión con Peter Stuyvesant?";
			link.l1 = "¿Con Stuyvesant? Pero ¿por qué?";
			link.l1.go = "noel_81";
		break;
		
		case "noel_81":
			dialog.text = "Un antiguo socio comercial podría tener algunas pistas serias, y algunas pruebas serias de la implicación de los Chevaliers. Estoy seguro de que Stuyvesant no está muy contento con Poincy y buscará venganza, especialmente después de estos recientes acontecimientos...";
			link.l1 = "Creo que sí, Barón. Personalmente, no me atreveré a ir al palacio de Stuyvesant. Es demasiado arriesgado para mí, después de todo lo que les he hecho...";
			link.l1.go = "noel_82";
		break;
		
		case "noel_82":
			dialog.text = "Ya lo he pensado. Iremos a Curazao, desembarcaremos en una bahía lejos de la ciudad y enviaremos a nuestro español cautivo de la mina con una carta para Stuyvesant. No te mencionaré allí, en su lugar le informaré que estoy llevando a cabo una investigación contra Poincy o algo por el estilo. Creo que el holandés vendrá al encuentro.";
			link.l1 = "Hmm. No creo que esto sea una buena idea. El Stuyvesant no es un tonto, toma lo que puede y podría incluso intentar encarcelarte y exigir un enorme rescate, pero si le hacemos creer que todo lo que sucedió fue por culpa de Poincy, podría ponerse de nuestro lado. Bueno, si estás tan decidido, intentémoslo.";
			link.l1.go = "noel_83";
		break;
		
		case "noel_83":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Shore40", "reload1_back", false);
			LocatorReloadEnterDisable("Shore40", "boat", false);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_LocationDisableOfficersGen("shore40", false);
			LAi_LocationDisableOfficersGen("Location_reserve_01", false);
			LAi_LocationDisableOfficersGen("Location_reserve_03", false);
			pchar.quest.Patria_CondotierCuracao.win_condition.l1 = "location";
			pchar.quest.Patria_CondotierCuracao.win_condition.l1.location = "shore22";
			pchar.quest.Patria_CondotierCuracao.function = "Patria_CondotierOnCuracao";
			AddQuestRecord("Patria", "81");
		break;
		
		case "noel_84":
			dialog.text = "Monsieur de Maure, por favor perdona mi necedad. Tenías razón sobre Stuyvesant. ¡Debería haber adivinado que solo un canalla aún más grande podría haber desafiado a de Poincy!";
			link.l1 = "¡Ja! Un millón... Poincy quería un millón, Stuyvesant quiere un millón... Parece que estamos dando vueltas en círculos...";
			link.l1.go = "noel_85";
		break;
		
		case "noel_85":
			dialog.text = "¿De qué estás hablando, Vicealmirante?";
			link.l1 = "Cuando llegué al Caribe, Poincy quería que pagara un millón como rescate por mi hermano.";
			link.l1.go = "noel_86";
		break;
		
		case "noel_86":
			dialog.text = "¿Y pagaste tanto?";
			link.l1 = "Gané y pagué. No en un mes, por supuesto. A decir verdad, yo era un simple grumete en aquel entonces. Aun así, el Chevalier no dejó ir a Michel.";
			link.l1.go = "noel_87";
		break;
		
		case "noel_87":
			dialog.text = "¿Y después de eso te alistaste para trabajar para Poincy? Honestamente, no te entiendo.";
			link.l1 = "Me alisté para servir a Francia y a aquellos que amo, no me inclino ante nadie más que el rey.";
			link.l1.go = "noel_88";
		break;
		
		case "noel_88":
			dialog.text = "Disculpe, Monsieur de Maure. ¡Por supuesto, usted sirve a Francia y al Rey! ¡Poincy responderá por todo! ¡Incluido todo el dolor que le causó a usted!";
			link.l1 = "Muy bien, Barón, encontraré un millón que pueda prescindir. Sube a bordo... Resolveré este problema.";
			link.l1.go = "noel_89";
		break;
		
		case "noel_89":
			DialogExit();
			//chrDisableReloadToLocation = false; //17-add
			LAi_LocationFightDisable(&Locations[FindLocation("shore22")], false);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "", 10.0);
			pchar.questTemp.Patria = "epizode_12_stivesant";
			AddQuestRecord("Patria", "83");
			if(bImCasual) NewGameTip("Modo exploración: el temporizador no está desactivado. ¡Cumple el plazo!");
			SetFunctionTimerCondition("Patria_CondotierStivesantTimeOver", 0, 0, 30, false); // таймер на месяц
		break;
		
		case "noel_90":
			dialog.text = "¿Queríais verme, Vicealmirante?";
			link.l1 = "Sí. Tuve una reunión con Stuyvesant. Aquí está su libro de cuentas.";
			link.l1.go = "noel_91";
		break;
		
		case "noel_91":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "¡No lo creo! Hmm, veamos... (leyendo)";
			link.l1 = "...";
			link.l1.go = "noel_92";
		break;
		
		case "noel_92":
			LAi_Fade("", "");
			dialog.text = "¡Esto es todo! Nuestro querido Chevalier está condenado. Tan pronto como todo esto de la contabilidad sea visto por el Ministro de Finanzas... Ni siquiera puedo imaginar lo que le sucederá. Ni siquiera tendremos que buscar al español de Cartagena. Monsieur de Maure, ¿realmente pagó un millón por este libro?";
			link.l1 = "Hice. Si intentara algo más, Francia podría perder sus colonias en el Caribe debido a una guerra civil, la cual podría ganar, pero ¿qué clase de almirante sería si luchara contra mi propio pueblo?";
			link.l1.go = "noel_93";
		break;
		
		case "noel_93":
			dialog.text = "Eres verdaderamente digno de tu nombre. Te juro Vicealmirante que lo recuperarás. Estoy seguro de que encontraremos una suma considerable de dinero en los cofres de Poincy y sus usureros. Solo te pido que esperes seis meses hasta que regrese de Europa con una comisión.";
			link.l1 = "Y no olvides traer un regimiento de soldados bien entrenados y armados. Y un barco como el 'Eclatant'. También creo que el capitán del 'Eclatant' se pondrá de nuestro lado cuando llegue el momento.";
			link.l1.go = "noel_94";
		break;
		
		case "noel_94":
			dialog.text = "No lo dudes, él también es un hombre honorable. Me di cuenta de que los valores morales juegan un papel importante en la toma de tus propias decisiones. Hiciste un gran trabajo, confiaste en mí y expusiste a este criminal del estado. Ahora llévame a Capsterville, donde informaré a Poincy sobre el éxito de tu misión: lograste convencerme y abandonaré la idea de crear la compañía comercial. Quizás Poincy incluso te recompense por esto; acepta la recompensa con la conciencia tranquila y no te preocupes por nada, tú de todos merecías esto. No serás arrastrado a esto, y tu nombre no será manchado con las fechorías de tu superior, de hecho diré las mejores cosas sobre ti cuando me reúna con el rey. El Barón Forget es un hombre de honor y un hombre de palabra.";
			link.l1 = "Me alegra, barón. ¡Zarpemos!";
			link.l1.go = "noel_95";
		break;
		
		case "noel_95":
			DialogExit();
			chrDisableReloadToLocation = false;
			bQuestDisableMapEnter = false;//открыть карту
			Island_SetReloadEnableGlobal("Curacao", true);
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 5.0);
			pchar.questTemp.Patria = "epizode_12_baronwin";
			AddQuestRecord("Patria", "85");
			pchar.quest.Patria_CondotierBaron_win.win_condition.l1 = "location";
			pchar.quest.Patria_CondotierBaron_win.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_CondotierBaron_win.function = "Patria_CondotierBaronWin";
		break;
		
		case "noel_96":
			dialog.text = "Así que, Vicealmirante, finalmente hemos llegado. Tu misión ha terminado, ahora me toca a mí. Ve a ocuparte de tus propios asuntos, defiende los intereses de Francia, como lo has hecho antes. En unos seis meses, esta vil historia llegará a su fin. Enviaré al mensajero a buscarte cuando seas necesario. ¡Adiós, Monsieur de Maure, tuve mucha suerte de encontrar a un hombre honorable aquí! El ministro y el Rey oirán de ti, eso lo prometo. Y oirán todo lo mejor.";
			link.l1 = "Gracias, Barón. ¡Buen viaje!";
			link.l1.go = "noel_97";
		break;
		
		case "noel_97":
			DialogExit();
			AddQuestRecord("Patria", "86");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 15.0);
			SetFunctionTimerCondition("Patria_CondotierPuancieFinal", 0, 0, 1, false); // таймер
		break;
		
		case "noel_98":
			dialog.text = "Me alegra verte, Vicealmirante. Estoy aquí de nuevo, como prometí. Y conmigo - el primer asistente del Ministro de Finanzas, Barón Olivier Bourdin.";
			link.l1 = "¿Dónde está el Chevalier de Poincy?";
			link.l1.go = "noel_99";
		break;
		
		case "noel_99":
			dialog.text = "Donde se supone que debe estar, en prisión. Fue arrestado y será llevado a Francia para ser investigado y juzgado. Dada su posición, seguramente evitará la ejecución, pero no puede evitar una gran multa, la degradación y, probablemente, la prisión.";
			link.l1 = "¿Fue pacífico el arresto?";
			link.l1.go = "noel_100";
		break;
		
		case "noel_100":
			dialog.text = "Realmente no. El Chevalier tenía aquí, en la residencia, toda una guardia de soldados leales. Pero estábamos preparados para tal escalada con antelación.";
			link.l1 = "¡Pues entonces, le felicito, barón! ¿Quizás ahora trate con la Compañía Francesa de Comercio?";
			link.l1.go = "noel_101";
		break;
		
		case "noel_101":
			dialog.text = "¿Yo? Sí. Su excelencia Monsieur Bourdin - volverá a Francia junto con el Chevalier de Poincy. Y usted, vicealmirante, también debería esperar algunos cambios. Ahora tiene un nuevo puesto. Su excelencia le dirá más.";
			link.l1 = "...";
			link.l1.go = "noel_102";
		break;
		
		case "noel_102":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("Finansist");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noel_103":
			dialog.text = "Monsieur de Maure! ¡Espera un momento!";
			link.l1 = "Sí, Barón. Estoy escuchando.";
			link.l1.go = "noel_104";
		break;
		
		case "noel_104":
			dialog.text = "En cuanto al millón que pagaste al Stuyvesant... No le conté al ministerio sobre esto, para... evitar preguntas, como cómo un oficial francés llegó a poseer tanto dinero. Esto podría haberte perjudicado, ya que probablemente te pedirían que aumentes el tesoro del Rey con el tuyo propio.";
			link.l1 = "Entiendo, gracias.";
			link.l1.go = "noel_105";
		break;
		
		case "noel_105":
			dialog.text = "Todo el dinero que se encontró en posesión de Poincy en Casterville fue confiscado por el barón Bourdin. Pero, resulta que Poincy también tenía un escondite que los prestamistas ingleses estaban ocultando para él. Hablaré con él sobre la devolución de las inversiones, y luego encontraré una forma de compensarte.";
			link.l1 = "Me temo que no será fácil para ti quitar algo de las manos de los usureros ingleses.";
			link.l1.go = "noel_106";
		break;
		
		case "noel_106":
			dialog.text = "Estoy de acuerdo. Pero trabajaremos en ello, y te mantendré informado sobre los resultados.";
			link.l1 = "Como desees.";
			link.l1.go = "noel_107";
		break;
		
		case "noel_107":
			dialog.text = "Vicealmirante, no parece que se encuentre tan bien, ¿o es solo mi impresión? ¡Acaba de recibir el puesto más alto en las colonias!";
			link.l1 = "No-no, para nada... Es solo que todo sucedió tan inesperadamente, y estoy un poco perdido.";
			link.l1.go = "noel_108";
		break;
		
		case "noel_108":
			dialog.text = "No te preocupes. Te acostumbrarás a tu nueva posición. Y además, tuviste bastante éxito siendo el gobernador de Saint-Martin durante medio año, así que no será nada nuevo para ti.";
			link.l1 = "Oh, estoy seguro de que me acostumbraré. He estado en peores situaciones durante mi tiempo aquí en el Caribe. Supongo que también manejaré esta.";
			link.l1.go = "noel_109";
		break;
		
		case "noel_109":
			// belamour legendary edition -->
			dialog.text = "Bueno, está bien. Además, tengo una sorpresa más para ti. Estoy seguro de que te gustará. Pero primero te pido que regreses a la residencia. Creo que alguien nos está esperando allí.";
			link.l1 = "Me has intrigado, Monsieur Forget. Bueno, volvamos.";
			link.l1.go = "noel_110";
		break;
		
		case "noel_110":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "ToEcliatonAward", -1);
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "noel_111":
			dialog.text = "Está bien, Marqués. Un verdadero capitán siempre debe cuidar primero de su barco, ¿verdad? Charles, ¿recuerdas al Marqués Hubert Dassier, capitán del navío de guerra 'Eclatant'?";
			link.l1 = "¡Por supuesto que lo recuerdo! Si no fuera por él, hoy no estaría vivo. La amistad más fuerte entre oficiales navales surge de batallas libradas codo con codo. Y Monsieur Dassier resultó ser un capitán increíblemente experimentado.";
			link.l1.go = "noel_112";
		break;
		
		case "noel_112":
			DialogExit();
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noel_113":
			dialog.text = "Vicealmirante, tengo el honor de informarle lo siguiente. Además de su nombramiento como Gobernador General en funciones de las colonias francesas en el archipiélago, también he planteado la cuestión de su buque insignia.";
			link.l1 = "¿Nave capitana?";
			link.l1.go = "noel_114";
		break;
		
		case "noel_114":
			dialog.text = "Exactamente. Hasta donde sé, cuando entraste al servicio de Francia, se te dio la fragata ligera 'Gryffondor' a tu disposición. Este es un barco maravilloso sin duda, pero aún así es solo para un oficial, y no para un vicealmirante y ahora, un gobernador general. Eres la cara de Francia aquí. Y tu buque insignia debe ser adecuado. Así que hemos decidido que el barco que pasó por sus primeras batallas aquí en el Caribe se añada a tu escuadrón...";
			link.l1 = "Monsieur Forget, ¿estás tratando de decir...?";
			link.l1.go = "noel_115";
		break;
		
		case "noel_115":
			dialog.text = "¡De ahora en adelante, el orgullo de la Armada Francesa, el buque de guerra de 66 cañones 'Eclatant' está a tu disposición! ¡Esta decisión está aprobada por el rey!";
			link.l1 = "Pero Barón, no puedo simplemente tomar...";
			link.l1.go = "noel_116";
		break;
		
		case "noel_116":
			dialog.text = "Puedes, Charles. Esto no se discute. En Francia, el 'Eclatant' fue mejorado un poco específicamente para ti, porque, como resultó, no hay batallas navales tan grandes en el Caribe como en Europa, y por lo tanto los requisitos para los barcos individuales son más altos. Aquí todo se decide por las características del buque y la experiencia de su capitán. Al 'Eclatant' se le reforzó el casco, se aumentó el peso muerto y el tamaño de la tripulación, se reequipó ligeramente el aparejo para permitirle tomar cursos más agudos, y también se reemplazaron por completo todos los cañones por calibres cuarenta y dos, estos son los cañones más fuertes que tenemos.";
			link.l1 = "Sí, ahora este barco es simplemente el amo de los mares... Pero Monsieur Forget, porque el capitán de este barco es el Marqués Hubert Dassier. No puedo quitárselo...";
			link.l1.go = "noel_117";
		break;
		
		case "noel_117":
			dialog.text = "Es solo que aún no te he dicho que el mismo Marqués ha expresado un fuerte deseo de servir bajo tu mando... ¿Monsieur Dassier?";
			link.l1 = "...";
			link.l1.go = "noel_118";
		break;
		
		case "noel_118":
			DialogExit();
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_19";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noel_119":
			dialog.text = "Sí, Monsieur Dassier, creo que no le retendremos por más tiempo.";
			link.l1 = "...";
			link.l1.go = "noel_120";
		break;
		
		case "noel_120":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload1");
			sld = characterFromId("Ecliaton_Cap");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "reload", "reload1", "EcliatonAwardNoelTalk", -1);
		break;
		
		case "noel_121":
			dialog.text = "Entre nosotros, Charles, te aconsejaría encarecidamente que mantengas al Marqués a tu servicio. Te aseguro que no encontrarás un capitán tan experimentado.";
			link.l1 = "Créame, barón, tuve el honor de ver esto personalmente durante las luchas contra España y Holanda. El señor Dassier es, de hecho, un excelente oficial de combate, y también mi amigo.";
			link.l1.go = "noel_122";
		break;
		
		case "noel_122":
			dialog.text = "¡Bueno, ahora permítame retirarme, Su Gracia, Gobernador General! Las cosas no pueden esperar: el trabajo de crear una compañía comercial está en el primer día de su creación. ¡Hasta pronto!";
			link.l1 = "¡Buena suerte, Monsieur Forget. Y buena suerte con tus esfuerzos comerciales!";
			link.l1.go = "noel_123";
		break;
		
		case "noel_123":
			DialogExit();
			// ставим Эклятон после апгрейда в Европе
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_24";
			sld.DeckDialogNode = "ecliaton_cap_24";
			sld.Ship.Type = GenerateShipExt(SHIP_ECLIATON, true, sld);
			SetBaseShipData(sld);
			sld.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS42;
			UpgradeShipFull(sld);
			/* UpgradeShipParameter(sld, "SpeedRate");
			UpgradeShipParameter(sld, "TurnRate");
			UpgradeShipParameter(sld, "WindAgainstSpeed");
			UpgradeShipParameter(sld, "HP");
			UpgradeShipParameter(sld, "MaxCrew");
			sld.ship.HP = 11880; */
			sld.Ship.name = "Ecliaton";
			SetCrewQuantityFull(sld);
			AddCrewMorale(sld, 100);
			ChangeCrewExp(sld, "Sailors", 100);
			ChangeCrewExp(sld, "Cannoners", 100);
			ChangeCrewExp(sld, "Soldiers", 100);
			SetCharacterGoods(sld, GOOD_BALLS, 6000);
			SetCharacterGoods(sld, GOOD_GRAPES, 2000);
			SetCharacterGoods(sld, GOOD_KNIPPELS, 2000);
			SetCharacterGoods(sld, GOOD_BOMBS, 5000);
			SetCharacterGoods(sld, GOOD_FOOD, 4000);
			SetCharacterGoods(sld, GOOD_POWDER, 12000);
			SetCharacterGoods(sld, GOOD_WEAPON, 900);
			SetCharacterGoods(sld, GOOD_MEDICAMENT, 900);
			SetCharacterGoods(sld, GOOD_RUM, 200);
			SetCharacterGoods(sld, GOOD_PLANKS, 100);
			SetCharacterGoods(sld, GOOD_SAILCLOTH, 100);
			Group_AddCharacter("Ecliaton_group", "Ecliaton_Cap");
			Group_SetGroupCommander("Ecliaton_group", "Ecliaton_Cap");
			Group_SetAddress("Ecliaton_group", "Nevis", "quest_ships", "quest_ship_1");
			Group_SetTaskNone("Ecliaton_group");
			Group_LockTask("Ecliaton_group");
			
			bDisableFastReload = false;//открыть переход
			bQuestDisableMapEnter = false;//открыть карту
			AddQuestRecord("Patria", "90");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			pchar.questTemp.Patria = "end"; // конец линейки
			pchar.questTemp.Patria.GenGovernor = "true"; // Шарль генерал-губернатор
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			DoQuestReloadToLocation("Charles_Town", "reload", "reload3", "OpenTheDoors");
		break;
		// <-- legendary edition
		
		case "noel_final":
			dialog.text = "¡Permítame expresar mi más sincero agradecimiento hacia usted, vicealmirante! Me ha salvado la vida al liberarme de esos malditos piratas. Le agradezco a usted, así como a Philippe de Poincy. Debo admitir que estaba absolutamente equivocado en mi juicio sobre él, y le pido que me perdone por eso. Usted y el Caballero tenían razón: la Compañía Francesa de Comercio tendrá muchos problemas aquí, y parece que solo perderemos dinero aquí.\nSolo personas experimentadas, como Poincy, y soldados tan valientes como usted, pueden resistir a estos lobos que viven en cada isla aquí. Necesito ir al palacio, y después de eso me iré a Europa lo antes posible, y olvidaré esta pesadilla.";
			link.l1 = "Me alegra que todo haya terminado bien, Barón. ¡Adiós!";
			link.l1.go = "noel_final_1";
		break;
		
		case "noel_final_1":
			DialogExit();
			AddQuestRecord("Patria", "76");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 15.0);
			SetFunctionTimerCondition("Patria_CondotierPuancieFinal", 0, 0, 1, false); // таймер
		break;
		
		// капитан Эклятона
		case "ecliaton_cap":
			dialog.text = TimeGreeting()+", monsieur. ¿Qué le trae a la cubierta del 'Eclatant'?";
			link.l1 = TimeGreeting()+", monsieur. Permítame presentarme: capitán Charles de Maure, vengo del Gobernador General de las colonias francesas en el Archipiélago, Chevalier de Poincy. Se me ordenó incorporar su barco a mi escuadrón y bajo mi mando. Aquí está la carta...";
			// belamour legendary edition фикс проверки мундира с мушкетом
			if(IsUniformEquip()) link.l1.go = "ecliaton_cap_1";
			else link.l1.go = "ecliaton_cap_no";
		break;
		
		case "ecliaton_cap_no":
			dialog.text = "Es algún tipo de error, monsieur. Estás a bordo de un navío de línea de la armada francesa, y solo escucho órdenes emitidas por aquellos que están al servicio de la Real Armada. Y no parece que tengas ningún distintivo o pertenencia a esa flota. Quizás confundas nuestro barco con otro.";
			link.l1 = "Pero...";
			link.l1.go = "ecliaton_cap_no_1";
		break;
		
		case "ecliaton_cap_no_1":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_no_2";
		break;
		
		case "ecliaton_cap_no_2":
			if(IsUniformEquip())
			{
				dialog.text = "Vaya, ni siquiera te reconocí con este uniforme, Capitán. Bueno, déjame ver tu carta, deseo examinar el contenido.";
				link.l1 = "Aquí.";
				link.l1.go = "ecliaton_cap_1";
			}
			else
			{
				dialog.text = "Hemos discutido todo ya, monseigneur...";
				link.l1 = "Ajá...";
				link.l1.go = "ecliaton_cap_no_1";
			}
		break;
		
		case "ecliaton_cap_1":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "Bueno, veamos... (leyendo) Interesante. Entonces, ¿yo y mi barco estaremos bajo tu mando, Capitán de Maure?";
			link.l1 = "Eso es la orden del Gobernador General.";
			link.l1.go = "ecliaton_cap_2";
		break;
		
		case "ecliaton_cap_2":
			dialog.text = "Sí-sí, las órdenes no se cuestionan. Muy bien. Permíteme presentarme: soy el Marqués Hubert Dassier, Capitán del navío de línea de 66 cañones de la armada francesa llamado 'Eclatant', junto con esta tripulación bien entrenada, y juro por mi honor que es uno de los mejores barcos que Francia haya tenido jamás.";
			link.l1 = "Me alegra oírlo, ya que la tarea que nos asignó el Gobernador General requerirá un buen conocimiento de navegación y artillería.";
			link.l1.go = "ecliaton_cap_3";
		break;
		
		case "ecliaton_cap_3":
			dialog.text = "¿Me contarás los detalles de esta operación próxima?";
			link.l1 = "Por supuesto. Nos trasladaremos a la isla española de Trinidad, ubicada a aproximadamente una semana de viaje al sureste de aquí. Atacaremos abruptamente el fuerte que guarda la colonia de San José y lo arrasaremos. Luego, hablaremos con los españoles sobre nuestra compensación por el reciente ataque al asentamiento francés de Saint-Pierre.";
			link.l1.go = "ecliaton_cap_4";
		break;
		
		case "ecliaton_cap_4":
			dialog.text = "Ya veo. ¿Cuándo partiremos?";
			link.l1 = "Tan pronto como sea posible. Tenemos que completar esta tarea en un mes, así que tenemos más que suficiente tiempo.";
			if (GetCompanionQuantity(pchar) > 4) link.l1.go = "ecliaton_cap_5_1";
			else link.l1.go = "ecliaton_cap_5";
		break;
		
		case "ecliaton_cap_5":
			dialog.text = "Está bien, Capitán de Maure. Partiremos a su orden.";
			link.l1 = "";
			link.l1.go = "ecliaton_cap_6";
		break;
		
		case "ecliaton_cap_6":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
			Patria_AddEcliaton();
		break;
		
		case "ecliaton_cap_wait":
			dialog.text = "¿Tiene alguna orden, o quizás preguntas, Capitán de Maure?";
			link.l1 = "Aún no...";
			link.l1.go = "ecliaton_cap_wait_1";
		break;
		
		case "ecliaton_cap_wait_1":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
		break;
		
		case "ecliaton_cap_5_1":
			dialog.text = "Pero, Capitán de Maure, primero tienes que hacer tu escuadrón más pequeño - mi barco no puede unirse a ti, o será un escuadrón demasiado grande.";
			link.l1 = "Vaya. Tienes razón. Dejaré un barco aquí en el puerto.";
			link.l1.go = "ecliaton_cap_5_2";
		break;
		
		case "ecliaton_cap_5_2":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_5_3";
		break;
		
		case "ecliaton_cap_5_3":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "¿Todavía no has reducido tu escuadrón, monsieur?";
				link.l1 = "Sí-sí, lo recuerdo, estoy trabajando en ello.";
				link.l1.go = "ecliaton_cap_5_2";
			}
			else
			{
				dialog.text = "Entonces, el 'Eclatant' está listo para unirse a tu escuadrón, monsieur.";
				link.l1 = "Entonces iré a mi barco, y deberías prepararte para entrar al mar.";
				link.l1.go = "ecliaton_cap_5";
			}
		break;
		
		case "ecliaton_cap_7":
			dialog.text = "Saludos, Comodoro. ¿Tenemos otra batalla por delante?";
			link.l1 = "En efecto, lo haremos. Una vez más uniremos fuerzas. Vamos a asaltar Philipsburg. El Gobernador General nos ha encomendado expulsar a los holandeses de Saint-Martin.";
			link.l1.go = "ecliaton_cap_9";
			link.l2 = "Lo hacemos, Capitán, pero un poco más tarde. Te lo diré cuando. El 'Eclatant' debe estar listo para zarpar en cualquier momento.";
			link.l2.go = "ecliaton_cap_8";
		break;
		
		case "ecliaton_cap_8":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_7";
			npchar.DeckDialogNode = "ecliaton_cap_7";
		break;
		
		case "ecliaton_cap_9":
			dialog.text = "Todo está claro. Será una misión dura, monseñor. Por lo que he oído, el fuerte de Philipsburg tiene muchos cañones.";
			link.l1 = "Estoy seguro de ello, mi amigo, pero lo manejaremos. Prepárate para entrar al mar, partimos pronto.";
			link.l1.go = "ecliaton_cap_10";
		break;
		
		case "ecliaton_cap_10":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
			Patria_BastionAddEcliaton();
		break;
		
		case "ecliaton_cap_11":
			dialog.text = "¡Me alegra verte en la cubierta del 'Eclatant', vicealmirante! ¿Cuáles son sus órdenes?";
			link.l1 = "Prepara el 'Eclatant' para la partida. Primero, navegaremos hacia la costa de Jamaica, y luego, junto con el escuadrón del Coronel D'Oyley, atacaremos Curazao.";
			link.l1.go = "ecliaton_cap_13";
			link.l2 = "Habrá órdenes, Capitán, pero más tarde. Te lo diré cuando. El 'Eclatant' tiene que estar listo para entrar al mar en cualquier momento.";
			link.l2.go = "ecliaton_cap_12";
		break;
		
		case "ecliaton_cap_12":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_11";
			npchar.DeckDialogNode = "ecliaton_cap_11";
		break;
		
		case "ecliaton_cap_13":
			dialog.text = "¡El 'Eclatant' y su tripulación están listos, Vicealmirante!";
			link.l1 = "Excelente. Entonces partimos inmediatamente.";
			link.l1.go = "ecliaton_cap_14";
		break;
		
		case "ecliaton_cap_14":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
			Patria_CuracaoAddEcliaton();
		break;
		
		// belamour legendary edition -->
		case "ecliaton_cap_15":
			dialog.text = "Disculpen caballeros, no pude unirme a ustedes antes, estaba ocupado dando órdenes en el barco. Ya pensé que llegaba bastante tarde, porque no los encontré en la residencia, y por eso iba a regresar al barco...";
			link.l1 = "...";
			link.l1.go = "ecliaton_cap_16";
		break;
		
		case "ecliaton_cap_16":
			DialogExit();
			Lai_SetPlayerType(pchar);
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_111";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "ecliaton_cap_17":
			dialog.text = "¡Fue un honor para mí luchar a tu lado, Monsieur de Maure! Debo decir que rara vez me encuentro con oficiales tan competentes y hábiles como tú. ¡Estoy seguro de que yo mismo no podría haberme enfrentado al fuerte de esa colonia española en Trinidad tan rápidamente!";
			link.l1 = "Os subestimáis, Monsieur Dassier. Lo resolvimos juntos.";
			link.l1.go = "ecliaton_cap_18";
		break;
		
		case "ecliaton_cap_18":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_113";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "ecliaton_cap_19":
			dialog.text = "Así es. Aunque soy un marqués, sigo siendo un marinero. Para mí, el archipiélago caribeño es nuevo, inexplorado y lleno de nuevas aventuras. La última vez que estuve aquí fue solo por unos meses, pero cuando regresé a Europa, comencé a extrañar este lugar. Me gustaría servir a nuestra Patria aquí. Y tú eres un capitán muy talentoso y experimentado, has logrado ganarte mi sincero respeto y mi amistad. Sería un honor servir bajo tu mando, ¡Vicealmirante!";
			link.l1 = "Bueno, no puedo y ¡qué es más!, ¡No quiero negarle, Monsieur Dassier!";
			link.l1.go = "ecliaton_cap_20";
		break;
		
		case "ecliaton_cap_20":
			dialog.text = "También entiendo que el Eclatant es ahora tu buque insignia, así que entenderé perfectamente si decides tomar el mando personalmente. En ese caso, puedes dejarme como tu oficial, darme otro barco o simplemente relevarme de mis deberes - el señor Forget amablemente me prometió que entonces me encontraría un puesto digno en la flota de la Compañía Francesa de las Indias Occidentales.";
			link.l1 = "Puedo asegurarte, amigo mío, que no llegará a eso. Eres uno de los mejores capitanes que he conocido, y contigo a mi lado seremos imparables.";
			link.l1.go = "ecliaton_cap_21";
		break;
		
		case "ecliaton_cap_21":
			dialog.text = "Gracias por tan halagadora evaluación de mis habilidades. Y una cosa más, Vicealmirante. No sé el tamaño de su escuadrón en este momento, así que por si acaso, lo estaré esperando en el puente del capitán del Eclatant en el muelle de Capsterville. Tan pronto como decida tomar el mando del barco, hágamelo saber.";
			link.l1 = "Muy bien, Monsieur Dassier.";
			link.l1.go = "ecliaton_cap_22";
		break;
		
		case "ecliaton_cap_22":
			dialog.text = "Entonces pido permiso para retirarme. Vicealmirante, Barón...";
			link.l1 = "Nos vemos pronto, Monsieur Dassier.";
			link.l1.go = "ecliaton_cap_23";
		break;
		
		case "ecliaton_cap_23":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_119";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
	
		case "ecliaton_cap_24":
			dialog.text = "Vicealmirante, bienvenido a bordo. ¿Le gustaría tomar el Eclatant bajo su mando?";
			if (GetCompanionQuantity(pchar) > 4)
			{
				
				link.l1 = "Aún no, Marqués. Espera órdenes.";
				link.l1.go = "ecliaton_cap_24_1";
			}
			else
			{
				link.l1 = "Sí, Marqués, le pido que se una a mi escuadrón. ¡Este hermoso navío será un símbolo de la grandeza y el poder de Francia en el Caribe!";
				link.l1.go = "ecliaton_cap_25";
			}
		break;
		
		case "ecliaton_cap_24_1":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_24";
			npchar.DeckDialogNode = "ecliaton_cap_24";
		break;
		
		case "ecliaton_cap_25":
			dialog.text = "¡No podría estar más de acuerdo, su Excelencia!";
			link.l1 = "... Ahora, veamos de qué somos realmente capaces!";
			link.l1.go = "ecliaton_cap_26";
		break;
		
		case "ecliaton_cap_26":
			DialogExit();
			DeleteAttribute(npchar, "ShipHideImmortal");
			SetCharacterRemovable(npchar, true);
			npchar.CompanionEnemyEnable = true; 
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			npchar.Dialog.CurrentNode = "hired";
			npchar.DeckDialogNode = "hired";
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.Payment = true;
			npchar.loyality = MAX_LOYALITY;
			npchar.OfficerWantToGo.DontGo = true;
			
			// удаление группы Эклятона, иначе клон-призрак
			pchar.quest.Patria_EcliatonDelGroup.win_condition.l1 = "ExitFromSea";
			pchar.quest.Patria_EcliatonDelGroup.function = "Patria_EcliatonDelGroup";
		break;
		// <-- legendary edition
		
		// д'Ойли на Антигуа
		case "doily":
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "end" && colonies[FindColony("Pirates")].nation == PIRATE)
			{
				PlaySound("Voice\Spanish\LE\Doily\Edvard_Doily_01.wav");
				dialog.text = "¡Oh, qué encuentro! ¿No es el propio Capitán Charles de Maure?! He oído que ahora tienes un puesto en la armada francesa. Qué sorpresa, considerando para quién estabas, digamos, 'trabajando' anteriormente...";
				link.l1 = "Saludos, señor. ¿Está hablando del asunto con Isla Tesoro? Oh, pero no fui yo quien escribió las leyes inglesas, según las cuales la isla fue heredada por el heredero del explorador que la encontró, según su testamento. Así que, no soy culpable de eso, solo ayudé a la señorita Sharp a obtener lo que era suyo por derecho.";
				link.l1.go = "doily_1";
			}
			else
			{
				dialog.text = TimeGreeting()+", capitán. Supongo que el representante de la armada francesa ha llegado a Antigua con un objetivo importante en mente.";
				link.l1 = "Así es, señor. Fui enviado aquí por el Gobernador General de las colonias francesas, Philippe de Poincy. Saint-Christopher ha sido sitiada por los escuadrones navales españoles y holandeses. El Caballero pide ayuda de usted y del señor Jonathan Fox también. Aquí está su carta para usted, coronel.";
				link.l1.go = "doily_3";
			}
		break;
		
		case "doily_1":
			dialog.text = "Me pregunto, Capitán, ¿cuánto dinero ganaste con esto? Supongo que bastante, ya que has conseguido pagar los servicios del pícaro Loxley, que no son nada baratos. Estoy seguro de que los barones piratas te pagan deducciones regularmente por mantener la isla en su posesión. Ambos sabemos perfectamente que Helen Sharp es solo una máscara.";
			link.l1 = "Coronel, ambos sabemos que los barones piratas operan principalmente en interés de Inglaterra, no oficialmente, entiéndase... Sin ellos, sería bastante difícil resistir la hegemonía de los españoles en la región, ¿no está de acuerdo? Así que, desde el punto de vista de los políticos, el hecho de que la Hermandad de la Costa haya mantenido la isla para sí mismos, fue quizás, incluso más provechoso que si Isla Tesoro se hubiera convertido en una base naval inglesa...";
			link.l1.go = "doily_2";
		break;
		
		case "doily_2":
			dialog.text = "Esto es discutiblemente cierto, Capitán, pero... sea como sea. ¿Ha llegado a Antigua con algún objetivo importante, supongo? ¿Quizás tenga que ver con el hecho de que las relaciones de dos antiguos aliados - Francia y Holanda, han empeorado considerablemente?";
			link.l1 = "Exactamente. Fui enviado por el gobernador general de las colonias francesas, Philippe de Poincy. Saint-Christopher ha sido sitiado por la armada española y holandesa. El Caballero solicita tu ayuda. Aquí está su carta para ti, coronel.";
			link.l1.go = "doily_3";
		break;
		
		case "doily_3":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "Déjame ver... (leyendo)";
			link.l1 = "";
			link.l1.go = "doily_3_1";
		break;
		
		case "doily_3_1":
			LAi_Fade("", "");
			dialog.text = "Hmm... ¡muy intrigante! Capitán, vuestro comandante sabe cómo captar mi interés, no es tan raro que la gente lo llame un zorro astuto. Deberíamos haber hecho esto hace mucho tiempo, en lugar de intentar hacernos amigos de los holandeses. Ya sabemos muy bien lo que representan la Compañía Holandesa y su Director. Bien entonces, creo que en esta situación realmente no deberíamos negar nuestra ayuda a la sitiada Casterville, y tenemos más que suficientes tropas para permitirlo. \n¿Cuáles son los números y tipos de barcos en sus escuadrones, Capitán?";
			link.l1 = "He contado seis barcos: un navío de línea de ochenta cañones de tercer rango y cinco barcos de cuarto. También podrían tener fragatas y galeones.";
			link.l1.go = "doily_4";
		break;
		
		case "doily_4":
			dialog.text = "Hum... Podemos adelantar nuestro escuadrón, compuesto por un navío de primera clase con cien cañones, dos barcos de cuarta clase y una fragata pesada, contra los suyos.";
			if (!CheckAttribute(pchar, "questTemp.Patria.FailLugger"))
			{
				link.l1 = "Señor, también tenemos un buque de guerra de 66 cañones, el 'Eclatant', navegando en ayuda de la defensa de San Cristóbal desde la costa de Guadalupe.";
				link.l1.go = "doily_5";
			}
			else
			{
				link.l1 = "Un barco de primer rango será de gran ayuda en la próxima batalla.";
				link.l1.go = "doily_5_1";
			}
		break;
		
		case "doily_5":
			dialog.text = "Perfecto. En ese caso, estamos muy por encima de la capacidad de disparo de nuestros enemigos. La victoria será nuestra.";
			link.l1 = "Y no olvidemos mi propio barco, señor. No voy a perderme tal batalla, ni lo considere.";
			link.l1.go = "doily_6";
		break;
		
		case "doily_5_1":
			dialog.text = "Eso es cierto. Incluyendo la ayuda del fuerte de Casterville, la victoria será nuestra.";
			link.l1 = "Y no olvidemos mi propio barco, señor. No voy a perderme tal batalla, ni lo consideres.";
			link.l1.go = "doily_6";
		break;
		
		case "doily_6":
			dialog.text = "Por supuesto, monsieur de Maure. Sea cual sea el caso, los relatos sobre tus talentos en la navegación se escuchan por todo el archipiélago. Tu buque insignia liderará el escuadrón.";
			if (GetCompanionQuantity(pchar) > 1)
			{
				link.l1 = "Pondré el resto de los barcos de mi escuadrón en espera, luego regresaré a ti, y nos apresuraremos a ayudar a los sitiados.";
				link.l1.go = "doily_7_1";
			}
			else
			{
				link.l1 = "Prepararé mi barco en breve, y nos apresuraremos a ayudar a los sitiados.";
				link.l1.go = "doily_8";
			}
		break;
		
		case "doily_7_1":
			DialogExit();
			npchar.dialog.currentnode = "doily_7_2";
		break;
		
		case "doily_7_2":
			dialog.text = "Entonces, ¿estás listo para zarpar?";
			if (GetCompanionQuantity(pchar) > 1)
			{
				link.l1 = "Espere un poco, señor.";
				link.l1.go = "doily_7_1";
			}
			else
			{
				link.l1 = "Sí, señor.";
				link.l1.go = "doily_8";
			}
		break;
		
		case "doily_8":
			dialog.text = "¡Entonces comencemos, y que Dios nos ayude!";
			link.l1 = "...";
			link.l1.go = "doily_9";
		break;
		
		case "doily_9":
			DialogExit();
			npchar.dialog.currentnode = "doily_10";
			chrDisableReloadToLocation = true;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			AddQuestRecord("Patria", "42");
			Patria_SiegeAddEngSquadron();
		break;
		
		case "doily_10":
			dialog.text = "¿Tiene alguna otra pregunta, señor?";
			link.l1 = "No, coronel...";
			link.l1.go = "doily_11";
		break;
		
		case "doily_11":
			DialogExit();
			npchar.dialog.currentnode = "doily_10";
			npchar.DeckDialogNode = "doily_10";
		break;
		
		case "doily_12":
			PlaySound("Voice\Spanish\LE\Doily\Edvard_Doily_02.wav");
			dialog.text = "Consiga la carta para el Stuyvesant, señor. Si no está al tanto de quién soy, permítame presentarme: Coronel Edward Doily, gobernador de Port-Royal y comandante de esta expedición!\nPara decirle la verdad, tengo un gran deseo de arrasar el escondite de bandidos conocido como Willemstad. La organización más vil, hipócrita y despreciable del Caribe, conocida como la Compañía Holandesa de las Indias Occidentales que piensa que todo el comercio en el Archipiélago es exclusivamente su derecho, y que contrata a individuos como Jacob van Berg y otros piratas para capturar y hundir los barcos de los comerciantes ingleses...";
			link.l1 = "...";
			link.l1.go = "doily_13";
		break;
		
		case "doily_13":
			dialog.text = "Estoy aquí para poner fin a estos actos indignantes, y, afortunadamente para ti, propongo un camino diplomático. Por ahora... Pero si el director de esta abominable organización no llega aquí para las conversaciones, arruinaré su negocio. Después de que asaltemos la ciudad, solo dejaré cenizas atrás, y cualquier pólvora que encontremos, la pondremos en el sótano de vuestro fuerte y lo volaremos. La misma suerte aguarda a vuestras plantaciones, y el propio Stuyvesant colgará del bauprés de mi buque insignia...";
			link.l1 = "...";
			link.l1.go = "doily_14";
		break;
		
		case "doily_14":
			dialog.text = "Necesitarás más de un año para reconstruir tu colonia, y entonces no tendrás tiempo para tus intrigas y complots. Dile a tu 'Mynheer Director' todo lo que acabo de decir, y no pienses que son bromas y promesas vacías. Se me ha acabado la paciencia, así que debes entenderme perfectamente. ¿Entiendes, oficial?!";
			link.l1 = "Todo está perfectamente claro, señor Coronel.";
			link.l1.go = "doily_15";
		break;
		
		case "doily_15":
			dialog.text = "Genial. Entonces vete. Te doy exactamente un día para reflexionar sobre esto. Si después de veinticuatro horas Peter Stuyvesant no estará aquí parado como lo estás tú ahora, que se lo reproche a sí mismo.";
			link.l1 = "...";
			link.l1.go = "doily_16";
		break;
		
		case "doily_16":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Doily_land");
			sld.dialog.currentnode = "doily_17";
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "doily_17":
			dialog.text = "¡Creo que ese perro andrajoso Stuyvesant vendrá aquí. Y si no, solo podrá culparse a sí mismo!";
			link.l1 = "...";
			link.l1.go = "doily_17_1";
		break;
		
		case "doily_17_1":
			DialogExit();
			npchar.dialog.currentnode = "doily_17";
			AddQuestRecord("Patria", "63");
			Patria_CuracaoParlamenterGo();
		break;
		
		case "doily_18": // д'Ойли на берегу
			dialog.text = "Has hecho un buen trabajo con el fuerte, monsieur de Maure. Ahora nos acercaremos a las puertas de la ciudad por tierra. Yo llevaré los cañones desde aquí, el camino es más corto y fácil, y tú desembarcarás la compañía de tus marines en el Cabo Santa-Maria y te moverás hacia Willemstad. Si encuentras enemigos en el camino, sabes qué hacer. Nadie puede quedar atrás de nosotros.";
			link.l1 = "Por supuesto, coronel. ¡Te encontraré en las puertas!";
			link.l1.go = "doily_19";
		break;
		
		case "doily_19":
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddQuestRecord("Patria", "61");
			npchar.dialog.currentnode = "doily_10";
			Patria_CuracaoGotoMarch();
		break;
		
		case "doily_20":
			dialog.text = "Bueno entonces, parece que nuestra misión ha terminado con bastante éxito. ¡Felicitaciones, Capitán! Oh, discúlpeme, ¡Vicealmirante! Regresemos a los barcos. Le diré a mis hombres que se mantengan en guardia - ese tonto Stuyvesant probablemente no se arriesgará a atacarnos mientras nos retiramos, pero no hará daño ser cuidadosos.";
			link.l1 = "Estoy seguro de que los holandeses no se atreverán a romper un tratado que acaba de firmarse.";
			link.l1.go = "doily_21";
		break;
		
		case "doily_21":
			dialog.text = "Fue un placer trabajar contigo, monsieur de Maure. Creo que nos volveremos a encontrar en Port-Royal o Capsterville.";
			link.l1 = "Sin duda, coronel. Ahora, digamos a nuestros hombres que se retiren.";
			link.l1.go = "doily_22";
		break;
		
		case "doily_22":
			DialogExit();
			AddQuestRecord("Patria", "64");
			Patria_CuracaoClear();
		break;
		
		case "doily_23":
			dialog.text = "Al parecer, los holandeses finalmente han aprendido que no tienen manera de acercarse a nosotros desde el fuerte por ese camino estrecho bajo el fuego de nuestra artillería. Y los que están atrapados en la ciudad probablemente no se atreverán a hacer una salida, a menos que estén completamente locos. Ahora sembramos un poco de pánico: bombardeemos la ciudad con nuestros cañones. Los hombres en mi barco lo verán y harán que parezca que se están preparando para desembarcar. Después de una o dos horas, Stuyvesant se cagará en los pantalones y estará listo para enviar a los enviados de tregua.";
			link.l1 = "¡Todo va según nuestro plan, coronel! ¡Hagámoslo!";
			link.l1.go = "doily_24";
		break;
		
		case "doily_24":
			DialogExit();
			Patria_CuracaoTownBombing();
		break;
		
		// голландский парламентёр под стенами Виллемстада
		case "holoff":
			dialog.text = "He llegado aquí para comenzar las negociaciones. ¿Cuáles son tus demandas?";
			link.l1 = "Exigimos una reunión con el Director de la Compañía, Peter Stuyvesant. Específicamente, queremos hablar sobre el hecho de que, debido a la culpa de su compañía, así como a la suya propia, Willemstad está actualmente bajo amenaza de destrucción.";
			link.l1.go = "holoff_1";
		break;
		
		case "holoff_1":
			dialog.text = "Muy bien, informaré al señor Stuyvesant sobre esto, y organizaremos una ruta segura hacia la ciudad para su delegación...";
			link.l1 = "¿Y qué tal una salida segura?";
			link.l1.go = "holoff_2";
		break;
		
		case "holoff_2":
			dialog.text = "¿No entiendo, señor?";
			link.l1 = "Dije: ¿arreglarás una salida segura de la ciudad para nosotros? No estoy seguro de eso. Me temo que el señor Stuyvesant podría simplemente decidir tomar a nuestros enviados como prisioneros. Por esta razón, invito al señor Stuyvesant a presentarse aquí mismo para las negociaciones.";
			link.l1.go = "holoff_3";
		break;
		
		case "holoff_3":
			dialog.text = "Pero...";
			link.l1 = "Oficial, nosotros dictamos las condiciones aquí. Su flota está destruida, la guarnición aislada de la ciudad, y penetraremos la defensa de Willemstad como una fragata penetra una chalupa si decidimos asaltar la ciudad. Ahora, recibirá una carta para el señor Stuyvesant, y se la entregará junto con nuestra invitación...";
			link.l1.go = "holoff_4";
		break;
		
		case "holoff_4": // перекидываем pchar на офицера и говорим с д'Ойли
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Curacao_parlamenter_1"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Doily_land");
			sld.dialog.currentnode = "doily_12";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		// офицер-испанец на маяке Тринидада
		case "SanJoseSpanish":
			dialog.text = "Entonces, capitán, ¿ha llamado a los enviados de la tregua porque quiere dictar sus demandas?";
			link.l1 = "Eres absolutamente correcto, señor. Permíteme explicarte brevemente mi razón para llegar a Trinidad: esta es nuestra respuesta a tu reciente ataque a Saint-Pierre. Has dañado considerablemente la ciudad, y ahora estarás obligado a compensarlo. El precio de la compensación es de trescientos mil pesos. Y eso no es tanto, considerando los viles actos que tus soldados han cometido en Martinica.";
			link.l1.go = "SanJoseSpanish_1";
		break;
		
		case "SanJoseSpanish_1":
			dialog.text = "Disculpe, señor, pero ¿qué tiene que ver San José con Saint-Pierre? ¿Por qué nuestra colonia tiene que pagar?";
			link.l1 = "Porque los atacantes eran españoles, no holandeses ni ingleses. Entonces pondréis la cuenta en Providence para Don de Mendosa, junto con mis más sinceros saludos. Como comprenderéis, en caso de que os neguéis a pagar la compensación, ordenaré a mis hombres desembarcar, y entonces San José perderá mucho más. Estoy seguro de que el gobernador de vuestra colonia tomará la decisión correcta. Tenéis un día para responder. Os deseo lo mejor, señores.";
			link.l1.go = "SanJoseSpanish_2";
		break;
		
		case "SanJoseSpanish_2":
			DialogExit();
			npchar.dialog.currentnode = "SanJoseSpanish_3";
			Patria_SanJoseMayakSpanishGo();
		break;
		
		case "SanJoseSpanish_3":
			dialog.text = "";
			link.l1 = "Entonces, según entiendo, ¿el gobernador ha tomado la decisión correcta?";
			link.l1.go = "SanJoseSpanish_4";
		break;
		
		case "SanJoseSpanish_4":
			AddMoneyToCharacter(pchar, 300000);
			dialog.text = "Llévate tus trescientos mil y sal de nuestra colonia.";
			link.l1 = "Excelente, señores. Les aseguro que esta era la mejor manera. Espero que esto desanime al Don de Mendosa y a otros de atacar nuestras colonias. No olviden enviar el mensaje a Providence y a él personalmente. Les deseo lo mejor, caballeros.";
			link.l1.go = "SanJoseSpanish_5";
		break;
		
		case "SanJoseSpanish_5":
			DialogExit();
			Patria_SanJoseMayakSpanishFin();
		break;
		
		// вестовой на 5 задание
		case "fraofficer":
			dialog.text = "Capitán Charles de Maure, permitidme informar: el Caballero Philippe de Poincy quería notificaros que el Barón Noel Forget está listo para partir hacia Saint-Martin y os esperará en el muelle.";
			link.l1 = "¡Excelente! Gracias, monsieur.";
			link.l1.go = "fraofficer_1";
		break;
		
		case "fraofficer_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 10.0);
			Patria_SanMartinSetBaron();
		break;
		
		case "fraofficer_2":
			dialog.text = "¡Capitán Charles de Maure! El Gobernador General te está llamando ahora mismo. ¡Una poderosa escuadra enemiga ha aparecido en la costa de Saint-Christopher!";
			link.l1 = "¡Entonces no perdamos tiempo!";
			link.l1.go = "fraofficer_3";
		break;
		
		case "fraofficer_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;
			Patria_SiegeHovernor();
		break;
		
		// патруль у рудника
		case "engofficer":
			dialog.text = "¿Quién eres tú? ¿Qué haces aquí?";
			link.l1 = "Uhh...";
			link.l1.go = "engofficer_1";
		break;
		
		case "engofficer_1":
			dialog.text = "¡No se permiten extraños aquí! ¿Quiénes son ustedes, espías? Los llevaré a la oficina del comandante, ellos se encargarán de ustedes.";
			link.l1 = "Pero no podemos ir a la oficina del comandante...";
			link.l1.go = "engofficer_2";
		break;
		
		case "engofficer_2":
			dialog.text = "¡Si no vas tú mismo, tendremos que arrastrarte por la fuerza! ¡Entrega tus armas!";
			link.l1 = "Sin trato...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Patria_CondotierBeachFight");
		break;
		
		// бывший управляющий рудника
		case "miner":
			dialog.text = "";
			link.l1 = "Entonces, ¿todo está claro?";
			link.l1.go = "miner_1";
		break;
		
		case "miner_1":
			dialog.text = "Sí, monsieur. La carta debe ser entregada personalmente a mynheer Peter Stuyvesant o Mathias Beck.";
			link.l1 = "Estoy seguro de que no tendrás problemas para encontrar un barco de Willemstad a Cartagena. Te dimos todos los fondos necesarios para pagar el viaje y el alojamiento. Y en caso de que necesites, ¿confirmarás tus informes ante la comisión francesa dentro de medio año?";
			link.l1.go = "miner_2";
		break;
		
		case "miner_2":
			dialog.text = "Monsieur, soy leal a mi palabra.";
			link.l1 = "Muy bien. Entonces te deseo suerte. Este camino lleva a Willemstad, síguelo. No está lejos de aquí.";
			link.l1.go = "miner_3";
		break;
		
		case "miner_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "Patria_CondotierOnCuracaoWait", 15.0);
			AddQuestRecord("Patria", "82");
			ReleasePrisoner(npchar);
		break;
		
		// курьер в Капстервиль
		case "cureer":
			dialog.text = "Vicealmirante Charles de Maure, ¿verdad?";
			link.l1 = "Precisamente. ¿Con quién tengo el honor de hablar?";
			link.l1.go = "cureer_1";
		break;
		
		case "cureer_1":
			dialog.text = "Tengo un mensaje para ti de parte del Barón Noel Forget. Te dijo que fueras al palacio del gobernador en Casterville lo antes posible.";
			link.l1 = "¡Oh! ¡Buenas nuevas! ¡Gracias, partiré de inmediato!";
			link.l1.go = "cureer_2";
		break;
		
		case "cureer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			Patria_EuropePrepare();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
		break;
		
		case "burden":
			dialog.text = "Saludos, vicealmirante. El barón Forget me contó historias sobre usted. Muchas historias. Le doy mi más sincero agradecimiento por su leal y brillante servicio por el bien de Francia en las colonias, así como por su ayuda en descubrir los planes del estafador de Poincy. Ahora, yo y el Ministro de Finanzas nos encargaremos de él personalmente, y usted ocupará el lugar de su antiguo comandante. Al menos, por el momento.";
			link.l1 = "Pero...";
			link.l1.go = "burden_1";
		break;
		
		case "burden_1":
			dialog.text = "¡No hay 'peros', vicealmirante! Esta decisión ya ha sido tomada y aprobada por el Rey. Tengo aquí una orden firmada por él personalmente sobre asignarle como el Gobernador General de facto de las colonias francesas en el Archipiélago. No tenemos mejores candidatos para este puesto. Su destacada experiencia en la guerra, su conocimiento de la región y de las personas que son responsables de todo aquí, sus habilidades y talentos son dignos de esta alta y respetable posición. Si me permitís ser honesto con vos, espero que después de algún tiempo se le asigne a este puesto nuevamente, sin la parte de 'de facto'.";
			link.l1 = "Pero soñaba con volver a París...";
			link.l1.go = "burden_2";
		break;
		
		case "burden_2":
			dialog.text = "¡Francia te necesita aquí! El Ministro de Finanzas está reuniendo una armada en Europa en este momento, y nuestra presencia aquí, en el Archipiélago, tampoco pasará desapercibida. Tu tarea principal será fortalecer y fortificar las colonias e incrementar el poder militar de nuestra flota, mientras que el Barón Forget y la Compañía de Comercio de las Indias Occidentales Francesas se centrarán en el comercio y el desarrollo interno. ¿Y quién más, si no tú, puede ayudar a preparar la armada francesa?\n¡Así que, comienza a trabajar, Gobernador General! Sé que no te gusta estar en una habitación todo el día, pero tu tarea ni siquiera lo requiere.";
			link.l1 = "¡En seguida, su Gracia! ¡Las órdenes no se cuestionan!";
			link.l1.go = "burden_3";
		break;
		
		case "burden_3":
			dialog.text = "Me alegra que me hayas entendido correctamente. Y también te pediré que visites al Chevalier de Poincy: insistió en conocerte. No podemos negarle tal placer antes de su partida a París, ¿verdad? Lo encontrarás en la prisión.";
			link.l1 = "Está bien, su Gracia...";
			link.l1.go = "burden_4";
		break;
		
		case "burden_4":
			DialogExit();
			DoQuestReloadToLocation("Charles_prison", "goto", "goto19", "Patria_EuropePuancieInPrison");
		break;
		
		// Портной Пуанси Xenon
		case "Tailor":
			dialog.text = "...se retrasarán, ¿entiendes? ¡Encargué estos materiales hace varios meses!";
			link.l1 = "...";
			link.l1.go = "Tailor_01";
			CharacterTurnByChr(npchar, characterFromId("Charles_PortMan"));
		break;
		
		case "Tailor_01":
			DialogExit();
			sld = characterFromId("Charles_PortMan");
			sld.dialog.currentnode = "Tailor";
			LAi_SetActorType(pchar);
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;
		
		case "Tailor_02":
			dialog.text = "¿Y cómo decidieron qué llevar en el primer barco y qué en el segundo?! ¡No soy simplemente una costurera de los confines - incluso tengo una orden del gobernador general, su excelencia el caballero de Poincy!";
			link.l1 = "...";
			link.l1.go = "Tailor_03";
			CharacterTurnByChr(npchar, characterFromId("Charles_PortMan"));
		break;
		
		case "Tailor_03":
			DialogExit();
			Lai_SetPlayerType(pchar);
			sld = characterFromId("Charles_PortMan");
			sld.dialog.currentnode = "Tailor_02";
			LAi_SetActorType(pchar);
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;
		
		case "Tailor_04":
			dialog.text = "Bueno, ¿qué más puedo hacer ahora...? Esperaré. Pero sepa esto: ¡no seré responsable de los pedidos incumplidos!";
			link.l1 = "Saludos. ¿Veo que tienes problemas?";
			link.l1.go = "Tailor_05";
			CharacterTurnByChr(npchar, characterFromId("Charles_PortMan"));
		break;
		
		case "Tailor_05":
			dialog.text = "¿Problemas? ¡Eso es quedarse corto! Oh, creo que te reconozco... Eres el nuevo vicealmirante, ¿correcto?";
			link.l1 = "Rápido de reflejos. Eso es correcto, ante usted se encuentra el segundo hombre en las colonias francesas, Vicealmirante de la flota francesa, Charles de Maure.";
			link.l1.go = "Tailor_06";
			link.l2 = "Deja esas formalidades, no estamos en un barco. Y no te preocupes, no llamaré a los guardias solo porque no me reconociste de inmediato. Simplemente llámame Charles de Maure.";
			link.l2.go = "Tailor_07";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Tailor_06":
			AddCharacterExpToSkill(pchar, "Leadership", 300);//харизма
			dialog.text = "¡Su Excelencia, por favor, perdóneme por no reconocerle inmediatamente! Sí, tiene razón, me he encontrado con circunstancias imprevistas.";
			link.l1 = "¿Y cuáles serían esas circunstancias? Según entiendo, ¿no te trajeron materiales de París?";
			link.l1.go = "Tailor_08";
		break;
		
		case "Tailor_07":
			AddCharacterExpToSkill(pchar, "Fortune", 300);//везение
			dialog.text = "Oh, muchas gracias. Tienes razón, me he encontrado con circunstancias imprevistas, por lo que no me di cuenta de inmediato de quién estaba frente a mí.";
			link.l1 = "¿Y cuáles serían esas circunstancias? Según tengo entendido, ¿no te trajeron materiales de París?";
			link.l1.go = "Tailor_08";
		break;
		
		case "Tailor_08":
			dialog.text = "Sí, eso es correcto. Los encargué hace varios meses. El gobernador firmó la orden para tu nombramiento en aquel entonces e insistió en que preparara todos los materiales necesarios para el uniforme de un nuevo almirante, confiado en que sería aprobado en la metrópoli.";
			link.l1 = "¿Y los materiales no fueron entregados, supongo?";
			link.l1.go = "Tailor_09";
		break;
		
		case "Tailor_09":
			dialog.text = "¡Imagínate eso! Expliqué lo importante que era, hice el pedido... ¡Pero tienen envíos más urgentes de los que ocuparse! ¿Qué se supone que debo hacer? ¿Hacer mis pedidos con un año de antelación, esperando que se dignen a traerme los materiales?";
			link.l1 = "¿Qué exactamente te falta? ¿Quizás pueda obtenerse en el Caribe?";
			link.l1.go = "Tailor_10";
		break;
		
		case "Tailor_10":
			dialog.text = "Aun si es posible, no tengo idea de dónde... No encontrarás buenos materiales aquí. Aunque... Podría usar tu antigua chaqueta de oficial como base, si lo permites. Probablemente no la necesitarás una vez que tengas el uniforme de almirante, ¿verdad?";
			link.l1 = "Si tengo un uniforme de almirante, entonces, por supuesto, no necesitaré una simple chaqueta de oficial. ¿Qué más?";
			link.l1.go = "Tailor_11";
		break;
		
		case "Tailor_11":
			dialog.text = "Necesito encontrar gemelos y un cuello para el uniforme. Normalmente, los encargo directamente de los talleres parisinos. Aunque sean muy básicos, puedo alterarlos y darles un aspecto más presentable. Aunque en ese caso, necesitaré más de ellos...";
			link.l1 = "Como no hay talleres parisinos en el Caribe, te encontraré un lote completo de ropa con cuellos y puños desmontables. ¿Qué más?";
			link.l1.go = "Tailor_12";
		break;
		
		case "Tailor_12":
			dialog.text = "Para los toques finales, necesito telas de muy alta calidad. Tengo una hilandera que puede hacer tal tela incluso de fibra tosca. Pero para eso, necesito material, idealmente algodón. Un fardo será más que suficiente.";
			link.l1 = "Eso también se puede obtener. ¿Qué sigue?";
			link.l1.go = "Tailor_13";
		break;
		
		case "Tailor_13":
			dialog.text = "Se suponía que debían entregar un tricornio de almirante desde París, pero puedo hacerlo yo mismo si tengo el material. Aunque el tricornio para ti debía ser de tela, el cuero sería mejor para los vientos salados y el sol abrasador del Caribe. Duraría más.";
			link.l1 = "Te conseguiré el cuero; no te preocupes. No tendré que perseguir toros por las selvas de España. ¿Eso es todo?";
			link.l1.go = "Tailor_14";
		break;
		
		case "Tailor_14":
			dialog.text = "También se suponía que debían entregar seda de primera calidad de Lyon. Es ligera, transpirable, absorbe la humedad fácilmente y se seca aún más rápido. Y lo más importante, no se estira y mantiene su forma.";
			link.l1 = "Sí, entiendo de qué seda estás hablando. Aunque podría ser más difícil conseguirla en las colonias.";
			link.l1.go = "Tailor_15";
		break;
		
		case "Tailor_15":
			dialog.text = "Eso es todo por los materiales. También he oído que te han entregado el más alto galardón de Francia... La Orden de San Luis no debe llevarse como un simple adorno en tu cinturón. Tiene su lugar. Así que, por favor, tráemela, y la coseré donde debe estar.";
			link.l1 = "Está bien, lo traeré también. ¡Solo no lo pierdas!";
			link.l1.go = "Tailor_16";
		break;
		
		case "Tailor_16":
			dialog.text = "¡Ciertamente no! ¡Lo protegeré con mi vida!";
			link.l1 = "Está bien entonces. Si eso es todo, iré a buscar los materiales.";
			link.l1.go = "Tailor_17";
		break;
		
		case "Tailor_17":
			dialog.text = "Hay una cosa más... Mis herramientas de sastrería se han vuelto inservibles. Pedí nuevas de París, pero ay... Si pudieras encontrar todos los materiales necesarios y prestarme las herramientas, si las tienes - solo préstamelas, ¡conseguiré nuevas más tarde!, ¡comenzaría a coser de inmediato!";
			link.l1 = "Bueno, ¿qué puedo hacer? Te traeré todo lo que necesites. ¿Dónde puedo encontrarte? No me estarás esperando en la autoridad portuaria, ¿verdad?";
			link.l1.go = "Tailor_18";
		break;
		
		case "Tailor_18":
			dialog.text = "Mi taller está ubicado en el edificio justo en el muelle; cuando desembarques, estará a tu derecha.";
			link.l1 = "Trato. Te conseguiré los materiales.";
			link.l1.go = "Tailor_19";
		break;
		
		case "Tailor_19":
			DialogExit();
			AddQuestRecord("Patria", "65_1");
			chrDisableReloadToLocation = false;
			ChangeCharacterAddressGroup(npchar, "Charles_houseS3", "barmen", "Stay");
			npchar.dialog.currentnode = "Tailor_20";
			LAi_SetOwnerType(npchar);
			pchar.questTemp.PatriaTailor = true;
		break;
		
		case "Tailor_20":
			dialog.text = "¡Saludos, vicealmirante! ¿Ha traído todo lo necesario para su nuevo uniforme?";
			link.l1 = "No todavía, no he tenido tiempo. Espera, conseguiré todo.";
			link.l1.go = "Tailor_20_exit";
			if(CheckCoatItems())
			{
				link.l2 = "Sí, traje todo. Aquí está mi vieja chaqueta, la Orden y las herramientas de sastrería. El resto de los materiales, mis marineros los llevarán a tu taller en breve.";
				link.l2.go = "Tailor_21";
			}
		break;
		
		case "Tailor_20_exit":
			npchar.dialog.currentnode = "Tailor_20";
			DialogExit();
		break;
		
		case "Tailor_21":
			RemoveItems(pchar, "talisman9", 1);
			RemoveItems(pchar, "suit1", 1);
			RemoveItems(pchar, "tailor_tool", 1);
			RemoveCharacterGoods(pchar, GOOD_CLOTHES, 1);
			RemoveCharacterGoods(pchar, GOOD_COTTON, 1);
			RemoveCharacterGoods(pchar, GOOD_LEATHER, 1);
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 1);
			dialog.text = "¡Maravilloso! Para ser honesto, no pensé que podrías obtener todo esto. Estoy acostumbrado a trabajar solo con telas de París, pero parece que puedes hacer trajes bastante decentes con materiales locales.";
			link.l1 = "¿Cuánto tiempo hasta que mi nuevo uniforme esté listo?";
			link.l1.go = "Tailor_22";
		break;
		
		case "Tailor_22":
			dialog.text = "Por lo general, no toma menos de una semana, pero considerando que los clientes son los dos oficiales de más alto rango de Francia en las colonias... Ven a verme en tres días, y te prometo que todo estará listo de la mejor manera posible. No necesitamos tomar medidas, haré todo basándome en tu vieja chaqueta.";
			link.l1 = "¡Genial! Entonces regresaré en tres días.";
			link.l1.go = "Tailor_23";
		break;
		
		case "Tailor_23":
			DialogExit();
			npchar.dialog.currentnode = "Tailor_24";
			SetFunctionTimerCondition("Patria_Tailor_Done", 0, 0, 3, false);
		break;
		
		case "Tailor_24":
			if(CheckAttribute(pchar,"questTemp.PatriaTailorDone"))
			{
				dialog.text = "¡Vicealmirante! ¡Es un placer verlo!";
				link.l1 = "Bueno, he venido por el nuevo uniforme, como acordamos.";
				link.l1.go = "Tailor_27";
			}
			else
			{
				dialog.text = "¡Saludos, vicealmirante! Me disculpo, pero su uniforme aún no está listo.";
				link.l1 = "Bueno, ¿puedo al menos echar un pequeño vistazo a lo que está pasando?";
				link.l1.go = "Tailor_25";
			}
		break;
		
		case "Tailor_25":
			dialog.text = "No, ¡no! Ahora mismo, luce completamente impresentable, y no quiero decepcionar tus expectativas. Por favor, ten paciencia.";
			link.l1 = "De acuerdo, esperaré.";
			link.l1.go = "Tailor_26";
		break;
		
		case "Tailor_26":
			DialogExit();
			npchar.dialog.currentnode = "Tailor_24";
		break;
		
		case "Tailor_27":
			dialog.text = "¡Sí, por supuesto! Debo decirte que resultó no peor que los hechos en París. Tenías razón, incluso en las colonias, puedes encontrar material adecuado si sabes dónde buscar. Un momento. ¡Aquí está! Por favor, inspecciona y pruébatelo.";
			link.l1 = "Gracias. ¡Excelente calidad! Y queda bien.";
			link.l1.go = "Tailor_28";
		break;
		
		case "Tailor_28":
			dialog.text = "¡No solo bien! ¡Puedes llevar esto con orgullo como vicealmirante de Francia en las colonias! Y tu Orden, como prometí, ahora está en su lugar adecuado, no colgando de tu cinturón.";
			link.l1 = "¡Buen trabajo! Cuando te encuentres con el Chevalier de Poincy, puedes decirle que estoy satisfecho.";
			link.l1.go = "Tailor_29";
		break;
		
		case "Tailor_29":
			dialog.text = "¡Definitivamente se lo diré! ¡Que el uniforme te sirva fielmente! ¡Buena suerte!";
			link.l1 = "¡Gracias! Adiós.";
			link.l1.go = "Tailor_30";
		break;
		
		case "Tailor_30":
			DialogExit();
			npchar.dialog.currentnode = "first time";
			npchar.lifeday = 0;
			DeleteAttribute(pchar,"questTemp.PatriaTailorDone");
			DeleteAttribute(pchar, "questTemp.PatriaTailor");
			//if(CheckAttribute (pchar, "IsMushketer")) SetMainCharacterToMushketer("", false);
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			GiveItem2Character(pchar, "suit5");
			EquipCharacterbyItem(pchar, "suit5");
			GiveItem2Character(pchar, "hat5");
			EquipCharacterbyItem(pchar, "hat5");
			AddItems(pchar, "tailor_tool", 1);
			Log_Info("¡Has recibido el uniforme de Vicealmirante!");
			AddQuestRecord("Patria", "65_2");
		break;
		
		//belamour legendary edition
		case "BladeUpg":
			string sItem, attrL, attrB;
			ref rItem;
			aref arItems; 
			int i, n, iItemsNum;
			dialog.text = "¿Qué hoja te gustaría mejorar?";
			
			i = 1;
			makearef(arItems, pchar.items);
			iItemsNum = GetAttributesNum(arItems);
			for(n=0; n<iItemsNum; n++)
			{
				sItem = GetAttributeName(GetAttributeN(arItems, n));
				rItem = ItemsFromID(sItem);
				if(!CheckAttribute(rItem, "groupID")) continue;
				if(rItem.groupID != BLADE_ITEM_TYPE) continue;
				if(rItem.price == 0) continue;
				if(IsEquipCharacterByItem(pchar, rItem.id)) continue;
				if(sItem != "" && rItem.groupID == BLADE_ITEM_TYPE) 
				{
					attrL = "l" + i;
					Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt") + ": Ataque, " + FloatToString(stf(rItem.attack),1) + ", equilibrio, " + FloatToString(stf(rItem.Balance),1) + ", peso, " + FloatToString(stf(rItem.Weight),1);
					Link.(attrL).go = "bladeindex_"+GetItemIndex(rItem.id);
					i++;
				}
			}
			
			link.l500 = "He cambiado de opinión";
			link.l500.go = "exit";
		break;
	}
} 

bool CheckCoatItems()
{
	if(GetSquadronGoods(pchar, GOOD_CLOTHES) > 0
	&& GetSquadronGoods(pchar, GOOD_COTTON) > 0
	&& GetSquadronGoods(pchar, GOOD_LEATHER) > 0
	&& GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0
	&& GetCharacterFreeItem(pchar, "talisman9") > 0
	&& GetCharacterFreeItem(pchar, "suit1") > 0
	&& GetCharacterFreeItem(pchar, "tailor_tool") > 0)
	return true;
	
	return false;
}
