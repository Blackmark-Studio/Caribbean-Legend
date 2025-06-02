void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
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
			dialog.text = "¿Qué quiere?";
			link.l1 = "Nada.";
			link.l1.go = "exit";
		break;

		case "Poorman_1":
			if (pchar.sex == "woman")
			{
				dialog.text = "Ey, preciosa, ¿qué te parece una joya exquisita para tu colección de damas? ¡Una verdadera joya! Para ti, miradas admiradas, y para mí, unas monedas para pan y un sorbo de ron.";
			}
			else
			{
				dialog.text = "Ey, capitán, ¿qué te parece un regalo exquisito para tu dama? ¡Una verdadera joya! Para ti, su cálido agradecimiento, y para mí, unas monedas para pan y un sorbo de ron.";
			}
			link.l1 = "¿Para que en una hora los soldados vengan a por mí y me encierren por robo? ¿De dónde lo sacaste, vagabundo?";
			link.l1.go = "Poorman_2_fortune";
			link.l2 = "¿Un regalo exquisito? ¿Y de dónde lo sacaría un vagabundo como tú?";
			link.l2.go = "Poorman_2_leadership";
			if (npchar.quest.meeting == "0") npchar.quest.meeting = "1";
		break;

		case "Poorman_2_fortune":
			dialog.text = ""+GetSexPhrase("Capitán, yo","Yo")+" encontré este hermoso colgante con camafeo, ¡lo juro! ¡Que me parta un rayo si miento! Estaba ahí, sin dueño. ¿Y quién dejaría algo tan bello tirado en el barro, verdad?";
			link.l1 = "Está bien. ¿Qué tienes ahí?";
			link.l1.go = "Poorman_3";
			link.l2 = "¿Quién creería a un caballero tan respetable como tú? Busca a alguien más crédulo.";
			link.l2.go = "Poorman_exit";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "Poorman_2_leadership":
			dialog.text = ""+GetSexPhrase("Capitán, yo","Yo")+" encontré este hermoso colgante con camafeo, ¡lo juro! ¡Que me parta un rayo si miento! Estaba ahí, sin dueño. ¿Y quién dejaría algo tan bello tirado en el barro, verdad?";
			link.l1 = "Está bien. ¿Qué tienes ahí?";
			link.l1.go = "Poorman_3";
			link.l2 = "¿Quién creería a un caballero tan respetable como tú? Busca a alguien más crédulo.";
			link.l2.go = "Poorman_exit";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Poorman_exit":
			DialogExit();
			AddDialogExitQuestFunction("TBP_PismoVDome");
		break;
		
		case "Poorman_3":
			dialog.text = "Miren... ¡es una cosa valiosa! La encontré en un parterre de flores, junto a la casa con el farol, cerca de la taberna. Pero hace mucho que no hay nadie por allí, así que no hay a quién devolvérsela.";
			link.l1 = "Interesante pieza. ¿Cuánto quieres por ella?";
			link.l1.go = "Poorman_4";
		break;

		case "Poorman_4":
			dialog.text = "Solo cien pesos"+GetSexPhrase(", capitán","")+"... una miseria para alguien como usted. ¡Y para mí, una semana sin preocuparme de dónde sacar un pedazo de pan! ¡Solo mire qué belleza!";
			if (sti(pchar.Money) >= 100)
			{
				link.l1 = "Está bien, toma tus cien pesos.";
				link.l1.go = "Poorman_5";
			}
			link.l2 = "Creo que pasaré. Busca suerte con alguien más.";
			link.l2.go = "Poorman_exit";
		break;

		case "Poorman_5":
			dialog.text = "¡Gracias, "+GetAddress_Form(NPChar)+"! ¡Ahora la suerte seguro le sonreirá! Se nota que es una buena persona.";
			link.l1 = "...";
			link.l1.go = "Poorman_exit";
			GiveItem2Character(PChar, "jewelry24");
			pchar.questTemp.TBP_BuyKulon = true;
			pchar.questTemp.TBP_BuyKulonOtdatBetsy = true;
		break;

		case "Pirate_1":
			if (pchar.sex == "woman")
			{
				dialog.text = "O-o-oh, ¿y quién se nos aparece? Parece que no te equivocaste de puerta, muñeca... pasa, pasa. Desvístete y ponte cómoda.";
				link.l1 = "Vaya, vaya... ¿Quién tenemos aquí? ¿No serán los mismos desgraciados que dejaron aquel 'cariñoso' mensaje amenazante para Betsy?";
			}
			else
			{
				dialog.text = "¿Y esto qué demonios es? ¿No te habrás equivocado de puerta, cabeza de chivo? ¡Lárgate antes de que te raje la barriga!";
				link.l1 = "Vaya, vaya... ¿Quién tenemos aquí? ¿No serán los mismos idiotas que dejaron un lindo mensaje con amenazas para Betsy?";
			}
			link.l1.go = "Pirate_2";
			PlaySound("Voice/Spanish/citizen/Pirati v Gorode-12.wav");
		break;

		case "Pirate_2":
			if (pchar.sex == "woman")
			{
				dialog.text = "¿Betsy? ¡Al diablo con esa Betsy! Mucho más interesante es saber qué haces tú aquí, dulzura... Ya que entraste, no tengas prisa por irte, ya se nos ocurrirá cómo entretenerte...";
			}
			else
			{
				dialog.text = "¿Qué Betsy ni qué demonios? No tientes a la suerte, imbécil. Mientras aún puedas irte caminando, hazlo. O tendremos que recoger tus pedazos con una cubeta.";
			}
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_2");
		break;
		
		case "BetsiPrice_1":
			dialog.text = "¡Ayuda! ¡Ayuda, se lo ruego!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_3");
			locCameraFromToPos(1.40, 1.62, 1.14, false, 2.58, -0.30, -1.64);
		break;

		case "Pirate_3":
			dialog.text = "...";
			link.l1 = "Ahí está. Estás metido hasta el cuello, amigo, y si no quieres que esto sea tu último error, te aconsejo que la sueltes. Ahora mismo.";
			link.l1.go = "Pirate_4";
		break;

		case "Pirate_4":
			dialog.text = "¡Ja! ¿Lo oíste, Reggie? "+GetSexPhrase("Él","Ella")+" también amenaza. "+GetSexPhrase("Qué baboso tan confiado","Qué bruja tan confiada")+". Vamos a mostrarle "+GetSexPhrase("a este engreído de qué color son sus tripas","a esta presumida lo que es el verdadero dolor")+".";
			link.l1 = "Peor para ustedes.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_4");
		break;

		case "Pirate_5":
			if (!CharacterIsAlive("TBP_Bandit_1"))
			{
				dialog.text = "...";
				link.l1 = "Y ahora suelta a la chica. O acabarás al lado de tu amiguito.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("TBP_HouseBetsi_6");
			}
			else
			{
				dialog.text = "...";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Pirate_5";
			}
		break;

		case "BetsiPrice_2":
			dialog.text = "¡Malditos perros! ¿Pensaban que me iba a quedar callada?";
			link.l1 = "...";
			link.l1.go = "BetsiPrice_2_1";
			sld = CharacterFromID("TBP_Bandit_2");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("TBP_BetsiPrice"));
			CharacterTurnByChr(npchar, sld);
		break;
		
		case "BetsiPrice_2_1":
			dialog.text = "¿Y tú...? Parece que no estás con ellos. ¿Quién eres?";
			link.l1 = "Capitán "+GetFullName(pchar)+", a tu servicio.";
			link.l1.go = "BetsiPrice_2_2";
			CharacterTurnByChr(npchar, pchar);
		break;

		case "BetsiPrice_2_2":
			dialog.text = "¿Entonces te debo la vida?";
			link.l1 = "Parece que sí. Pero ahora hay algo más importante: ¿quiénes son esos hombres y en qué lío te has metido?";
			link.l1.go = "BetsiPrice_3";
		break;

		case "BetsiPrice_3":
			dialog.text = "Esos hombres... Fueron enviados por un importante funcionario inglés. Alguna vez fue muy cercano a mí... y ahora, como ves, quiere verme muerta.";
			link.l1 = "Empiezo a entender tu historia. Fuiste su amante, pero en algún momento pensaste que podías usar eso a tu favor. ¿Querías asustarlo... contarle a su familia?";
			link.l1.go = "BetsiPrice_4";
		break;

		case "BetsiPrice_4":
			dialog.text = "Estás sorprendentemente cerca de la verdad, "+GetSexPhrase("guapo","linda")+"... y al mismo tiempo muy lejos. Si así hubiera sido, ya estaría muerta. Sí, fui su amante, pero nunca se me ocurrió montar un drama familiar\nTodo era mucho más complicado: un día descubrí que había encontrado un nuevo juguete y decidió deshacerse de mí, dejándome sin nada. Solo me quería tirar como si fuera basura. Pero no estoy acostumbrada a irme con las manos vacías\nAsí que tomé lo que realmente tenía valor: documentos capaces de arruinar su vida, y huí al Nuevo Mundo. Luego le propuse un trato: sus secretos a cambio de mi seguridad y una compensación generosa\nPor eso sigo viva: necesitan los documentos. Y yo no tenía prisa por decir dónde los escondí.";
			link.l1 = "Bueno, no solo eres hermosa, también diabólicamente astuta. Jugaste con valentía, pero seamos honestos: este juego ya se te ha ido de las manos. Tal vez sea hora de considerar otra opción, mientras aún puedes salir con vida. Si te encontraron aquí, dudo que puedas esconderte en otro lugar. Tarde o temprano, tu suerte se acabará.";
			link.l1.go = "BetsiPrice_5";
		break;

		case "BetsiPrice_5":
			dialog.text = "¿Y qué propones? ¿Entregarle los documentos y quedarme sin nada? ¿Después de todo lo que he pasado?";
			link.l1 = "Sabes que para ellos no eres más que un problema que deben eliminar. No se detendrán hasta conseguir lo que quieren. Pero aún tienes una elección. Entrega los documentos a ese imbécil. Que se los lleve a su jefe y le diga que has renunciado a tus intenciones y solo quieres que todo esto termine.";
			link.l1.go = "BetsiPrice_6";
		break;

		case "BetsiPrice_6":
			dialog.text = "Si es mi única oportunidad... Está bien, estoy dispuesta a arriesgarme. Siempre tuve los documentos conmigo. Los cosí dentro de mi corsé para no separarme de ellos ni un segundo. Espera un momento...";
			link.l1 = "...";
			link.l1.go = "BetsiPrice_7";
		break;

		case "BetsiPrice_7":
			dialog.text = "Aquí, toma. Estos son todos los documentos que tenía. ¿Le dirás unas palabras a ese bastardo? Tú sabes cómo ser persuasiv"+GetSexPhrase("o","a")+", ¿verdad?";
			link.l1 = "Creo que ya aprendió la lección principal. Ahora solo queda dejarle claro qué debe hacer.";
			link.l1.go = "exit";
			notification(StringFromKey("Neutral_15"), "BoxMinus");
			PlaySound("interface\important_item.wav");
			AddDialogExitQuestFunction("TBP_HouseBetsi_11");
		break;
		
		case "Pirate_6":
			dialog.text = "...";
			link.l1 = "Escúchame bien, bastardo. Aquí están los documentos que vinieron a buscar. Llévaselos a tu amo y dile: si sigue enviando asesinos tras la cabeza de Betsy, acabarán igual que tus amiguitos. Dile que ella se va de su vida para siempre, y que ya no tiene razones para perseguirla. Que lo vea como su gesto voluntario de reconciliación. Espero que sea lo bastante sensato como para terminar esto aquí. ¿Lo entendiste todo, o tengo que grabártelo en la cabeza?";
			link.l1.go = "Pirate_7";
			notification(StringFromKey("Neutral_16"), "BoxMinus");
			PlaySound("interface\important_item.wav");
		break;

		case "Pirate_7":
			dialog.text = "Lo entendí todo, "+GetAddress_Form(NPChar)+"...";
			link.l1 = "Entonces lárgate de aquí. Y ni se te ocurra quedarte — no tendrás una segunda oportunidad.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_12");
		break;

		case "BetsiPrice_8":
			dialog.text = "Bueno, "+GetSexPhrase("mi héroe","mi furia")+", parece que olvidé darte las gracias... Es por la emoción. No todos los días uno es prisionero y luego recupera la libertad gracias a "+GetSexPhrase("un valiente salvador","una valiente salvadora")+". Dime, ¿es costumbre tuya rescatar damiselas en apuros, o simplemente tuve una suerte increíble?";
			link.l1 = "Qué te puedo decir, Betsy, tengo debilidad por las apariciones dramáticas y "+GetSexPhrase("las damas hermosas","toda clase de aventuras")+".";
			link.l1.go = "BetsiPrice_9";
		break;

		case "BetsiPrice_9":
			dialog.text = "Mi nombre es Miranda. Miranda Bell. Tomé el nombre de Betsy cuando tuve que desaparecer — nueva vida, nuevo nombre, ya sabes. Huí de Europa tan deprisa que solo llevé unas pocas monedas y un par de joyas\nEl resto seguramente lo tomaron esos malditos que me perseguían. Ahora, en vez de banquetes de lujo y vestidos caros, una choza en las afueras y trabajo en una taberna. Nunca imaginé que un día estaría sirviendo ron en vez de saborear vino en buena compañía...";
			link.l1 = "Aun con todo eso, pareces tener tu destino en tus propias manos. Tal vez ese sea tu verdadero talento.";
			link.l1.go = "BetsiPrice_10";
		break;

		case "BetsiPrice_10":
			dialog.text = ""+GetSexPhrase("Adulador. Pero te queda bien","Me estás halagando")+"... Después de todo esto, no me siento muy segura. ¿Y si alguien ya me está esperando a la vuelta de la esquina? Acompáñame a casa, sé "+GetSexPhrase("mi salvador","mi salvadora")+" un poco más.";
			link.l1 = "No soy de los que dejan las cosas a medio camino. Así que, señora, estoy a su servicio. Vamos.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma");
		break;

		case "BetsiPrice_11":
			dialog.text = "Ya hemos llegado. ¿Sabes? Ni siquiera te pregunté qué te llevó a esa casa.";
			link.l1 = "No llegué allí por accidente. El tabernero parecía realmente preocupado por tu desaparición y me pidió que averiguara qué pasó. ¿Y cómo iba yo a negarme? Abandonar a una dama en apuros no es propio de un capitán.";
			link.l1.go = "BetsiPrice_12";
			if (CheckAttribute(pchar, "questTemp.TBP_BuyKulonOtdatBetsy") && pchar.questTemp.TBP_BuyKulonOtdatBetsy == true)
            {
			link.l2 = "No llegué allí por accidente. Este colgante me llevó allí. Tómalo.​ El tabernero parecía realmente preocupado por tu desaparición y me pidió que averiguara qué pasó. ¿Y cómo iba yo a negarme? Abandonar a una dama en apuros no es propio de un capitán.";
			link.l2.go = "BetsiPrice_12_otdal_kulon";
			}
		break;

		case "BetsiPrice_12":
			dialog.text = "Oh, ¡eso es tan noble de tu parte, capitán "+pchar.name+"! En cuanto al tabernero, estoy segura de que se preocupaba más por sus ingresos que por mí. Por desgracia, no puedo invitarte hoy — necesito recuperarme. El tiempo en el sótano no me hizo más hermosa, me temo. Pero si no volvemos a vernos, no te lo perdonaré. Así que ven mañana a la taberna, tendré... un regalo para ti.";
			link.l1 = "Bueno, ahora tengo una razón más para pasar por allí. Hasta pronto, M... Betsy.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_3");
		break;
		
		case "BetsiPrice_12_otdal_kulon":
			dialog.text = "Oh, ¡eso es tan noble de tu parte, capitán "+pchar.name+"! En cuanto al tabernero, estoy segura de que se preocupaba más por sus ingresos que por mí. Por desgracia, no puedo invitarte hoy — necesito recuperarme. El tiempo en el sótano no me hizo más hermosa, me temo. Pero si no volvemos a vernos, no te lo perdonaré. Así que ven mañana a la taberna, tendré... un regalo para ti.";
			link.l1 = "Bueno, ahora tengo una razón más para pasar por allí. Hasta pronto, M... Betsy.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_3");
			TakeItemFromCharacter(pchar, "jewelry24");
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
		break;

		case "TBP_Helena_1":
			dialog.text = "Vaya, vaya... Qué dulce despedida. ¿Quién es esa dama desaliñada? Parece que ha pasado una semana en el sótano, pero ni eso te impidió devorarla con la mirada, ¿verdad, "+pchar.name+"?";
			link.l1 = "No es lo que crees. La chica estaba en una situación complicada, y la ayudé a salir. Eso es todo.";
			link.l1.go = "TBP_Helena_2";
		break;
		
		case "TBP_Helena_2":
			dialog.text = "¿Y tú, por supuesto, decidiste convertirte en su caballero de brillante armadura?";
			link.l1 = "Sabes que no puedo quedarme de brazos cruzados cuando alguien está en peligro.";
			link.l1.go = "TBP_Helena_3";
		break;

		case "TBP_Helena_3":
			dialog.text = "Está bien. Pero la próxima vez, "+pchar.name+", ten más cuidado... y no me des motivos para estar celosa.";
			link.l1 = "Por supuesto, querida. Vámonos de aquí, aún tenemos mucho que hacer.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_5");
		break;

		case "TBP_Mary_1":
			dialog.text = "Vaya, vaya... Qué dulce despedida. Tanto cuidado, tantas promesas tiernas... Incluso la llamas por su nombre con cariño, sí, ¿eh? Tal vez yo también deba desaparecer un par de días para que me busques con el mismo fervor.";
			link.l1 = "Mary, sabes bien que tú eres mi brújula, y ella... solo una chica en apuros.";
			link.l1.go = "TBP_Mary_2";
		break;

		case "TBP_Mary_2":
			dialog.text = "¡Ah, claro! Solo una pobre chica que necesita un caballero. ¿Y esa mirada tuya? ¿También fue por cortesía? ¡Casi la desnudaste con los ojos!";
			link.l1 = "Mary, exageras. ¿Y cómo te miro a ti? ¿Ves la diferencia? ¿O necesito recordártelo... de cerca?";
			link.l1.go = "TBP_Mary_3";
		break;

		case "TBP_Mary_3":
			dialog.text = "Está bien, "+pchar.name+", esta vez te salvaste, sí, ¿eh? Pero si vuelvo a ver algo así...";
			link.l1 = "Entonces tendré que recordarte otra vez quién ocupa el primer y único lugar en mi corazón. Vamos, querida, aún tenemos mucho que hacer.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_5");
		break;

		case "BetsiPrice_sex_1":

			switch (rand(1))
			{
				case 0:
					dialog.text = "Mmm... No te imaginas los pensamientos que me pasan por la cabeza cuando estoy tan cerca de ti... Y cuánto deseo hacerlos realidad.";
					link.l1 = "Entonces deja de solo pensarlo... y muéstrame cada uno de ellos.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;

				case 1:
					dialog.text = "Ah, mi"+GetSexPhrase(" querido"," querida")+"... No sabes lo difícil que me resulta controlarme cuando estás cerca...";
					link.l1 = "Entonces basta de esta dulce tortura... Ven a mí...";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;
			}
			AddDialogExitQuestFunction("TBP_Betsi_sex_3");
		break;

		case "BetsiPrice_sex_2":
			switch (rand(1))
			{
				case 0:
					dialog.text = "Ah, "+GetSexPhrase("mi dulce capitán","mi dulce "+pchar.name)+"... Aún estoy envuelta en esta dulce locura.";
					link.l1 = "Quizás esta locura merece ser recordada... o incluso repetida algún día.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;

				case 1:
					dialog.text = "Oh, "+pchar.name+"... Si digo que fue increíble, ¿no te pondrás demasiado orgullos"+GetSexPhrase("o","a")+"?";
					link.l1 = "Solo si prometes decirlo de nuevo... en un susurro.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;
			}
			AddDialogExitQuestFunction("TBP_Betsi_sex_7");
		break;

		
		
		
		
		
		
		
	}
}