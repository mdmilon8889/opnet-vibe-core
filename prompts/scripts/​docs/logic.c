// This is the core logic file for Opnet-vibe simulation.
/* * Project: Opnet-Vibe-Core
 * File: logic.c
 * Description: Core logic for network simulation and node processing.
 * Developed via: Vibecoding (AI-Assisted Scripting)
 */

#include <opnet.h>

/* Define state constants for the simulation */
#define INIT_STATE 0
#define IDLE_STATE 1
#define PROCESS_STATE 2

/* Process model entry point */
void opnet_vibe_core_logic(void)
{
    static int state = INIT_STATE;
    Packet* pktptr;
    double pk_size;

    FIN(opnet_vibe_core_logic());

    switch (state)
    {
        case INIT_STATE:
            /* Initializing simulation parameters */
            printf("Vibe-Core: Initializing Network Simulation...\n");
            state = IDLE_STATE;
            break;

        case IDLE_STATE:
            /* Waiting for packet arrival */
            if (op_intrpt_type() == OPC_INTRPT_STRM)
            {
                state = PROCESS_STATE;
            }
            break;

        case PROCESS_STATE:
            /* Processing arrived packets */
            pktptr = op_pk_get(op_intrpt_strm());
            if (pktptr != OPC_NIL)
            {
                pk_size = (double) op_pk_total_size_get(pktptr);
                printf("Vibe-Core: Packet Received. Size: %f bits\n", pk_size);
                
                /* Forwarding packet to next node */
                op_pk_send(pktptr, 0);
            }
            state = IDLE_STATE;
            break;

        default:
            op_prg_log_entry_write("Vibe-Core: Unknown State Encountered.");
            break;
    }

    FOUT;
}
