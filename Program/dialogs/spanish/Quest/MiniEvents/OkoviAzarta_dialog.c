void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	bool bOk1, bOk2;
	
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
			dialog.text = "¿Qué quiere?";
			link.l1 = "Nada.";
			link.l1.go = "exit";
		break;
		
		case "OZ_Kuznets_1":
			PlaySound("VOICE\Spanish\Master_05.wav");
			dialog.text = "¿Qué desea, "+GetAddress_Form(NPChar)+"? Perdón, pero no acepto nuevos encargos. Simplemente... tengo demasiado trabajo...";
			link.l1 = "¿Ah, sí? Dicen que recientemente perdió algo muy valioso en un juego de cartas, ¿es cierto?";
			link.l1.go = "OZ_Kuznets_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Kuznets_2":
			dialog.text = "Bueno, si vino a regodearse, póngase en la fila - sobran los que quieren hacerlo sin usted. Pero ninguno me ha ofrecido ayuda. Mi destino pende de un hilo y depende por completo de Javier Castillo, y la gente solo quiere burlarse de mi desgracia.";
			link.l1 = "No soy de los que se ríen de las desgracias ajenas. Cuénteme cómo fue todo. Tal vez pueda ayudarle.";
			link.l1.go = "OZ_Kuznets_3";
			link.l2 = "¿Ayuda? ¿Y por qué alguien debería dársela? Yo no lo haré. Usted es el herrero de su propia fortuna... y de su desgracia también. Así que deje de hacerse la víctima - simplemente acepte las consecuencias de sus actos, son más que lógicas.";
			link.l2.go = "OZ_Kuznets_NoAgree";
		break;
		
		case "OZ_Kuznets_NoAgree":
			DialogExit();
			AddDialogExitQuestFunction("OZ_Kuznets_NoAgree");
		break;
		
		case "OZ_Kuznets_3":
			dialog.text = "Esa noche no debería haber sido fatal. Solo entré en la taberna para tomar una jarra de ron después de que el propio almirante Eugenio de la Torre me hiciera un gran pedido. Pero, bastante bebido, me senté a jugar a las cartas. Fue entonces cuando Javier se ocupó de mí\nAl principio la suerte estaba de mi lado - incluso gané una suma considerable, pero en cuanto empecé a creer en mi suerte, la situación cambió drásticamente. Javier no paraba de llenar mi jarra con ron, y yo perdía una y otra vez: primero gasté todo el efectivo, luego el dinero reservado para materiales, y después todos mis ahorros\nCuando me di cuenta de cuánto ya había perdido, era demasiado tarde para retroceder. Estaba obsesionado con una sola idea: recuperar lo perdido a toda costa. Entonces aposté mi libro. Ese canalla de Javier lo valoró en solo cinco mil pesos\nPor supuesto, vale mucho más, pero estaba tan cegado por la emoción que acepté. Y luego... Creo que ya lo sabe. Perdí. Nunca me había pasado algo así. Creo que ese desgraciado me drogó con algo.";
			link.l1 = "¿Y de qué manera, si se puede saber, puedo ayudarle? Usted mismo se sentó a la mesa, usted mismo apostó sus bienes y usted mismo lo perdió todo. ¿Ahora simplemente no quiere aceptar las consecuencias? ¿Y qué tiene de especial ese libro por el que tanto se lamenta?";
			link.l1.go = "OZ_Kuznets_4";
		break;
		
		case "OZ_Kuznets_4":
			dialog.text = "Ese libro es lo más valioso que tenía. Contiene secretos transmitidos durante siglos de maestro a aprendiz. Es el corazón de mi forja, el alma de mi oficio. Ya he aceptado la pérdida, "+GetAddress_Form(NPChar)+", pero ¿cómo aceptar la pérdida del libro? Le ofrecí a Javier un rescate por él: cinco mil pesos\nEstaba dispuesto a endeudarme solo para recuperarlo. ¿Y sabe lo que me dijo? Que quería cien mil por él. ¡Cien, "+GetAddress_Form(NPChar)+"! No tengo ese dinero. Y no acepta ni bajar el precio ni recibirlo en partes. Le rogué... pero solo se rió de mí. Veo que usted es "+GetSexPhrase("una persona valiente, marinero... tal vez incluso capitán. Y no lleva el arma solo por adorno","una mujer poco común, capaz de encontrar la manera de tratar con cualquier hombre")+"\nSe lo ruego, hable con Javier. Tal vez lo escuche y acepte un aplazamiento del pago de la deuda. Sin ese libro... mi vida no tiene sentido. A cambio, siempre podré venderle materiales de calidad a buen precio cuando me recupere, y tal vez incluso fabricar algo especial para usted, capitán.";
			link.l1 = "Bueno, hablar no es difícil. Veremos qué sale de eso. Pero antes permítame presentarme: me llamo "+GetFullName(pchar)+", soy capitán de mi propio barco.";
			link.l1.go = "OZ_Kuznets_5";
		break;
		
		case "OZ_Kuznets_5":
			dialog.text = ""+GetSexPhrase("Y yo soy Sebastián Córdoba...","¿Una mujer capitán de su propio barco? He oído hablar de ellas, pero nunca había tenido ocasión de conocer y conversar con una en persona.")+" Encantado de conocerle, capitán "+pchar.lastname+". Y gracias. Hoy en día es más fácil encontrar a quienes se burlan de la desgracia ajena que a quienes están dispuestos a ayudar. Si mi libro vuelve a mí, le juro: nunca más jugaré a juegos de azar.";
			link.l1 = "Por ahora no tiene nada que agradecerme. Primero resolveré mis asuntos, y después, si me queda tiempo, hablaré con Javier.";
			link.l1.go = "OZ_Kuznets_6";
		break;
		
		case "OZ_Kuznets_6":
			dialog.text = "Me temo que puede llegar tarde. Javier resultó ser mucho más rápido de lo que pensaba\nYa encontró un comprador para el libro: es Étienne Renoir, un maestro armero francés. Si el almirante se entera de que por mi culpa un valor así terminó en manos de los franceses... perderé la cabeza. La prisión sería un castigo leve.";
			link.l1 = "Hmm... Bien. Me ocuparé de su problema de inmediato.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_repeat";
			AddDialogExitQuestFunction("OZ_Kuznets_Agree");
		break;
		
		case "OZ_Kuznets_repeat":
			dialog.text = "¡Capitán "+ pchar.lastname +"! ¿Habló con Javier? ¿Qué noticias hay?";
			link.l1 = "Aún no, pero justo me dirijo a la taberna.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_repeat";
			if (CheckCharacterItem(PChar, "OZ_book"))
			{
				link.l1 = "Hablé"+GetSexPhrase("","é")+". Y con bastante éxito. Javier partió apresuradamente al otro mundo, pero antes de eso devolvió su libro. Tome.";
				link.l1.go = "OZ_Kuznets_11";
				DelLandQuestMark(npchar);
			}
		break;
		
		case "OZ_Kuznets_11":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", ¡ni se imagina lo que esto significa para mí! Gracias a usted podré cumplir todos los encargos, ¡incluso el trabajo para el propio almirante! Dinero, lamentablemente, no tengo, pero aun así he preparado una recompensa para usted\nTome, esta coraza: la fabriqué para un don, pero estoy seguro de que él puede esperar un poco. Además tengo algunos materiales que le serán útiles si decide fabricar algo por su cuenta.";
			link.l1 = "Gracias, "+npchar.name+", ¡es usted muy generoso!";
			link.l1.go = "OZ_Kuznets_12";
			TakeItemFromCharacter(pchar, "OZ_book");
		break;
		
		case "OZ_Kuznets_12":
			dialog.text = "Y además, visíteme si necesita materiales. Recibo suministros una vez al mes, así que siempre habrá algo útil para usted - y a buen precio. Cumplo mis promesas.";
			link.l1 = "¡Sin duda pasaré! Bueno, "+npchar.name+", cuídese. Yo me marcho, tengo asuntos.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Kuznets_Nagrada");
			GiveItem2Character(PChar, "cirass3");
			AddItems(PChar, "jewelry13", 10);
			AddItems(PChar, "jewelry12", 5);
			AddItems(PChar, "jewelry10", 5);
			AddItems(PChar, "jewelry11", 2);
			AddQuestRecordInfo("Useful_Acquaintances", "7");
		break;
		
		case "OZ_Kuznets_Fail":
			dialog.text = "¡Capitán "+ pchar.lastname +"! ¿Habló con Javier? ¿Qué noticias hay?";
			link.l1 = "Verá... el libro estuvo en mis manos. Pero... las circunstancias hicieron que fuera vendido.";
			link.l1.go = "OZ_Kuznets_Fail_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Kuznets_Fail_2":
			dialog.text = "¿¡Qué!? ¿Usted... lo vendió? ¡¿Mi libro?!";
			link.l1 = "El libro que perdió en las cartas. Fue vendido al francés al que Javier se lo había prometido.";
			link.l1.go = "OZ_Kuznets_Fail_3";
		break;
		
		case "OZ_Kuznets_Fail_3":
			dialog.text = "Pero... ahora estoy perdido. El libro está en manos de los franceses, el encargo del almirante no se cumplirá... mi vida está destruida... ¡Estoy condenado!";
			link.l1 = "Usted mismo se metió en este callejón sin salida. Creo que le servirá de buena lección. Adiós.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Kuznets_Fail");
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
		break;
		
		case "OZ_Shuler_1":
			PlaySound("Voice\Spanish\tavern\Igroki v Tavernah-06.wav"); 
			dialog.text = "Ey, "+GetSexPhrase("marinero","preciosa")+", ¿quieres tentar a la suerte con unas cartas? Siéntate, las apuestas aquí no son tan altas... al menos para los novatos.";
			link.l1 = "Tengo la impresión de que eres justo a quien buscaba. ¿No fue así como atrajiste a Sebastián antes de dejarlo sin blanca? Estoy aquí para recuperar su libro.";
			link.l1.go = "OZ_Shuler_2";
			DelLandQuestMark(npchar);
		break;

		case "OZ_Shuler_2":
			dialog.text = "Muy bien. Dame cien mil, y el libro es tuyo. No me sirve de nada, ni siquiera puedo distinguir unas tenazas de un martillo.";
			link.l1 = "Te daré cinco mil - tú mismo pusiste ese precio cuando ganaste al herrero.";
			link.l1.go = "OZ_Shuler_3";
		break;

		case "OZ_Shuler_3":
			dialog.text = "¡Ja! ¿Me tomas por idiota? Sé perfectamente cuánto vale ese libro. Cien mil, ni una moneda menos. O se lo vendo a los franceses - ellos sí que tienen dinero de sobra.";
			link.l1 = "¿Crees que las autoridades mirarán hacia otro lado mientras vendes planos españoles a los franceses? El almirante se enfurecerá cuando lo sepa.";
			link.l1.go = "OZ_Shuler_4";
		break;

		case "OZ_Shuler_4":
			dialog.text = "Oh, vamos. A las autoridades no les importa un librito cualquiera, tienen preocupaciones más grandes. ¿El almirante? Claro, odia a los franceses con todo su ser, pero no voy a esperarlo - con tanto dinero seré bienvenido en cualquier colonia del Nuevo Mundo.";
			link.l1 = "Entonces hagamos un trato. Tendrás tu dinero, pero no de inmediato. El herrero te lo pagará en partes, y el libro vuelve hoy mismo a él, bajo palabra de honor de mi capitán. Para ti no cambia nada - igual cobrarás, y no pierdes ni un peso.";
			link.l1.go = "OZ_Shuler_5";
		break;

		case "OZ_Shuler_5":
			dialog.text = "Parece que no me entiendes. Lo dejé claro: necesito el dinero ahora mismo. No en una semana, ni en un mes, ni cuando el herrero lo junte - ahora mismo. Me largo de esta maldita isla cuanto antes. Así que, o me das toda la suma ahora, o el libro va a parar a los franceses, y tú empeñas tu honor ante el verdugo del almirante.";
			if (sti(pchar.Money) >= 100000 && GetSummonSkillFromName(pchar, SKILL_SNEAK) >= 30)
			{
				link.l1 = "Hagamos esto: juguemos. Mis cien mil contra el libro. Si ganas, te vas de la isla con una fortuna. Si pierdes, me quedo con el libro. ¿O solo juegas con los que ven cartas por primera vez?";
				link.l1.go = "OZ_Shuler_6";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "OZ_Shuler_6_No_Money";
				AddDialogExitQuestFunction("OZ_GameCards_Fail");
			}
		break;

		case "OZ_Shuler_6_No_Money":
			DialogExit();
			Notification_Money(false, 100000, "peso");
			LAi_CharacterDisableDialog(npchar);
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) >= 30)
			{
			Notification_Skill(true, 30, SKILL_SNEAK);
			}
			else
			{
			Notification_Skill(false, 30, SKILL_SNEAK);
			}
		break;

		case "OZ_Shuler_6":
			dialog.text = "¡Ja! No necesito hacerme rico - ¡ya lo soy! ¿Por qué arriesgar lo que puede traerme tanto dinero?";
			link.l1 = "Vaya, ¿el mismísimo Javier Castillo tiene miedo de jugar? Y yo que pensaba"+GetSexPhrase("","a")+" que eras un jugador curtido, no un simple estafador que se aprovecha de borrachos ingenuos.";
			link.l1.go = "OZ_Shuler_7";
			Notification_Money(true, 100000, "peso");
			Notification_Skill(true, 30, SKILL_SNEAK);
		break;
		
		case "OZ_Shuler_7":
			dialog.text = "No tengo miedo, simplemente no veo sentido en sentarme a la mesa cuando ya tengo todo lo que necesito.";
			link.l1 = "Vamos, veo cómo te tiembla la mano solo de pensar en jugar con alguien que no es la primera vez que sostiene cartas. Déjame adivinar, ¿tienes tanta prisa por irte porque te da vergüenza? ¿Todos ya se dieron cuenta de que no puedes vencer a un rival más fuerte que un borracho ingenuo?";
			link.l1.go = "OZ_Shuler_8";
		break;
		
		case "OZ_Shuler_8":
			dialog.text = "¡Cómo te atreves! He ganado a personas que ni se sentarían a la misma mesa contigo. Hemos tenido botes tan grandes que se podía comprar un barco para cada uno y para un capitán tan descarado como tú. Juguemos. Cinco mil por carta, cada uno con cien mil; quien se quede sin dinero, pierde. Vamos a ver quién gana.";
			link.l1 = "Menos palabras y más acción. Reparte.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_GameCards");
		break;
		
		case "OZ_Shuler_Win_1":
			dialog.text = "¡Maldita sea! Esto no puede ser...";
			link.l1 = "¿Qué pasa, no es tan divertido cuando gana otro?";
			link.l1.go = "OZ_Shuler_Win_2";
		break;
		
		case "OZ_Shuler_Win_2":
			dialog.text = "¡Eres un tramposo! ¿Crees que no vi nada? ¡Ni en sueños dejaré que me estafes! Prefiero hacerte pedazos.";
			link.l1 = "¿Tramposo? ¡Ja, ja! Parece que simplemente no sabes perder, amigo. Pero si tienes tanta prisa por ir al otro mundo, te ayudaré. ¡A las armas!";
			link.l1.go = "exit";
			pchar.questTemp.OZ_Draka = true;
			AddDialogExitQuestFunction("OZ_GameCards_Duel");
		break;
		
		case "OZ_Shuler_Lose_1":
			dialog.text = "¡Ja! Bueno, "+GetSexPhrase("amigo","guapa")+", ¿qué tal se siente estar desplumad"+GetSexPhrase("o","a")+"? Dicen que la audacia es una segunda felicidad, pero no en tu caso.";
			link.l1 = "No te ilusiones. Simplemente tuviste suerte.";
			link.l1.go = "OZ_Shuler_Lose_2";
		break;
		
		case "OZ_Shuler_Lose_2":
			dialog.text = "Los perdedores siempre dicen eso. Bueno, jugaste"+GetSexPhrase("","") + " – perdiste"+GetSexPhrase("","")+", no te ofendas. Si alguna vez encuentras otros cien mil, puedes probar suerte de nuevo... Aunque dudo que el resultado cambie...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_GameCards_Lose");
			AddLandQuestMark(characterFromId("PortSpein_Tavern"), "questmarkmain");
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Felip_1":
			dialog.text = "Buenos días, "+GetAddress_Form(NPChar)+". ¿A qué debo su visita?";
			link.l1 = "Saludos. Soy el capitán "+GetFullName(pchar)+", y quiero hablar con usted sobre Javier Castillo.";
			link.l1.go = "OZ_Felip_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Felip_2":
			dialog.text = "Hmm... Si ese bribón también le debe a usted, me temo que tendrá que ponerse a la cola. Javier nunca se ha apresurado a pagar sus deudas. Pero si llega a hacerse con dinero, primero me pagará a mí – ya me aseguré de que no le quede otra opción.";
			link.l1 = "Por suerte, no soy su acreedor. ¿Cuánto le debe exactamente? ¿Y qué medidas ha tomado?";
			link.l1.go = "OZ_Felip_3";
		break;
		
		case "OZ_Felip_3":
			dialog.text = "El monto total de su deuda es de ciento cincuenta mil pesos. Solo pagó diez mil, al parecer pensando que podía detenerse ahí. Pero rápidamente le dejé claro que estaba equivocado. Mis hombres le sacaron otros veinte mil. El resto debe devolverlo en el transcurso de una semana, y el plazo está por expirar. Por suerte, he oído que pronto recibirá una buena suma por la venta de algún libro.";
			link.l1 = "¿De verdad cree que piensa devolverle el dinero? No creo que deba contar seriamente con eso. Javier ni siquiera oculta que, en cuanto tenga el dinero, se escapará de aquí.";
			link.l1.go = "OZ_Felip_4";
		break;
		
		case "OZ_Felip_4":
			dialog.text = "Lo sé, capitán. Le aseguro que ya me he encargado de que no pueda huir sin pagarme.";
			link.l1 = "Veo que mantiene la situación bajo control. Sin embargo, la experiencia demuestra que la precaución nunca está de más. Verá, soy especialista"+GetSexPhrase("","a")+" en la recuperación de deudas. Si me permite actuar en su nombre, podré devolverle su dinero.";
			link.l1.go = "OZ_Felip_5";
		break;
		
		case "OZ_Felip_5":
			dialog.text = "Lamentablemente, capitán, la recuperación de esta deuda ya me está costando demasiado, y no puedo permitirme pagar también sus servicios...";
			link.l1 = ""+UpperFirst(GetAddress_Form(NPChar))+", no se preocupe por eso. En este asunto tengo mi propio interés, y por lo tanto le ayudaré gratuitamente.";
			link.l1.go = "OZ_Felip_6";
		break;
		
		case "OZ_Felip_6":
			dialog.text = "¿Puedo saber cuál es exactamente su interés?";
			link.l1 = "Digamos que algunas de sus jugarretas en la mesa de cartas no puedo dejarlas sin castigo.";
			link.l1.go = "OZ_Felip_7";
		break;
		
		case "OZ_Felip_7":
			dialog.text = "Bueno, si no me costará nada, no veo razones para negarme. Solo le pido una cosa, capitán: no vaya demasiado lejos. Si ese canalla se va al otro mundo antes de devolver la deuda, no me servirá de nada.";
			link.l1 = "No se preocupe, Felipe, actuaré con cuidado.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Felip_again";
			AddDialogExitQuestFunction("OZ_Felip_2");
			pchar.questTemp.OZ_Dolg = true;
		break;
		
		case "OZ_Felip_again":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+"! ¿No me diga que ya lo ha solucionado tan rápido?";
			link.l1 = "Por desgracia, todavía no. Pero estoy trabajando en ello.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Felip_again";
		break;
		
		case "OZ_Shuler_11":
			if (CheckAttribute(npchar, "quest.OZ_Shuler_Lose"))
			{
				dialog.text = "Ah, "+GetSexPhrase("capitán","guapa")+" presumido"+GetSexPhrase("","a")+"! ¿Otra vez tú? ¿Quieres perder un par de miles más?";
			}
			else
			{
				dialog.text = "¿Otra vez tú? Ya te lo dije claro: dinero sobre la mesa o lárgate.";
			}
			link.l1 = "Cambia el tono, Javier. Y saca la bolsa – no estoy aquí por casualidad. No habrás olvidado tu deuda con Felipe Alarcón, ¿verdad? Ahora represento sus intereses. Así que elige: o pagas la deuda ahora mismo, o tendré que buscar el dinero en tus bolsillos después de que te vayas al otro mundo.";
			link.l1.go = "OZ_Shuler_12";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Shuler_12":
			dialog.text = "¡Maldita sea! Tengo un trato, ¿no lo ves? Vuelve en un par de horas y entonces hablaremos.";
			link.l1 = "Parece que no me has oído. Dejé bien clar"+GetSexPhrase("o","a")+" que necesito el dinero ahora mismo. Ni en una semana, ni en un mes, ni cuando logres reunirlo, sino ahora. Ciento veinte mil pesos y ni una moneda menos. Aceptaré el libro como pago de cinco mil.";
			link.l1.go = "OZ_Shuler_13";
		break;
		
		case "OZ_Shuler_13":
			dialog.text = ""+GetSexPhrase("¡Sucio bastardo","¡Maldita sea")+"! Si crees que podrás deshacerte de mí fácilmente, es el mayor error de tu miserable vida.";
			link.l1 = "Ya veremos.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Shuler_Bitva");
		break;
		
		case "OZ_Frantsuz_1":
			//PlaySound("VOICE\Russian\tra_quest_1.wav");
			if (CheckAttribute(pchar, "questTemp.OZ_Draka"))
			{
				dialog.text = "Qué espectáculo... Debo admitir, "+GetAddress_Form(NPChar)+", que me ha complacido. Maneja usted la espada de forma excelente. Permítame presentarme: "+GetFullName(npchar)+". Y este desafortunado, si no me equivoco, es Javier Castillo?";
				link.l1 = "Exactamente, es él. Y yo soy el capitán "+GetFullName(pchar)+".";
				link.l1.go = "OZ_Frantsuz_1_1";
			}
			else
			{
				dialog.text = "Qué espectáculo... Debo admitir, "+GetAddress_Form(NPChar)+", que me ha complacido. Maneja usted la espada de forma excelente. Curioso cómo a veces se dan las circunstancias: el libro por el que he hecho tan largo viaje ha cambiado de dueño de la manera más inesperada. Pero espero no irme de aquí con las manos vacías.";
				link.l1 = "Hmm... ¿Y en cuánto valora usted ese libro?";
				link.l1.go = "OZ_Frantsuz_2";
			}
		break;
		
		case "OZ_Frantsuz_1_1":
			dialog.text = "Verá, capitán, he recorrido una gran distancia por un libro... Y, por lo que veo, ahora está en sus manos. Espero sinceramente que podamos llegar a un acuerdo – no quisiera abandonar este lugar con las manos vacías.";
			link.l1 = "Hmm... ¿Y en cuánto valora usted ese libro?";
			link.l1.go = "OZ_Frantsuz_2";
		break;
		
		case "OZ_Frantsuz_2":
			dialog.text = "Oh, "+GetAddress_Form(NPChar)+", conozco el valor de las cosas verdaderamente raras. Ochenta mil pesos. Una suma más que generosa y, créame, difícilmente recibirá una oferta así otra vez.";
			link.l1 = "Bueno, el libro es realmente valioso, y admito que pregunté"+GetSexPhrase("","") +" solo por curiosidad. No pienso comerciar con el destino de una persona. Lamentablemente, monsieur, no habrá trato: este libro debe volver a su dueño.";
			link.l1.go = "OZ_Frantsuz_3";
			link.l2 = "Una suma ridícula. Este libro reúne los secretos de los mejores maestros de la forja. Ciento cincuenta mil pesos – o acepta o vuelve a su dueño. No habrá regateo.";
			link.l2.go = "OZ_Frantsuz_4";
		break;
		
		case "OZ_Frantsuz_3":
			dialog.text = "Le ruego que no se apresure a rechazar. He recorrido un largo camino por él. Estoy dispuesto a ofrecerle cien mil, únicamente como muestra de respeto por la maestría con la que se encargó de ese hombre.";
			link.l1 = "Ya lo he dicho todo. Así que, discúlpeme, debo irme.";
			link.l1.go = "OZ_Frantsuz_4_1";
		break;
		
		case "OZ_Frantsuz_4_1":
			DialogExit();
			AddDialogExitQuestFunction("OZ_Frantsuz_1");
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, SPAIN, 10);
		break;
		
		case "OZ_Frantsuz_4":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", aprecio su confianza, pero ciento cincuenta mil no es un precio, es un absurdo. No convirtamos el trato en una farsa. Cien mil pesos es una suma razonable; acéptela, nadie dará más por este libro.";
			link.l1 = "Parece que no hemos llegado a un acuerdo. Bueno, no veo sentido en continuar esta conversación. Adiós, monsieur.";
			link.l1.go = "OZ_Frantsuz_5";
		break;
		
		case "OZ_Frantsuz_5":
			dialog.text = "¡Espere! Está bien, ha ganado. Ciento cincuenta mil. ¿Trato hecho?";
			link.l1 = "Me alegra que haya tomado la decisión correcta. El libro es suyo. Creo que con él se convertirá en el mejor maestro del Caribe.";
			link.l1.go = "OZ_Frantsuz_6";
			TakeItemFromCharacter(pchar, "OZ_book");
			AddMoneyToCharacter(pchar, 150000);
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
			ChangeCharacterNationReputation(pchar, SPAIN, -10);
			ChangeCharacterReputation(pchar, -5);
		break;
		
		case "OZ_Frantsuz_6":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", incluso sin este libro no tenía igual. Pero, lo admito, es agradable obtener un trofeo tan raro. Ahora, discúlpeme – estoy impaciente por comprobar si realmente vale las alabanzas que he escuchado.";
			link.l1 = "Bueno, entonces no lo entretengo más. Que le vaya bien.";
			link.l1.go = "OZ_Frantsuz_7";
		break;
		
		case "OZ_Frantsuz_7":
			DialogExit();
			AddDialogExitQuestFunction("OZ_Frantsuz_2");
		break;
		
		case "OZ_Bandit_1":
			if (pchar.sex == "man")
			{
				dialog.text = "Vaya, ¿y qué tenemos aquí? ¿Pensaste vaciar nuestro cofre y salir corriendo? Error, amigo. Ahora vamos a meterte a ti mismo en ese cofre y clavar la tapa bien fuerte.";
			}
			else
			{
				dialog.text = "Vaya, vaya... ¿Y quién tenemos aquí? ¿Te perdiste, muñeca? ¿Pensaste vaciar el cofre y escabullirte? Error, querida. Ahora vamos a registrarte bien – y veremos qué tienes en los bolsillos... y no solo ahí.";
			}
			link.l1 = "Demasiadas palabras para gusanos miserables como ustedes. Saquen sus hierros y veamos de qué son capaces de verdad.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Grot_4");
		break;
		
		case "OZ_Felip_11":
			dialog.text = "¡Capitán! Ya me han informado de que Javier partió al otro mundo por su culpa. ¡Y le pedí que no lo matara antes de tiempo! Espero que esté aquí para devolverme mi dinero.";
			if (sti(pchar.Money) >= 100000)
			{
				link.l1 = "Exactamente. Logré encontrar su escondite, en el que había cien mil pesos. Es todo el dinero que tenía.";
				link.l1.go = "OZ_Felip_12";
			}
			link.l2 = "Sí, tuve que matarlo. Pero él mismo me atacó, y tuve que defenderme. En sus bolsillos no había nada – ni una moneda. Lamentablemente, no pude recuperar la deuda.";
			link.l2.go = "OZ_Felip_14";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.OZ_Dolg");
		break;
		
		case "OZ_Felip_12":
			dialog.text = "Cien mil... Claro, no es toda la suma, pero conociendo a Javier, dudo que alguien pudiera sacarle más. Bueno, gracias, capitán. Parece que contraté a la gente equivocada. Usted sí que es un verdadero maestro en lo suyo.";
			link.l1 = "No fue difícil. En este punto, debo despedirme"+GetSexPhrase("","")+". Los asuntos me esperan.";
			link.l1.go = "OZ_Felip_13";
			AddMoneyToCharacter(pchar, -100000);
		break;
		
		case "OZ_Felip_13":
			dialog.text = "Adiós, capitán.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Felip_good");
		break;
		
		case "OZ_Felip_14":
			dialog.text = "¡Maldit"+GetSexPhrase("o","a")+"! ¿Me mientes mirándome directamente a los ojos? ¡Esto no te saldrá gratis!";
			link.l1 = "Argh...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Felip_bad");
		break;
		
		case "OZ_Kuznets_Tovar":
			PlaySound("VOICE\Spanish\Master_02.wav");
			dialog.text = "¡Hola, "+pchar.name+"! ¿Desea adquirir materiales o productos?";
			link.l1 = ""+TimeGreeting()+". Veamos qué tiene usted.";
			link.l1.go = "OZ_Kuznets_Tovar_2";
			link.l2 = "Y hola también a usted, "+npchar.name+"! Gracias por la oferta, pero solo quería saludar"+GetSexPhrase("","")+".";
			link.l2.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_Tovar_repeat";
			SetFunctionTimerCondition("OZ_Kuznets_Reset", 0, 0, 1, false);
			if (!CheckAttribute(npchar, "quest.OZ_Kuznets_tovar")) 
			{
				SetFunctionTimerCondition("OZ_Kuznets_Reset_2", 0, 0, 30, false);
				npchar.quest.OZ_Kuznets_tovar = true;
			}
		break;
		
		case "OZ_Kuznets_Tovar_repeat":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", ¿ha decidido finalmente comprar algo?";
			link.l1 = "Exactamente. Muéstreme qué tiene hoy.";
			link.l1.go = "OZ_Kuznets_Tovar_2";
			link.l2 = "Lamentablemente, ya me voy.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_Tovar_repeat";
		break;
		
		case "OZ_Kuznets_Tovar_2":
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
			NextDiag.CurrentNode = "OZ_Kuznets_Tovar_repeat";
		break;
		
	}
}